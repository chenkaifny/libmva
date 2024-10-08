#include "mva_feature_match.h"

#include <stdlib.h>
#include <string.h>

// handle
typedef struct MVA_FEATURE_MATCH_HANDLE_
{
    // base info
    unsigned int nWidth;
    unsigned int nHeight;


    // parameter
    unsigned int nKernelSize;
    unsigned int nThreshold;

    // recog param
    int r;
    int c;
    int octv;
    int intvl;
    double subintvl;
    double scl_octv;


    unsigned char *pTempImageData;

}MVA_FEATURE_MATCH_HANDLE;

typedef struct MVA_FEATURE_MATCH_MODEL_INFO_
{
    // verify number
    unsigned short nVerifyNum;
    // version
    unsigned int nModelVersion;
    // image info
    unsigned int nWidth;
    unsigned int nHeight;
    unsigned char* pImageData;

    // rect info

    // model create param


}MVA_FEATURE_MATCH_MODEL_INFO;


unsigned int MVA_FEATURE_MATCH_GetSDKVersion()
{
    return ((unsigned int)MVA_FEATURE_MATCH_VERSION_H) << 24 + 
        ((unsigned int)MVA_FEATURE_MATCH_VERSION_M) << 16 +
        ((unsigned int)MVA_FEATURE_MATCH_VERSION_H) << 8 +
        ((unsigned int)MVA_FEATURE_MATCH_VERSION_D);
}

void * MVA_FEATURE_MATCH_Create()
{
    MVA_FEATURE_MATCH_HANDLE *handle = (MVA_FEATURE_MATCH_HANDLE*)malloc(sizeof(MVA_FEATURE_MATCH_HANDLE));
    if (!handle)
    {
        return NULL;
    }
    memset(handle, 0, sizeof(MVA_FEATURE_MATCH_HANDLE));
    return handle;
}

void MVA_FEATURE_MATCH_Destroy(void* handle)
{
    if (handle)
    {
        free(handle);
        handle = NULL;
    }
}

int MVA_FEATURE_MATCH_Init(void *handle, MVA_FEATURE_MATCH_INIT_CFG *init_cfg)
{
    if (!handle)
    {
        return -1;
    }

    MVA_FEATURE_MATCH_HANDLE *algo_handle = (MVA_FEATURE_MATCH_HANDLE*)handle;
    algo_handle->pTempImageData = (unsigned char*)malloc(algo_handle->nWidth * algo_handle->nHeight);
    if (!algo_handle->pTempImageData)
    {
        return -1;
    }

    return 0;
}

int MVA_FEATURE_MATCH_SetParam(void *handle, int key, int value )
{
    return -1;
}

int MVA_FEATURE_MATCH_GetParam(void *handle, int key, int *value)
{
    return -1;
}

int do_template_match()
{


    // 1 建立高斯金字塔
    // 1.1 高斯卷积

    // 1.2 高斯差分

    // 2 检测关键点

    // 3 关键点方向的分配

    // 4. 特征点描述符号

    // 5. 计算关键点的欧式距离

    return -1;
}

int do_model_create()
{
    return -1;
}

int MVA_FEATURE_MATCH_Process(void *handle, MVA_FEATURE_MATCH_PROCESS_TYPE process_type, void *input, unsigned int input_data_size, void * output, unsigned int output_data_size)
{
    int octvs, i, n = 0;
    if (!handle || !input || !output)
    {
        return -1;
    }

    if (process_type == MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_CREATE)
    {
        return do_model_create();
    }
    else if (process_type == MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_MATCH_BY_BRISK)
    {
        return do_template_match();
    }




    return -1;
}