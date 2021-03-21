#include <iostream>
#include <vector>

#define COUNT 500000

auto main() -> int{
    std::vector<long long> primes;
    primes.reserve(COUNT);


    primes.push_back(2);
    primes.push_back(3);
    primes.push_back(5);
    primes.push_back(7);

    long long i {9};

    while(primes.size()<COUNT){
        bool divided {false};

        for(size_t j=0;(j<primes.size())&&(!divided);++j)
            if((i%primes[j])==0) divided = true;

        if(!divided)  primes.push_back(i);
        
        ++i;
    };

    for(size_t j=0;j<primes.size();++j) std::cout << primes[j] << "\r\n";

    return 1;
}