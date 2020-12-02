LOCAL_PATH := $(call my-dir)
 

include $(CLEAR_VARS)
LOCAL_CFLAGS += -Wno-unused-result
LOCAL_CFLAGS += -D__ANDROID_O
LOCAL_CFLAGS += -Wno-unused-variable
LOCAL_CFLAGS += -Wno-sign-compare
LOCAL_CFLAGS += -Wno-pointer-sign
LOCAL_CFLAGS += -Wno-unused-function
LOCAL_CFLAGS += -Wno-unused-parameter
LOCAL_CFLAGS += -Wno-unused-variable
LOCAL_CFLAGS += -Wno-implicit-function-declaration
LOCAL_CFLAGS += -Wno-unused-result
LOCAL_CPPFLAGS += -fexceptions



LOCAL_MODULE := native_server
LOCAL_SRC_FILES := \
    ./callbacks/IDataReaderCallback.cpp \
    INServer.cpp \
    NativeServer.cpp


LOCAL_SHARED_LIBRARIES := \
    libstdc++ \
    libcutils \
    libutils \
    libbinder \
    libandroid \
    libcompiler_rt \
    liblog

LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

