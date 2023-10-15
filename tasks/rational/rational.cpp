#include "rational.h"
#include <numeric>
#include <string>

const int64_t DECIMAL_BASE = 10;

enum class PartOfRational { Numerator, Denominator };

Rational::Rational() {
    numer_ = 0;
    denom_ = 1;
}

Rational::Rational(int value) : numer_{value} {
    denom_ = 1;
}

Rational::Rational(int numer, int denom) : numer_{numer}, denom_{denom} {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    numer_ = value;
}

void Rational::SetDenominator(int value) {
    if (value == 0) {
        throw RationalDivisionByZero{};
    }
    denom_ = value;
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int64_t new_numer = static_cast<int64_t>(lhs.GetDenominator()) * static_cast<int64_t>(rhs.GetNumerator()) +
                        static_cast<int64_t>(rhs.GetDenominator()) * static_cast<int64_t>(lhs.GetNumerator());
    int64_t new_denom = static_cast<int64_t>(lhs.GetDenominator()) * static_cast<int64_t>(rhs.GetDenominator());
    int64_t gcd = std::gcd(new_denom, new_numer);
    new_numer /= gcd;
    new_denom /= gcd;
    lhs.Set(new_numer, new_denom);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    int64_t new_numer = static_cast<int64_t>(lhs.GetNumerator()) * static_cast<int64_t>(rhs.GetNumerator());
    int64_t new_denom = static_cast<int64_t>(lhs.GetDenominator()) * static_cast<int64_t>(rhs.GetDenominator());
    int64_t gcd = std::gcd(new_denom, new_numer);
    new_numer /= gcd;
    new_denom /= gcd;
    lhs.Set(new_numer, new_denom);
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.SetNumerator(ratio.GetDenominator() + ratio.GetNumerator());
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.SetNumerator(ratio.GetNumerator() - ratio.GetDenominator());
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    std::string input;
    std::cin >> input;
    int64_t numer = 0;
    int64_t denom = 0;
    size_t first_digit = 0;
    if (input[0] == '-') {
        ++first_digit;
    }
    PartOfRational digit_of = PartOfRational::Numerator;
    for (size_t i = first_digit; i < input.size(); ++i) {
        if (input[i] == '/') {
            digit_of = PartOfRational::Denominator;
            continue;
        }
        if (digit_of == PartOfRational::Numerator) {
            numer *= DECIMAL_BASE;
            numer += (input[i] - '0');
        } else {
            denom *= DECIMAL_BASE;
            denom += (input[i] - '0');
        }
    }
    if (digit_of == PartOfRational::Numerator) {
        denom = 1;
    }
    if (first_digit == 1) {
        numer = -numer;
    }
    ratio.Set(numer, denom);
    return is;
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    numer_ = static_cast<int>(numer);
    denom_ = static_cast<int>(denom);
}

Rational operator+(const Rational& ratio) {
    Rational result = ratio;
    return result;
}

Rational operator-(const Rational& ratio) {
    Rational result = ratio;
    result.SetNumerator(-result.GetNumerator());
    return result;
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs += -rhs;
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    Rational inversed_rhs(rhs.GetDenominator(), rhs.GetNumerator());
    lhs *= inversed_rhs;
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result += rhs;
    return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result -= rhs;
    return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result *= rhs;
    return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result /= rhs;
    return result;
}

Rational operator++(Rational& ratio, int) {
    Rational original = ratio;
    ++ratio;
    return original;
}

Rational operator--(Rational& ratio, int) {
    Rational original = ratio;
    --ratio;
    return original;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    Rational diff = lhs - rhs;
    return diff.GetNumerator() < 0;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    Rational diff = lhs - rhs;
    return diff.GetNumerator() > 0;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    Rational diff = lhs - rhs;
    return diff.GetNumerator() <= 0;
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    Rational diff = lhs - rhs;
    return diff.GetNumerator() >= 0;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.GetNumerator() == rhs.GetNumerator()) && (lhs.GetDenominator() == rhs.GetDenominator());
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return (lhs.GetNumerator() != rhs.GetNumerator()) || (lhs.GetDenominator() != rhs.GetDenominator());
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    if (ratio.GetDenominator() == 1) {
        std::cout << ratio.GetNumerator();
        return os;
    }
    std::cout << ratio.GetNumerator() << "/" << ratio.GetDenominator();
    return os;
}