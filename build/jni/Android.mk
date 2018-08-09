LOCAL_PATH :=$(call my-dir)


_ROOT := $(LOCAL_PATH)/../..
_INC := $(_ROOT)/include
_SRC := $(_ROOT)/src
_SRC_CORE := $(_ROOT)/src/core
_SRC_UTILS := $(_ROOT)/src/utils
_TEST := $(_ROOT)/test

include $(CLEAR_VARS)
LOCAL_MODULE := ab
LOCAL_SRC_FILES := $(_SRC_CORE)/threads.c $(_SRC_UTILS)/RefBase.cpp $(_SRC_UTILS)/Log.cpp $(_SRC_UTILS)/Timers.cpp $(_SRC_UTILS)/Threads.cpp $(_TEST)/test_thread.cpp
LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_C_INCLUDES := $(_INC)
LOCAL_CFLAGS := -DHAVE_PTHREADS=1
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog -latomic

include $(BUILD_SHARED_LIBRARY)