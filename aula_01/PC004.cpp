#include <iostream>
#include <cmath>

int main() {
    int n;
    std::cin >> n;

    std::cout << n/5 + int(round(sqrt(n)))/5 << std::endl;

    return 0;
}
