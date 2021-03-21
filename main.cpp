#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <ctime>
#include <math.h>
#include <chrono>
#include <gmp.h>
#include <future>

#define FACTOR_BASE "../factor_base.txt"
#define PRIMES_COUNT 100000
#define G 1000
#define N 1774751
#define UNUSED(value) (void)value

static inline long long lg(long long p) { return log2l(p) * 100.0; }
static inline long long absl(long long x) { return x < 0 ? -x : x; }

double LogE(mpq_t m_op)
{
    // log(a/b) = log(a) - log(b)
    // And if a is represented in base B as:
    // a = a_N B^N + a_{N-1} B^{N-1} + ... + a_0
    // => log(a) \approx log(a_N B^N)
    // = log(a_N) + N log(B)
    // where B is the base; ie: ULONG_MAX

    static double logB = log(ULONG_MAX);

    // Undefined logs (should probably return NAN in second case?)
    if (mpz_get_ui(mpq_numref(m_op)) == 0 || mpz_sgn(mpq_numref(m_op)) < 0)
        return -INFINITY;

    // Log of numerator
    double lognum = log(mpq_numref(m_op)->_mp_d[abs(mpq_numref(m_op)->_mp_size) - 1]);
    lognum += (abs(mpq_numref(m_op)->_mp_size) - 1) * logB;

    // Subtract log of denominator, if it exists
    if (abs(mpq_denref(m_op)->_mp_size) > 0)
    {
        lognum -= log(mpq_denref(m_op)->_mp_d[abs(mpq_denref(m_op)->_mp_size) - 1]);
        lognum -= (abs(mpq_denref(m_op)->_mp_size) - 1) * logB;
    }
    return lognum;
}

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
    long long B = 4 * expl(sqrtl(logl(N) * logl(logl(N))) / 2.0);
    long long M = B / 2;
    long long ln_a = 0.5 * (1 + lg(N)) - lg(M);

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
    POLE.reserve(P.size() - 1); // кажется что его размерность равна максимальному простому числу в P

    std::cout << "M=" << M << std::endl;
    std::cout << "P[P.size()-1]=" << P[P.size() - 1] << std::endl;
    std::cout << "G=" << G << std::endl;

    for (long long i = 0; i < P[P.size() - 1]; ++i)
        POLE.push_back(lg(absl((i * i) - (M * M) / 2)) + ln_a);

    // main cycle

    auto time_start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < P.size(); ++i)
    {
        long long n1{0};
        long long n2{0};
        // generate random diffrent n1 & n2 less then P[i]
        generate_n1_n2(P[i], n1, n2);

        //std::cout << "start iteration for n1=" << n1 << ", n2=" << n2 << " less then "<< P[i] << std::endl;
        while ((n1 < M) || (n2 < M))
        {
            POLE[n1] = POLE[n1] - lg(P[i]);
            POLE[n2] = POLE[n2] - lg(P[i]); 
            n1 += P[i];
            n2 += P[i];
            // std::cout << "- n1=" << n1 << ", n2=" << n2 << std::endl;
        }
    }
    auto time_end = std::chrono::high_resolution_clock::now();
    std::cout << "time:" << std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start).count() << std::endl;

    // get smooth numbers
    /*
    for (size_t i = 0; i < POLE.size(); ++i)
        if (POLE[i] < G)
            std::cout << POLE[i] <<" ";
    std::cout << std::endl;*/
    return 1;
}