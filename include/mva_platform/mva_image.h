/* image
 */
#ifndef MVA_IMAGE_H_
#define MVA_IMAGE_H_

#include "mva_data_define.h"

MVAP_BEGIN_DECLS

// Image
typedef struct mva_image_
{
    unsigned char *image_data;                 // Image Data
    unsigned int width;                        // Image Width
    unsigned int height;                       // Image Height
}mva_image;

/* @brief create a zero image
 * @param width             image width
 * @param height            image height
 * @return NULL or mva_image ptr
 */
MVAP_API mva_image * mva_create_zero_image(unsigned int width, unsigned int height);

/* @brief create a image
 * @param image_data        image data
 * @param width             image width
 * @param height            image height
 * @return NULL or mva_image ptr
 */
MVAP_API mva_image * mva_create_image(unsigned char *image_data, unsigned int width, unsigned int height);

/* @brief release image resource
 * @param image        image handle
 */
MVAP_API void mva_release_image(mva_image *image);

MVAP_END_DECLS

#endif