# CP_Math

A high-performance Python module written in C++ using **Pybind11**, specifically optimized for **Competitive Programming** math utilities.

## Features

* **Sieve of Eratosthenes**: Efficient prime number generation.
* **Prime Factorization**: Optimized $O(\sqrt{N})$ integer decomposition.
* **Extended Euclidean Algorithm**: Solving for coefficients in $ax + by = \gcd(a, b)$.
* **Modular Arithmetic**: Fast modular exponentiation and modular inverse.

## Performance
By bridging C++ logic into Python, this module allows you to execute heavy mathematical computations at native speed while maintaining the flexibility of Python for competitive programming contests.

## Installation

### Prerequisites
- A C++11 compatible compiler (e.g., GCC, Clang)
- Python 3.x
- `pybind11` library

### Manual Compilation
To compile the module and generate the shared object file (`.so`), use the provided Makefile:

```bash
make
