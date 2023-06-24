#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

const int NUM_PHILOSOPHERS = 5;

mutex chopsticks[NUM_PHILOSOPHERS];

void philosopher(int id) {
    int min_chopstick = min(id,(id + 1) % NUM_PHILOSOPHERS);
    int max_chopstick = max(id,(id + 1) % NUM_PHILOSOPHERS);
    while (true){

    chopsticks[min_chopstick].lock();
    chopsticks[max_chopstick].lock();
    

    // Eat for a random amount of time.
    cout << "Philosopher " << id << " is eating." << endl;
    this_thread::sleep_for(chrono::milliseconds(rand() % 1000));

    // Release the chopsticks.
    chopsticks[min_chopstick].unlock();
    chopsticks[max_chopstick].unlock();

    // Think for a random amount of time.
    cout << "Philosopher " << id << " is thinking." << endl;
    this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
    }
}

int main() {
    srand(time(NULL));

    // Create threads for each philosopher.
    thread philosophers[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i] = thread(philosopher, i);
    }
    // Wait for all threads to finish.
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i].join();
    }
    return 0;
}
