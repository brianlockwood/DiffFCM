#pragma once

#include <array>
#include <iostream>

#include "types/Matrix.h"

template <int Order, typename ScalarType = double>
class BSpline
{
public:
    constexpr BSpline()
    {
        for (int i = 0; i < Order+1; ++i)
            _knots[i] = -1.0;
        for (int i = 0; i < Order+1; ++i)
            _knots[i + Order + 1] = 1.0;
    }

    constexpr ScalarType operator()(int index, ScalarType x)
    {
        return evalImpl<Order>(index, x);
    }

    static constexpr int size() { return Order + 1; }

private:
    template <int Order2>
    constexpr ScalarType evalImpl(int index, ScalarType x)
    {
        if constexpr (Order2 == 0)
        {
            if (index == Order)
                return ScalarType(1.0);
            else
                return ScalarType(0.0);
        } 
        else
        {
            ScalarType Ni = evalImpl<Order2-1>(index, x);
            ScalarType Nip = evalImpl<Order2-1>(index+1, x);

            ScalarType a(0.0);
            ScalarType b(0.0);

            if (index < Order+1 && index + Order2 >= Order+1)
            {    
                a = (x + 1.0)/(2.0);
            }
            if (index+1 < Order+1 && index + Order2 + 1 >= Order+1)
            {
                b = (1.0 - x)/(2.0);
            }
            return a*Ni + b*Nip;
        } 
    }

    std::array<double, 2*Order+2> _knots;
};


enum class Topology 
{
    Cell,
    Nodes, 
    HorizontalEdge,
    VerticalEdge,
    Interior
};

template <int ND, Topology topology, int Size>
struct MultiIndex;

template <int Size>
struct MultiIndex<2, Topology::Cell, Size>
{
    MultiIndex(int i, int j)
         : i(i)
         , j(j)
         , index(j*Size + i)
    {}

    int i; 
    int j;
    int index;

    MultiIndex<2, Topology::Cell, Size> operator++()
    {
        ++i;
        if (i == Size)
        {
            i = 0;
            ++j;
        }
        index++;

        return *this;
    }

    bool operator!=(const MultiIndex<2, Topology::Cell, Size> &other)
    {
        return (i != other.i) || (j != other.j);
    }

    static constexpr MultiIndex<2, Topology::Cell, Size> front() { return {0,0}; }
    static constexpr MultiIndex<2, Topology::Cell, Size> back() { return {Size-1, Size-1}; }
};

template <int Size>
struct MultiIndex<2, Topology::Nodes, Size>
{
    MultiIndex(int i, int j)
         : i(i)
         , j(j)
         , index(j*Size + i)
    {}

    int i; 
    int j;
    int index;

    MultiIndex<2, Topology::Nodes, Size> operator++()
    {
        i = i + Size-1;
        if (i >= Size)
        {
            i = 0;
            j = j + Size-1;
        }
        index++;

        return *this;
    }

    bool operator!=(const MultiIndex<2, Topology::Nodes, Size> &other)
    {
        return (i != other.i) || (j != other.j);
    }

    static constexpr MultiIndex<2, Topology::Nodes, Size> front() { return {0,0}; }
    static constexpr MultiIndex<2, Topology::Nodes, Size> back() { return {Size-1, Size-1}; }
};

template <int Size>
struct MultiIndex<3, Topology::Cell, Size>
{
    MultiIndex(int i, int j, int k)
         : i(i)
         , j(j)
         , k(k)
         , index(k*Size*Size + j*Size + i)
    {}

    int i; 
    int j;
    int k;
    int index;

    MultiIndex<3, Topology::Cell, Size> operator++()
    {
        ++i;
        if (i == Size)
        {
            i = 0;
            ++j;
            if (j == Size)
            {
                j = 0;
                ++k;
            }
        }
        index++;

        return *this;
    }

    bool operator!=(const MultiIndex<3, Topology::Cell, Size> &other)
    {
        return (i != other.i) || (j != other.j) || (k != other.k);
    }

    static constexpr MultiIndex<3, Topology::Cell, Size> front() { return {0,0,0}; }
    static constexpr MultiIndex<3, Topology::Cell, Size> back() { return {Size-1, Size-1, Size-1}; }
};

template <int Size>
struct MultiIndex<3, Topology::Nodes, Size>
{
    MultiIndex(int i, int j, int k)
         : i(i)
         , j(j)
         , k(k)
         , index(k*Size*Size + j*Size + i)
    {}

    int i; 
    int j;
    int k;
    int index;

    MultiIndex<3, Topology::Nodes, Size> operator++()
    {
        i = i + Size-1;
        if (i >= Size)
        {
            i = 0;
            j = j + Size-1;
            if (j >= Size)
            {
                j = 0;
                k = k + Size-1;
            }
        }
        index++;

        return *this;
    }

    bool operator!=(const MultiIndex<3, Topology::Nodes, Size> &other)
    {
        return (i != other.i) || (j != other.j) || (k != other.k);
    }

    static constexpr MultiIndex<3, Topology::Nodes, Size> front() { return {0,0,0}; }
    static constexpr MultiIndex<3, Topology::Nodes, Size> back() { return {Size-1, Size-1, Size-1}; }
};


template <typename BasisType, Topology Type, int ND>
class Basis
{
public:
    static constexpr int size() 
    {   
        if constexpr (ND == 2)
            return BasisType::size()*BasisType::size(); 
        else if constexpr (ND == 3)
            return BasisType::size()*BasisType::size()*BasisType::size(); 
    }

    Basis() = default;

    class BasisFunction
    {
    public:
        BasisFunction(BasisType &basis,
                      MultiIndex<ND, Type, BasisType::size()> index)
            : basis_(basis)
            , index_(index)
        {}

        BasisFunction operator++()
        {
            ++index_;

            return *this;
        }

        template <int ND2 = ND>
        std::enable_if_t<ND2==2, double> eval(double x, double y) const
        {
            int j = index_.j;
            int i = index_.i;

            return basis_(i, x)*basis_(j,y);
        }

        template <int ND2 = ND>
        std::enable_if_t<ND2==3, double> eval(double x, double y, double z) const
        {
            int k = index_.k;
            int j = index_.j;
            int i = index_.i;

            return basis_(i, x)*basis_(j,y)*basis_(k,z);
        }

        int index() const { return index_.index; }

        bool operator!=(const BasisFunction &other)
        {
            return index_ != other.index_;
        }

        BasisFunction &operator*() { return *this; }

    private:
        BasisType &basis_;
        MultiIndex<ND, Type, BasisType::size()> index_;
    };

    BasisFunction begin() 
    { 
        return BasisFunction(basis_, MultiIndex<ND, Type, BasisType::size()>::front()); 
    }

    BasisFunction end() 
    { 
        return BasisFunction(basis_, ++MultiIndex<ND, Type, BasisType::size()>::back()); 
    }

    BasisType basis_;
};

template <int Order, typename T>
using BSplineBasis = Basis<BSpline<Order, T>, Topology::Cell, 2>;