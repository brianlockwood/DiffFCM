#pragma once

#include "mesh/Grid.h"

#include <span>
#include <vector>
#include <iostream>

template <int ND, typename T>
class GridStorage;

template <typename T>
class GridStorage<2, T>
{
public:
    GridStorage(int nX, int nY)
        : _nX(nX)
        , _nY(nY)
        , _data(nX*nY, -1)
    {}

    T operator()(int i, int j) const
    {
        return _data[_nY*i + j];
    }

    T &operator()(int i, int j) 
    {
        return _data[_nY*i + j];
    }

    // Uniform 
    GridStorage<2,T> &operator=(T value)
    {
        _data.assign(_nX*_nY, value);

        return *this;
    }

    int _nX;
    int _nY;
    std::vector<T> _data;
};


template <int ND, typename T>
class GridRaggedArray;

template <typename T>
class Span
{
public:
    Span(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
        : _begin(begin)
        , _end(end)
    {}

    typename std::vector<T>::iterator begin() { return _begin; }
    typename std::vector<T>::iterator end() { return _end; }

    T &operator[](int i)
    {
        return *(_begin + i);
    }

private:
    typename std::vector<T>::iterator _begin;
    typename std::vector<T>::iterator _end;
};

template <typename T>
class Span<const T>
{
public:
    Span(typename std::vector<T>::const_iterator begin, typename std::vector<T>::const_iterator end)
        : _begin(begin)
        , _end(end)
    {}

    typename std::vector<T>::const_iterator begin() { return _begin; }
    typename std::vector<T>::const_iterator end() { return _end; }

    const T &operator[](int i)
    {
        return *(_begin + i);
    }

private:
    typename std::vector<T>::const_iterator _begin;
    typename std::vector<T>::const_iterator _end;
};


template <typename T>
class GridRaggedArray<2, T>
{
public:
    GridRaggedArray(int nX, int nY)
        : _nX(nX)
        , _nY(nY)
        , _data()
        , _offsets(nX*nY+1)
    {}

    void setCapacity(int i, int j, int size)
    {
        int index = getIndex(i,j);

        _offsets[index+1] = size;
    }

    void buildOffsets()
    {
        _offsets[0] = 0;
        for (int i = 1; i < int(_offsets.size()); ++i)
        {
            _offsets[i] += _offsets[i-1];
        }

        _data.resize(_offsets.back(), -1);
    }

    Span<T> operator()(int i, int j) 
    {
        int index = getIndex(i,j);

        return Span<T>(_data.begin()+_offsets[index], _data.begin() + _offsets[index+1]);
    }

    Span<const T> operator()(int i, int j) const
    {
        int index = getIndex(i,j);

        return Span<const T>(_data.cbegin()+_offsets[index], _data.cbegin() + _offsets[index+1]);
    }

    int getIndex(int i, int j) const { return _nY*i + j; }

    int _nX;
    int _nY;
    std::vector<T> _data;
    std::vector<unsigned int> _offsets;
};

namespace GridLoops
{
    template <typename F>
    void cellLoop(const Grid<2> &grid, const F &cellOp)
    {
        for (int i = 0; i < grid.getNx()-1; ++i)
        {
            for (int j = 0; j < grid.getNy()-1; ++j)
            {
                cellOp(i,j);
            }
        }
    }

    template <typename F>
    void nodeLoop(const Grid<2> &grid, const F &nodeOp)
    {
        for (int i = 0; i < grid.getNx(); ++i)
        {
            for (int j = 0; j < grid.getNy(); ++j)
            {
                nodeOp(i,j);
            }
        }
    }
}

struct GridDofs
{
    GridRaggedArray<2,int> cellDofs;
    int totalDofs;
};

class Cell
{
 // Consider topology visitors.
 // Still need to figure out how topology visits are kept consistent with BasisIterator
 // Basis Iterator could be nested class? 

