#pragma once
#include <list>

#include "../Entity/Point.h"

class PathfindingProcess
{
public:

    PathfindingProcess() {}
    ~PathfindingProcess() {}
   
    /**
     *  adds neighbor to the list if the Point wasn't checked yet
     */
    void AddNeighborPoint(std::list<Point*>& InChecklist, Point& InPoint, const Point* ParentPoint);

    int FindPath(const int StartX, const int StartY,
        const int TargetX, const int TargetY,
        const unsigned char* Map, const int MapWidth, const int MapHeight,
        int* OutPath);
};

