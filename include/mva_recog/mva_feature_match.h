#ifndef MVA_FEATURE_MATCH_H_
#define MVA_FEATURE_MATCH_H_

#define MVA_FEATURE_MATCH_VERSION_H              1
#define MVA_FEATURE_MATCH_VERSION_M              0
#define MVA_FEATURE_MATCH_VERSION_L              0
#define MVA_FEATURE_MATCH_VERSION_D              0

#define MVA_FEATURE_MATCH_METHOD_SIFT            0  
#define MVA_FEATURE_MATCH_METHOD_SUFT            1
#define MVA_FEATURE_MATCH_METHOD_ORB             2
#define MVA_FEATURE_MATCH_METHOD_BRISK           3
#define MVA_FEATURE_MATCH_METHOD_LATCH           4
#define MVA_FEATURE_MATCH_METHOD_DEFAULT         MVA_FEATURE_MATCH_METHOD_SUFT

// ability
typedef enum MVA_FEATURE_MATCH_ABILITY_
{
    MVA_FEATURE_MATCH_ABILITY_TEMPLATE_CREATE = 0x01,
    MVA_FEATURE_MATCH_ABILITY_TEMPLATE_MATCH = 0x02
}MVA_FEATURE_MATCH_ABILITY;

// init cfg
typedef struct MVA_FEATURE_MATCH_INIT_CFG_
{
    unsigned int nWidth;
    unsigned int nHeight;
    unsigned int abilities;
}MVA_FEATURE_MATCH_INIT_CFG;

// process type
typedef enum MVA_FEATURE_MATCH_PROCESS_TYPE_
{
    MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_CREATE = 0x01,
    MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_MATCH_BY_SIFT = 0x02,
    MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_MATCH_BY_SUFT = 0x03,
    MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_MATCH_BY_ORB = 0x04,
    MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_MATCH_BY_BRISK = 0x05,
    MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_MATCH_BY_LATCH = 0x06
}MVA_FEATURE_MATCH_PROCESS_TYPE;


// template create input info
typedef struct MVA_FEATURE_MATCH_TEMPLATE_CREATE_INPUT_
{
    unsigned char* pData;
    unsigned int nWidth;
    unsigned int nHeight;

    unsigned char* pMaskData;
    unsigned int nMaskWidth;
    unsigned int nMaskHeight;
}MVA_FEATURE_MATCH_TEMPLATE_CREATE_INPUT;

// template create output info
typedef struct MVA_FEATURE_MATCH_TEMPLATE_CREATE_OUTPUT_
{
    unsigned char* pModelData;
    unsigned int nModelDataLen;
}MVA_FEATURE_MATCH_TEMPLATE_CREATE_OUTPUT;

// template match input info
typedef struct MVA_FEATURE_MATCH_TEMPLATE_MATCH_INPUT_
{
    unsigned char* pData;
    unsigned int nWidth;
    unsigned int nHeight;

    unsigned char* pModelData;
    unsigned int nModelDataLen;
}MVA_FEATURE_MATCH_TEMPLATE_MATCH_INPUT;


// template match output info
typedef struct MVA_FEATURE_MATCH_TEMPLATE_MATCH_OUTPUT_
{
    
}MVA_FEATURE_MATCH_TEMPLATE_MATCH_OUTPUT;

unsigned int MVA_FEATURE_MATCH_GetSDKVersion();
void * MVA_FEATURE_MATCH_Create();
void MVA_FEATURE_MATCH_Destroy(void* handle);
int MVA_FEATURE_MATCH_Init(void *handle, MVA_FEATURE_MATCH_INIT_CFG *init_cfg);
int MVA_FEATURE_MATCH_SetParam(void *handle, int key, int value );
int MVA_FEATURE_MATCH_GetParam(void *handle, int key, int *value);
int MVA_FEATURE_MATCH_Process(void *handle, MVA_FEATURE_MATCH_PROCESS_TYPE process_type, void *input, unsigned int input_data_size, void * output, unsigned int output_data_size);


#endif