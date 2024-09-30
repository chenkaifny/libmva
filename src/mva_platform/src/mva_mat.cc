#include "mva_mat.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef min
#define min(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef equal
#define equal(a, b) ((a - b) < 1e-7 && (a - b) > -(1e-7))
#endif

void swap(int *a, int *b)
{
    int m = *a;
    *a = *b;
    *b = m;
}

void perm(int list[], int k, int m, int *p, mva_mat *mat, float *det)
{
    int i;
    if (k > m)
    {
        float res = mat->data[0][list[0]];
        for (i = 1; i < mat->row; i++)
        {
            res *= mat->data[i][list[i]];
        }

        if (*p % 2)
        {
            // odd is negative
            *det -= res;
        }
        else
        {
            // even is positive
            *det += res;
        }
    }
    else
    {
        // if the element is 0
        if (!equal(mat->data[k][list[k]], 0.0f))
        {
            perm(list, k + 1, m, p, mat, det);
        }
        for (i = k + 1; i <= m; i++)
        {
            if (equal(mat->data[k][list[i]], 0.0f))
            {
                continue;
            }
            swap(&list[k], &list[i]);
            *p += 1;
            perm(list, k + 1, m, p, mat, det);
            swap(&list[k], &list[i]);
            *p -= 1;
        }
    }
}

mva_mat *mva_mat_create(unsigned int row, unsigned int col)
{
    int i;

    mva_mat *mat = NULL;
    bool is_failed = false;

    do
    {
        mat = (mva_mat *)malloc(sizeof(mva_mat));
        if (!mat)
        {
            return NULL;
        }

        mat->data = (float **)malloc(row * sizeof(float *));
        if (!mat->data)
        {
            is_failed = true;
            break;
        }

        for (i = 0; i < row; i++)
        {
            mat->data[i] = (float *)malloc(col * sizeof(float));
            if (!mat->data[i])
            {
                is_failed = true;
                break;
            }
        }

    } while (0);

    if (is_failed)
    {
        mva_mat_destroy(mat);
        mat = NULL;
    }

    return mat;
}

void mva_mat_destroy(mva_mat *mat)
{
    int i;

    if (mat)
    {
        if (mat->data)
        {
            for (i = 0; i < mat->row; i++)
            {
                if (mat->data[i])

                {
                    free(mat->data[i]);
                    mat->data[i] = NULL;
                }
            }
            free(mat->data);
            mat->data = NULL;
        }

        free(mat);

        mat = NULL;
    }
}

void mva_mat_set_val_all(mva_mat *mat, float *val, unsigned int val_size)
{
    if (!mat)
    {
        return;
    }
    if (val_size < (mat->col * mat->row))
    {
        return;
    }

    int row, col;

    for (row = 0; row < mat->row; row++)
    {
        for (col = 0; col < mat->col; col++)
        {
            mat->data[row][col] = val[col + row * mat->col];
        }
    }
}

void mva_mat_set_val_line(mva_mat *mat, unsigned int row, float *val, unsigned int val_size)
{
    if (!mat)
    {
        return;
    }
    if (val_size < (mat->col))
    {
        return;
    }
    if (row >= mat->row)
    {
        return;
    }

    int col;

    for (col = 0; col < mat->col; col++)
    {
        mat->data[row][col] = val[col + row * mat->col];
    }
}

void mva_mat_dump(const mva_mat *mat)
{
    int row, col;

    if (!mat)
    {
        return;
    }
}

void mva_mat_zero(mva_mat *mat)
{
    if (!mat)
    {
        return;
    }
    int row, col;

    for (row = 0; row < mat->row; row++)
    {
        for (col = 0; col < mat->col; col++)
        {
            mat->data[row][col] = 0.0f;
        }
    }
}

void mva_mat_eye(mva_mat *mat)
{
    if (!mat)
    {
        return;
    }

    int i = 0;
    mva_mat_zero(mat);

    for (i = 0; i < min(mat->row, mat->col); i++)
    {
        mat->data[i][i] = 1.0f;
    }
}

int mva_mat_add(mva_mat *src1, mva_mat *src2, mva_mat *dst)
{
    if (!(src1->row == src2->row && src2->row == dst->row && src1->col == src2->col && src2->col == dst->col))
    {
        return -1;
    }

    int row, col;

    for (row = 0; row < src1->row; row++)
    {
        for (col = 0; col < src1->col; col++)
        {
            dst->data[row][col] = src1->data[row][col] + src2->data[row][col];
        }
    }
    return 0;
}

