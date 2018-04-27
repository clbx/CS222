#ifndef COMPLEX_H
#define COMPLEX_H

class Complex{
	double real;
	double imaginary;

public:
	Complex(double realvalue = 0, double imaginaryValue = 0);
	~Complex(void);

	double getReal();
	double getImaginary();
};

#endif
