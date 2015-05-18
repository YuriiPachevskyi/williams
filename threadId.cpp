#include <iostream>
#include <thread>

void some_core_part_of_algorithm(std::thread::id master_thread) {
    if ( std::this_thread::get_id() == master_thread ) {
        std::cout << "mastert thread" << std::endl;
    }
    std::cout << "common thread" << std::endl;
}

int main() {
    std::thread::id master_thread = std::this_thread::get_id();
    some_core_part_of_algorithm(master_thread);
    std::thread t(some_core_part_of_algorithm, master_thread);

    t.join();

    return 0;
}
