#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Enables automatic conversion between C++ STL and Python types
#include <bits/stdc++.h>

namespace py = pybind11;

// Generates all prime numbers up to n using the Sieve of Eratosthenes
std::vector<long long> sieve(const long long &n)
{
    std::vector<long long> primes;
    if (n < 2) return primes;
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (long long p = 2; p <= n; p++) {
        if (is_prime[p]) {
            primes.push_back(p);
            // Start marking from p*p to avoid redundant checks
            for (long long m = p * p; m <= n; m += p) is_prime[m] = false;
        }
    }
    return primes;
}

// Returns the prime factorization of n as a list of (prime, exponent) pairs
std::vector<std::pair<long long, long long>> prime_fact(long long n)
{
    std::vector<std::pair<long long,long long>> f;
    for (long long d = 2; d * d <= n; d++) if (n % d == 0)
    {
        long long m = 0;
        while (n % d == 0) n /= d, m++;
        f.push_back({d, m});
    }
    if (n > 1) f.push_back({n, 1});
    return f;
}

// Basic primality test for small to medium long longegers
bool isprime(const long long &n)
{
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (long long d = 3; d * d <= n; d += 2) if (n % d == 0) return false;
    return true;
}

// Efficiently computes (base^exp) % m using binary exponentiation
long long modpow(const long long &base, const long long &exp, const long long &m)
{
    if (exp == 0) return 1;
    long long u = modpow(base, exp / 2, m);
    u = (u * u) % m;
    return (exp & 1 ? base : 1LL) * u % m;
}

// Extended Euclidean Algorithm to find g = gcd(a, b) and coefficients x, y
// such that ax + by = gcd(a, b)
std::tuple<long long, long long, long long> extendedEuclid(const long long &a, const long long &b)
{
    if (b == 0) return {a, 1, 0};
    long long g, x1, y1;
    std::tie(g, x1, y1) = extendedEuclid(b, a % b);
    long long x = y1, y = x1 - (a / b) * y1;
    return {g, x, y};
}

// Computes the modular multiplicative inverse using the Extended Euclidean Algorithm
// Throws an exception if the inverse does not exist (gcd(a, m) != 1)
long long modinv(const long long &a, const long long &m)
{
    long long g, x, y;
    std::tie(g, x, y) = extendedEuclid(a, m);
    if (g != 1) throw std::invalid_argument("Modular inverse does not exist: gcd(" +
											std::to_string(a) + ", " + std::to_string(m) + ") != 1");
    return (x % m + m) % m; // Ensure the result is positive
}

// Performs matrix multiplication: c = a * b
// Throws an exception if the matrices have incompatible dimensions
std::vector<std::vector<long long>> matrix_multiplication(const std::vector<std::vector<long long>> &a,
                                                 const std::vector<std::vector<long long>> &b)
{
    if (a.empty() || b.empty())
        throw std::invalid_argument("Matrix multiplication error: matrices must not be empty");

    long long n1 = a.size();
    long long m1 = a[0].size();
    long long n2 = b.size();
    long long m2 = b[0].size();

    if (m1 != n2)
        throw std::invalid_argument("Matrix multiplication error: incompatible dimensions (" +
                                    std::to_string(n1) + "x" + std::to_string(m1) + " * " +
                                    std::to_string(n2) + "x" + std::to_string(m2) + ")");

    std::vector<std::vector<long long>> c(n1, std::vector<long long>(m2, 0));
    for (long long i = 0; i < n1; i++)
        for (long long j = 0; j < m2; j++)
            for (long long k = 0; k < m1; k++)
                c[i][j] += a[i][k] * b[k][j];

    return c;
}

// Computes the matrix exponentiation a^p using binary exponentiation
// Throws an exception if the matrix is not square or if p is negative
std::vector<std::vector<long long>> matrix_exponentiation(const std::vector<std::vector<long long>> &a, 
														const long long &p)
{
    if (a.empty() || a[0].empty())
        throw std::invalid_argument("Matrix exponentiation error: matrix must not be empty");

    if (a.size() != a[0].size())
        throw std::invalid_argument("Matrix exponentiation error: matrix must be square");

    if (p < 0)
        throw std::invalid_argument("Matrix exponentiation error: exponent must be non-negative");

    if (p == 0)
    {
        std::vector<std::vector<long long>> b(a.size(), std::vector<long long>(a.size(), 0));
        for (size_t i = 0; i < a.size(); i++) b[i][i] = 1;
        return b;
    }

    std::vector<std::vector<long long>> u = matrix_exponentiation(a, p / 2);
    u = matrix_multiplication(u, u);
    if (p & 1) u = matrix_multiplication(u, a);
    return u;
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
    m.def("matrix_multiplication", &matrix_multiplication, "Matrix multiplication", py::arg("a"), py::arg("b"));
    m.def("matrix_exponentiation", &matrix_exponentiation, "Matrix exponentiation", py::arg("a"), py::arg("p"));
}
