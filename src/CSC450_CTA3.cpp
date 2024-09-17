/*--------------------------------------------------------
Program Name: Integer Pointer Program
Author: Zoheb Khan
Date: 08/28/24
----------------------------------------------------------
Pseudocode:
//Mutex for synchronizing output
//Lock the mutex
//Lock the mutex
//Ask the user for three integer values
//Dynamically allocate memory for the three variables
//Store the values in the dynamically allocated memory
//Create three threads, passing the pointers to the functions
//Wait for the threads to finish execution
//Deallocate the memory
----------------------------------------------------------
Program Inputs: Three user input integer values
Program Outputs: The values of the pointers
--------------------------------------------------------*/
#include <windows.h>  // For Windows thread functions
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  //Mutex for synchronizing output

// Function to assign the thread to a specific core and print its pointer value
void threadTask(int* ptr, DWORD_PTR coreMask) {
    HANDLE current_thread = GetCurrentThread();  //Get the current thread handle

    //Set the thread's CPU affinity to the specified core using coreMask
    if (SetThreadAffinityMask(current_thread, coreMask) == 0) {
        std::cerr << "Error setting thread affinity!" << std::endl;
    }

    //Lock the mutex to synchronize output
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Thread running on core with mask: " << coreMask << " and pointer value: " << *ptr << std::endl;
    }
}

int main() {
    //Ask the user for three integer values
    int val1, val2, val3;
    std::cout << "Enter three integer values: " << std::endl;
    std::cin >> val1 >> val2 >> val3;

    //Dynamically allocate memory for the three variables
    int* ptr1 = new int;
    int* ptr2 = new int;
    int* ptr3 = new int;

    //Store the values in the dynamically allocated memory
    *ptr1 = val1;
    *ptr2 = val2;
    *ptr3 = val3;

    //Core 0 has a mask of 0x1, Core 1 has a mask of 0x2, Core 2 has a mask of 0x4
    std::thread t1(threadTask, ptr1, 0x1);  //Assign thread to core 0
    std::thread t2(threadTask, ptr2, 0x2);  //Assign thread to core 1
    std::thread t3(threadTask, ptr3, 0x4);  //Assign thread to core 2

    //Wait for the threads to finish execution
    t1.join();
    t2.join();
    t3.join();

    //Deallocate the memory
    delete ptr1;
    delete ptr2;
    delete ptr3;

    return 0;
}

