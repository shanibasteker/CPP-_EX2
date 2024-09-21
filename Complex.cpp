//311318075
//shanibasteker@gmail.com

#include "Complex.hpp"
#include <cmath>
#include <sstream>

// Constructor
// constructor with parameters - set the real and imaginary parts to the given parameters
// if no parameters are given, set the real and imaginary parts to 0 - defined in hpp file
Complex::Complex(const double& re, const double& im) : _re(re), _im(im) {}

// Getters
// return the real part of the complex number
double Complex::re() const {
    return _re;
}

// return the imaginary part of the complex number
double Complex::im() const {
    return _im;
}
// !a
// ! - Logical NOT: is the real number == 0 and the imaginary number == 0
bool Complex::operator!() const {
    return _re == 0 && _im == 0;
}

//a = -b
// Unary minus - return a new complex number with the real and imaginary parts negated
Complex Complex::operator-() const {
    return Complex(-_re, -_im);
}

// a+=b
// Plus equals - add the real and imaginary parts of the given complex number to the current complex number
Complex& Complex::operator+=(const Complex& other) {
    _re += other._re;
    _im += other._im;
    return *this;
}

// a -= b
// Minus equals - subtract the real and imaginary parts of the given complex number from the current complex number
Complex& Complex::operator-=(const Complex& other) {
    _re -= other._re;
    _im -= other._im;
    return *this;
}

// a *= b
// Multiply equals - multiply the real and imaginary parts of the given complex number from the current complex number
Complex& Complex::operator*=(const Complex& other) {
    // (a+bi)*(c+di) = (ac - bd) + (ad + bc)i, new_re = (ac -bd), new_im = (ad + bc)
    double new_re = _re * other._re - _im * other._im;
    double new_im = _re * other._im + _im * other._re;
    _re = new_re;
    _im = new_im;
    return *this;
}

// Prefix increment - increment the real part of the complex number
// & - return a reference to the current complex number
Complex& Complex::operator++() {
    _re++;
    return *this;
}

// Postfix increment - increment the real part of the complex number and return a copy of the original complex number
// int - dummy parameter to differentiate between prefix and postfix increment
Complex Complex::operator++(int) {
    Complex copy = *this;
    _re++;
    return copy;
}

// Binary minus a - b
// Operator - return a new complex number with the real and imaginary parts subtracted
Complex Complex::operator-(const Complex& other) {
    return Complex(_re - other._re, _im - other._im);
}

// Binary plus a + b
// Operator + return a new complex number with the real and imaginary parts added
Complex Complex::operator+(const Complex &other)
{
    return Complex(_re + other._re, _im + other._im);
}

// Multiply - a * b
// Operator * return a new complex number with the real and imaginary parts multiplied
Complex Complex::operator*(const Complex& other) {
    // (a+bi)*(c+di) = (ac - bd) + (ad + bc)i
    return Complex(_re * other._re - _im * other._im,
                   _re * other._im + _im * other._re);
}

// hypot is a function in the cmath library that returns the hypotenuse of 
// the square root of the sum of the squares of the real and imaginary parts
// sqrt(a^2 + b^2) < sqrt(c^2 + d^2)
bool Complex::operator<(const Complex& other) const {
    return std::hypot(_re, _im) < std::hypot(other._re, other._im);
}

// ==
bool Complex::operator==(const Complex& other) {
    return this->im() == other.im() && this->re() == other.re();  // check imaginary and real parts equality
}

// >
bool Complex::operator>(const Complex& other) const {
    return (!(*this < other) && !(this == &other)); // using NOT(<) and NOT(==) operators
}

//  !=
bool Complex::operator!=(const Complex& other) {
    return !(*this == other); // using NOT(==) operator
}

// Friend global IO operators
// stream output operator
// using friend to access the private members of the class ostream
// and to define that the stream to be on the left-hand side - std::cout << c1
std::ostream& operator<<(std::ostream& output, const Complex& c) {
    output << c._re << (c._im >= 0 ? '+' : '-') << std::abs(c._im) << 'i';
    return output;
}

// stream input operator 
// using friend to access the private members of the class istream
// and to define that the stream to be on the left-hand side - std::cin >> c1
std::istream& operator>>(std::istream& input, Complex& c) {
    double re = 0, im = 0;
    char ch1, ch2;

    if (input >> re >> ch1 >> im >> ch2 && ch2 == 'i') {
        if (ch1 == '+') {
            c._re = re;
            c._im = im;
        } else if (ch1 == '-') {
            c._re = re;
            c._im = -im;
        } else {
            // set the failbit state if the input is invalid
            input.setstate(std::ios::failbit); // not + - chars as expected
        }
    } else {
        input.setstate(std::ios::failbit);  // not i char as expected
    }

    return input;
}