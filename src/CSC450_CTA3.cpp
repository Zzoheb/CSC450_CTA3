#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // Mutex for synchronizing output

void thread1(int* ptr1) {
    std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex
    std::cout << "Thread 1 pointer value: " << *ptr1 << std::endl;
}

void thread2(int* ptr2) {
    std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex
    std::cout << "Thread 2 pointer value: " << *ptr2 << std::endl;
}

void thread3(int* ptr3) {
    std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex
    std::cout << "Thread 3 pointer value: " << *ptr3 << std::endl;
}

int main() {
    // Ask the user for three integer values
    int val1, val2, val3;
    std::cout << "Enter three integer values: " << std::endl;
    std::cin >> val1 >> val2 >> val3;

    // Dynamically allocate memory for the three variables
    int* ptr1 = new int;
    int* ptr2 = new int;
    int* ptr3 = new int;

    // Store the values in the dynamically allocated memory
    *ptr1 = val1;
    *ptr2 = val2;
    *ptr3 = val3;

    // Create three threads, passing the pointers to the functions
    std::thread t1(thread1, ptr1);
    std::thread t2(thread2, ptr2);
    std::thread t3(thread3, ptr3);

    // Wait for the threads to finish execution
    t1.join();
    t2.join();
    t3.join();

    // Deallocate the memory
    delete ptr1;
    delete ptr2;
    delete ptr3;

    return 0;
}
