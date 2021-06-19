#pragma once

#include <iostream>
#include <vector>

namespace NBigInt
{

class TBigInt
{
public:
    static size_t const BASE = 10000;
    static size_t const RADIX = 4;

    TBigInt() = default;
    TBigInt(std::string const& str);
    void Init(std::string const& str);
    TBigInt const MultShort(TBigInt const& rhs) const;
    void DeleteLeadingZeros();
    void ShiftRight();

    friend std::istream& operator>>(std::istream& in, TBigInt& rhs);
    friend std::ostream& operator<<(std::ostream& out, TBigInt const& rhs);
    friend TBigInt const operator+(TBigInt const& lhs, TBigInt const& rhs);
    friend TBigInt const operator-(TBigInt const& lhs, TBigInt const& rhs);
    friend TBigInt const operator*(TBigInt const& lhs, TBigInt const& rhs);
    friend TBigInt const operator^(TBigInt const& lhs, TBigInt const& power);
    friend TBigInt const operator/(TBigInt const& lhs, TBigInt const& rhs);
    friend bool operator<(TBigInt const& lhs, TBigInt const& rhs);
    friend bool operator<=(TBigInt const& lhs, TBigInt const& rhs);
    friend bool operator>(TBigInt const& lhs, TBigInt const& rhs);
    friend bool operator>=(TBigInt const& lhs, TBigInt const& rhs);
    friend bool operator==(TBigInt const& lhs, TBigInt const& rhs);
    friend bool operator!=(TBigInt const& lhs, TBigInt const& rhs);

private:
    std::vector<int32_t> data;
};

}
