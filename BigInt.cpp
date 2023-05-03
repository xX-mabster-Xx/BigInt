#include "BigInt.h"
const unsigned int max = 1000000000;


BigInt::BigInt() : m_num({0})
,sign(1)
{}

int symbs(unsigned int n) {
    return (n ? std::floor(std::log10(n)) + 1 : 1);
}

BigInt::BigInt(int n)
{
    if ((unsigned int)std::abs(n) < max)
        m_num = {(unsigned int)std::abs(n)};
    else
        m_num = {(unsigned int)std::abs(n) - max, 1};
    if (n == 0) {
        sign = 1;
        return;
    }
    sign = n / std::abs(n);
}


BigInt::BigInt(std::vector<unsigned int> n, int s)
    :m_num(n)
    ,sign(s)
{
    delete_leading_zeros();
}



BigInt operator+(const BigInt & A, const BigInt & B) {
    if (B.sign == -1 && A.sign == -1)
        return -(-B + -A);
    if (B.sign == -1)
        return A - B;
    if (A.sign == -1)
        return B - A;
    int sign = 1;
    std::vector<unsigned int> sum;
    unsigned int pr = 0;
    int i;
    for (i = 0; i < std::min(A.len(), B.len()); ++i) {
        if (A.m_num[i] + B.m_num[i] + pr >= max) {
            sum.push_back(A.m_num[i] + B.m_num[i] + pr - max);
            pr = 1;
        }
        else {
            sum.push_back(A.m_num[i] + B.m_num[i] + pr);
            pr = 0;
        }
    }
    if (i < std::max(A.len(), B.len())) {
        if (A.len() > B.len()) {
            for (; i < A.len(); ++i) {
                if (A.m_num[i]  + pr >= max) {
                    sum.push_back(A.m_num[i] + pr - max);
                    pr = 1;
                }
                else {
                    sum.push_back(A.m_num[i] + pr);
                    pr = 0;
                }
            }
        }
        if (A.len() < B.len()) {
            for (; i < B.len(); ++i) {
                if (B.m_num[i] + pr >= max) {
                    sum.push_back(B.m_num[i] + pr - max);
                    pr = 1;
                }
                else {
                    sum.push_back(B.m_num[i] + pr);
                    pr = 0;
                }
            }
        }
    }
    else if (pr)
        sum.push_back(1);
    return BigInt(sum, sign);
}

BigInt operator-(const BigInt & A, const BigInt & B) {
    if (B.sign == -1 && A.sign == -1)
        return (-B - -A);
    if (B.sign == -1)
        return (-B + A);
    if (A.sign == -1)
        return -(B + -A);
    if (A < B) {
        return -(B - A);
    }
    int sign = 1;
    std::vector<unsigned int> sum;
    unsigned int pr = 0;
    int i;
    for (i = 0; i < B.len(); ++i) {
        if (B.m_num[i] > A.m_num[i] - pr) {
            sum.push_back(max - B.m_num[i] + A.m_num[i] - pr);
            pr = 1;
        }
        else {
            sum.push_back(A.m_num[i] - B.m_num[i] - pr);
            pr = 0;
        }
    }
    if (i < A.len()) {
        for (; i < A.len(); ++i) {
            if (A.m_num[i] < pr) {
                sum.push_back(max + A.m_num[i] - pr);
                pr = 1;
            }
            else {
                sum.push_back(A.m_num[i] - pr);
                pr = 0;
            }
        }
    }
    return BigInt(sum, sign);
}



BigInt BigInt::operator-() const{
    return {this->m_num, -this->sign};
}



bool operator<(const BigInt & A, const BigInt & B) {
    if (A.sign < B.sign)
        return true;
    if (A.sign > B.sign)
        return false;
    if (A.len() > B.len())
        return false;
    if (A.len() < B.len())
        return true;
    size_t i = A.len() - 1;
    while (i >= 0 && A.m_num[i] == B.m_num[i])
        --i;
    if (i < 0)
        return false;
    return A.m_num[i] < B.m_num[i];
}
bool operator>(const BigInt & A, const BigInt & B) {
    return B < A;
}

bool operator==(const BigInt & A, const BigInt & B) {
    return (A.m_num == B.m_num && A.sign == B.sign);
}

bool operator<(const BigInt & A, int B) {
    return A < BigInt(B);
}

