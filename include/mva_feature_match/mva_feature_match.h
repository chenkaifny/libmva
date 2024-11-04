#ifndef MVA_FEATURE_MATCH_H_
#define MVA_FEATURE_MATCH_H_

// versiom
#define MVA_FEATURE_MATCH_VERSION_H 1
#define MVA_FEATURE_MATCH_VERSION_M 0
#define MVA_FEATURE_MATCH_VERSION_L 0
#define MVA_FEATURE_MATCH_VERSION_D 0

// define

#define MVA_FEATURE_MATCH_IMAGE_WIDTH_MAX (12032)
#define MVA_FEATURE_MATCH_IMAGE_HEIGHT_MAX (9024)
#define MVA_FEATURE_MATCH_MATCH_NUM_SIZE (64)

// parameter
#define MVA_FEATURE_MATCH_METHOD_SIFT 0
#define MVA_FEATURE_MATCH_METHOD_SUFT 1
#define MVA_FEATURE_MATCH_METHOD_ORB 2
#define MVA_FEATURE_MATCH_METHOD_BRISK 3
#define MVA_FEATURE_MATCH_METHOD_LATCH 4
#define MVA_FEATURE_MATCH_METHOD_DEFAULT MVA_FEATURE_MATCH_METHOD_SUFT

#define MVA_FEATURE_MATCH_MATCH_COUNT_MIN 0
#define MVA_FEATURE_MATCH_MATCH_COUNT_MAX 256
#define MVA_FEATURE_MATCH_MATCH_COUNT_DEFAULT MVA_FEATURE_MATCH_MATCH_COUNT_MIN

// ability
typedef enum MVA_FEATURE_MATCH_ABILITY_
{
    MVA_FEATURE_MATCH_ABILITY_TEMPLATE_CREATE = 0x01,
    MVA_FEATURE_MATCH_ABILITY_TEMPLATE_MATCH = 0x02
} MVA_FEATURE_MATCH_ABILITY;

// init cfg
typedef struct MVA_FEATURE_MATCH_INIT_CFG_
{
    unsigned int nWidth;
    unsigned int nHeight;
    unsigned int abilities;
} MVA_FEATURE_MATCH_INIT_CFG;

// process type
typedef enum MVA_FEATURE_MATCH_PROCESS_TYPE_
{
    MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_CREATE = 0x01,
    MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_MATCH_BY_SIFT = 0x02,
    MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_MATCH_BY_SUFT = 0x03,
    MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_MATCH_BY_ORB = 0x04,
    MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_MATCH_BY_BRISK = 0x05,
    MVA_FEATURE_MATCH_PROCESS_TYPE_TEMPLATE_MATCH_BY_LATCH = 0x06
} MVA_FEATURE_MATCH_PROCESS_TYPE;

// template create input info
typedef struct MVA_FEATURE_MATCH_TEMPLATE_CREATE_INPUT_
{
    unsigned char *pData;
    unsigned int nWidth;
    unsigned int nHeight;

    unsigned char *pMaskData;
    unsigned int nMaskWidth;
    unsigned int nMaskHeight;
} MVA_FEATURE_MATCH_TEMPLATE_CREATE_INPUT;

// template create output info
typedef struct MVA_FEATURE_MATCH_TEMPLATE_CREATE_OUTPUT_
{
    unsigned char *pModelData;
    unsigned int nModelDataLen;
} MVA_FEATURE_MATCH_TEMPLATE_CREATE_OUTPUT;

// template match input info
typedef struct MVA_FEATURE_MATCH_TEMPLATE_MATCH_INPUT_
{
    unsigned char *pData;
    unsigned int nWidth;
    unsigned int nHeight;

    unsigned char *pModelData;
    unsigned int nModelDataLen;
} MVA_FEATURE_MATCH_TEMPLATE_MATCH_INPUT;

// template match output info
typedef struct MVA_FEATURE_MATCH_TEMPLATE_MATCH_OUTPUT_
{

} MVA_FEATURE_MATCH_TEMPLATE_MATCH_OUTPUT;

/**
 * get mva_feature_match sdk version
 * @return version
 */
unsigned int MVA_FEATURE_MATCH_GetSDKVersion();

/**
 * create mva_feature_match handle
 * @return handle
 */
void *MVA_FEATURE_MATCH_Create();

/**
 * destroy mva_feature_match handle
 * @param handle        handle
 */
void MVA_FEATURE_MATCH_Destroy(void *handle);

/**
 * init mva_feature_match handle
 * @param handle        handle
 * @param init_cfg      init configuration info
 * @return 0 or error code
 */
int MVA_FEATURE_MATCH_Init(void *handle, MVA_FEATURE_MATCH_INIT_CFG *init_cfg);

/**
 * set algorithm param 
 * @param handle        handle
 * @param key           key
 * @param value         value
 * @return 0 or error code
 */
int MVA_FEATURE_MATCH_SetParam(void *handle, int key, int value);

/**
 * get algorithm param
 * @param handle        handle
 * @param key           key
 * @param value         value
 * @return 0 or error code
 */
int MVA_FEATURE_MATCH_GetParam(void *handle, int key, int *value);

/**
 * process algorithm
 * @param handle       handle
 * @param process_type process type
 * @param input        input struct
 * @param input_data_size input struct data size
 * @param output       output struct
 * @param output_data_size output struct data size
 * @return 0 or error code
 */
int MVA_FEATURE_MATCH_Process(void *handle, MVA_FEATURE_MATCH_PROCESS_TYPE process_type, void *input, unsigned int input_data_size, void *output, unsigned int output_data_size);

#endif