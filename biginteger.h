#pragma once

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
class BigInteger {
  private:
    int64_t l;
    bool neg;
    std::vector<long long> a;

  public:
    BigInteger();
    BigInteger operator-() const;
    BigInteger(int64_t i);
    BigInteger(const BigInteger& i);
    BigInteger(const std::string& s);
    std::string toString() const;
    void swap(BigInteger& s2);
    friend std::istream& operator>>(std::istream& in, BigInteger& s);
    friend std::ostream& operator<<(std::ostream& out, const BigInteger& s);
    friend bool operator==(const BigInteger& s1, const BigInteger& s2);
    friend bool operator<(const BigInteger& s1, const BigInteger& s2);
    friend BigInteger operator+(BigInteger s1, const BigInteger& s2);
    BigInteger& operator+=(const BigInteger& s);
    BigInteger& operator/=(const BigInteger& s);
    friend BigInteger operator/(BigInteger s1, const BigInteger& s2);
    BigInteger& operator++();
    BigInteger operator++(int);
    friend BigInteger operator-(BigInteger s1, const BigInteger& s2);
    BigInteger& operator-=(const BigInteger& s);
    BigInteger& operator--();
    BigInteger operator--(int);
    BigInteger& operator%=(const BigInteger s);
    friend BigInteger operator*(const BigInteger& s1, const BigInteger& s2);
    BigInteger& operator*=(const BigInteger& s);
    BigInteger& operator=(BigInteger s);
    explicit operator bool() const;
};
bool operator!=(const BigInteger& s1, const BigInteger& s2);
bool operator>(const BigInteger& s1, const BigInteger& s2);
bool operator<=(const BigInteger& s1, const BigInteger& s2);
bool operator>=(const BigInteger& s1, const BigInteger& s2);
BigInteger operator"" _bi(unsigned long long c);
BigInteger operator"" _bi(const char* c, size_t);
BigInteger operator%(BigInteger s1, const BigInteger& s2);

class Rational {
  private:
    BigInteger a, b;

  public:
    Rational();
    Rational(const BigInteger& c);
    Rational(int64_t c);
    Rational(const Rational& c);
    Rational operator-() const;
    std::string toString() const;
    friend bool operator<(const Rational& s1, const Rational& s2);
    friend bool operator==(const Rational& s1, const Rational& s2);
    Rational& operator/=(const Rational& c);
    Rational& operator-=(const Rational& c);
    Rational& operator+=(const Rational& c);
    Rational& operator*=(const Rational& c);
    Rational& operator=(const Rational& c);
    std::string asDecimal(size_t precision) const;
    explicit operator double() const;
};
bool operator>(const Rational& s1, const Rational& s2);
bool operator>=(const Rational& s1, const Rational& s2);
bool operator<=(const Rational& s1, const Rational& s2);
bool operator!=(const Rational& s1, const Rational& s2);
Rational operator/(Rational s1, const Rational& s2);
Rational operator+(Rational s1, const Rational& s2);
Rational operator-(Rational s1, const Rational& s2);
Rational operator*(Rational s1, const Rational& s2);
