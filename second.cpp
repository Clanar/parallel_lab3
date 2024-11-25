#include <iostream>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <mutex>

std::mutex mutex;

void countElements(const int* arr, int size, int start, int end, int& count, int& max) {
    int local_count = 0;
    int local_max = 0;

    for (int i = start; i < end; ++i) {
        if (arr[i] > 10) {
            local_count++;
            if (arr[i] > local_max) {
                local_max = arr[i];
            }
        }
    }

    {
        std::lock_guard<std::mutex> lock(mutex);
        count += local_count;
        if (local_max > max) {
            max = local_max;
        }
    }
}

int main() {
    int size = 10000000;
    int count = 0;
    int max = 0; 
    int num_threads = 20;
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    int* arr = new int[size];
    
    //std::cout << "Array:\n";
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 101;
        //std::cout << arr[i] << " "; 
    }
    //std::cout << std::endl;

    auto start = std::chrono::high_resolution_clock::now(); 

    std::thread* threads = new std::thread[num_threads];

    int chunk_size = size / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int start_index = i * chunk_size;
        int end_index = (i == num_threads - 1) ? size : (i + 1) * chunk_size;
        threads[i] = std::thread(countElements, arr, size, start_index, end_index, std::ref(count), std::ref(max));
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 

    std::cout << "Number of elements larger than 10: " << count << std::endl;
    std::cout << "The largest number greater than 10 (max 100): " << max << std::endl;
    std::cout << "Time: " << duration.count() << " ms" << std::endl;

    delete[] arr;
    delete[] threads;

    return 0;
}
