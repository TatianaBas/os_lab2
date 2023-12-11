#pragma once
#include <iostream>

struct complex_double {
    double x;
    double i;

    complex_double();
    complex_double(double&);
    ~complex_double() = default;

    friend std::istream& operator>>(std::istream&, complex_double&);
    friend std::ostream& operator<<(std::ostream&, complex_double&);

    complex_double operator=(const double&);
    complex_double operator=(const complex_double&);

    complex_double operator+(const complex_double&);
    complex_double operator-(const complex_double&);
    complex_double operator*(const complex_double&);

    complex_double operator+=(const complex_double&);
};