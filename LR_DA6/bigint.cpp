#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include "bigint.hpp"

namespace NBigInt
{

TBigInt::TBigInt(std::string const& str) { this->Init(str); }

void TBigInt::Init(std::string const& str)
{
    data.clear();
    int size = static_cast<int>(str.size());
    for (int i = size - 1; i >= 0; i = i - TBigInt::RADIX)
    {
        if (i < TBigInt::RADIX) { data.push_back(static_cast<int32_t>(atoll(str.substr(0, i + 1).c_str()))); }
        else { data.push_back(static_cast<int32_t>(atoll(str.substr(i - TBigInt::RADIX + 1, TBigInt::RADIX).c_str())));}
    }
    DeleteLeadingZeros();
}

void TBigInt::DeleteLeadingZeros()
{
    while(!data.empty() && data.back() == 0) { data.pop_back(); }
}

std::istream& operator>>(std::istream& in, TBigInt& rhs)
{
    std::string str;
    in >> str;
    rhs.Init(str);
    return in;
}

std::ostream& operator<<(std::ostream& out, TBigInt const& rhs)
{
    if(rhs.data.empty())
    {
        out << "0";
        return out;
    }
    out << rhs.data.back();
    for(int i = rhs.data.size() - 2; i >= 0; --i)
    {
        out << std::setfill('0') << std::setw(TBigInt::RADIX) << rhs.data[i];
    }
    return out;
}

TBigInt const operator+(TBigInt const& lhs, TBigInt const& rhs)
{
    TBigInt res;
    int32_t carry = 0;
    size_t n = std::max(lhs.data.size(), rhs.data.size());
    res.data.resize(n);
    for(size_t i = 0; i < n; ++i)
    {
        int32_t sum = carry;
        if(i < rhs.data.size()) { sum += rhs.data[i]; }
        if(i < lhs.data.size()) { sum += lhs.data[i]; }
        carry = sum / TBigInt::BASE;
        res.data[i] = sum % TBigInt::BASE;
    }
    if(carry != 0) { res.data.push_back(static_cast<int32_t>(1)); }
    res.DeleteLeadingZeros();
    return res;
}

TBigInt const operator-(TBigInt const& lhs, TBigInt const& rhs)
{
    TBigInt res;
    int32_t carry = 0;
    size_t n = std::max(lhs.data.size(), rhs.data.size());
    res.data.resize(n);
    for(size_t i = 0; i < n; ++i)
    {
        int32_t sub = lhs.data[i] - carry;
        if(i < rhs.data.size()) { sub -= rhs.data[i]; }
        carry = 0;
        if(sub < 0)
        {
            carry = 1;
            sub += TBigInt::BASE;
        }
        res.data[i] = sub % TBigInt::BASE;
    }
    res.DeleteLeadingZeros();
    return res;
}

TBigInt const operator*(TBigInt const& lhs, TBigInt const& rhs)
{
    if(rhs.data.size() == 1) { return lhs.MultShort(rhs); }
    if(lhs.data.size() == 1) { return rhs.MultShort(lhs); }
    TBigInt res;
    size_t n = lhs.data.size() * rhs.data.size();
    res.data.resize(n + 1);
    int32_t k = 0;
    int32_t r = 0;
    for(size_t i = 0; i < lhs.data.size(); ++i)
    {
        for(size_t j = 0; j < rhs.data.size(); ++j)
        {
            k = rhs.data[j] * lhs.data[i] + res.data[i+j];
            r = k / TBigInt::BASE;
            res.data[i+j+1] = res.data[i+j+1] + r;
            res.data[i+j] = k % TBigInt::BASE;
        }
    }
    res.DeleteLeadingZeros();
    return res;
}

TBigInt const TBigInt::MultShort(TBigInt const& rhs) const
{
    int32_t carry = 0;
    int32_t mult = 0;
    size_t size = data.size();
    TBigInt res;

    for (size_t i = 0; i < size; ++i)
    {
        mult = data[i] * rhs.data[0] + carry;
        res.data.push_back(mult % BASE);
        carry = mult / BASE;
    }
    if (carry != 0) { res.data.push_back(carry); }
    res.DeleteLeadingZeros();
    return res;
}

TBigInt const operator^(TBigInt const& lhs, TBigInt const& power)
{
    TBigInt res("1");
    TBigInt two("2");
    TBigInt one("1");
    TBigInt zero("0");
    if(power == zero) { return res; }
    if(power == one || lhs == one) { return lhs; }
    if(power.data[0] % 2 == 0)
    {
        TBigInt res = lhs ^ (power / two);
        return res * res;
    }
    else
    {
        TBigInt res = lhs ^ (power - one);
        return lhs * res;
    }
}

void TBigInt::ShiftRight()
{
    if (data.size() == 0)
    {
        data.push_back(0);
        return;
    }
    data.push_back(data[data.size() - 1]);
    for (size_t i = data.size() - 2; i > 0; --i) { data[i] = data[i - 1]; }
    data[0] = 0;
}

TBigInt const operator/(TBigInt const& lhs, TBigInt const& rhs)
{
    TBigInt curr, res;
    size_t lhs_size = lhs.data.size();
    res.data.resize(lhs_size);
    int l = 0;
    int r = TBigInt::BASE;
    int m = 0;
    int data_res = 0;
    for(int i = lhs_size - 1; i >= 0; --i)
    {
        m = 0;
        l = 0;
        r = TBigInt::BASE;
        curr.ShiftRight();
        curr.data[0] = lhs.data[i];
        curr.DeleteLeadingZeros();
        while(l <= r)
        {
            m = (l + r) / 2;
            if(rhs * TBigInt(std::to_string(m)) <= curr)
            {
                data_res = m;
                l = m + 1;
            }
            else { r = m - 1; }
        }
        res.data[i] = data_res;
        curr = curr - rhs * TBigInt(std::to_string(data_res));
    }
    res.DeleteLeadingZeros();
    return res;
}

bool operator<(TBigInt const& lhs, TBigInt const& rhs)
{
    if(lhs.data.size() != rhs.data.size()) { return lhs.data.size() < rhs.data.size(); }
    for(int i = lhs.data.size() - 1; i >= 0; --i)
    {
        if(lhs.data[i] != rhs.data[i]) { return  lhs.data[i] < rhs.data[i]; }
    }
    return false;
}

bool operator==(TBigInt const& lhs, TBigInt const& rhs) { return !(lhs < rhs) && !(rhs < lhs); }
bool operator!=(TBigInt const& lhs, TBigInt const& rhs) { return !(lhs == rhs); }
bool operator<=(TBigInt const& lhs, TBigInt const& rhs) { return !(rhs < lhs); }
bool operator>(TBigInt const& lhs, TBigInt const& rhs) { return !(lhs <= rhs); }
bool operator>=(TBigInt const& lhs, TBigInt const& rhs) { return !(lhs < rhs); }

}
