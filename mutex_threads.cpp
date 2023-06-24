#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
mutex mtx;

int shared_variable = 0;

void yes_mutex(int n) {
    for (int i = 0; i < n; i++) {
        mtx.lock();
        shared_variable++;
        mtx.unlock();
    }
}

void no_mutex(int n) {
    for (int i = 0; i < n; i++) {
        shared_variable++;
    }
}

int main() {
    int n = 100000;
    //WITH MUTEX
    auto start_time = chrono::high_resolution_clock::now();
    std::thread t1(yes_mutex, n);
    std::thread t2(yes_mutex, n);
    t1.join();
    t2.join();
    std::cout << "With mutex: " << shared_variable << std::endl;
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed_time = end_time - start_time;
    cout << "Time elapsed with mutex: " << elapsed_time.count() << " ms" << endl;
    shared_variable = 0;
    //NO MUTEX
    start_time = chrono::high_resolution_clock::now();
    std::thread t3(no_mutex, n);
    std::thread t4(no_mutex, n);
    t3.join();
    t4.join();
    std::cout << "Without mutex: " << shared_variable << std::endl;
    end_time = chrono::high_resolution_clock::now();
    elapsed_time = end_time - start_time;
    cout << "Time elapsed without mutex: " << elapsed_time.count() << " ms" << endl;
    return 0;
}