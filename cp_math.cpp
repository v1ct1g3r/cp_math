#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <bits/stdc++.h>

namespace py = pybind11;


std::vector<int> sieve(const int &n)
{
	std::vector<int> primes;
	if (n < 2) return primes;
	std::vector<bool> is_prime(n + 1, true);
	is_prime[0] = is_prime[1] = false;
	for (long long p = 2; p * p <= n; p++) if (is_prime[p])
	{
		primes.push_back(p);
		for (long long m = p * p; m <= n; m += p) is_prime[m] = false;
	}
	return primes;
}

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

bool isprime(const int &n)
{
	if (n < 2) return false;
	if (n == 2) return true;
	for (long long d = 3; d * d <= n; d += 2) if (n % d == 0) return false;
	return true;
}

long long modpow(const int &base, const int &exp, const int &m)
{
	if (exp == 0) return 1;
	long long u = modpow(base, exp / 2, m);
	u = u * u % m;
	return (exp & 1 ? base : 1) * u % m;
}

std::tuple<int, int, int> extendedEuclid(const int &a, const int &b)
{
	if (b == 0) return {a, 1, 0};
	int g, x1, y1;
	std::tie(g, x1, y1) = extendedEuclid(b, a % b);
	int x = y1, y = x1 - (a / b) * y1;
	return {g, x, y};
}

int modinv(const int &a, const int &m)
{
	int g, x, y;
	std::tie(g, x, y) = extendedEuclid(a, m);
	if (g != 1) throw std::invalid_argument(std::to_string(a) + " has no modular inverse modulo " + std::to_string(m));
	int inverse = (x % m + m) % m;
	return inverse;
}


PYBIND11_MODULE(cp_math, m)
{
	m.doc() = "C++ competitive programming math algorithms module for Python";
	
	m.def("sieve", &sieve, "Sieve of Eratosthenes");
	m.def("prime_fact", &prime_fact, "Prime factorization");
	m.def("modpow", &modpow, "Modular exponentiation");
	m.def("extendedEuclid", &extendedEuclid, "Extended Euclidean algorithm");
	m.def("modinv", &modinv, "Modular inverse");
}