int mva_mat_sub(mva_mat *src1, mva_mat *src2, mva_mat *dst)
{
    if (!(src1->row == src2->row && src2->row == dst->row && src1->col == src2->col && src2->col == dst->col))
    {
        return -1;
    }

    int row, col;

    for (row = 0; row < src1->row; row++)
    {
        for (col = 0; col < src1->col; col++)
        {
            dst->data[row][col] = src1->data[row][col] - src2->data[row][col];
        }
    }
    return 0;
}

int mva_mat_mul(mva_mat *src1, mva_mat *src2, mva_mat *dst)
{

    if (src1->col != src2->row || src1->row != dst->row || src2->col != dst->col)
    {
        return -1;
    }

    int row, col;
    int i;
    float temp;

    for (row = 0; row <dst->row ;row++)
    {
        for (col = 0; col < dst->col; col++)
        {
            temp = 0.0f;
            for (i = 0; i < src1->col; i++)
            {
                temp += src1->data[row][i] * src2->data[i][col];
            }
            dst->data[row][col] = temp;
        }
    }
    return 0;
}

int mva_mat_trans(mva_mat *src, mva_mat *dst)
{
    if (src->row != dst->col || src->col != dst->row)
    {
        return -1;
    }
    int row, col;
    for (row = 0; row < dst->row; row++)
    {
        for (col = 0; col < dst->col; col++)
        {
            dst->data[row][col] = src->data[col][row];
        }
    }
    return 0;
}

float mva_mat_det(mva_mat *mat)
{
    if (!mat)
    {
        return 0.0f;
    }
    if (mat->col != mat->row)
    {
        return 0.0f;
    }

    float det = 0.0f;
    int plarity = 0;
    int *list;
    int i;

    list = (int *)malloc(mat->col * sizeof(int));
    if (!list)
    {
        return 0.0f;
    }

    for (i = 0; i < mat->col; i++)
    {
        list[i] = i;
    }

    perm(list, 0, mat->row -1,  &plarity, mat,&det);
    free(list);
    list = NULL;

    return det;
}

int mva_mat_adj(mva_mat *src, mva_mat *dst)
{
    if (!src || !dst){
        return -1;
    }
    if (src->row != src->col || src->row != dst->row || src->col != dst->col){
        return -1;
    }

    mva_mat* smat = NULL;
    int row, col;
    int i, j, r, c;
    float det;

    smat = mva_mat_create(src->row, src->col);
    if (!smat){
        return -1;
    }

    for (row = 0; row < src->row; row++){
        for (col = 0; col < src->col; col ++){
            r = 0;
            for (i = 0; i < src->row; i++){
                if (i == row){
                    continue;
                }
                c = 0;
                for (j = 0; j < src->col; j++){
                    if (j == col){
                        continue;
                    }
                    smat->data[r][c] = src->data[i][j];
                    c++;
                }
                r++;
            }
            det = mva_mat_det(smat);
            if ((row + col) %2){
                det = -det;
            }
            dst->data[col][row] = det;
        }
    }

    mva_mat_destroy(smat);
    smat = NULL;
    return 0;
}

int mva_mat_inv(mva_mat *src, mva_mat *dst)
{
    if (!src || !dst)
    {
        return -1;
    }

    if (src->row != src->col || src->row != dst->row || src->col != dst->col)
    {
        return -1;
    }
    mva_mat *adj_mat;
    float det;
    int row, col;

    adj_mat = mva_mat_create(src->row, src->col);
    if (!adj_mat)
    {
        return -1;
    }
    mva_mat_adj(src, adj_mat);
    det = mva_mat_det(src);
    if (equal(det, 0.0f))
    {
        return -1;
    }

    for (row = 0; row < src->row; row++)
    {
        for (col = 0; col < src->col; col++)
        {
            dst->data[row][col] = adj_mat->data[row][col] / det;
        }
    }
    mva_mat_destroy(adj_mat);
    adj_mat = NULL;
    return 0;
}

void mva_mat_clone(mva_mat *src, mva_mat *dst)
{
    if (!src || !dst)
    {
        return;
    }
    if (src->row != dst->row || src->col != dst->col)
    {
        return;
    }

    int row, col;

    for (row = 0; row < src->row; row++)
    {
        for (col = 0; col < src->col; col++)
        {
            dst->data[row][col] = src->data[row][col];
        }
    }
}