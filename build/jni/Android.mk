LOCAL_PATH :=$(call my-dir)


_ROOT := $(LOCAL_PATH)/../..
_INC := $(_ROOT)/include
_SRC := $(_ROOT)/src
_SRC_CUTILS := $(_ROOT)/src/cutils
_SRC_UTILS := $(_ROOT)/src/utils
_SRC_FDN := $(_ROOT)/src/foundation
_TEST := $(_ROOT)/test/jni

L_SRC_CUTILS := $(_SRC_CUTILS)/threads.c
L_SRC_UTILS := $(_SRC_UTILS)/RefBase.cpp $(_SRC_UTILS)/Log.cpp $(_SRC_UTILS)/Timers.cpp $(_SRC_UTILS)/Threads.cpp $(_SRC_UTILS)/VectorImpl.cpp $(_SRC_UTILS)/SharedBuffer.cpp
L_SRC_FOUNDATION := $(_SRC_FDN)/ALooper.cpp $(_SRC_FDN)/AString.cpp $(_SRC_FDN)/ALooperRoster.cpp $(_SRC_FDN)/AMessage.cpp $(_SRC_FDN)/ABuffer.cpp $(_SRC_FDN)/AAtomizer.cpp $(_SRC_FDN)/AHandler.cpp $(_SRC_FDN)/hexdump.cpp

include $(CLEAR_VARS)
LOCAL_MODULE := ab
LOCAL_SRC_FILES := $(L_SRC_CUTILS) $(L_SRC_UTILS) $(L_SRC_FOUNDATION) $(_TEST)/test_thread.cpp
LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_C_INCLUDES := $(_INC)
LOCAL_CFLAGS := -DHAVE_PTHREADS=1 -DHAVE_SYS_UIO_H=1
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog -latomic

include $(BUILD_SHARED_LIBRARY)