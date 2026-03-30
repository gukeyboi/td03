
#include <vector>
#include <iostream>
#include <utility>  

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

int main()
{
    std::vector<int> array{12, 3, 7, 5, 6, 9, 2, 98};
    bubble_sort(array);
    for (int x : array)
        std::cout << x << ' ';
    std::cout << std::endl;

    return 0;
}





