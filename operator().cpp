#include <iostream>
#include <thread>

void printHello() {
    std::cout << "Hello World!!!" << std::endl;
}

class TestCallable {
    public:
        void operator()(int value) {
            printHello();
            std::cout << "value =  " << value << std::endl;
        }
};

// void testFunction(TestCallable value, int forTestInt) {
//     std::cout << "testFunction " << std::endl;
//     value(forTestInt);
//     return;
// }

int main() {
    TestCallable f;
    // testFunction(f, 5);
    std::thread testThread(TestCallable(), 5);
    testThread.join();
    
    return 0;
}
