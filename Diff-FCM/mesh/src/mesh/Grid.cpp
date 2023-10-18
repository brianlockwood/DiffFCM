#include "Grid.h"

Grid<3>::Grid(int nx, int ny, int nz)
    : _nx(nx)
    , _ny(ny)
    , _nz(nz)
{}

void Grid<3>::setBounds(const Point &min, const Point &max)
{
    _min = min;
    _max = max;
}

Grid<2>::Grid(int nx, int ny)
    : _nx(nx)
    , _ny(ny)
{}

void Grid<2>::setBounds(const Point &min, const Point &max)
{
    _min = min;
    _max = max;
}

