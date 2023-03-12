//
// Created by Goh Chang Ming Clement on 3/12/23.
//

#include "vanilla_threads.h"
#include <chrono>
#include <thread>
#include <iostream>

void mockDatabaseCall() {
    /**
     * Mocks a database call that takes 3 seconds
     */
    using namespace std::literals::chrono_literals;
    std::cout << "database call started on second thread. Second thread id: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(1s);
    std::cout << "database call completed on second thread" << std::endl;
}


int main() {
    // c++ 14
    std::cout << "C++ version: " << __cplusplus << '\n';
    std::cout << "Main thread starts. Main thread id is: " << std::this_thread::get_id() << std::endl;

    std::cout << "Starting a second thread to start the database call" << std::endl;
    // create a second thread
    std::thread secondThread(mockDatabaseCall);

    // suspend the current main thread till the second thread finishes
    secondThread.join();

    std::cout << "Main thread finishes" << std::endl;

}