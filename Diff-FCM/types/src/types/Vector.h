#pragma once

#include <array>

template <typename T, int N>
class Vector
{
public:
    Vector() = default;

    T &operator()(int i)
    {
        return _data[i];
    }

    T operator()(int i) const
    {
        return _data[i];
    }

    Vector<T,N> &operator=(const Vector<T,N> &a)
    {
        for (int i = 0; i < N; ++i)
            _data[i] = a._data[i];

        return this;
    }

    Vector<T,N> &operator+=(const Vector<T,N> &a)
    {
        for (int i = 0; i < N; ++i)
            _data[i] += a._data[i];

        return this;
    }

    Vector<T,N> &operator*=(T &a)
    {
        for (int i = 0; i < N; ++i)
            _data[i] *= a;

        return this;
    }


private:
    std::array<T, N> _data;
};

template <typename T, int N>
Vector<T,N> operator*(T a, const Vector<T,N> &b)
{
    Vector<T,N> result;

    for (int i = 0; i < N; ++i)
    {
        result(i) = a*b(i);
    }

    return result;
}

template <typename T, int N>
Vector<T,N> operator*(const Vector<T,N> &a, T b)
{
    return b*a;
}

template <typename T, int N>
Vector<T,N> operator+(const Vector<T,N> &a, const Vector<T,N> &b)
{
    Vector<T,N> result;

    for (int i = 0; i < N; ++i)
    {
        result(i) = a(i) + b(i);
    }

    return result;
}
