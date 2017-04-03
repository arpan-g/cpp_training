

#include "Complex.h" 





Complex::Complex(const double a , const double b) :real(a),imag(b)
	{}

Complex::Complex() : real(0.0), imag(0.0) {

}

double Complex::getReal () const {

	return real;
}

double Complex::getImag() const{

	return imag;
}

Complex& Complex::operator*(int a ,const Complex & com ) {

	return Complex(a*com.getReal, a*com.getImag);

}


