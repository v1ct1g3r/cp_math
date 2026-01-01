#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Enables automatic conversion between C++ STL and Python types
#include <bits/stdc++.h>

namespace py = pybind11;

// Generates all prime numbers up to n using the Sieve of Eratosthenes
std::vector<int> sieve(const int &n)
{
    std::vector<int> primes;
    if (n < 2) return primes;
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (long long p = 2; p <= n; p++) {
        if (is_prime[p]) {
            primes.push_back(p);
            // Optimization: start marking from p*p to avoid redundant checks
            for (long long m = p * p; m <= n; m += p) is_prime[m] = false;
        }
    }
    return primes;
}

// Returns the prime factorization of n as a list of (prime, exponent) pairs
std::vector<std::pair<int, int>> prime_fact(int n)
{
    std::vector<std::pair<int,int>> f;
    for (int d = 2; d * d <= n; d++) if (n % d == 0)
    {
        int m = 0;
        while (n % d == 0) n /= d, m++;
        f.push_back({d, m});
    }
    if (n > 1) f.push_back({n, 1});
    return f;
}

// Basic primality test for small to medium integers
bool isprime(const int &n)
{
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (long long d = 3; d * d <= n; d += 2) if (n % d == 0) return false;
    return true;
}

// Efficiently computes (base^exp) % m using binary exponentiation
long long modpow(const int &base, const int &exp, const int &m)
{
    if (exp == 0) return 1;
    long long u = modpow(base, exp / 2, m);
    u = (u * u) % m;
    return (exp & 1 ? (long long)base : 1LL) * u % m;
}

// Extended Euclidean Algorithm to find g = gcd(a, b) and coefficients x, y
// such that ax + by = gcd(a, b)
std::tuple<int, int, int> extendedEuclid(const int &a, const int &b)
{
    if (b == 0) return {a, 1, 0};
    int g, x1, y1;
    std::tie(g, x1, y1) = extendedEuclid(b, a % b);
    int x = y1, y = x1 - (a / b) * y1;
    return {g, x, y};
}

// Computes the modular multiplicative inverse using the Extended Euclidean Algorithm
// Throws an exception if the inverse does not exist (gcd(a, m) != 1)
int modinv(const int &a, const int &m)
{
    int g, x, y;
    std::tie(g, x, y) = extendedEuclid(a, m);
    if (g != 1) throw std::invalid_argument("Modular inverse does not exist: gcd(" + std::to_string(a) + ", " + std::to_string(m) + ") != 1");
    return (x % m + m) % m; // Ensure the result is positive
}

PYBIND11_MODULE(cp_math, m)
{
    m.doc() = "C++ competitive programming math algorithms module for Python";
    
    // Binding functions to Python with docstrings for help() support
    m.def("sieve", &sieve, "Sieve of Eratosthenes", py::arg("n"));
    m.def("prime_fact", &prime_fact, "Prime factorization", py::arg("n"));
    m.def("isprime", &isprime, "Check if a number is prime", py::arg("n"));
    m.def("modpow", &modpow, "Modular exponentiation (base^exp % m)", py::arg("base"), py::arg("exp"), py::arg("m"));
    m.def("extendedEuclid", &extendedEuclid, "Extended Euclidean algorithm", py::arg("a"), py::arg("b"));
    m.def("modinv", &modinv, "Modular inverse", py::arg("a"), py::arg("m"));
}
