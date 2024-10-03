#include "mva_feature_match.h"

#include <stdlib.h>

// handle
typedef struct MVA_FEATURE_MATCH_HANDLE_
{
    // base info
    unsigned int nWidth;
    unsigned int nHeight;


    // parameter
    unsigned int nThreshold;

    // recog param
    int r;
    int c;
    int octv;
    int intvl;
    double subintvl;
    double scl_octv;

}MVA_FEATURE_MATCH_HANDLE;


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
    return -1;
}

int MVA_FEATURE_MATCH_SetParam(void *handle, int key, int value )
{
    return -1;
}

int MVA_FEATURE_MATCH_GetParam(void *handle, int key, int *value)
{
    return -1;
}

int MVA_FEATURE_MATCH_Process(void *handle, MVA_FEATURE_MATCH_PROCESS_TYPE process_type, void *input, unsigned int input_data_size, void * output, unsigned int output_data_size)
{
    return -1;
}