#pragma once

#include <array>

template <int ND> class Grid;

template <>
class Grid<3>
{
public:
    using Point = std::array<double,3>;

    Grid(int nx, int ny, int nz);

    void setBounds(const Point &min, const Point &max);

    int getNx() const { return _nx; }
    int getNy() const { return _ny; }
    int getNz() const { return _nz; }

    int getSize() const { return _nx*_ny*_nz; }

    Point getMin() const { return _min; }
    Point getMax() const { return _max; }

private:
    int _nx;
    int _ny;
    int _nz;

    Point _min;
    Point _max;
};

template <>
class Grid<2>
{
public:
    using Point = std::array<double,2>;

    Grid(int nx, int ny);

    void setBounds(const Point &min, const Point &max);

    int getNx() const { return _nx; }
    int getNy() const { return _ny; }

    int getSize() const { return _nx*_ny; }

    Point getMin() const { return _min; }
    Point getMax() const { return _max; }

private:
    int _nx;
    int _ny;

    Point _min;
    Point _max;
};