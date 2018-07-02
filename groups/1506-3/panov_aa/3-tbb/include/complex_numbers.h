#pragma once
#include <iostream>
#include <string>
using std::string;
double inline sqr(double a)
{
    return a*a;
}
struct Complex
{
    double real;
    double imaginary;
    Complex(): real(0.0), imaginary(0.0){}
    Complex(double r, double im): real(r), imaginary(im) {}
    Complex(const Complex &n):real(n.real), imaginary(n.imaginary) {}
    Complex getConjugate() const
    {
        return Complex(real, -imaginary);
    }
    bool operator == (const Complex &n)
    {
        return (real == n.real && imaginary == n.imaginary);
    }
    Complex operator + (const Complex &n)
    {
        return Complex(real + n.real, imaginary + n.imaginary);
    }
    Complex operator - (const Complex &n)
    {
        return Complex(real - n.real, imaginary - n.imaginary);
    }
    Complex operator * (const Complex &n)
    {
        return Complex(real*n.real - imaginary*n.imaginary, real*n.imaginary + imaginary*n.real);
    }
    Complex operator / (const Complex &n)
    {
        return Complex((real*n.real+ imaginary*n.imaginary)/(sqr(imaginary)+ sqr(n.imaginary)), (imaginary*n.real - n.imaginary*real)/(sqr(imaginary) + sqr(n.imaginary)));
    }
    friend std::ostream& operator<<(std::ostream& os, const Complex &c)
    {
        string s ="";
        if (c.imaginary >= 0.0) s = "+";
        os << c.real << s << c.imaginary;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Complex &c)
    {
        is >> c.real >> c.imaginary;
        return is;
    }
};