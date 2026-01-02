# CP_Math

**CP_Math** is a proof-of-concept project designed to demonstrate how to bridge C++ and Python using **Pybind11**. 

While the algorithms are inspired by Competitive Programming, the primary goal of this repository is **educational**: showing how to optimize Python workflows by offloading heavy mathematical computations to native C++ code.

---

## Features

This module implements fundamental Number Theory algorithms optimized for performance:

* **Sieve of Eratosthenes**: Efficient prime number generation.
* **Prime Factorization**: Optimized $O(\sqrt{N})$ integer decomposition.
* **Extended Euclidean Algorithm**: Solving for coefficients in $ax + by = \gcd(a, b)$.
* **Modular Arithmetic**: Fast modular exponentiation and modular inverse.

---

## How it Works

The bridge between Python and C++ is handled by **Pybind11**, which maps C++ data types to Python objects with minimal overhead.



### Architecture Flow
1.  **C++ Core**: Mathematical algorithms are implemented using standard C++ types (`std::vector`, `long long`, etc.) to ensure maximum execution speed.
2.  **Pybind11 Wrappers**: These wrappers expose the C++ functions to the Python interpreter by creating a shared library (`.so`).
3.  **Python Interface**: Users can import `cp_math` as a standard Python module, benefiting from C++ speed without leaving the Python ecosystem.

### Data Conversion
Thanks to the `#include <pybind11/stl.h>` header, the conversion between Python lists and C++ vectors is handled automatically:
* `std::vector<int>` in C++ becomes a `list` in Python.
* `std::pair<int, int>` becomes a `tuple`.
* C++ exceptions are caught and re-raised as Python exceptions.

---

## Installation

### Prerequisites
* A C++11 compatible compiler (GCC, Clang)
* Python 3.x
* `pybind11` library (`pip install pybind11`)

### Compilation
To compile the module and generate the shared object file, use the provided **Makefile**:

```bash
make
