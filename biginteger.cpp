#include "biginteger.h"

Rational::Rational(int64_t c) : a(c), b(1) {}
Rational::Rational() : a(0), b(1) {}
Rational::Rational(const BigInteger& c) : a(c), b(1) {}
Rational::Rational(const Rational& c) : a(c.a), b(c.b) {}
Rational& Rational::operator/=(const Rational& c) {
    BigInteger help1, help2;
    help1 = a * c.b;
    help2 = b * c.a;
    a = help1;
    b = help2;
    while (help2 != 0) {
        help1 %= help2;
        help1.swap(help2);
    }
    a /= help1;
    b /= help1;
    if (b < 0) {
        b = -b;
        a = -a;
    }
    return *this;
}
Rational Rational::operator-() const {
    Rational ans(*this);
    ans.a = -a;
    return ans;
}
std::string Rational::toString() const {
    std::string ans = a.toString();
    if (b != 1) {
        ans += "/" + b.toString();
    }
    return ans;
}
bool operator<(const Rational& s1, const Rational& s2) {
    return s1.a * s2.b < s2.a * s1.b;
}
bool operator>(const Rational& s1, const Rational& s2) {
    return s2 < s1;
}
bool operator>=(const Rational& s1, const Rational& s2) {
    return !(s1 < s2);
}
bool operator<=(const Rational& s1, const Rational& s2) {
    return !(s2 < s1);
}
bool operator==(const Rational& s1, const Rational& s2) {
    return s1.a == s2.a && s1.b == s2.b;
}
bool operator!=(const Rational& s1, const Rational& s2) {
    return !(s1 == s2);
}
Rational operator/(Rational s1, const Rational& s2) {
    s1 /= s2;
    return s1;
}
Rational& Rational::operator+=(const Rational& c) {
    BigInteger help1, help2;
    help1 = a * c.b + c.a * b;
    help2 = b * c.b;
    a = help1;
    b = help2;
    while (help2 != 0) {
        help1 %= help2;
        help1.swap(help2);
    }
    a /= help1;
    b /= help1;
    if (b < 0) {
        b = -b;
        a = -a;
    }
    return *this;
}
Rational operator+(Rational s1, const Rational& s2) {
    s1 += s2;
    return s1;
}
Rational& Rational::operator-=(const Rational& c) {
    BigInteger help1, help2;
    help1 = a * c.b - c.a * b;
    help2 = b * c.b;
    a = help1;
    b = help2;
    while (help2 != 0) {
        help1 %= help2;
        help1.swap(help2);
    }
    a /= help1;
    b /= help1;
    if (b < 0) {
        b = -b;
        a = -a;
    }
    return *this;
}
Rational operator-(Rational s1, const Rational& s2) {
    s1 -= s2;
    return s1;
}
Rational& Rational::operator*=(const Rational& c) {
    BigInteger help1, help2;
    help1 = a * c.a;
    help2 = b * c.b;
    a = help1;
    b = help2;
    while (help2 != 0) {
        help1 %= help2;
        help1.swap(help2);
    }
    a /= help1;
    b /= help1;
    if (b < 0) {
        b = -b;
        a = -a;
    }
    return *this;
}
Rational operator*(Rational s1, const Rational& s2) {
    s1 *= s2;
    return s1;
}
std::string Rational::asDecimal(size_t precision) const {
    BigInteger h1 = a, h2 = b;
    std::string ans = (h1 / h2).toString();
    if (precision == 0) {
        return ans;
    }
    if (ans[0] == '0') {
        ans = "-0";
    }
    ans += ".";
    h1 %= h2;
    if (h1 < 0) {
        h1 = -h1;
    }
    for (size_t i = 0; i < precision; ++i) {
        h1 *= 10;
        ans += (h1 / h2).toString();
        h1 %= h2;
    }
    return ans;
}
Rational& Rational::operator=(const Rational& c) {
    a = c.a;
    b = c.b;
    return *this;
}
Rational::operator double() const {
    std::string s1 = a.toString(), s2 = b.toString();
    double c = std::stod(s1), d = std::stod(s2);
    return c / d;
}

