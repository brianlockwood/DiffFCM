#pragma once

#include "Grid.h"


// Edges aligned with X-axis
class XEdgeIndex
{
public:
    XEdgeIndex(const Grid<3> &grid)
        : _nx(grid.getNx()-1)
        , _ny(grid.getNy())
        , _nz(grid.getNz())
    {}
    
    int operator()(int i, int j, int k) const
    {
        return _nx*_ny*k + _nx*j + i;
    }

private:
    int _nx;
    int _ny;
    int _nz;
};

// Edges aligned with Y-axis
class YEdgeIndex
{
public:
    YEdgeIndex(const Grid<3> &grid)
        : _nx(grid.getNx())
        , _ny(grid.getNy()-1)
        , _nz(grid.getNz())
    {}
    
    int operator()(int i, int j, int k) const
    {
        return _nx*_ny*k + _nx*j + i;
    }

private:
    int _nx;
    int _ny;
    int _nz;
};

// Edges aligned with Z-axis
class ZEdgeIndex
{
public:
    ZEdgeIndex(const Grid<3> &grid)
        : _nx(grid.getNx())
        , _ny(grid.getNy())
        , _nz(grid.getNz()-1)
    {}
    
    int operator()(int i, int j, int k) const
    {
        return _nx*_ny*k + _nx*j + i;
    }

private:
    int _nx;
    int _ny;
    int _nz;
};