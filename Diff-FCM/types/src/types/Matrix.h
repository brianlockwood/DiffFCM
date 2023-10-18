#pragma once

#include <array>

#include "types/Vector.h"

#include <ostream>

// Statically-sized, square Matrix. Stored in Row-major order
template <typename T, int N>
class Matrix
{
public:
    Matrix() = default;

    Matrix(T a)
    {
        for (int i = 0; i < N*N; ++i)   
            _data[i] = a;
    }

    Matrix(const Matrix<T, N> &a)
    {
        for (int i = 0; i < N*N; ++i)   
            _data[i] = a._data[i];
    }


    T &operator()(int i, int j)
    {
        return _data[i*N + j];        
    }

    T operator()(int i, int j) const
    {
        return _data[i*N + j];        
    }

    Matrix<T,N> &operator=(const Matrix<T,N> &a)
    {
        for (int i = 0; i < N*N; ++i)
            _data[i] = a._data[i];

        return *this;
    }

    Matrix<T,N> &operator+=(const Matrix<T,N> &a)
    {
        for (int i = 0; i < N*N; ++i)
            _data[i] += a._data[i];

        return *this;
    }

    Matrix<T,N> &operator*=(T &a)
    {
        for (int i = 0; i < N*N; ++i)
            _data[i] *= a;

        return *this;
    }

private:
    std::array<T, N*N> _data;
};

template <typename T, int N>
Matrix<T,N> operator*(T a, const Matrix<T,N> &b)
{
    Matrix<T,N> result(b);

    result *= a;

    return result;
}

template <typename T, int N>
Matrix<T,N> operator*(const Matrix<T,N> &a, T b)
{
    return b*a;
}

template <typename T, int N>
Matrix<T,N> operator+(const Matrix<T,N> &a, const Matrix<T,N> &b)
{
    Matrix<T,N> result;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            result(i,j) = a(i,j) + b(i,j);
        }
    }

    return result;
}

template <typename T, int N>
Vector<T,N> operator*(const Matrix<T,N> &a, const Vector<T,N> &b)
{
    Vector<T,N> result;

    for (int i = 0; i < N; ++i)
    {
        result(i) = 0.0;
        for (int j = 0; j < N; ++j)
        {
            result(i) += a(i,j) + b(j);
        }
    }

    return result;
}

template <typename T, int N>
std::ostream &operator<<(std::ostream &os, const Matrix<T,N> &a)
{
    os << "[";
    for (int i = 0; i < N; ++i)
    {
        os << "[";
        for (int j = 0; j < N; ++j)
            os << a(i,j) << " ";
        if (i == N-1)
            os << "]]" << std::endl;
        else
            os << "]" << std::endl;
    }

    return os;
}