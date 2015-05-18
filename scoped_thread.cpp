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

class scoped_thread {
    private:
        std::thread m_thread;
    public:
        explicit scoped_thread(std::thread&& t): m_thread(std::move(t)) {
            if ( !m_thread.joinable() ) {
                throw std::logic_error("No thread");
            }
        }
        ~scoped_thread() {
            m_thread.join();
        }
        scoped_thread(scoped_thread const&) = delete;
        scoped_thread& operator=(scoped_thread const&) = delete;
};

void shortLoopWork() {
    for ( int i = 0; i< 10; i++ ) {
        std::cout << "i = " << i << std::endl;
    }
}

void test () {
    int some_local_state = 1000000000;
    scoped_thread t(std::move(std::thread(func(some_local_state)))) ;
    shortLoopWork();
}

int main() {
    std::thread inMain(test );
    inMain.join();
    
    return 0;
}
