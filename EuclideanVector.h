#include <iostream>
#include <vector>
#include <array>
#include <list>


namespace evec {
class EuclideanVector {
public:
EuclideanVector();
~EuclideanVector();
EuclideanVector(unsigned int dim);
EuclideanVector(unsigned int dim, double mag);

EuclideanVector(std::list<double>::iterator start, std::list<double>::iterator end);
EuclideanVector(std::vector<double>::iterator start, std::vector<double>::iterator end);

EuclideanVector(std::initializer_list<double> l);

EuclideanVector(const EuclideanVector& ev);
EuclideanVector(EuclideanVector&& ev);


unsigned getNumDimensions();
double get(unsigned int dim);
double getEuclideanNorm();
EuclideanVector createUnitVector();
double& operator [](int i);
EuclideanVector & operator=(EuclideanVector&& ev);

void operator +=(EuclideanVector& rhs);
void operator -=(EuclideanVector& rhs);
void operator *=(double rhs);
void operator /=(double& rhs);

// type conversion
operator std::vector<double> const();
operator std::list<double> const();

//
friend bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs);
friend bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs);
friend EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs);
friend EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs);

friend double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs);

friend EuclideanVector operator*(const double& lhs, const EuclideanVector& rhs);
friend EuclideanVector operator*(const EuclideanVector& lhs, const double& rhs);
friend EuclideanVector operator/(const EuclideanVector& lhs, const double& rhs);

friend std::ostream& operator <<(std::ostream& os, const EuclideanVector& rhs);

private:
unsigned int dimension;
double *magnitudes;

};

bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs);
bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs);
EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs);
EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs);

    double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs);

EuclideanVector operator*(const double& lhs, const EuclideanVector& rhs);
EuclideanVector operator*(const EuclideanVector& lhs, const double& rhs);
EuclideanVector operator/(const EuclideanVector& lhs, const double& rhs);

std::ostream& operator <<(std::ostream& os, const EuclideanVector& rhs);


}
