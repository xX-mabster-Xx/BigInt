#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
class BigInt {
private:
    std::vector<unsigned int> m_num;
    int sign;
    size_t len()const {return m_num.size();}
    void delete_leading_zeros();
public:
    BigInt();
    BigInt(int);
    BigInt(unsigned long long);
    BigInt(std::vector<unsigned int>, int);

    friend BigInt operator+(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt operator/(const BigInt&, const BigInt&);
    friend BigInt operator+(const BigInt& A, const int B) {return A + BigInt(B);};
    friend BigInt operator-(const BigInt& A, const int B) {return A - BigInt(B);};
    friend BigInt operator*(const BigInt& A, const int B) {return A * BigInt(B);};
    friend BigInt operator/(const BigInt& A, const int B) {return A / BigInt(B);};
    friend BigInt operator+(const int A, const BigInt& B) {return BigInt(B) + A;};
    friend BigInt operator-(const int A, const BigInt& B) {return BigInt(B) - A;};
    friend BigInt operator*(const int A, const BigInt& B) {return BigInt(B) * A;};
    friend BigInt operator/(const int A, const BigInt& B) {return BigInt(B) / A;};

    BigInt operator-()const;
    BigInt operator+()const{return *this;}

    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);
    //TODO += -= *= /=

    friend bool operator<(const BigInt &, const BigInt &);
    friend bool operator<(const BigInt &, int);
    friend bool operator<(int, const BigInt &);
    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator>(const BigInt &, int);
    friend bool operator>(int, const BigInt &);
    friend bool operator==(const BigInt &, const BigInt &);
    friend bool operator==(const BigInt &, int);
    friend bool operator==(int, const BigInt &);
    friend bool operator!=(const BigInt &, const BigInt &);
    friend bool operator!=(const BigInt &, int);
    friend bool operator!=(int, const BigInt &);
    friend bool operator<=(const BigInt &, const BigInt &);
    friend bool operator<=(const BigInt &, int);
    friend bool operator<=(int, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, int);
    friend bool operator>=(int, const BigInt &);
    friend std::ostream& operator<<(std::ostream & out, const BigInt & A);
    friend void dbg__print(std::ostream & out, const BigInt & A);
    friend BigInt multbymax(const BigInt &);
    friend BigInt multby10(const BigInt &);
    friend BigInt multbydig(const BigInt &, unsigned int);
};

