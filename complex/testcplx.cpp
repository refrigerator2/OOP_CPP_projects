#include <iostream>
using namespace std;
#include "complex.h"

int main()
{
    Complex a(0.0, 15), b(0, 13), c;
    c = 10;
    cout << c << endl;
    c = -a;
    cout << c << endl;
    c = a + b;
    c = c - Complex(10);
    cout << c << endl;
    c = 10 - a;
    (c -= b) -= 10;
    cout << c << endl;

    printf("\nNew functions\n");
    Complex f(10, 13), s(-20, -13);
    cout << f/s << endl;
    f /= s;
    cout << f << endl;
    double abs = f.abs();
    cout << abs << endl;
    double arg = f.arg();
    cout << arg << endl;
    cout << f.conj() << endl;
}
