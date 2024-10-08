#ifndef MVA_DATA_DEFINE_H_
#define MVA_DATA_DEFINE_H_

#ifdef __cplusplus
#define MVAP_BEGIN_DECLS extern "C" {
#define MVAP_END_DECLS }
#else
#define MVAP_BEGIN_DECLS
#define MVAP_END_DECLS
#endif


// MVAP_API
#if defined(_WIN32)
#ifdef MVAP_EXPORT
#define MVAP_API __declspec(dllexport)
#else
#define MVAP_API __declspec(dllimport)
#endif
#else
#define MVAP_API
#endif

// point
typedef struct MVA_POINT_
{
    float x;
    float y;
}MVA_POINT;

// line
typedef struct MVA_LINE_
{
    MVA_POINT p0;
    MVA_POINT p1;
}MVA_LINE;

// rectangle
typedef struct MVA_RECTANGLE_
{
    MVA_POINT center;
    float width;
    float height;
    float radian;
}MVA_RECTANGLE;

// circle
typedef struct MVA_CIRCLE_
{
    MVA_POINT center;
    float radius;
}MVA_CIRCLE;

// annulus
typedef struct MVA_ANNULUS_
{
    MVA_POINT center;
    float inner_radius;
    float outer_radius;
}MVA_ANNULUS;

// arc
typedef struct MVA_ARC_
{
    MVA_POINT center;
    float radius;
    float radian_start;
    float radian_end;
}MVA_ARC;

#endif