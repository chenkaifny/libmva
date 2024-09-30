/* matrix calculate functions
 * light_matrix
 */
#ifndef MVA_MAT_H_
#define MVA_MAT_H_

#include "mva_data_define.h"

/* @brief create mat
 * @param row    mat.row
 * @param col    mat.col
 * @return NULL or mat
 */
mva_mat *mva_mat_create(unsigned int row, unsigned int col);

/* @brief destory mat
 * @param        mat
 */
void mva_mat_destroy(mva_mat *mat);

/* @brief set mat data
 * @param mat    mat
 * @param val    new data
 * @param val_size val_size
 */
void mva_mat_set_val_all(mva_mat *mat, float *val, unsigned int val_size);

/* @brief set mat one line data
 * @param mat     mat
 * @param row     the line will update data
 * @param val     new data
 * @param val_size val_size
 */
void mva_mat_set_val_line(mva_mat *mat, unsigned int row, float *val, unsigned int val_size);

/* @brief print mat data
 * @param mat      mat
 */
void mva_mat_dump(const mva_mat *mat);

/* @brief clear mat data
 * @param mat       mat
 */
void mva_mat_zero(mva_mat *mat);

/* @brief set eye mat data
 * @param mat       mat
 */
void mva_mat_eye(mva_mat *mat);

/* @brief mat add
 * @param src1       src1 mat
 * @param src2       src2 mat
 * @param dst        dst mar
 */
int mva_mat_add(mva_mat *src1, mva_mat *src2, mva_mat *dst);
int mva_mat_sub(mva_mat *src1, mva_mat *src2, mva_mat *dst);
int mva_mat_mul(mva_mat *src1, mva_mat *src2, mva_mat *dst);

int mva_mat_trans(mva_mat *src, mva_mat *dst);

float mva_mat_det(mva_mat *mat);
int mva_mat_adj(mva_mat *src, mva_mat *dst);
int mva_mat_inv(mva_mat *src, mva_mat *dst);

void mva_mat_clone(mva_mat *src, mva_mat *dst);

#endif