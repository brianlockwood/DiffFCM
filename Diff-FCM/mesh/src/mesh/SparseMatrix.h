#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-enum-enum-conversion"
#pragma GCC diagnostic ignored "-Wdeprecated-copy"
#include <Eigen/Sparse>
#include<Eigen/SparseLU>
#pragma GCC diagnostic pop

#include <iostream>

class SparseMatrix
{
public:
    SparseMatrix(int size)
        : _spMat(size, size)
    {}

    class EntryRef
    {
    public:
        EntryRef(int i, int j, SparseMatrix &spMatrix)
            : _i(i)
            , _j(j)
            , _spMatrix(spMatrix)
        {}

        EntryRef &operator+=(double value)
        {   
            _spMatrix._triplets.push_back({_i, _j, value});

            return *this;
        }

        EntryRef &operator=(double value)
        {
            _spMatrix.coeff(_i,_j) = value;

            return *this;
        }

        operator double() const 
        {
            return _spMatrix.coeff(_i,_j);
        }

        operator double&()  
        {
            return _spMatrix.coeff(_i,_j);
        }

    private:
        int _i;
        int _j;
        SparseMatrix &_spMatrix;
    };

    EntryRef operator()(int i, int j)
    {
        return {i, j, *this};
    }

    double operator()(int i, int j) const
    {
        return coeff(i,j);
    }

    void assemble()
    {
        _spMat.setFromTriplets(_triplets.begin(), _triplets.end());
    }

    int nonZeros() const
    {
        return _spMat.nonZeros();
    }

    friend std::vector<double> solve(SparseMatrix &matrix, std::vector<double> &b);

//private:
    double coeff(int i, int j) const
    {
        return _spMat.coeff(i,j);
    }

    double &coeff(int i, int j)
    {
        return _spMat.coeffRef(i,j);
    }

    std::vector<Eigen::Triplet<double>> _triplets;
    Eigen::SparseMatrix<double> _spMat;
};


inline std::vector<double> solve([[maybe_unused]] SparseMatrix &matrix, std::vector<double> &b)
{
    Eigen::VectorXd bVector = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(b.data(), b.size());
    Eigen::SparseLU<Eigen::SparseMatrix<double> > solver;
    solver.compute(matrix._spMat);
 
    Eigen::VectorXd x = solver.solve(bVector);

    return std::vector<double>(x.data(), x.data() + b.size());
}
