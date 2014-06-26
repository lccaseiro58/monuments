LOCAL_PATH := $(call my-dir)

#OPENCV_CAMERA_MODULES:=on
#OPENCV_INSTALL_MODULES:=on

include $(CLEAR_VARS)
LOCAL_MODULE    := nonfree
LOCAL_SRC_FILES := libnonfree.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := opencv_java
LOCAL_SRC_FILES := libopencv_java.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

include /home/luis/Transferências/OpenCV-2.4.8-android-sdk/sdk/native/jni/OpenCV.mk


LOCAL_SHARED_LIBRARIES := nonfree opencv_java
LOCAL_SRC_FILES :=  Common/Image.cpp Common/Monument.cpp Features/TrackFeature.cpp Features/FeatureHandler.cpp
LOCAL_SRC_FILES += VideoTrack.cpp GeocodeMonuments.cpp com_example_prjmonument_Imagelib.cpp

LOCAL_LDLIBS += -ldl -llog	

LOCAL_MODULE     :=ndklib

include $(BUILD_SHARED_LIBRARY)
