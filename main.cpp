#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <ctime>
#include <math.h>

#define FACTOR_BASE "../factor_base.txt"
#define PRIMES_COUNT 100000
#define G 1000
#define N 1774751

static inline long long lg(long long p) { return log2l(p) * 100.0; }

auto main() -> int
{
    std::vector<long long> P;
    P.reserve(PRIMES_COUNT);

    // loading P array
    std::ifstream istr(FACTOR_BASE);
    std::istream_iterator<long long> eos; // end-of-stream iterator
    std::istream_iterator<long long> iit(istr);
    while (iit != eos)
        P.push_back(*(iit++));

    //for(auto i: P)
    //    std::cout  << lg(i) << "\r\n";

    // calculate constance
    long long B = 4 * expl(sqrtl(lg(N) * lg(lg(N))) / 2.0);
    long long M = B / 2;
    
    // generate ri
    std::srand(std::time(nullptr));
    auto generate_n1_n2 = [](long long Pi, long long &n1, long long &n2) {
        do
        {
            n1 = std::rand() % Pi;
            n2 = std::rand() % Pi;
        } while (n1 == n2);
    };

    // init POLEE - непонятно
    std::vector<long long> POLE;
    POLE.reserve(P.size()); // кажется что его размерность равна максимальному простому числу в P

    for (size_t i = 0; i < P.size(); ++i)
    {
       // POLE[i] = lg();
    }



    // main cycle

    for (size_t i = 0; i < P.size(); ++i)
    {
        long long n1{0};
        long long n2{0};
        // generate random diffrent n1 & n2 less then P[i]
        generate_n1_n2(P[i], n1, n2);

        while ((n1 < M) || (n2 < M))
        {
            POLE[n1] = POLE[n1] - lg(P[i]);
            POLE[n2] = POLE[n2] - lg(P[i]); // какая то фигня, так как n1<P[i] а оно может быть больше размерности POLE
            n1 += P[i];
            n2 += P[i];
        }
    }

    // get smooth numbers
    for (size_t i = 0; i < POLE.size(); ++i)
        if (POLE[i] < G)
            std::cout << POLE[i] << std::endl;
            
    return 1;
}