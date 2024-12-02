#include "mva_image.h"

#include <memory.h>
#include <stdlib.h>

mva_image * mva_create_zero_image(unsigned int width, unsigned int height)
{
    mva_image *new_image = (mva_image *)malloc(sizeof(mva_image));
    if (!new_image)
    {
        return NULL;
    }

    new_image->image_data = NULL;
    new_image->width = width;
    new_image->height = height;

    new_image->image_data = (unsigned char *)malloc(width * height);
    if (!new_image->image_data)
    {
        mva_release_image(new_image);
        new_image = NULL;
        return NULL;
    }

    return new_image;
}

mva_image * mva_create_image(unsigned char *image_data, unsigned int width, unsigned int height)
{
    return NULL;
}

void mva_release_image(mva_image *image)
{

}