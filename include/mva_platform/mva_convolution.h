#ifndef MVA_CONVOLUTION_H_
#define MVA_CONVOLUTION_H_

/*// 核心
typedef struct convolution_kenel_
{
    double *kenel_data;
    unsigned int kenel_size;
    unsigned int data_size;
}convolution_kenel;


void free_kenel(convolution_kenel* kenel);

convolution_kenel* create_gaussian_kernel(unsigned int nKenelSize, double signal);
convolution_kenel* create_sobel_kenel();
convolution_kenel *create_canny_kenel();
convolution_kenel *create_laplacian_kenel();*/

int mva_sobel(unsigned char *pSrc, unsigned int nSrcWidth, unsigned int nSrcHeight,
              unsigned char *pDst, unsigned int nDstWidth, unsigned int nDstHeight,
              int dx, int dy, unsigned int kenel_size);
int mva_laplacian(unsigned char *pSrc, unsigned int nSrcWidth, unsigned int nSrcHeight,
                  unsigned char *pDst, unsigned int nDstWidth, unsigned int nDstHeight,
                  unsigned int kenel_size);
int mva_canny(unsigned char *pSrc, unsigned int nSrcWidth, unsigned int nSrcHeight,
              unsigned char *pDst, unsigned int nDstWidth, unsigned int nDstHeight);



#endif