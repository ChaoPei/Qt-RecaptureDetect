//
// MATLAB Compiler: 5.1 (R2014a)
// Date: Fri May 26 22:02:04 2017
// Arguments: "-B" "macro_default" "-W" "cpplib:Remake" "-T" "link:lib" "-d"
// "E:\Matlab\software\Remake\for_testing" "-v"
// "E:\Matlab\software\Classifier.m" "E:\Matlab\software\ensemble_testing.m"
// "E:\Matlab\software\ensemble_training.m" "E:\Matlab\software\Feature_one.m"
// "E:\Matlab\software\Feature_two.m" "E:\Matlab\software\features_extract.m"
// "E:\Matlab\software\main_FeatureClassifier.m"
// "class{Class1:E:\Matlab\software\Classifier.m,E:\Matlab\software\ensemble_tes
// ting.m,E:\Matlab\software\ensemble_training.m,E:\Matlab\software\Feature_one.
// m,E:\Matlab\software\Feature_two.m,E:\Matlab\software\features_extract.m,E:\M
// atlab\software\main_FeatureClassifier.m}" 
//

#ifndef __Remake_h
#define __Remake_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_Remake
#define PUBLIC_Remake_C_API __global
#else
#define PUBLIC_Remake_C_API /* No import statement needed. */
#endif

#define LIB_Remake_C_API PUBLIC_Remake_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_Remake
#define PUBLIC_Remake_C_API __declspec(dllexport)
#else
#define PUBLIC_Remake_C_API __declspec(dllimport)
#endif

#define LIB_Remake_C_API PUBLIC_Remake_C_API


#else

#define LIB_Remake_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_Remake_C_API 
#define LIB_Remake_C_API /* No special import/export declaration */
#endif

extern LIB_Remake_C_API 
bool MW_CALL_CONV RemakeInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_Remake_C_API 
bool MW_CALL_CONV RemakeInitialize(void);

extern LIB_Remake_C_API 
void MW_CALL_CONV RemakeTerminate(void);



extern LIB_Remake_C_API 
void MW_CALL_CONV RemakePrintStackTrace(void);

extern LIB_Remake_C_API 
bool MW_CALL_CONV mlxClassifier(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Remake_C_API 
bool MW_CALL_CONV mlxEnsemble_testing(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                      *prhs[]);

extern LIB_Remake_C_API 
bool MW_CALL_CONV mlxEnsemble_training(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                       *prhs[]);

extern LIB_Remake_C_API 
bool MW_CALL_CONV mlxFeature_one(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Remake_C_API 
bool MW_CALL_CONV mlxFeature_two(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_Remake_C_API 
bool MW_CALL_CONV mlxFeatures_extract(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                      *prhs[]);

extern LIB_Remake_C_API 
bool MW_CALL_CONV mlxMain_FeatureClassifier(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                            *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_Remake
#define PUBLIC_Remake_CPP_API __declspec(dllexport)
#else
#define PUBLIC_Remake_CPP_API __declspec(dllimport)
#endif

#define LIB_Remake_CPP_API PUBLIC_Remake_CPP_API

#else

#if !defined(LIB_Remake_CPP_API)
#if defined(LIB_Remake_C_API)
#define LIB_Remake_CPP_API LIB_Remake_C_API
#else
#define LIB_Remake_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_Remake_CPP_API void MW_CALL_CONV Classifier(int nargout, mwArray& decide_result, const mwArray& cover_path, const mwArray& stego_path, const mwArray& Feature_test);

extern LIB_Remake_CPP_API void MW_CALL_CONV ensemble_testing(int nargout, mwArray& results, const mwArray& X, const mwArray& trained_ensemble);

extern LIB_Remake_CPP_API void MW_CALL_CONV ensemble_training(int nargout, mwArray& trained_ensemble, mwArray& results, const mwArray& Xc, const mwArray& Xs, const mwArray& settings);

extern LIB_Remake_CPP_API void MW_CALL_CONV Feature_one(int nargout, mwArray& f, const mwArray& IMAGE);

extern LIB_Remake_CPP_API void MW_CALL_CONV Feature_two(int nargout, mwArray& f, const mwArray& IMAGE, const mwArray& Tc, const mwArray& part);

extern LIB_Remake_CPP_API void MW_CALL_CONV features_extract(int nargout, mwArray& Features_6997, const mwArray& img_path);

extern LIB_Remake_CPP_API void MW_CALL_CONV main_FeatureClassifier(int nargout, mwArray& Result, const mwArray& img_path, const mwArray& cover_path, const mwArray& stego_path);

#endif
#endif
