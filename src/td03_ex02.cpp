
#include <vector>
#include <iostream>
#include <utility>  

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


int main()
{
    std::vector<int> array{12, 3, 7, 5, 6, 8, 2, 9};
    quick_sort(array);
    
    std::cout << "[";
    for(int value : array) {
        std::cout << value << ", ";
    }
    std::cout << "]" << std::endl;
    return 0;
}





