
//  

#include <stdatomic.h>
#include <utils/Thread.h>

#include <jni.h>
#include <android/log.h>

#ifndef xlog
#define xlog(tag, ...)  __android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__)
#endif


using namespace android;

class TestThrd : virtual public Thread
{
public:
    TestThrd() : m_counter(0)
    {}

    virtual ~TestThrd()
    {}

protected:
    virtual bool threadLoop()
    {
        /*if (m_counter > 1000000)
        {
            int r = atomic_load(&s_ref);
            xlog("ab", "TestThrd::threadLoop end | ref:%d\n", r);
            return false;
        }
        m_counter++;
        int r = atomic_fetch_add(&s_ref, 1);
        xlog("ab", "TestThrd::threadLoop ... | ref:%d\n", r);//*/

        xlog("ab", "TestThrd::threadLoop ... \n");
        
        return true;
    }

public:
    static atomic_int s_ref;
protected:
    int m_counter;
};

//static 
atomic_int TestThrd::s_ref = 0;

class TestThrdMgr
{
public:
    TestThrdMgr()
    {
        //m_thrds = new sp<Thread>[2];
    }
    virtual ~TestThrdMgr()
    {
        /*if (m_thrds)
        {
            delete[] m_thrds;
        }//*/
    }

public:
    static TestThrdMgr & instance()
    {
        static TestThrdMgr _inst;
        return _inst;
    }

public:
    void start(int idx)
    {
        if (idx >= 0 && idx < 2)
        {
            if (m_thrds[idx] == NULL)
            {
                m_thrds[idx] = new TestThrd();
            }
            if (m_thrds[idx] != NULL)
            {
                m_thrds[idx]->run("testThrd1");
            }
        }
    }

    void stop(int idx)
    {
        if (idx >= 0 && idx < 2)
        {
            if (m_thrds[idx] != NULL)
            {
                m_thrds[idx]->requestExit();
            }
        }
    }

private:
    sp<Thread> m_thrds[2];
};

#define _testMgr TestThrdMgr::instance()

extern "C"
JNIEXPORT jint
JNICALL
Java_com_naiwen17_tatomic_TAtomic_testThreadStart(
    JNIEnv *env,
    jobject /* this */) {
    xlog("ab", "Java_com_naiwen17_tatomic_TAtomic_testThreadStart begin\n");
    _testMgr.start(0);
    //_testMgr.start(1);
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
    _testMgr.stop(0);
    //_testMgr.stop(1);
    xlog("ab", "Java_com_naiwen17_tatomic_TAtomic_testThreadStop end\n");
    return 0;
}