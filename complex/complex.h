#ifndef __Complex_H__
#define __Complex_H__
#include <iostream>
#include <math.h>

using namespace std;

class Complex {
private:
  double Real, Imag;

public:
  Complex(double Real = 0, double Imag = 0) : Real(Real), Imag(Imag) {}

  Complex &operator=(const Complex &s) {
    Real = s.Real;
    Imag = s.Imag;
    return *this;
  };

  Complex operator-() const { return Complex(-Real, -Imag); };

  Complex &operator=(double co) {
    Real = co;
    Imag = 0;
    return *this;
  };

  Complex operator+(const Complex &co) const {
    Complex n;
    n.Real = this->Real + co.Real;
    n.Imag = this->Imag + co.Imag;
    return n;
  };

  Complex &operator-=(Complex co) {
    Real -= co.Real;
    Imag -= co.Imag;
    return *this;
  };
  Complex operator/(Complex co) {
    double den = co.Real * co.Real + co.Imag * co.Imag;
    if (den == 0) {
      printf("Error in division by zero\n");
      return Complex(0, 0);
    }
    double re = (Real * co.Real + Imag * co.Imag) / den;
    double im = (Imag * co.Real - Real * co.Imag) / den;
    return Complex(re, im);
  }
  Complex &operator/=(Complex co) {
    double den = co.Real * co.Real + co.Imag * co.Imag;
    if (den == 0) {
      throw runtime_error("Dividing by zero");
    }
    double re = (Real * co.Real + Imag * co.Imag) / den;
    double im = (Imag * co.Real - Real * co.Imag) / den;
    Real = re;
    Imag = im;
    return *this;
  }
  double abs() const { return std::sqrt(Real * Real + Imag * Imag); }
  double arg() const { return std::atan2(Imag, Real); }
  Complex conj() const { return Complex(Real, -Imag); }
  friend Complex operator-(Complex, Complex);
  friend ostream &operator<<(ostream &s, const Complex &c) {
    s << "(" << c.Real << "," << c.Imag << ")";
    return s;
  };
};

inline Complex operator-(Complex s1, Complex s2) {
  Complex n(s1);
  return n -= s2;
}

#endif /* __Complex_H__ */
