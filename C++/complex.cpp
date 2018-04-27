#include "complex.h"


Complex::Complex(double realValue, double imaginaryValue){
	real = realValue;
	imaginary = imaginaryValue;

}

Complex::~Complex(void){

}

double Complex::getReal(){
	return real;
}

double Complex::getImaginary(){
	return imaginary;
}
