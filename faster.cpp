#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;

std::atomic<int> v(0);

void incrementWithoutLock(int n) {
    for (int i = 0; i < n; i++) {
        v++;
    }
}

int main() {
    int n = 1000000000;
    auto start_time = chrono::high_resolution_clock::now();
    std::thread t1(incrementWithoutLock, n);
    std::thread t2(incrementWithoutLock, n);
    
    t1.join();
    t2.join();
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed_time = end_time - start_time;
    cout << "Time elapsed: " << elapsed_time.count() << " ms" << endl;
    std::cout << "Result: " << v << std::endl;
    return 0;
}