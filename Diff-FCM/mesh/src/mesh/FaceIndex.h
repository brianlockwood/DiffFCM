#pragma once

#include "Grid.h"


// Faces with Normals in the Z direction
class ZFacesIndex
{
public:
    ZFacesIndex(const Grid<3> &grid)
        : _nx(grid.getNx()-1)
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

// Faces with Normals in the Y direction
class YFacesIndex
{
public:
    YFacesIndex(const Grid<3> &grid)
        : _nx(grid.getNx()-1)
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


// Faces with Normals in the X direction
class XFacesIndex
{
public:
    XFacesIndex(const Grid<3> &grid)
        : _nx(grid.getNx())
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