BigInteger::operator bool() const {
    return a[l - 1] != 0;
}
BigInteger::BigInteger() : l(0), neg(0) {}
BigInteger BigInteger::operator-() const {
    BigInteger help(*this);
    if (a[l - 1] != 0) {
        help.neg = !neg;
    }
    return help;
}
void BigInteger::swap(BigInteger& s2) {
    std::swap(a, s2.a);
    std::swap(l, s2.l);
    std::swap(neg, s2.neg);
}
BigInteger& BigInteger::operator=(BigInteger s) {
    swap(s);
    return *this;
}
BigInteger::BigInteger(const BigInteger& s) {
    neg = s.neg;
    l = s.l;
    a.resize(l);
    a.assign(s.a.begin(), s.a.end());
}
BigInteger::BigInteger(int64_t i) {
    neg = (i < 0);
    i = std::abs(i);
    l = 1;
    a.push_back(i % 100000);
    i /= 100000;
    while (i > 0) {
        ++l;
        a.push_back(i % 100000);
        i /= 100000;
    }
}
std::istream& operator>>(std::istream& in, BigInteger& s) {
    s.a.clear();
    s.l = 0;
    s.neg = 0;
    char c = ' ';
    c = in.get();
    while (c == ' ' || c == '\n') {
        c = in.get();
    }
    if (c == '-') {
        s.neg = 1;
        c = in.get();
    }
    std::string help;
    while (isdigit(c)) {
        help += c;
        c = in.get();
    }
    s.l = (help.size() + 4) / 5;
    s.a.resize(s.l);
    int64_t i = help.size() % 5;
    if (i == 0) {
        i = 5;
    }
    s.a[s.l - 1] = stoi(help.substr(0, i));
    for (size_t j = i; j < help.size(); j += 5) {
        s.a[s.l - (j - i) / 5 - 2] = stoi(help.substr(j, 5));
    }
    return in;
}
std::ostream& operator<<(std::ostream& out, const BigInteger& s) {
    if (s.neg) {
        out << '-';
    }
    out << s.a[s.l - 1];
    for (int64_t i = s.l - 2; i >= 0; --i) {
        out << std::setfill('0') << std::setw(5) << s.a[i];
    }
    return out;
}
bool operator==(const BigInteger& s1, const BigInteger& s2) {
    return (s1.neg == s2.neg && s1.a == s2.a);
}
bool operator!=(const BigInteger& s1, const BigInteger& s2) {
    return !(s1 == s2);
}
bool operator<(const BigInteger& s1, const BigInteger& s2) {
    if (s1.neg ^ s2.neg) {
        return s1.neg && !s2.neg;
    }
    if (s1.neg) {
        if (s1.l != s2.l) {
            return s1.l > s2.l;
        }
        for (long long i = s1.l - 1; i >= 0; --i) {
            if (s1.a[i] != s2.a[i]) {
                return s1.a[i] > s2.a[i];
            }
        }
        return false;
    }
    if (s1.l != s2.l) {
        return (s1.l < s2.l);
    }
    for (int64_t i = s1.l - 1; i >= 0; --i) {
        if (s1.a[i] != s2.a[i]) {
            return s1.a[i] < s2.a[i];
        }
    }
    return false;
}
bool operator>(const BigInteger& s1, const BigInteger& s2) {
    return s2 < s1;
}
bool operator<=(const BigInteger& s1, const BigInteger& s2) {
    return !(s1 > s2);
}
bool operator>=(const BigInteger& s1, const BigInteger& s2) {
    return !(s1 < s2);
}
std::string BigInteger::toString() const {
    std::string ans, help;
    if (neg) {
        ans += '-';
    }
    ans += std::to_string(a[l - 1]);
    for (int64_t i = l - 2; i >= 0; --i) {
        help = std::to_string(a[i]);
        ans += std::string(5 - help.size(), '0');
        ans += help;
    }
    return ans;
}
BigInteger operator+(BigInteger s1, const BigInteger& s2) {
    s1 += s2;
    return s1;
}
BigInteger& BigInteger::operator+=(const BigInteger& s) {
    l = std::max(l + 1, s.l + 1);
    a.resize(l, 0);
    for (long long i = 0; i < l - 1; ++i) {
        if (i < s.l) {
            a[i] += (1 - 2 * (neg ^ s.neg)) * s.a[i];
        }
        a[i + 1] += (a[i] - (100000 + a[i] % 100000) % 100000) / 100000;
        a[i] = (100000 + a[i] % 100000) % 100000;
    }
    while (a[l - 1] == 0 && l > 1) {
        a.pop_back();
        --l;
    }
    if (a[l - 1] < 0) {
        neg = !neg;
        for (long long i = 0; i < l; ++i) {
            a[i] *= -1;
        }
        for (long long i = 0; i < l - 1; ++i) {
            if (a[i] < 0) {
                a[i] += 100000;
                --a[i + 1];
            }
        }
        while (a[l - 1] == 0 && l > 1) {
            a.pop_back();
            --l;
        }
    }
    if (a[l - 1] == 0) {
        neg = false;
    }
    return *this;
}
BigInteger operator-(BigInteger s1, const BigInteger& s2) {
    s1 -= s2;
    return s1;
}
BigInteger& BigInteger::operator-=(const BigInteger& s) {
    l = std::max(l + 1, s.l + 1);
    a.resize(l, 0);
    for (long long i = 0; i < l - 1; ++i) {
        if (i < s.l) {
            a[i] += (1 - 2 * (neg ^ !s.neg)) * s.a[i];
        }
        a[i + 1] += (a[i] - (100000 + a[i] % 100000) % 100000) / 100000;
        a[i] = (100000 + a[i] % 100000) % 100000;
    }
    while (a[l - 1] == 0 && l > 1) {
        a.pop_back();
        --l;
    }
    if (a[l - 1] < 0) {
        neg = !neg;
        for (long long i = 0; i < l; ++i) {
            a[i] *= -1;
        }
        for (long long i = 0; i < l - 1; ++i) {
            if (a[i] < 0) {
                a[i] += 100000;
                --a[i + 1];
            }
        }
        while (a[l - 1] == 0 && l > 1) {
            a.pop_back();
            --l;
        }
    }
    if (a[l - 1] == 0) {
        neg = false;
    }
    return *this;
}
BigInteger operator*(const BigInteger& s1, const BigInteger& s2) {
    BigInteger ans;
    ans.l = s1.l + s2.l + 1;
    ans.a.resize(ans.l);
    long long k;
    for (long long i = 0; i < s1.l; ++i) {
        for (long long j = 0; j < s2.l; ++j) {
            ans.a[i + j] += s1.a[i] * s2.a[j];
            k = i + j;
            while (ans.a[k] >= 100000) {
                ans.a[k + 1] += ans.a[k] / 100000;
                ans.a[k] %= 100000;
            }
        }
    }
    while (ans.a[ans.l - 1] == 0 && ans.l > 1) {
        ans.a.pop_back();
        --ans.l;
    }
    ans.neg = s1.neg ^ s2.neg;
    if (ans.a[ans.l - 1] == 0) {
        ans.neg = false;
    }
    return ans;
}
BigInteger& BigInteger::operator*=(const BigInteger& s) {
    *this = *this * s;
    return *this;
}
BigInteger& BigInteger::operator/=(const BigInteger& s) {
    if (l < s.l) {
        *this = 0;
        return *this;
    }
    BigInteger ans, x, use;
    long long d, l0, r0;
    use.l = l;
    use.a.insert(use.a.end(), a.begin(), a.end());
    ans.l = l - s.l + 1;
    ans.a.resize(ans.l);
    x.l = l;
    x.a.resize(l - s.l);
    x.a.insert(x.a.end(), s.a.begin(), s.a.end());
    for (long long i = ans.l - 1; i >= 0; --i) {
        l0 = 0;
        r0 = 1e10;
        while (r0 - l0 > 1) {
            d = (l0 + r0) / 2;
            if (d * x <= use) {
                l0 = d;
            } else {
                r0 = d;
            }
        }
        use -= l0 * x;
        ans.a[i] = l0;
        --x.l;
        x.a.erase(x.a.begin());
    }
    ans.a.swap(a);
    l = ans.l;
    while (l > 1 && a[l - 1] == 0) {
        a.pop_back();
        --l;
    }
    neg = neg ^ s.neg;
    return *this;
}
BigInteger operator/(BigInteger s1, const BigInteger& s2) {
    s1 /= s2;
    return s1;
}
BigInteger& BigInteger::operator++() {
    if (neg) {
        if (l == 1 && a[0] == 1) {
            neg = false;
            a[0] = 0;
            return *this;
        }
        long long j = 0;
        while (a[j] == 0) {
            a[j] = 99999;
            ++j;
        }
        --a[j];
        if (a[l - 1] == 0) {
            a.pop_back();
            --l;
        }
        return *this;
    }
    long long j = 0;
    while (j < l && a[j] == 99999) {
        a[j] = 0;
        ++j;
    }
    if (j == l) {
        ++l;
        a.push_back(0);
    }
    ++a[j];
    return *this;
}
BigInteger& BigInteger::operator--() {
    if (neg) {
        long long j = 0;
        while (j < l && a[j] == 99999) {
            a[j] = 0;
            ++j;
        }
        if (j == l) {
            ++l;
            a.push_back(0);
        }
        ++a[j];
        return *this;
    }
    if (a[l - 1] == 0) {
        a[0] = 1;
        neg = true;
        return *this;
    }
    long long j = 0;
    while (a[j] == 0) {
        a[j] = 99999;
        ++j;
    }
    --a[j];
    if (a[l - 1] == 0 && l != 1) {
        --l;
        a.pop_back();
    }
    return *this;
}
BigInteger BigInteger::operator++(int) {
    BigInteger temp = *this;
    ++*this;
    return temp;
}
BigInteger BigInteger::operator--(int) {
    *this -= 1;
    BigInteger help = *this;
    help += 1;
    return help;
}
BigInteger operator"" _bi(unsigned long long c) {
    return BigInteger(c);
}
BigInteger operator"" _bi(const char* c, size_t) {
    return BigInteger(c);
}
BigInteger& BigInteger::operator%=(const BigInteger s) {
    if (l < s.l) {
        return *this;
    }
    BigInteger ans, x, use;
    long long d, l0, r0;
    use.l = l;
    use.a.insert(use.a.end(), a.begin(), a.end());
    ans.l = l - s.l + 1;
    ans.a.resize(ans.l);
    x.l = l;
    x.a.resize(l - s.l);
    x.a.insert(x.a.end(), s.a.begin(), s.a.end());
    for (long long i = ans.l - 1; i >= 0; --i) {
        l0 = 0;
        r0 = 1e10;
        while (r0 - l0 > 1) {
            d = (l0 + r0) / 2;
            if (d * x <= use) {
                l0 = d;
            } else {
                r0 = d;
            }
        }
        use -= l0 * x;
        --x.l;
        x.a.erase(x.a.begin());
    }
    use.a.swap(a);
    l = use.l;
    while (l > 1 && a[l - 1] == 0) {
        a.pop_back();
        --l;
    }
    if (a[l - 1] == 0) {
        neg = false;
    }
    return *this;
}
BigInteger operator%(BigInteger s1, const BigInteger& s2) {
    s1 %= s2;
    return s1;
}
BigInteger::BigInteger(const std::string& help) : neg(false) {
    l = (help.size() + 4) / 5;
    a.resize(l);
    int j = 0;
    if (help[0] == '-') {
        j = 1;
        neg = true;
    }
    int64_t i = (help.size() - j) % 5;
    if (i == 0) {
        i = 5;
    }
    a[l - 1] = stoi(help.substr(j, i));
    for (size_t k = i + j; k < help.size(); k += 5) {
        a[l - (k - i) / 5 - 2] = stoi(help.substr(k, 5));
    }
}
