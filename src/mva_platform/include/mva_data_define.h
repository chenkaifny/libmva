#ifndef MVA_DATA_DEFINE_H_
#define MVA_DATA_DEFINE_H_

// 矩阵
typedef struct mva_mat_
{
    unsigned int row;
    unsigned int col;
    float **data;
}mva_mat;

#endif