    // template <typename Visitor>
    // void visitNodes(const Visitor &visitor)
    // {
    //     visitor(i,j);
    //     visitor(i+1,j);
    //     visitor(i,j+1);
    //     visitor(i+1,j+1);
    // }

//    auto nodeDofs();
//    {
//         {i, j},
//         {i+1, j},
//         {i, j+1},
//         {i+1, j+1}
//    };

//    auto hEdgeDofs();
//    {
//         {i, j},
//         {i, j+1}
//    };

//    auto vEdgeDofs();
//    {
//         {i, j},
//         {i+1, j}
//    };

};


static inline GridDofs labelDegreesOfFreedom(const Grid<2> &grid, const GridStorage<2, int> &cellOrder)
{   
    auto horizontalEdges = GridRaggedArray<2,int>(grid.getNx()-1, grid.getNy());
    auto verticalEdges = GridRaggedArray<2,int>(grid.getNx(), grid.getNy()-1);
    auto interiorDof = GridRaggedArray<2,int>(grid.getNx()-1, grid.getNy()-1);

    auto nodeDofs = GridStorage<2, int>(grid.getNx(), grid.getNy());

    auto cellDofs = GridRaggedArray<2,int>(grid.getNx()-1, grid.getNy()-1);

    GridLoops::cellLoop(grid, [&](int i, int j) {
        int n = cellOrder(i,j);

        horizontalEdges.setCapacity(i,j,n-2);
        horizontalEdges.setCapacity(i,j+1,n-2);
        verticalEdges.setCapacity(i,j, n-2);
        verticalEdges.setCapacity(i+1,j, n-2);

        interiorDof.setCapacity(i,j, (n-2)*(n-2));

        cellDofs.setCapacity(i,j, n*n);
    });

    horizontalEdges.buildOffsets();
    verticalEdges.buildOffsets();
    interiorDof.buildOffsets();
    cellDofs.buildOffsets();

    int totalDof = 0;

   GridLoops::cellLoop(grid, [&](int i, int j) {
       int n = cellOrder(i,j);

        if (nodeDofs(i,j) == -1)
        {
            nodeDofs(i,j) = totalDof;
            totalDof++;
        }

        auto hEdge0 = horizontalEdges(i,j);

        for (int l = 0; l < n-2; ++l)
        {
            if (hEdge0[l]==-1)
            {
                hEdge0[l] = totalDof;
                totalDof++;
            }
        }

        if (nodeDofs(i+1,j) == -1)
        {
            nodeDofs(i+1,j) = totalDof;
            totalDof++;
        }
    
        auto vEdge0 = verticalEdges(i,j);
        auto vEdge1 = verticalEdges(i+1,j);

        auto intEdge = interiorDof(i,j);

        for (int k = 0; k < n-2; ++k)
        {
            if (vEdge0[k]==-1)
            {
                vEdge0[k] = totalDof;
                totalDof++;
            }

            for (int l = 0; l < n-2; ++l)
            {
                intEdge[k*(n-2)+l] = totalDof;
                totalDof++;
            }

            if (vEdge1[k]==-1)
            {
                vEdge1[k] = totalDof;
                totalDof++;
            }
        }

        if (nodeDofs(i,j+1) == -1)
        {
            nodeDofs(i,j+1) = totalDof;
            totalDof++;
        }

        auto hEdge1 = horizontalEdges(i,j+1);

        for (int l = 0; l < n-2; ++l)
        {
            if (hEdge1[l]==-1)
            {
                hEdge1[l] = totalDof;
                totalDof++;
            }
        }

        if (nodeDofs(i+1,j+1) == -1)
        {
            nodeDofs(i+1,j+1) = totalDof;
            totalDof++;
        }
   });

    GridLoops::cellLoop(grid, [&](int i, int j) {

        int n = cellOrder(i,j);

        auto dofs = cellDofs(i,j);

        dofs[0] = nodeDofs(i,j);

        auto hEdge0 = horizontalEdges(i,j);
        for (int l = 0; l < n-2; ++l)
            dofs[l+1] = hEdge0[l];

        dofs[n-1] = nodeDofs(i+1,j);

        auto vEdge0 = verticalEdges(i,j);
        auto vEdge1 = verticalEdges(i+1,j);

        auto intEdge = interiorDof(i,j);

        for (int k = 0; k < n-2; ++k)
        {
            dofs[n + k*n] = vEdge0[k];

            for (int l = 0; l < n-2; ++l)
            {
                dofs[n + k*n + l + 1] = intEdge[k*(n-2)+l];
            }

            dofs[n + k*n + n-1] = vEdge1[k];
        }

        dofs[(n-1)*n] = nodeDofs(i,j+1);
        
        auto hEdge1 = horizontalEdges(i,j+1);
        for (int l = 0; l < n-2; ++l)
        {
            dofs[(n-1)*n + l + 1] = hEdge1[l];
        }

        dofs[n*n - 1] = nodeDofs(i+1, j+1);
    });


    return {cellDofs, totalDof};
}