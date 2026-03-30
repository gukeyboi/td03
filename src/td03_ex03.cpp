
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include "ScopedTimer.hpp"

std::vector<int> generate_random_vector(size_t const size, int const max = 100) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max;} );
    return vec;
}

void quick_sort(std::vector<int> & vec, size_t const left, size_t const right) {
    if (left >= right){
        return;
    }
    size_t flag = right;
    for (size_t i = left; i < right; i++)
    {
        if (vec[i] > vec[right]) {
            flag = i;
        break;
        }
    }

    for (size_t i = flag+1; i < right; i++)
    {
        if (vec[i] < vec[right]) {
            std::swap(vec[i], vec[flag]);
            flag = flag + 1;
        }
    }
    std::swap(vec[flag], vec[right]);
    if(flag > 0) {
        quick_sort(vec, left, flag-1);
    }
    quick_sort(vec, flag+1, right);
    
    

}
void quick_sort(std::vector<int> & vec) {
    quick_sort(vec, 0, vec.size() - 1);

}

void bubble_sort(std::vector<int> &vec)
{
    size_t n = vec.size();
    for (size_t i = 0; i + 1 < n; ++i) {
        bool swapped = false;
        for (size_t j = 1; j < n - i; ++j) {
            if (vec[j - 1] > vec[j]) {
                std::swap(vec[j - 1], vec[j]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

int main() {
    int const size = 10000;

    std::vector<int> array {generate_random_vector(size)};

    {
        ScopedTimer timer("bubble sort");
        bubble_sort(array);
    }

    array = generate_random_vector(size);
    {
        ScopedTimer timer("standard");
        std::sort(array.begin(), array.end());
    }

    array = generate_random_vector(size);
    {
        ScopedTimer timer("quick sort");
        quick_sort(array);
    }

    return 0;
}





