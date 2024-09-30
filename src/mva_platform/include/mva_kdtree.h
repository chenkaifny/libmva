/* kd-tree
 *
 */
#ifndef MVA_KDTREE_H_
#define MVA_KDTREE_H_

#include "mva_data_define.h"

MVAP_BEGIN_DECLS

// hyper rect
typedef struct mva_kdhyperrect_
{
    int dim;                       // dim
    double *min;                   // every dim min
    double *max;                   // every dim max
}mva_kdhyperrect;

typedef struct mva_kdnode_ mva_kdnode ;
typedef struct mva_resnode_ mva_resnode;

// kd-node
typedef struct mva_kdnode_
{
    double *pos;                   // pos
    int dir ;                      // dir
    void* data;                    // data
    mva_kdnode *left;              // left node
    mva_kdnode *right;             // right node
}mva_kdnode;

// result node
typedef struct mva_resnode_
{
    mva_kdnode *item;              // node
    double dist_sq;                // node distance
    mva_resnode* next;             // next resnode
}mva_resnode;

// kd-tree
typedef struct mva_kdtree_
{
    int dim;                       // dim
    mva_kdnode *root;              // root node
    mva_kdhyperrect *rect;         // hyper rect
    void (*destr)(void*) ;         // destroy function
}mva_kdtree;

// kd result
typedef struct mva_kdres_
{
    mva_kdtree *tree;
    mva_resnode *rlist;
    mva_resnode *riter;
    int size;
}mva_kdres;


MVAP_API mva_kdtree *mva_kd_create(int k);
void mva_kd_free(mva_kdtree *tree);
void mva_kd_clear(mva_kdtree *tree);
void mva_kd_destructor(mva_kdtree *tree, void (*destr)(void*));

int mva_kd_insert(mva_kdtree *tree, const double *pos, void *data);
int mva_kd_insertf(mva_kdtree *tree, const float *pos, void *data);
int mva_kd_insert3(mva_kdtree *tree, double x, double y, double z, void *data);
int mva_kd_insert3f(mva_kdtree *tree, float x, float y, float z, void *data);

mva_kdres *mva_kd_nearest(mva_kdtree *tree, const double *pos);
mva_kdres *mva_kd_nearestf(mva_kdtree *tree, const float *pos);
mva_kdres *mva_kd_nearest3(mva_kdtree *tree, double x, double y, double z);
mva_kdres *mva_kd_nearest3f(mva_kdtree *tree, float x, float y, float z);

mva_kdres *mva_kd_nearest_range(mva_kdtree *tree, const double *pos, double range);
mva_kdres *mva_kd_nearest_rangef(mva_kdtree *tree, const float *pos, float range);
mva_kdres *mva_kd_nearest_range3(mva_kdtree *tree, double x, double y, double z, double range);
mva_kdres *mva_kd_nearest_range3f(mva_kdtree *tree, float x, float y, float z, float range);


void mva_kd_res_free(mva_kdres *set);
int mva_kd_res_size(mva_kdres *set);
void mva_kd_res_rewind(mva_kdres *set);
int mva_kd_res_end(mva_kdres *set);
int mva_kd_res_next(mva_kdres *set);

void *mva_kd_res_item(mva_kdres *set, double *pos);
void *mva_kd_res_itemf(mva_kdres *set, float *pos);
void *mva_kd_res_item3(mva_kdres *set, double *x, double *y, double *z);
void *mva_kd_res_item3f(mva_kdres *set, float *x, float *y, float *z);

void * mva_kd_res_item_data(mva_kdres *set);

MVAP_END_DECLS

#endif