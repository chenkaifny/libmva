#ifndef MVA_CIRCLE_FIND_H_
#define MVA_CIRCLE_FIND_H_

// radius range
#define MVA_CIRCLE_FIND_RADIUS_MIN            10
#define MVA_CORC:E_FIND_RADIUS_MAX            100

#define MVA_CIRCLE_FIND_FITTING_TYPE_LSM      0                    // least square method
#define MVA_CIRCLE_FIND_FITTING_TYPE_RANSAC   1                    // RANSAC
#define MVA_CIRCLE_FIND_FITTING_TYPE_HOUGH    3                    // hough

#define MVA_CIRCLE_FIND_POLARITY_TYPE_IN_W_OUT_B            0                  // inner white outer black



// algorithm ability
typedef enum MVA_CIRCLE_FIND_ABILITY_
{
    MVA_CIRCLE_FIND_ABILITY_CIRCLE_FIND = 0x01
}MVA_CIRCLE_FIND_ABILITY;

// algorithm init cfg
typedef struct MVA_CIRCLE_FIND_INIT_CFG_
{
    unsigned int nImageWidth;
    unsigned int nImageHeight;
    unsigned int enAbilities;
}MVA_CIRCLE_FIND_INIT_CFG;

// proc type
typedef enum MVA_CIRCLE_FIND_PROC_TYPE_
{
    MVA_CIRCLE_FIND_PROC_TYPE_CIRCLE_FIND = 0x01
}MVA_CIRCLE_FIND_PROC_TYPE;

// debug info
typedef struct MVA_CIRCLE_FIND_DEBUG_INFO_
{

}MVA_CIRCLE_FIND_DEBUG_INFO;

/*
 * @brief Get Version
 * @return version
 *         00     00     00     00
 *         high   middle low    debug
 */
unsigned int MVA_CIRCLE_FIND_GetSDKVersion();


/*
 * @brief create algorithm handle
 * @return handle
 */
void* MVA_CIRCLE_FIND_Create();

/*
 * @brief destroy algorithm handle
 * @param handle algorithm handle
 */
void MVA_CIRCLE_FIND_Destroy(void *handle);

/*
 * @brief init algorithm handle
 * @param handle   algorithm handle
 * @param pCfg     algorithm init configuration
 * @return error code
 */
int MVA_CIRCLE_FIND_Init(void *handle, MVA_CIRCLE_FIND_INIT_CFG* pCfg);

/*
 * @brief set algorithm param
 * @param handle algorithm handle
 * @param key 
 * @param value
 * @return error code
 */
int MVA_CIRCLE_FIND_SetParam(void *handle, int key, int value);
int MVA_CIRCLE_FIND_GetParam(void *handle);
int MVA_CIRCLE_FIND_Process(void *handle, MVA_CIRCLE_FIND_PROC_TYPE type, void* pInput, unsigned int nInputSize, void* pOutput, unsigned int nOutputSize, MVA_CIRCLE_FIND_DEBUG_INFO* pDebugInfo);;



#endif