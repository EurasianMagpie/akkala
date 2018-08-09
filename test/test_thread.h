
//  

#ifndef _____test_thread_h_____
#define _____test_thread_h_____

#include <stdatomic.h>
#include <utils/Thread.h>

#ifdef __ANDROID__

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
    TestThrd(bool testAtomic) : m_counter(0), m_test_atomic(testAtomic)
    {}

    virtual ~TestThrd()
    {}

protected:
    virtual bool threadLoop()
    {
        if (m_test_atomic)
        {
            return test_atomic_int();
        }
        else
        {
            return test_int();
        }
    }
    
    bool test_int()
    {
        if (m_counter > 1000000)
        {
            xlog("ab", "TestThrd::threadLoop<int> end | ref:%d\n", s_n_ref);
            return false;
        }
        m_counter++;
        s_n_ref++;
        //xlog("ab", "TestThrd::threadLoop ... | ref:%d\n", s_n_ref);
        return true;
    }
    
    bool test_atomic_int()
    {
        if (m_counter == 1000000)
        {
            int r = atomic_load(&s_ref);
            xlog("ab", "TestThrd::threadLoop<atomic> end | ref:%d\n", r);
            return false;
        }
        m_counter++;
        int r = atomic_fetch_add(&s_ref, 1);
        //xlog("ab", "TestThrd::threadLoop ... | ref:%d\n", r);
        return true;
    }

public:
    static volatile int s_n_ref;
    static atomic_int s_ref;
protected:
    bool m_test_atomic;
    int m_counter;
};

//static
volatile int TestThrd::s_n_ref = 0;
atomic_int TestThrd::s_ref = 0;

class TestThrdMgr
{
public:
    TestThrdMgr()
    {
    }
    virtual ~TestThrdMgr()
    {
    }

public:
    static TestThrdMgr & instance()
    {
        static TestThrdMgr _inst;
        return _inst;
    }

public:
    void start(int idx, bool _atomic)
    {
        if (idx >= 0 && idx < 2)
        {
            if (m_thrds[idx] == NULL)
            {
                m_thrds[idx] = new TestThrd(_atomic);
            }
            if (m_thrds[idx] != NULL)
            {
                m_thrds[idx]->run("testThrd1");
            }
        }
    }

    void stopAndClear(int idx)
    {
        if (idx >= 0 && idx < 2)
        {
            if (m_thrds[idx] != NULL)
            {
                m_thrds[idx]->requestExit();
                m_thrds[idx].clear();
            }
        }
    }
    
    void join()
    {
        int sz = sizeof(m_thrds) / sizeof(m_thrds[0]);
        for (int i=0; i<sz; i++) {
            if (m_thrds[i] != NULL)
            {
                m_thrds[i]->join();
            }
        }
    }

private:
    sp<Thread> m_thrds[2];
};

#ifndef _testMgr
#define _testMgr TestThrdMgr::instance()
#endif

void testCountInt()
{
    _testMgr.start(0, false);
    _testMgr.start(1, false);
    _testMgr.join();
}

void testCountAtomic()
{
    _testMgr.start(0, true);
    _testMgr.start(1, true);
    _testMgr.join();
}

void testCountStart(bool testAtomic)
{
    _testMgr.start(0, testAtomic);
    _testMgr.start(1, testAtomic);
}

void testCountStop()
{
    _testMgr.stopAndClear(0);
    _testMgr.stopAndClear(1);
}

#endif//_____test_thread_h_____
