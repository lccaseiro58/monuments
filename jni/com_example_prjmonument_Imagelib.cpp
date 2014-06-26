#include "com_example_prjmonument_Imagelib.h"
#include "Common/Image.h"
#include "GeocodeMonuments.h"

void processDescriptors(cv::Mat input, cv::Mat result){
	GeocodeMonuments* gc = new GeocodeMonuments( DET_FAST, DES_SIFT, DESM_FB);
	gc->processDC(input,result);
}

JNIEXPORT void JNICALL Java_com_example_prjmonument_Imagelib_getNativeDescriptorsfromMat
  (JNIEnv *env, jobject obj, jlong img, jlong result){
	processDescriptors( *((cv::Mat*)img) , *((cv::Mat*)result));

}
