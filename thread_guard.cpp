#include <iostream>
#include <thread>

struct func {
    private:
        int& m_i;
    public:
        func(int& i): m_i(i) {}
        void operator()() {
            std::cout << "test = " << m_i << std::endl;
            for ( unsigned i = 0; i < m_i; i++ ) {
                
            }
            std::cout << "long work in thread finished" << std::endl;
        }
};

class thread_guard {
    private:
        std::thread& m_thread;
    public:
        explicit thread_guard(std::thread& t): m_thread(t) {
            
        }
        ~thread_guard() {
            if ( m_thread.joinable() ) {
                m_thread.join();
            }
        }
        thread_guard(thread_guard const&) = delete;
        thread_guard& operator=(thread_guard const&) = delete;
};

void shortLoopWork() {
    for ( int i = 0; i< 10; i++ ) {
        std::cout << "i = " << i << std::endl;
    }
}

int main() {
    int some_local_state = 1000000000;
    std::thread t((func(some_local_state)));
    
    thread_guard g(t);
    
    shortLoopWork();
    
    return 0;
}
