
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>


int search(std::vector<int> & vec, size_t const left, size_t const right, int searched_value) {
    int middle = (right + left) / 2;

    if (searched_value == vec[middle]) {
        return middle;
    }
    if (left >= right) {
        return -1;
    }
    if (searched_value < vec[middle]) {
        return search(vec, left, middle -1, searched_value);
    }
    return search(vec, middle+1, right, searched_value);
    
}

int main() {
    int const size = 10000;
    std::vector<int> array {3, 5, 7, 8, 13, 15, 26};
    std::cout << "je cherche le 13 : " << search(array, 0, array.size()-1, 13) << std::endl;
    return 0;
}





