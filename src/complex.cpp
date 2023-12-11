#include "complex.hpp"

complex_double::complex_double() {
    x = 0;
    i = 0;
}
complex_double::complex_double(double& val) {
    x = val;
    i = 0;
}

std::istream& operator>>(std::istream& in, complex_double& val) {
    std::string s;
    in >> s;

    int n = 0;
    bool sign = true;
    for (char c : s) {
        if (c <= '9' && c >= '0') {
            n = n * 10 + (c - '0');
        }
        if (c == 'i') {
            if (n == 0) {
                if (sign)
                    val.i = 1;
                else
                    val.i = -1;
            }
            else {
                if (sign)
                    val.i = n;
                else
                    val.i = -n;
                n = 0;
            }
        }
        if (c == '+') {
            if (sign)
                val.x = n;
            else
                val.x = -n;
            n = 0;
            sign = true;
        }
        if (c == '-') {
            if (sign)
                val.x = n;
            else
                val.x = -n;
            n = 0;
            sign = false;
        }
    }
    if (n > 0){
        if (sign)
            val.x = n;
        else
            val.x = -n;
    }

    return in;
}
std::ostream& operator<<(std::ostream& out, complex_double& val) {
    out << val.x;
    if (val.i == 0) {
        return out;
    }
    else if (val.i >= 0) {
        out << '+';
    }
    else {
        out << '-';
    }
    out << std::abs(val.i) << 'i';

    return out;
}

complex_double complex_double::operator=(const double& val) {
    x = val;
    i = 0;
    return *this;
}
complex_double complex_double::operator=(const complex_double& other) {
    x = other.x;
    i = other.i;
    return *this;
}

complex_double complex_double::operator+(const complex_double& other) {
    complex_double *res = new complex_double();
    res->x = x + other.x;
    res->i = i + other.i;
    return *res;
}
complex_double complex_double::operator-(const complex_double& other) {
    complex_double res = complex_double();
    res.x = x - other.x;
    res.i = i - other.i;
    return res;
}
complex_double complex_double::operator*(const complex_double& other) {
    complex_double res = complex_double();
    res.x = x * other.x - i * other.i;
    res.i = i * other.x + x * other.i;
    return res;
}

complex_double complex_double::operator+=(const complex_double& other) {
    x += other.x;
    i += other.i;
    return *this;
}