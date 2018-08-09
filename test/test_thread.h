
//  

#ifndef _____test_thread_h_____
#define _____test_thread_h_____

#include <stdatomic.h>
#include <utils/Thread.h>

#ifdef __ANDROID__

#include <jni.h>
#include <android/log.h>
#ifndef xlog
#define xlog(tag, ...)  __android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__)
#endif

#else
#include <stdio.h>
#ifndef xlog
#define xlog(tag, ...)  printf(__VA_ARGS__)
#endif

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
        if (m_counter > 1000000)
        {
            int r = atomic_load(&s_ref);
            xlog("ab", "TestThrd::threadLoop end | ref:%d\n", r);
            return false;
        }
        m_counter++;
        int r = atomic_fetch_add(&s_ref, 1);
        xlog("ab", "TestThrd::threadLoop ... | ref:%d\n", r);//*/

        //xlog("ab", "TestThrd::threadLoop ... \n");
        
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

#ifndef _testMgr
#define _testMgr TestThrdMgr::instance()
#endif

void testStart()
{
    _testMgr.start(0);
    //_testMgr.start(1);
}

void testStop()
{
    _testMgr.stop(0);
    //_testMgr.stop(1);
}

#endif//_____test_thread_h_____
