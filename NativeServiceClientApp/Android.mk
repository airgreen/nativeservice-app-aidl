LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)
 
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := $(call all-subdir-java-files)
LOCAL_PACKAGE_NAME := DeveloperTools
LOCAL_CERTIFICATE := platform
LOCAL_MANIFEST_FILE := app/src/main/AndroidManifest.xml
LOCAL_RESOURCE_DIR := $(LOCAL_PATH)/app/src/main/res
 
LOCAL_PROGUARD_FLAG_FILES := proguard.cfg
LOCAL_PROGUARD_ENABLED := full
 
include $(BUILD_PACKAGE)

