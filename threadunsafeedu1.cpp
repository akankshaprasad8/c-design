#include <iostream>
#include <thread>
#include <mutex>
#include <random>

// Class to demonstrate race conditions
class RaceCondition {
public:
    // Method to run the test
    static void runTest() {
        RaceCondition rc;

        // Create threads
        std::thread thread1(&RaceCondition::printer, &rc);
        std::thread thread2(&RaceCondition::modifier, &rc);

        // Wait for threads to finish
        thread1.join();
        thread2.join();
    }

private:
    int randInt;
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;
    std::mutex mtx;

    // Constructor to initialize random number generator
    RaceCondition() : generator(std::random_device{}()), distribution(0, 999) {}

    // Printer method to check and print randInt
    void printer() {
        int i = 1000000;
        while (i != 0) {
            std::lock_guard<std::mutex> lock(mtx);
            if (randInt % 5 == 0) {
                if (randInt % 5 != 0) {
                    std::cout << randInt << std::endl;
                }
            }
            i--;
        }
    }

    // Modifier method to generate random numbers
    void modifier() {
        int i = 1000000;
        while (i != 0) {
            std::lock_guard<std::mutex> lock(mtx);
            randInt = distribution(generator);
            i--;
        }
    }
};

// Main function to run the demonstration
int main() {
    RaceCondition::runTest();
    return 0;
}
