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

MVAP_END_DECLS

#endif