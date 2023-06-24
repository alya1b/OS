#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

const int NUM_PHILOSOPHERS = 5;

mutex chopsticks[NUM_PHILOSOPHERS];

void philosopher(int id) {
    while (true){
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    // Make sure odd philosophers pick up left chopstick first,
    // and even philosophers pick up right chopstick first.
    if (id % 2 == 1) {
        chopsticks[left_chopstick].lock();
        chopsticks[right_chopstick].lock();
    } else {
        chopsticks[right_chopstick].lock();
        chopsticks[left_chopstick].lock();
    }

    // Eat for a random amount of time.
    cout << "Philosopher " << id << " is eating." << endl;
    this_thread::sleep_for(chrono::milliseconds(rand() % 1000));

    // Release the chopsticks.
    chopsticks[left_chopstick].unlock();
    chopsticks[right_chopstick].unlock();

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
