#pragma once

#include "Grid.h"

class CellIndex
{
public:
    CellIndex(const Grid<3> &grid)
        : _nx(grid.getNx()-1)
        , _ny(grid.getNy()-1)
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