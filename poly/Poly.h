#include <iostream>
#include <assert.h>
#include <math.h>
#define DEFAULT_SIZE 4

using namespace std;

class Poly{
  public:
    Poly(double first_val = 0.0);
    Poly(const Poly& pol);
    ~Poly();
    Poly& operator=(const Poly& pol);
    Poly& operator=(double val);
    Poly operator-();
    Poly& operator-=(const Poly& pol);
    Poly& operator+=(const Poly& pol);
    Poly& operator*=(const Poly& pol);
    double& operator[](int pos);
    double& operator[](int pos) const;
    double operator()(double val);
    double operator()(double val) const;
    friend Poly operator+(const Poly&, const Poly&);
    friend Poly operator-(const Poly&, const Poly&);
    friend Poly operator*(const Poly&, const Poly&);
    friend ostream& operator<<(ostream& out, const Poly& p);
    friend void zeration(Poly& p, size_t start_pos, size_t end_pos);
    friend void size_change(size_t new_size, Poly& p);
  private:
    double *data;
    size_t size;
};
