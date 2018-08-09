
//  

#include "../test_thread.h"
#include <jni.h>

extern "C"
JNIEXPORT jint
JNICALL
Java_com_naiwen17_tatomic_TAtomic_testThreadStart(
    JNIEnv *env,
    jobject /* this */,
    jboolean testAtomic) {
    xlog("ab", "Java_com_naiwen17_tatomic_TAtomic_testThreadStart begin\n");
    testCountStart(testAtomic == JNI_TRUE);
    xlog("ab", "Java_com_naiwen17_tatomic_TAtomic_testThreadStart end\n");
    return 0;
}

extern "C"
JNIEXPORT jint
JNICALL
Java_com_naiwen17_tatomic_TAtomic_testThreadStop(
    JNIEnv *env,
    jobject /* this */) {
    xlog("ab", "Java_com_naiwen17_tatomic_TAtomic_testThreadStop begin\n");
    testCountStop();
    xlog("ab", "Java_com_naiwen17_tatomic_TAtomic_testThreadStop end\n");
    return 0;
}