bool operator<(int A, const BigInt & B) {
    return BigInt(A) < B;

}
bool operator>(const BigInt & A, int B) {
    return BigInt(B) < A;
}

bool operator>(int A, const BigInt & B) {
    return BigInt(A) > B;
}

bool operator==(const BigInt & A, int B) {
    return A == BigInt(B);
}

bool operator==(int B, const BigInt & A) {
    return A == BigInt(B);
}

void BigInt::delete_leading_zeros() {
    for (size_t i = len() - 1; i > 0; --i) {
        if (m_num[i] == 0)
            m_num.pop_back();
    }
}

std::ostream& operator<<(std::ostream & out, const BigInt & A) {
    if (A.sign == -1)
        out << "-";
    out << A.m_num.back();
    for(int i = A.len() - 2; i >= 0; --i) {
        std::string s(symbs(max) - symbs(A.m_num[i]) - 1, '0');
        out << s << A.m_num[i];
    }
    return out;
}

void dbg__print(std::ostream & out, const BigInt & A) {
    if (A.sign == -1)
        out << "-";
    out << A.m_num.back();
    for(int i = A.len() - 2; i >= 0; --i) {
        std::string s(symbs(max) - symbs(A.m_num[i]) - 1, '0');
        out << " " << s << A.m_num[i];
    }
}

bool operator!=(const BigInt & A, const BigInt & B) {
    return !(A == B);
}

bool operator!=(int A, const BigInt & B) {
    return !(A == B);
}

bool operator!=(const BigInt & A, int B) {
    return !(A == B);
}


bool operator<=(const BigInt & A, const BigInt & B) {return (A < B|| A == B);}
bool operator<=(const BigInt & A, int B) {return (A < B|| A == B);}
bool operator<=(int A, const BigInt & B) {return (A < B|| A == B);}
bool operator>=(const BigInt & A, const BigInt & B) {return (A > B|| A == B);}
bool operator>=(const BigInt & A, int B) {return (A > B|| A == B);}
bool operator>=(int A, const BigInt & B) {return (A > B|| A == B);}

BigInt& BigInt::operator++() {
    *this = *this + 1;
    return *this;
}
BigInt BigInt::operator++(int) {
    return *this + 1;
}
BigInt& BigInt::operator--() {
    *this = *this - 1;
    return *this;
}
BigInt BigInt::operator--(int) {
    return *this - 1;
}

BigInt operator*(const BigInt & A, const BigInt & B) {
    if (A.sign == -1 && B.sign == -1)
        return ((-A) * (-B));
    if (A.sign == -1)
        return -((-A) * B);
    if (B.sign == -1)
        return -(A * (-B));
    BigInt ans;
    for (int k = B.len() - 1; k >= 0; --k) {
        for (int i = max / 10; i >= 1; i /= 10) {
            ans = multby10(ans);
            ans = ans + multbydig(A, ((B.m_num[k] / i) % 10));
        }
    }
    return ans;
}

BigInt multbydig(const BigInt & A, unsigned int B) {
    BigInt sum;
    for (int j = A.len() - 1; j >= 0; --j) {
        unsigned long long m = (unsigned long long)A.m_num[j] * B;
        sum = multbymax(sum);
        sum = sum + BigInt(m);
    }
    return sum;
}

BigInt multbymax(const BigInt & A) {
    BigInt res = A;
    res.m_num.push_back(0);
    for (int i = res.len() - 2; i >= 0; --i) {
        res.m_num[i + 1] = res.m_num[i];
    }
    res.m_num[0] = 0;
    return res;
}
BigInt multby10(const BigInt & A) {
    BigInt res = A;
    unsigned int plus = 0;
    for (int i = 0; i < A.len(); ++i) {
        unsigned long long m = (unsigned long long)A.m_num[i] * 10 + plus;
        if (m >= max) {
            plus = m / max;
            m = m % max;
            res.m_num[i] = m;
        }
        else {
            res.m_num[i] = m;
            plus = 0;
        }
    }
    if (plus > 0)
        res.m_num.push_back(plus);
    return res;
}

BigInt::BigInt(unsigned long long n) {
    if (n >= (unsigned long long)max) {
        *this = BigInt({(unsigned int)(n % max), (unsigned int)(n / max)}, 1);
    }
    else {
        *this = BigInt({(unsigned int) n}, 1);
    }
}




