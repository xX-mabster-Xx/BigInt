#include <iostream>
#include "BigInt.h"




int main() {
    BigInt c(1000000000 * 9);
    int k = 1290;
    BigInt a(k);
    //std::cout << multbymax(a);
    //std::cout << INT32_MAX << "\n";
    //unsigned long long k = 100000000000;
    //std::cout << k << "\n";
    BigInt d((unsigned long long)80);
    BigInt b((unsigned long long)90000000000);
    int j = 8;

    dbg__print(std::cout, d * b);
    //std::cout << d * b << "\n";
}
