//311318075
//shanibasteker@gmail.com

#pragma once

#include <iostream>

class Complex {
private:
    double _re;
    double _im;

public:
    Complex(const double& re = 0.0, const double& im = 0.0); // Constructor.

    double re() const; //get the real part of the complex number
    double im() const; //get the imaginary part of the complex number

    // Unary operators
    bool operator!() const; // Logical NOT
    Complex operator-() const; // Unary minus

    // Binary operators
    Complex& operator+=(const Complex& other);  // Plus +=
    Complex& operator-=(const Complex& other);  // Minus -=
    Complex& operator*=(const Complex& other);  // Multiply *=
    Complex& operator++();  // prefix increment
    Complex operator++(int);  // postfix increment
    Complex operator-(const Complex& other);  // Binary minus - 
    Complex operator+(const Complex& other);  // Binary minus +
    Complex operator*(const Complex& other);  // Multiply *

    // Comparison operators
    bool operator<(const Complex& other) const;
    bool operator>(const Complex& other) const;
    bool operator==(const Complex& other);  
    bool operator!=(const Complex& other);  


    // friend global IO operators
    friend std::ostream& operator<<(std::ostream& output, const Complex& c);  // global output operator
    friend std::istream& operator>>(std::istream& input, Complex& c);  // global input operator

};

