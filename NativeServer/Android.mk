LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional


LOCAL_SRC_FILES := \
    TestBinderService.cpp \
    hao/sui/nativebinder/IMyAidlTestCallback.cpp \
    hao/sui/nativebinder/IMyAidlTestInterface.cpp

LOCAL_SHARED_LIBRARIES:= libcutils libutils libbinder

LOCAL_MODULE := TestBinderService

include $(BUILD_EXECUTABLE)
