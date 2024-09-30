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

#endif