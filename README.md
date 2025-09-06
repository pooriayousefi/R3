# R3 - 3D Real Space Mathematics Library

[![Build Status](https://github.com/pooriayousefi/R3/actions/workflows/ci.yml/badge.svg)](https://github.com/pooriayousefi/R3/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B20)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg)](https://cmake.org/)

A modern C++20 header-only library for 3D real space mathematics, providing comprehensive support for multiple coordinate systems with compile-time type safety and high-performance operations.

## 🚀 Features

- **Multiple Coordinate Systems**: Cartesian, Cylindrical, and Spherical coordinate support
- **Type Safety**: Compile-time coordinate system validation using C++20 concepts
- **Header-Only**: Zero-compilation dependency, just import and use
- **High Performance**: Template metaprogramming and constexpr operations
- **Cross-Platform**: Works on Linux (g++), macOS (clang++), and Windows (MSVC)
- **Modern C++20**: Extensive use of concepts, modules, and constexpr
- **IEEE Compliance**: Full floating-point precision support (float, double, long double)

## 🎯 Quick Start

```cpp
import R3;
using namespace R3;

#include <iostream>
#include <numbers>

int main() {
    // Cartesian coordinates
    coordinates<double, cartesian_system> point1{1.0, 2.0, 3.0};
    coordinates<double, cartesian_system> point2{-1.0, 0.0, 1.0};
    
    // Vector operations
    auto sum = point1 + point2;
    auto dot_product = point1 * point2;
    auto cross_product = point1 ^ point2;
    
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Dot product: " << dot_product << std::endl;
    std::cout << "Cross product: " << cross_product << std::endl;
    
    // Coordinate system conversion
    coordinates<float, cylindrical_system> cylindrical{
        3.0f, std::numbers::pi_v<float> / 4.0f, -1.0f
    };
    
    auto spherical = cylindrical.to_spherical_coordinates();
    auto cartesian = cylindrical.to_cartesian_coordinates();
    
    return 0;
}
```

## 📚 Coordinate Systems

### Cartesian System (`cartesian_system`)
Standard 3D Cartesian coordinates with x, y, z components.

### Cylindrical System (`cylindrical_system`)  
Cylindrical coordinates with ρ (rho), φ (phi), z components.

### Spherical System (`spherical_system`)
Spherical coordinates with r, θ (theta), φ (phi) components.

## 🔄 Coordinate Conversions

This system is equipped with all internal system converters:
- **Cartesian ↔ Cylindrical**
- **Cartesian ↔ Spherical** 
- **Cylindrical ↔ Spherical**

All conversions are performed with high precision and compile-time optimization.

## 📐 Geometrical Transformations

The library provides support for developing geometrical transformations in multiple metrics:
- **Minkowski Metric**: For spacetime calculations
- **Manhattan Metric**: For grid-based distances  
- **Euclidean Metric**: For standard geometric distances
- **Chebyshev Metric**: For maximum coordinate differences

## 🏗️ Building from Source

```bash
# Clone repository
git clone https://github.com/pooriayousefi/R3.git
cd R3

# Build with default settings
cmake --preset=default
cmake --build build/default

# Run the demo
./build/default/R3_demo
```

## 📄 License

This project is licensed under the MIT License - see the [LICENSE.txt](LICENSE.txt) file for details.

---

**Author**: [Pooria Yousefi](https://github.com/pooriayousefi)  
**Repository**: [https://github.com/pooriayousefi/R3](https://github.com/pooriayousefi/R3)
