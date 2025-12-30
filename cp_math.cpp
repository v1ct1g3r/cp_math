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

long long modpow(const int &base, const int &exp, const int &modulo)
{
	if (exp == 0) return 1;
	long long u = modpow(base, exp / 2, modulo);
	u = (u * u) % modulo;
	return (exp & 1 ? base : 1) * u % modulo;
}


PYBIND11_MODULE(cp_math, m)
{
	m.doc() = "C++ competitive programming math algorithms module for Python";
	
	m.def("sieve", &sieve, "Sieve of Eratosthenes");
	m.def("modpow", &modpow, "Modular exponentiation");
}
