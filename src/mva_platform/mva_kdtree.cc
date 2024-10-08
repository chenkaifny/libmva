#include "mva_kdtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SQ(x) (x) * (x)

void clear_rec(mva_kdnode *node, void (*destr)(void *));
int insert_rec(mva_kdnode **node, const double *pos, void *data, int dir, int dom);
int rlist_insert(mva_resnode *list, mva_kdnode *item, double dist_sq);
void clear_results(mva_kdres *set);
mva_kdhyperrect *hyperrect_create(int dim, const double *min, const double *max);
void hyperrect_free(mva_kdhyperrect *rect);
mva_kdhyperrect *hyperrect_duplicate(const mva_kdhyperrect *rect);
void hyperrect_extend(mva_kdhyperrect *rect, const double *pos);
double hyperrect_dist_sq(mva_kdhyperrect *rect, const double *pos);
void kd_nearest_i(mva_kdnode *node, const double *pos, mva_kdnode **result, double *result_dist_sq, mva_kdhyperrect *rect);
int find_nearest(mva_kdnode *node, const double *pos, double range, mva_resnode *list, int ordered, int dim);

#ifdef USE_LIST_NODE_ALLOCATOR
mva_resnode *alloc_resnode(void);
void free_resnode(mva_resnode *);
#else
#define alloc_resnode() malloc(sizeof(mva_resnode))
#define free_resnode(n) free(n)
#endif

mva_kdtree *mva_kd_create(int k)
{
    mva_kdtree *tree = NULL;

    tree = (mva_kdtree *)malloc(sizeof(mva_kdtree));
    if (!tree)
    {
        return NULL;
    }

    tree->dim = k;
    tree->root = NULL;
    tree->destr = NULL;
    tree->rect = NULL;
    return tree;
}

void mva_kd_free(mva_kdtree *tree)
{
    if (tree)
    {
        mva_kd_clear(tree);
        free(tree);
        tree = NULL;
    }
}

void mva_kd_clear(mva_kdtree *tree)
{
    if (!tree)
    {
        return;
    }
    // clear hyperrect
    clear_rec(tree->root, tree->destr);
    tree->root = NULL;

    // free pointer
    if (tree->rect)
    {
        hyperrect_free(tree->rect);
        tree->rect = NULL;
    }
}

void mva_kd_destructor(mva_kdtree *tree, void (*destr)(void *))
{
    if (!tree)
    {
        return;
    }
    // set destructor function
    tree->destr = destr;
}

int mva_kd_insert(mva_kdtree *tree, const double *pos, void *data)
{
    if (!tree || !pos || !data)
    {
        return -1;
    }
    // insert hyperrect
    if (insert_rec(&tree->root, pos, data, 0, tree->dim))
    {
        return -1;
    }
    // if has no hyperrect, then create it
    // if has hyperrect already, extend
    if (!tree->rect)
    {
        tree->rect = hyperrect_create(tree->dim, pos, pos);
    }
    else
    {
        hyperrect_extend(tree->rect, pos);
    }
    return 0;
}

