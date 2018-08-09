
//  test_std_atomic.cpp

#include <stdatomic.h>

#include <jni.h>
#include <android/log.h>

#ifndef xlog
#define xlog(tag, ...)  __android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__)
#endif

class tr
{
public:
    tr() : m_ref(0)
    {
    }
    virtual ~tr() {}

public:
    void incRef()
    {
        int r = atomic_fetch_add(&m_ref, 1);
        xlog("ab", "tr::incRef | ref:%d\n", r);
    }

    void decRef()
    {
        int r = atomic_fetch_add(&m_ref, -1);
        xlog("ab", "tr::decRef | ref:%d\n", r);
        if (r == 0)
        {
            //delete this;
        }
    }

private:
    atomic_int m_ref;
};


void testAtomic()
{
    tr * p = new tr;
    p->incRef();
    p->decRef();
    delete p;
}

extern "C"
JNIEXPORT jint
JNICALL
Java_com_naiwen17_tatomic_TAtomic_testAtomic(
    JNIEnv *env,
    jobject /* this */) {
    testAtomic();
    return 0;
}