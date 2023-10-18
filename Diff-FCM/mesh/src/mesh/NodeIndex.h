#pragma once

#include "Grid.h"

class NodeIndex
{
public:
    NodeIndex(const Grid<3> &grid)
        : _nx(grid.getNx())
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