int mva_kd_insertf(mva_kdtree *tree, const float *pos, void *data)
{
    if (!tree || !pos || !data)
    {
        return -1;
    }

    double sbuf[16];
    double *bptr, *buf = 0;
    int res, dim = tree->dim;

    // if kdtree dim more than 16, alloc arrary
    if (dim > 16)
    {
#ifndef NO_ALLOCA
        if (dim <= 256)
        {
            bptr = buf = (double *)alloca(dim * sizeof(double));
        }
        else
#endif
            if (!(bptr = buf = (double *)malloc(dim * sizeof(double))))
        {
            return -1;
        }
    }
    else
    {
        // if kdtree dim less than 16,  use pointer
        bptr = buf = sbuf;
    }

    // move pos to alloc array
    while (dim-- > 0)
    {
        *bptr++ = *pos++;
    }

    // use kd_insert
    res = mva_kd_insert(tree, buf, data);
#ifndef NO_ALLOCA
    if (tree->dim > 256)
#else
    if (tree->dim > 16
#endif
    {
        free(buf);
    }

    return res;
}

int mva_kd_insert3(mva_kdtree *tree, double x, double y, double z, void *data)
{
    double buf[3];
    buf[0] = x;
    buf[1] = y;
    buf[2] = z;
    return mva_kd_insert(tree, buf, data);
}

int mva_kd_insert3f(mva_kdtree *tree, float x, float y, float z, void *data)
{
    double buf[3];
    buf[0] = x;
    buf[1] = y;
    buf[2] = z;
    return mva_kd_insert(tree, buf, data);
}

mva_kdres *mva_kd_nearest(mva_kdtree *tree, const double *pos)
{
    if (!tree || !tree->rect)
    {
        return NULL;
    }
    mva_kdhyperrect *rect;
    mva_kdnode *result;
    mva_kdres *rset;
    double dist_sq;
    double dist_tmp;
    int i;

    rset = (mva_kdres *)malloc(sizeof(mva_kdres));
    if (!rset)
    {
        return NULL;
    }
    rset->rlist = (mva_resnode *)alloc_resnode();
    if (!rset->rlist)
    {
        free(rset);
        return NULL;
    }
    rset->rlist->next = NULL;
    rset->tree = NULL;

    // copy hyperrect
    rect = hyperrect_duplicate(tree->rect);
    if (!rect)
    {
        mva_kd_res_free(rset);
        return NULL;
    }

    // our first guesstimate is the root node
    result = tree->root;
    dist_sq = 0;
    for (i = 0; i < tree->dim; i++)
    {
        dist_tmp = result->pos[i] - pos[i];
        dist_sq += SQ(dist_tmp);
    }

    // search for the nearest neighbour recursively
    kd_nearest_i(tree->root, pos, &result, &dist_sq, rect);

    // free hyperrect
    hyperrect_free(rect);

    // storage the result
    if (result)
    {
        if (rlist_insert(rset->rlist, result, -1.0) == -1)
        {
            mva_kd_res_free(rset);
            return NULL;
        }
        rset->size = 1;
        mva_kd_res_rewind(rset);
        return rset;
    }
    else
    {
        mva_kd_res_free(rset);
        return NULL;
    }
}

mva_kdres *mva_kd_nearestf(mva_kdtree *tree, const float *pos)
{
    double sbuf[16];
    double *bptr, *buf = NULL;
    int dim = tree->dim;
    mva_kdres *res;

    if (dim > 16)
    {
#ifndef NO_ALLOCA
        if (dim <= 256)
        {
            bptr = buf = (double *)alloca(dim * sizeof(double));
        }
        else
#endif
            if (!(bptr = buf = (double *)malloc(dim * sizeof(double))))
        {
            return NULL;
        }
    }
    else
    {
        bptr = buf = sbuf;
    }

    while (dim-- > 0)
    {
        *bptr++ = *pos++;
    }

    res = mva_kd_nearest(tree, buf);
#ifndef NO_ALLOCA
    if (tree->dim > 256)
#else
    if (tree->dim > 16)
#endif
    {
        free(buf);
    }
    return res;
}

mva_kdres *mva_kd_nearest3(mva_kdtree *tree, double x, double y, double z)
{
    double pos[3];
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    return mva_kd_nearest(tree, pos);
}

mva_kdres *mva_kd_nearest3f(mva_kdtree *tree, float x, float y, float z)
{
    double pos[3];
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    return mva_kd_nearest(tree, pos);
}

mva_kdres *mva_kd_nearest_range(mva_kdtree *tree, const double *pos, double range)
{
    int ret;
    mva_kdres *rset;

    if (!(rset = (mva_kdres *)malloc(sizeof(mva_kdres))))
    {
        return NULL;
    }

    if (!(rset->rlist = (mva_resnode *)malloc(sizeof(mva_resnode))))
    {
        free(rset);
        return NULL;
    }

    rset->rlist->next = NULL;
    rset->tree = NULL;

    if ((ret = find_nearest(tree->root, pos, range, rset->rlist, 0, tree->dim)) == -1)
    {
        mva_kd_res_free(rset);
        return NULL;
    }
    rset->size = ret;
    mva_kd_res_rewind(rset);
    return rset;
}

mva_kdres *mva_kd_nearest_rangef(mva_kdtree *tree, const float *pos, float range)
{
    double sbuf[16];
    double *bptr, *buf = NULL;
    int dim = tree->dim;
    mva_kdres *res;

    if (dim > 16)
    {
#ifndef NO_ALLOCA
        if (dim <= 256)
        {
            bptr = buf = (double *)alloca(dim * sizeof(double));
        }
        else
#endif
            if (!(bptr = buf = (double *)malloc(dim * sizeof(double))))
        {
            return NULL;
        }
    }
    else
    {
        bptr = buf = sbuf;
    }

    while (dim-- > 0)
    {
        *bptr++ = *pos++;
    }

    res = mva_kd_nearest_range(tree, buf, range);
#ifndef NO_ALLOCA
    if (tree->dim > 256)
#else
    if (tree->dim > 16)
#endif
    {
        free(buf);
    }
    return res;
}

mva_kdres *mva_kd_nearest_range3(mva_kdtree *tree, double x, double y, double z, double range)
{
    double buf[3];
    buf[0] = x;
    buf[1] = y;
    buf[2] = z;
    return mva_kd_nearest_range(tree, buf, range);
}

mva_kdres *mva_kd_nearest_range3f(mva_kdtree *tree, float x, float y, float z, float range)
{
    double buf[3];
    buf[0] = x;
    buf[1] = y;
    buf[2] = z;
    return mva_kd_nearest_range(tree, buf, range);
}

void mva_kd_res_free(mva_kdres *rset)
{
    clear_results(rset);
    free_resnode(rset->rlist);
    free(rset);
    rset = NULL;
}

int mva_kd_res_size(mva_kdres *set)
{
    return (set->size);
}

void mva_kd_res_rewind(mva_kdres *set)
{
    set->riter = set->rlist->next;
}

int mva_kd_res_end(mva_kdres *set)
{
    return set->riter == 0;
}

int mva_kd_res_next(mva_kdres *set)
{
    set->riter = set->riter->next;
    return set->riter != 0;
}

void *mva_kd_res_item(mva_kdres *set, double *pos)
{
    if (set->riter)
    {
        if (pos)
        {
            memcpy((void *)pos, set->riter->item->pos, set->tree->dim * sizeof(double));
        }
        return set->riter->item->data;
    }
    return 0;
}

void *mva_kd_res_itemf(mva_kdres *set, float *pos)
{
    if (set->riter)
    {
        if (pos)
        {
            int i;
            for (i = 0; i < set->tree->dim; i++)
            {
                pos[i] = set->riter->item->pos[i];
            }
        }
        return set->riter->item->data;
    }
    return NULL;
}

void *mva_kd_res_item3(mva_kdres *set, double *x, double *y, double *z)
{
    if (set->riter)
    {
        if (*x)
        {
            *x = set->riter->item->pos[0];
        }
        if (*y)
        {
            *y = set->riter->item->pos[1];
        }
        if (*z)
        {
            *z = set->riter->item->pos[2];
        }
    }
    return 0;
}

void *mva_kd_res_item3f(mva_kdres *set, float *x, float *y, float *z)
{
    if (set->riter)
    {
        if (*x)
        {
            *x = set->riter->item->pos[0];
        }
        if (*y)
        {
            *y = set->riter->item->pos[1];
        }
        if (*z)
        {
            *z = set->riter->item->pos[2];
        }
    }
    return 0;
}

void *mva_kd_res_item_data(mva_kdres *set)
{
    return mva_kd_res_item(set, 0);
}

void clear_rec(mva_kdnode *node, void (*destr)(void *))
{
    if (!node)
    {
        return;
    }

    // call function
    clear_rec(node->left, destr);
    clear_rec(node->right, destr);

    if (destr)
    {
        destr(node->data);
    }

    free(node->pos);
    free(node);
    node = NULL;
}

int insert_rec(mva_kdnode **nptr, const double *pos, void *data, int dir, int dim)
{
    int new_dir;
    mva_kdnode *node;

    // if node not exist
    if (!*nptr)
    {
        // alloc a node
        if (!(node = (mva_kdnode *)malloc(sizeof(mva_kdnode))))
        {
            return -1;
        }
        if (!(node->pos = (double *)malloc(dim * sizeof(double))))
        {
            free(node);
            return -1;
        }
        memcpy(node->pos, pos, dim * sizeof(double));
        node->data = data;
        node->dir = dir;
        node->left = node->right = NULL;
        *nptr = node;
    }
    node = *nptr;
    new_dir = (node->dir + 1) % dim;
    if (pos[node->dir] < node->pos[node->dir])
    {
        return insert_rec(&(*nptr)->left, pos, data, new_dir, dim);
    }
    return insert_rec(&(*nptr)->right, pos, data, new_dir, dim);
}

int rlist_insert(mva_resnode *list, mva_kdnode *item, double dist_sq)
{
    mva_resnode *rnode;

    // create a result node
    if (!(rnode = (mva_resnode *)alloc_resnode()))
    {
        return -1;
    }
    rnode->item = item;
    rnode->dist_sq = dist_sq;

    // if distance moren than 0
    if (dist_sq >= 0.0)
    {
        while (list->next && list->next->dist_sq > dist_sq)
        {
            list = list->next;
        }
    }
    rnode->next = list->next;
    list->next = rnode;
    return 0;
}

void clear_results(mva_kdres *set)
{
    mva_resnode *tmp, *node = set->rlist->next;
    while (node)
    {
        tmp = node;
        node = node->next;
        free_resnode(tmp);
    }
    set->rlist->next = NULL;
}

mva_kdhyperrect *hyperrect_create(int dim, const double *min, const double *max)
{
    unsigned int size = dim * sizeof(double);
    mva_kdhyperrect *rect = 0;

    if (!(rect = (mva_kdhyperrect *)malloc(sizeof(mva_kdhyperrect))))
    {
        return NULL;
    }

    rect->dim = dim;

    if (!(rect->min = (double *)malloc(size)))
    {
        free(rect);
        return NULL;
    }
    if (!(rect->max = (double *)malloc(size)))
    {
        free(rect->min);
        free(rect);
        return NULL;
    }
    memcpy(rect->min, min, size);
    memcpy(rect->max, max, size);
    return rect;
}
void hyperrect_free(mva_kdhyperrect *rect)
{
    if (rect)
    {
        if (rect->min)
        {
            free(rect->min);
        }
        if (rect->max)
        {
            free(rect->max);
        }
        free(rect);
    }
}
mva_kdhyperrect *hyperrect_duplicate(const mva_kdhyperrect *rect)
{
    return hyperrect_create(rect->dim, rect->min, rect->max);
}

void hyperrect_extend(mva_kdhyperrect *rect, const double *pos)
{
    int i;

    for (i = 0; i < rect->dim; i++)
    {
        if (pos[i] < rect->min[i])
        {
            rect->min[i] = pos[i];
        }
        if (pos[i] > rect->max[i])
        {
            rect->max[i] = pos[i];
        }
    }
}

double hyperrect_dist_sq(mva_kdhyperrect *rect, const double *pos)
{
    int i;
    double result = 0;

    for (i = 0; i < rect->dim; i++)
    {
        if (pos[i] < rect->min[i])
        {
            double tmp = rect->min[i] - pos[i];
            result += SQ(tmp);
        }
        else if (pos[i] > rect->max[i])
        {
            double tmp = rect->max[i] - pos[i];
            result += SQ(tmp);
        }
    }
    return result;
}

void kd_nearest_i(mva_kdnode *node, const double *pos, mva_kdnode **result, double *result_dist_sq, mva_kdhyperrect *rect)
{
    int dir = node->dir;
    int i;
    double dummy, dist_sq;
    mva_kdnode *nearer_subtree, *farther_subtree;
    double *nearer_hyperrect_coord, *father_hyperrect_coord;

    // decide whether to go left or right
    dummy = pos[dir] - node->pos[dir];
    if (dummy <= 0)
    {
        nearer_subtree = node->left;
        farther_subtree = node->right;
        nearer_hyperrect_coord = rect->max + dir;
        father_hyperrect_coord = rect->min + dir;
    }
    else
    {
        nearer_subtree = node->right;
        farther_subtree = node->left;
        nearer_hyperrect_coord = rect->min + dir;
        father_hyperrect_coord = rect->max + dir;
    }

    if (nearer_subtree)
    {
        // slice the hyperrect to get the hyperrect of the nearer subtree
        dummy = *nearer_hyperrect_coord;
        *nearer_hyperrect_coord = node->pos[dir];
        kd_nearest_i(nearer_subtree, pos, result, result_dist_sq, rect);
        *nearer_hyperrect_coord = dummy;
    }
    dist_sq = 0;
    for (i = 0; i < rect->dim; i++)
    {
        dist_sq += SQ(node->pos[i] - pos[i]);
    }
    if (dist_sq < *result_dist_sq)
    {
        *result = node;
        *result_dist_sq = dist_sq;
    }

    if (farther_subtree)
    {
        dummy = *father_hyperrect_coord;
        *father_hyperrect_coord = node->pos[dir];
        if (hyperrect_dist_sq(rect, pos) < *result_dist_sq)
        {
            kd_nearest_i(farther_subtree, pos, result, result_dist_sq, rect);
        }
        *father_hyperrect_coord = dummy;
    }
}

int find_nearest(mva_kdnode *node, const double *pos, double range, mva_resnode *list, int ordered, int dim)
{
    double dist_sq, dx;
    int i, ret, added_res = 0;

    if (!node) {
        return 0;
    }

    dist_sq = 0;
    for (i = 0; i < dim; i++)
    {
        dist_sq += SQ(node->pos[i] - pos[i]);
    }
    if (dist_sq <= SQ(range))
    {
        if (rlist_insert(list, node, ordered ? dist_sq : -1.0)  == -1)
        {
            return -1;
        }
        added_res = 1;
    }

    dx = pos[node->dir] - node->pos[node->dir];

    ret = find_nearest(dx <= 0.0 ? node->left : node->right, pos, range, list, ordered, dim);

    if (ret >= 0 && fabs(dx) < range){
        added_res == ret;
        ret =  find_nearest(dx <= 0.0 ? node->right : node->left, pos, range, list, ordered, dim);
    }

    if (ret == -1){
        return -1;
    }
    added_res += ret;
    return added_res ;
}