#include "EuclideanVector.h"
#include <vector>
#include <string>
#include <math.h>
namespace evec {
EuclideanVector::EuclideanVector() {
dimension = 1;
*magnitudes = 0;
}
EuclideanVector::~EuclideanVector() {
magnitudes = nullptr;
};
EuclideanVector::EuclideanVector(unsigned int dim) {
dimension = dim;
double *p = new double[dim];
for (unsigned int i = 0; i < dimension; i++) {
p[i] = 0;

}
magnitudes = p;

}


EuclideanVector::EuclideanVector(unsigned int dim, double mag) {
double *p = new double[dim];
for (unsigned int i = 0; i < dimension; i++) {
p[i] = mag;
}
magnitudes = p;
dimension = dim;
};
EuclideanVector::EuclideanVector(std::list<double>::iterator start, std::list<double>::iterator end) {
int count = 0;

for (auto iter = start; iter != end; iter++) {
count++;
}
double *p = new double[count];
dimension = count;
count = 0;
for (auto iter = start; iter != end; iter++) {
p[count] = *iter;
count++;
}

magnitudes = p;

};

EuclideanVector::EuclideanVector(std::vector<double>::iterator start, std::vector<double>::iterator end) {
int count = 0;

for (auto iter = start; iter != end; iter++) {
count++;
}
double *p = new double[count];
dimension = count;
count = 0;
for (auto iter = start; iter != end; iter++) {
p[count] = *iter;
count++;
}
magnitudes = p;

};

EuclideanVector::EuclideanVector(std::initializer_list<double> l) {
dimension = l.size();
int count = 0;

for (auto iter = l.begin(); iter != l.end(); iter++) {
count++;
}
double *p = new double[count];
dimension = count;
count = 0;
for (auto iter = l.begin(); iter != l.end(); iter++) {
p[count] = *iter;
count++;
}
magnitudes = p;

};

EuclideanVector::EuclideanVector(const EuclideanVector& ev) {
dimension = ev.dimension;
double *p = new double[dimension];
for (unsigned int i = 0; i < dimension; i++) {
p[i]= ev.magnitudes[i];
}
magnitudes = p;


};

EuclideanVector::EuclideanVector(EuclideanVector&& ev) {

dimension = std::move(ev.dimension);
magnitudes = std::move(ev.magnitudes);
ev.magnitudes = nullptr;
ev.dimension = 0;
};

unsigned EuclideanVector::getNumDimensions() {
return dimension;
}

double EuclideanVector::get(unsigned int dim) {
return magnitudes[dim];
}





double EuclideanVector::getEuclideanNorm() {
double Euclidean_norm = 0;

for (unsigned int i = 0; i < dimension; i++) {

Euclidean_norm += (magnitudes[i])*(magnitudes[i]);
}
return  sqrt(Euclidean_norm);

}

EuclideanVector EuclideanVector::createUnitVector() {
std::vector<double> p;
double Euclidean_norm = getEuclideanNorm();

for (unsigned int i = 0; i < dimension; i++) {
p.push_back(magnitudes[i] / Euclidean_norm);
}
EuclideanVector result(p.begin(),p.end());

return result;
}

double& EuclideanVector::operator [](int i) {

return magnitudes[i];
}

EuclideanVector& EuclideanVector::operator=(EuclideanVector&& ev) {
if (this !=&ev){
dimension = ev.dimension;
magnitudes = ev.magnitudes;
ev.magnitudes = nullptr; 
ev.dimension = 0;
}

return *this;
}

void EuclideanVector::operator +=(EuclideanVector& rhs) {
if (dimension != rhs.dimension) {
std::cout << "ERROR: Dimension Not Match" << std::endl;
}
else {
for (unsigned int i = 0; i < dimension; i++) {
magnitudes[i] += rhs.magnitudes[i];
}
}
}

void EuclideanVector::operator -=(EuclideanVector& rhs) {
if (dimension != rhs.dimension) {
std::cout << "ERROR: Dimension Not Match" << std::endl;
}
else {
for (unsigned int i = 0; i < dimension; i++) {
magnitudes[i] -= rhs.magnitudes[i];
}
}
}

void EuclideanVector::operator *=(double rhs) {

for (unsigned int i = 0; i < dimension; i++) {
magnitudes[i] = magnitudes[i]*rhs;
}

}


void EuclideanVector::operator /=(double& rhs) {
if (rhs == 0) {
std::cout << "ERROR: Devide By Zero" << std::endl;
}
else {
for (unsigned int i = 0; i < dimension; i++) {
magnitudes[i] /= rhs;
}
}
}

EuclideanVector::operator std::vector<double> const() {
std::vector<double> v;
for (unsigned int i = 0; i < dimension; i++) {
v.push_back(magnitudes[i]);
}
return v;
}

EuclideanVector::operator std::list<double> const() {
std::list<double> l;
for (unsigned int i = 0; i < dimension; i++) {
l.push_back(magnitudes[i]);
}
return l;
}


bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs) {
if (lhs.dimension != rhs.dimension) {
return false;
}
else {
for (unsigned int i = 0; i < lhs.dimension; i++) {
if (lhs.magnitudes[i] != rhs.magnitudes[i]) { return false; }
}
return true;
}
}

bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs) {
if (lhs == rhs) {
return false;

}
else { return true; }
}


EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs) {

if (lhs.dimension == rhs.dimension) {
EuclideanVector result(lhs.dimension);

for (unsigned int i = 0; i < lhs.dimension; i++) {
result.magnitudes[i] = lhs.magnitudes[i] + rhs.magnitudes[i];
}
return result;
}
else { return 0; }
}

EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs) {

if (lhs.dimension == rhs.dimension) {
EuclideanVector result(lhs.dimension);

for (unsigned int i = 0; i < lhs.dimension; i++) {
result.magnitudes[i] = lhs.magnitudes[i] - rhs.magnitudes[i];
}
return result;
}
else { return 0; }

}

double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs) {

if (lhs.dimension == rhs.dimension) {
EuclideanVector result(lhs.dimension);
double dot_product = 0;
for (unsigned int i = 0; i < lhs.dimension; i++) {
result.magnitudes[i] = lhs.magnitudes[i] * rhs.magnitudes[i];
dot_product += result.magnitudes[i];
}
return dot_product;
}
else { return 0; }
}

EuclideanVector operator*(const double& lhs, const EuclideanVector& rhs) {


EuclideanVector result(rhs.dimension);

for (unsigned int i = 0; i < rhs.dimension; i++) {
result.magnitudes[i] = lhs*rhs.magnitudes[i];
}
return result;
}

EuclideanVector operator*(const EuclideanVector& lhs, const double& rhs) {


EuclideanVector result(lhs.dimension);

for (unsigned int i = 0; i < lhs.dimension; i++) {
result.magnitudes[i] = rhs*lhs.magnitudes[i];
}
return result;


}

EuclideanVector operator/(const EuclideanVector& lhs, const double& rhs) {


EuclideanVector result(lhs.dimension);

for (unsigned int i = 0; i < lhs.dimension; i++) {
result.magnitudes[i] = lhs.magnitudes[i] / rhs;
}
return result;


}

std::ostream& operator <<(std::ostream& os, const EuclideanVector& rhs) {
os << "[";
for (unsigned int i = 0; i < rhs.dimension; i++) {
if (i != rhs.dimension - 1) {
os << rhs.magnitudes[i] << " ";
}
else {
os << rhs.magnitudes[i];
}
}
os << "]";
return os;
}
}
