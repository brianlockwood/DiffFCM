#pragma once

#include <array>

#include "Grid.h"

template <int ND> class Coord;

template <>
class Coord<3>
{
public:
    using Point = Grid<3>::Point;

    Coord(const Grid<3> &grid)
        : _min(grid.getMin())
    {
        const Point &min = grid.getMin();
        const Point &max = grid.getMax();

        int nx = grid.getNx();
        int ny = grid.getNy();
        int nz = grid.getNz();

        _delta[0] = (max[0]-min[0])/double(nx-1);
        _delta[1] = (max[1]-min[1])/double(ny-1);
        _delta[2] = (max[2]-min[2])/double(nz-1);
    }
    
    Point operator()(int i, int j, int k)
    {
        return { _min[0]+i*_delta[0], _min[1]+j*_delta[1], _min[2]+k*_delta[2]};
    }

private:
    Point _min;
    std::array<double,3> _delta;
};

template <>
class Coord<2>
{
public:
    using Point = Grid<2>::Point;

    Coord(const Grid<2> &grid)
        : _min(grid.getMin())
    {
        const Point &min = grid.getMin();
        const Point &max = grid.getMax();

        int nx = grid.getNx();
        int ny = grid.getNy();

        _bounds[0] = nx;
        _bounds[1] = ny;

        _delta[0] = (max[0]-min[0])/double(nx-1);
        _delta[1] = (max[1]-min[1])/double(ny-1);
    }
    
    Point operator()(int i, int j) const
    {
        return { _min[0]+i*_delta[0], _min[1]+j*_delta[1]};
    }

    struct Index
    {
        int i;
        int j;
    };

    Index getNode(const Point &point) const
    {
        int i = (point[0] - _min[0])/_delta[0];
        int j = (point[1] - _min[1])/_delta[1];

        return {std::min(i,_bounds[0]-2), std::min(j, _bounds[1]-2)};
    }

    // Map Global Points to [-1,1] interval
    Point getLocalCoord(int i, int j, const Point &globalPoint) const
    {
        auto [xi, yi] = this->operator()(i,j);

        double xp = 2*(globalPoint[0] - xi)/_delta[0] - 1;
        double yp = 2*(globalPoint[1] - yi)/_delta[1] - 1;

        return {xp, yp};
    }

//private:
    Point _min;
    std::array<int,2> _bounds;
    std::array<double,2> _delta;
};