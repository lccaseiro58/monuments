#include "com_example_prjmonument_NativeServer.h"
#include "Common/Image.h"
#include "Common/Monument.h"
#include "GeocodeMonuments.h"

void processRes(cv::Mat input, cv::Mat server, int* size){
	GeocodeMonuments* gc = new GeocodeMonuments( DET_FAST, DES_SIFT, DESM_FB);
	Image* img1 = new Image(input);
	img1->setDescriptors(input);
	Image* img2 = new Image(server);
	img2->setDescriptors(server);

}

JNIEXPORT void JNICALL Java_com_example_prjmonument_NativeServer_nativeRes
  (JNIEnv *env, jobject obj, jlong input, jlong res, jint u){
	processRes( *((cv::Mat*)img) , *((cv::Mat*)result),url);
}

