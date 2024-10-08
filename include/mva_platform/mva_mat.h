/* matrix calculate functions
 * light_matrix
 */
#ifndef MVA_MAT_H_
#define MVA_MAT_H_

#include "mva_data_define.h"

MVAP_BEGIN_DECLS

// 矩阵
typedef struct mva_mat_
{
    unsigned int row;
    unsigned int col;
    float **data;
}mva_mat;



/* @brief create mat
 * @param row    mat.row
 * @param col    mat.col
 * @return NULL or mat
 */
MVAP_API mva_mat *mva_mat_create(unsigned int row, unsigned int col);

/* @brief destory mat
 * @param        mat
 */
MVAP_API void mva_mat_destroy(mva_mat *mat);

/* @brief set mat data
 * @param mat    mat
 * @param val    new data
 * @param val_size val_size
 */
MVAP_API void mva_mat_set_val_all(mva_mat *mat, float *val, unsigned int val_size);

/* @brief set mat one line data
 * @param mat     mat
 * @param row     the line will update data
 * @param val     new data
 * @param val_size val_size
 */
MVAP_API void mva_mat_set_val_line(mva_mat *mat, unsigned int row, float *val, unsigned int val_size);

/* @brief print mat data
 * @param mat      mat
 */
MVAP_API void mva_mat_dump(const mva_mat *mat);

/* @brief clear mat data
 * @param mat       mat
 */
MVAP_API void mva_mat_zero(mva_mat *mat);

/* @brief set eye mat data
 * @param mat       mat
 */
MVAP_API void mva_mat_eye(mva_mat *mat);

/* @brief mat add
 * @param src1       src1 mat
 * @param src2       src2 mat
 * @param dst        dst mar
 * @return 0 or error code
 */
MVAP_API int mva_mat_add(mva_mat *src1, mva_mat *src2, mva_mat *dst);

/* @brief mat sub
 * @param src1       src1.mat
 * @param src2       src2.mat
 * @param dst        dst.mat
 * @return 0 or error code
 */
MVAP_API int mva_mat_sub(mva_mat *src1, mva_mat *src2, mva_mat *dst);

/* @brief mat multiply
 * @param src1       src1.mat
 * @param src2       src2.mat
 * @param dst        dst.mat
 * @return 0 or error code
 */
MVAP_API int mva_mat_mul(mva_mat *src1, mva_mat *src2, mva_mat *dst);

/* @brief mat trans
 * @param src        src.mat
 * @param dst        dst.mat
 * @return 0 or error code
 */
MVAP_API int mva_mat_trans(mva_mat *src, mva_mat *dst);

/* @brief mat determinant
 * @param mat
 * @return det
 */
MVAP_API float mva_mat_det(mva_mat *mat);

/* @brief mat adjoint
 * @param src        src.mat
 * @param dst        dst.mat
 * @return 0 or error code
 */
MVAP_API int mva_mat_adj(mva_mat *src, mva_mat *dst);

/* @brief mat inversion
 * @param src        src.mat
 * @param dst        dst.mat
 * @return 0 or error code
 */
MVAP_API int mva_mat_inv(mva_mat *src, mva_mat *dst);

/* @brief mat clone
 * @param src        src.mat
 * @param dst        dst.mat
 * @return 0 or error code
 */
MVAP_API void mva_mat_clone(mva_mat *src, mva_mat *dst);

MVAP_END_DECLS

#endif