#include <iostream>
#include <chrono>
#include <cstdlib>

int main() {
    int size = 10000000;
    int* arr = new int[size];
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    //std::cout << "Array:\n";
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 101; 
        //std::cout << arr[i] << " ";
    }
    //std::cout << std::endl;

    int count = 0;
    int max = 0; 
    auto start = std::chrono::high_resolution_clock::now(); 

    for (int i = 0; i < size; ++i) {
        if (arr[i] > 10) {
            count++;
            if (arr[i] > max) {
                max = arr[i];
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 

    std::cout << "Number of elements greater than 10: " << count << std::endl;
    std::cout << "The largest number greater than 10 (max 100): " << max << std::endl;
    std::cout << "Time: " << duration.count() << " ms" << std::endl;

    delete[] arr;

    return 0;
}
