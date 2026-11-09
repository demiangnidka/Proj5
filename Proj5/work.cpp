#include "work.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <syncstream>

void compute(const std::string& name, int duration_sec) {
    std::this_thread::sleep_for(std::chrono::seconds(duration_sec));
    std::osyncstream(std::cout) << name << '\n';
}

void slow(const std::string& name) {
    compute(name, 7);
}

void quick(const std::string& name) {
    compute(name, 1);
}

void work() {
    auto start_time = std::chrono::steady_clock::now();

    std::future<void> a2_future = std::async(std::launch::async, slow, "A2");

    quick("A1");
    quick("C1");
    quick("C2");
    quick("D2"); 

    a2_future.get();

    slow("B");
    quick("D1");

    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::osyncstream(std::cout) << "Time: " << elapsed.count() << " s\n"
                                << "Work is done!\n";
}
