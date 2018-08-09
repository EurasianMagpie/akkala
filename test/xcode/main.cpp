
//

#include "../test_thread.h"

int main(int argc, const char * argv[]) {
    
    sp<TestThrd> spThrd = new TestThrd();
    spThrd->run();
    spThrd->join();
    
    return 0;
}
