#include<iostream>
#include "bigNum.h"
#pragma once
#ifndef _FRACTION_H_
#define _FRACTION_H_
#endif

using namespace std;
class Fraction:public bigNum
{
private:
	bigNum numerator;
	bigNum denominator;
	bigNum gcd(bigNum numerator,bigNum denominator){
		while(denominator!=0){
			bigNum temp = numerator%denominator;
			numerator = denominator;
			denominator = temp;
		}
		return numerator;
	}

public:
	Fraction(void):numerator(), denominator(){}
	~Fraction(void);
	Fraction(int n, int d):numerator(n), denominator(d){}
	Fraction& operator=(Fraction &rhs){
		numerator = rhs.numerator; denominator=rhs.denominator;
		return *this;
	}
	
	Fraction& operator+=(const Fraction &f2){
		numerator = numerator*f2.denominator+denominator*f2.numerator;
		denominator = denominator*f2.denominator;
		bigNum div = gcd(numerator, denominator);
		numerator/=div; denominator/=div;
		return *this;
	}

	Fraction& operator+=(const int n){
		numerator += denominator*n;
		return *this;
	}
	

	friend Fraction operator+(const int n, const Fraction f){
		Fraction sumf(f);
		sumf.numerator += sumf.denominator*n;
		return sumf;
	}
	
	friend Fraction operator/(const int &n, const Fraction &f){
		Fraction divf;
		divf.numerator = f.denominator*n;
		divf.denominator = f.numerator;
		bigNum div = divf.gcd(divf.getNumeroator(), divf.getDenominator());
		divf.numerator/=div; divf.denominator/=div;
		return divf;
	}
	
	Fraction& inverse(){
		bigNum temp = denominator; denominator=numerator; numerator = temp;
		return *this;
	}
	
	friend ostream& operator<<(ostream &os, const Fraction f){
		os<<f.numerator<<"/"<<f.denominator;
		return os;
	}

	inline bigNum getDenominator() const {return denominator;}
	
	inline bigNum getNumeroator() const {return numerator;}
};
