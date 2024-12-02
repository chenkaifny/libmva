#ifndef MVA_FEATURE_MATCH_SIFT_H_
#define MVA_FEATURE_MATCH_SIFT_H_

// Sift图像
typedef struct SiftImage
{

}SiftImage;

// Data Struct for a float image

// 金字塔每一层
typedef struct ImageSt
{
    float levelSigma;
    int levelSigmaLength;
    float absolute;
    float sigma;
}ImageLevels;

// 金字塔每一阶梯
typedef struct ImageSt1
{
    int row;
    int col;
    float subSample;
    ImageLevels *Octave;
}ImageOctaves;

// keypoint 数据结构
typedef struct keypointSt
{
    float row;
    float col;
    float sx;
    float sy;
    float ovtave;
    float level;
    float scale;
    float ori_mag;
    float *descrin;
    struct keypointSt *next;
}*Keypoint;

// 下采样
SiftImage * halfSizeImage(SiftImage *image);

// 上采样，最近临方法
SiftImage * doubleSizeImage(SiftImage *image);

// 上采样，线性插值
SiftImage * doubleSizeImage2(SiftImage *image);

// 双线性插值
float getPixelRT(SiftImage *image,  float col, float row);

// 向量归一化
void normalizeVec(float *vec, int dim);

// 得到1维高斯核
SiftImage * GaussianKernel1D(float signal, int dim);

// 在像素宽度处进行高斯卷积
float ConvolveLocWidth(float *kernel, int dim, SiftImage *src, int x, int y);

// 在整个图像宽度进行1D高斯卷积
void Convolve1DWidth(float *kernel, int dim, SiftImage *src, SiftImage *dst);

int mva_sift_features();

#endif