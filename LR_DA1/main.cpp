#include <iostream>
#include <algorithm>
#include <cmath>
 
template <typename T>
class TVector {
public:
    TVector() = default;
    
    TVector(size_t newSize) {
        capacity = newSize;
        size = 0;
        storage = new T[newSize];
    }

    TVector(const TVector& v) {
        size = v.size;
        capacity = v.capacity;
        storage = new T[size];
        for (size_t i = 0; i < size; i++) {
            storage[i] = v.storage[i];
        }
    }
    
    const T& operator[](size_t index) const {
        return storage[index];
    }
 
    T& operator[](size_t index) {
        return storage[index];
    }
 
    ~TVector() {
        delete[] storage;
    }
 
    size_t sizeM() const {
        return size;
    }
 
    const T* begin() const {
        return storage;
    }
 
    const T* end() const {
        return storage + size;
    }
 
    T* Begin() {
        return storage;
    }
 
    T* End() {
        return storage + size;
    }
 
    void AddLast(const T& value) {
        if (size < capacity) {
            storage[size] = value;
            ++size;
            return;
        }
        int next_size = 10000;
        if (capacity > 0)
            next_size = capacity * 10;
 
        T* tempvec = new T[next_size];
        std::copy(begin(), end(), tempvec);
        delete[] storage;
        storage = tempvec;
        capacity = next_size;
        storage[size] = value;
        ++size;
    }
 
    TVector& operator=(TVector& other) {
        if (&other == this) {
            return *this;
        }
        if (other.size <= capacity) {
            std::copy(other.begin(), other.end(), begin());
            size = other.size;
        }
        else {
            delete[] storage;
            storage = new T[other.capacity];
            std::copy(other.begin(), other.end(), begin());
            size = other.size;
            capacity = other.capacity;
        }
        return *this;
    }
 
    TVector& operator = (TVector&& other) {
        if (&other == this) {
            return *this;
        }
        delete[] storage;
        storage = other.storage;
        other.storage = nullptr;
        size = other.size;
        other.size = 0;
        capacity = other.capacity;
        other.capacity = 0;
        return *this;
 
    }
 
private:
    std::size_t capacity = 0;
    std::size_t size = 0;
    T* storage = nullptr;
 
};
 
struct TElem {
    std::uint64_t Key;
    char Value[2049];
};
 
struct TSortElem {
    std::uint64_t Key;
    std::uint64_t Ind;
};
 
 
TVector<TSortElem> Sortvec(TVector<TSortElem>vec, std::uint64_t maxKey) {
    std::uint64_t h = pow(10, 19);
    int i, count[10] = { 0 };
    int k = vec.sizeM();
    TVector<TSortElem> res(k);
    for (std::uint64_t exp = 1; maxKey / exp > 0 && exp <= h; exp *= 10) {
        for (i = 0; i <= 9; i++)
            count[i] = 0;
        for (i = 0; i < k; i++) {
            count[(vec[i].Key / exp) % 10]++;
        }
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];
        for (i = k - 1; i >= 0; i--) {
            res[count[(vec[i].Key / exp) % 10] - 1] = vec[i];
            count[(vec[i].Key / exp) % 10]--;
        }
        for (i = 0; i < k; i++) {
            vec[i] = res[i];
        }
        if (exp == h)
            break;
    }
    return vec;
}
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    TVector<TElem> vec;
    TElem temp;
    TVector<TSortElem> vecSort;
    TVector<TSortElem> Result;
    TSortElem tempSort;
    int i = 0;
    std::uint64_t maxKey = 0;
    while (std::cin >> temp.Key >> temp.Value) {
        vec.AddLast(temp);
        if (temp.Key > maxKey) {
            maxKey = temp.Key;
        }
        tempSort.Key = vec[i].Key;
        tempSort.Ind = i;
        vecSort.AddLast(tempSort);
        i++;
    }
 
    Result = Sortvec(vecSort, maxKey);
 
    int M = vec.sizeM();
 
    for (i = 0; i < M; i++) {
        tempSort = Result[i];
        std::cout << tempSort.Key << " " << vec[tempSort.Ind].Value << "\n";
 
    }
}