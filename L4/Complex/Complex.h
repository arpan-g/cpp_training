#pragma once


class Complex{


public:
	double getReal() const;
	double getImag() const;
	Complex(double a, double b);
	Complex();
	Complex & operator*( const int b);
	
private:
	double real;
	double imag;
};