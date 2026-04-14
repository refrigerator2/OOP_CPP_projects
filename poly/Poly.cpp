#include "Poly.h"

void size_change(size_t new_size, Poly &p){
  if(!new_size) return;
    double *temp = (double *)realloc(p.data, new_size*sizeof(double));
    assert(temp);
    p.data = temp;
    p.size = new_size;
}

void zeration(Poly& p, size_t start_pos, size_t end_pos){
  if(start_pos>=end_pos) return;
  for(size_t i = start_pos; i < end_pos; i++){
    *(p.data+i) = 0.0;
  }
}

Poly::Poly(double first_val){
  data = (double *)calloc(DEFAULT_SIZE, sizeof(double));
  assert(data);
  *data = first_val;
  size = DEFAULT_SIZE;
}
Poly::Poly(const Poly& pol){
  data = (double *)calloc(pol.size, sizeof(double));
  assert(data);
  for(size_t i = 0; i < pol.size; i++){
    *(data+i) = *(pol.data+i);
  }
  size = pol.size;
}
Poly::~Poly(){
  if(data) free(data);
  size = 0;
}
Poly& Poly::operator=(const Poly& pol){
  if(this == &pol) return *this;
  if(size < pol.size) size_change(pol.size, *this); 
  for(size_t i = 0; i < pol.size; i++){
    *(data+i) = *(pol.data +i);
  }
  return *this;
}
Poly &Poly::operator=(double val){
  if(!size) size_change(1, *this);
  *(data) = val;
  zeration(*this, 1, size);
  return *this;
}
double& Poly::operator[](int pos){
  if((size_t )pos >= size){
    size_t old_size = size;
    size_change((size_t)pos+1, *this);
    zeration(*this, old_size, size);
  }
  return *(data+pos);
}
double& Poly::operator[](int pos) const{
  if((size_t )pos >= size) return *data;
  return *(data+pos);
}
ostream& operator<<(ostream& out, const Poly& p){
  out << "y = ";
  bool not_first = false;
  int pos = (int )p.size-1;
  while(true){
    if(pos<0) break;
    if(*(p.data+pos)==0) {
      if(!pos && !not_first) out << "0";
      pos--;
      continue;
    }
    if (*(p.data+pos) > 0 && not_first) out << "+ ";
    if (*(p.data+pos) && !not_first) not_first = true; 
    if(*(p.data+pos) < 0 && !(pos == 0 && abs(*(p.data+pos))==1)) out << "- ";
    
    abs(*(p.data + pos)) != 1 ? out << abs(*(p.data+pos)) : out << "";
    pos > 1 ? out << "x^" << pos << " " : pos == 0 ? out << "" : out << "x "; 
    pos--;
  }
  return out;
}
Poly Poly::operator-(){
  Poly temp;
  for(size_t i = 0; i<size;i++){
    temp[i] = -*(data+i);
  }
  return temp;
}
Poly& Poly::operator-=(const Poly& pol){
  if(size < pol.size){
    size_t old_size = size;
    size_change(pol.size, *this);
    zeration(*this, old_size, size);
  }
  for(size_t i = 0; i<pol.size;i++){
    *(data+i) -= *(pol.data +i);
  }
  return *this;
}
Poly operator-(const Poly& p1, const Poly& p2){
  Poly temp = p1;
  temp -= p2;
  return temp;
}
Poly& Poly::operator+=(const Poly& pol){

  if(size < pol.size){
    size_t old_size = size;
    size_change(pol.size, *this);
    zeration(*this, old_size, size);
  }

  for(size_t i = 0; i < pol.size;i++){
    *(data+i) += *(pol.data+i);
  }
  return *this;
}
Poly operator+(const Poly& p1, const Poly& p2){
  Poly temp = p1;
  temp += p2;
  return temp;
}
Poly& Poly::operator*=(const Poly &pol){
  size_t new_size = size+pol.size-1;
  double *res = (double *)calloc(new_size, sizeof(double));
  assert(res);
  for(size_t i = 0; i < size; i++){
    for(size_t j = 0; j < pol.size; j++){
      *(res+i+j) += *(data+i) * *(pol.data+j);
    }
  }
  free(data);
  data = res;
  size = new_size;
  return *this;
}

Poly operator*(const Poly& p1, const Poly& p2){
  Poly temp = p1;
  temp *= p2;
  return temp;
}

double Poly::operator()(double val){
  double res=*data;
  for(size_t i = 1; i < size; i++){
    res += pow(*(data+i), i)*val;
  }
  return res;
}
double Poly::operator()(double val) const {
  double res=*data;
  for(size_t i = 1; i < size; i++){
    res += pow(val, i) * *(data+i);
  }
  return res;
}
