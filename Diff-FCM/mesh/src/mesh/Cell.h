#pragma once

#include <array>

#include "mesh/NodeIndex.h"
#include "mesh/CellIndex.h"
#include "mesh/EdgeIndex.h"
#include "mesh/FaceIndex.h"

class Cell
{
public: 
    Cell(const Grid<3>& grid, int i, int j, int k)
        : _i(i)
        , _j(j)
        , _k(k)
        , _nodeInd(grid)
        , _xEdgeInd(grid)
        , _yEdgeInd(grid)
        , _zEdgeInd(grid)
        , _zFaceInd(grid)
        , _yFaceInd(grid)
        , _xFaceInd(grid)
        , _cellInd(grid)
    {}

    std::array<int, 8> getNodes() const
    {
        int i = _i;
        int j = _j;
        int k = _k;

        return { _nodeInd(i,j,k),
                 _nodeInd(i+1,j,k),
                 _nodeInd(i+1,j+1,k),
                 _nodeInd(i, j+1, k),
                 _nodeInd(i,j,k+1),
                 _nodeInd(i+1,j,k+1),
                 _nodeInd(i+1,j+1,k+1),
                 _nodeInd(i, j+1, k+1)
               };    
    }

    std::array<int, 4> getXEdges() const
    {
        int i = _i;
        int j = _j;
        int k = _k;

        return { _xEdgeInd(i,j,k),
                 _xEdgeInd(i, j+1, k),
                 _xEdgeInd(i, j+1, k+1),   
                 _xEdgeInd(i, j, k+1)
               };
    }

    std::array<int, 4> getYEdges() const
    {
        int i = _i;
        int j = _j;
        int k = _k;

        return { _yEdgeInd(i,j,k),
                 _yEdgeInd(i+1, j, k),
                 _yEdgeInd(i+1, j, k+1),   
                 _yEdgeInd(i, j, k+1)
               };
    }

    std::array<int, 4> getZEdges() const
    {
        int i = _i;
        int j = _j;
        int k = _k;

        return { _yEdgeInd(i,j,k),
                 _yEdgeInd(i+1, j, k),
                 _yEdgeInd(i+1, j+1, k),   
                 _yEdgeInd(i, j+1, k)
               };
    }

    std::array<int,2> getZFaces() const
    {
        int i = _i;
        int j = _j;
        int k = _k;

        return { _zFaceInd(i,j,k),
                 _zFaceInd(i,j,k+1)
               };
    }

    std::array<int,2> getYFaces() const
    {
        int i = _i;
        int j = _j;
        int k = _k;

        return { _yFaceInd(i,j,k),
                 _yFaceInd(i,j+1,k)
               };
    }


    std::array<int,2> getXFaces() const
    {
        int i = _i;
        int j = _j;
        int k = _k;

        return { _xFaceInd(i,j,k),
                 _xFaceInd(i+1,j,k)
               };
    }

    int getIndex() const
    {
        return _cellInd(_i,_j,_k);
    }

private:
    int _i;
    int _j;
    int _k;
    NodeIndex _nodeInd;
    XEdgeIndex _xEdgeInd;
    YEdgeIndex _yEdgeInd;
    ZEdgeIndex _zEdgeInd;
    ZFacesIndex _zFaceInd;
    YFacesIndex _yFaceInd;
    XFacesIndex _xFaceInd;
    CellIndex _cellInd;
};