#include "PathfindingProcess.h"

#include <vector>

void PathfindingProcess::AddNeighborPoint(std::list<Point*>& InChecklist, Point& InPoint, const Point* ParentPoint)
{
    if(InPoint.NeedToCheck())
    {
        InPoint.SetParent(ParentPoint);
        InPoint.MarkChecked();
        InChecklist.push_back(&InPoint);
    }
}

int PathfindingProcess::FindPath(const int StartX, const int StartY, const int TargetX, const int TargetY,
    const unsigned char* Map, const int MapWidth, const int MapHeight, int* OutPath)
{
    const Vector2D Start(StartX, StartY); /** start point in the cartesian coordinate system */
    const Vector2D Target(TargetX, TargetY); /** target point in the cartesian coordinate system */

    int ResultPathLength = -1;
    if (Start.IsEqual(Target))
    {
        /**if Start and Target is in the same position, avoid any calculation and return 0 */
        ResultPathLength = 0;
    }
    else
    {
        int MapSize = MapWidth * MapHeight;
        /**
         *  allocate memory as one piece to avoid relocation of std::vector during the calculation
         *  also to speed up work with elements of the vector because there is the probability to
         *  cache parts of it in the cache lines of the processor
         *
         *  can be an issue when we have a big map and low capacity of the memory, in this case, will be better to use lazy creation of Points
         */

        std::vector<Point> MapState(MapSize);
        for (int i = 0; i < MapSize; i++)
        {
            Vector2D Location = Vector2D::MakeFromMapIndex(i, MapWidth);
            const Vector2D Distance = Target - Location;
            MapState[i] = Point(i, Location, Map[i]);
        }

        /**
         *  list of the Pointers that we need to check
         *  pathfinding process will be stopped when this list will be empty
         *  we use a list because the number of elements and their order will be continuously change
         */
        std::list<Point*> Checklist;
        Point& StartPoint = MapState[Start.ConvertToMapIndex(MapWidth)];
        StartPoint.MarkAsStart();
        Checklist.push_back(&StartPoint);

        const int MaxWidthIndex = MapWidth - 1; /** max index in the row */
        const int MaxHeightIndex = MapHeight - 1; /** max index in the col */
        std::vector<Vector2D> Directions2D = {
            Vector2D::RightVector, Vector2D::BottomVector, Vector2D::TopVector, Vector2D::LeftVector
        };

        while (!Checklist.empty())
        {
            Point* CurrentPoint = Checklist.front();
            Checklist.pop_front();

            CurrentPoint->MarkChecked();
            const Vector2D& CurrentLocation = CurrentPoint->GetLocation();

            /**
             *  add our neighbors to the checklist and increase the value of the step
             *  we ignore diagonals and use only top/bottom/left/right directions
             *  we will stop the process if one of our neighbors will be equal to the target point
             */
            for (const auto StepDirection : Directions2D)
            {
                const Vector2D NewPosition = CurrentLocation + StepDirection;
                if (NewPosition.IsInRange(0, MaxWidthIndex, MaxHeightIndex))
                {
                    Point& NextPoint = MapState[NewPosition.ConvertToMapIndex(MapWidth)];
                    AddNeighborPoint(Checklist, NextPoint, CurrentPoint);

                    if (NewPosition.IsEqual(Target))
                    {
                        Checklist.clear();
                        break;
                    }
                }
            }
        }

        /**
         * writes path points to the OutPath,
         * uses the child-parent relationship to find all indexes of the path
         */
        const Point& TargetPoint = MapState[Target.ConvertToMapIndex(MapWidth)];
        if (TargetPoint.IsChecked())
        {
            ResultPathLength = TargetPoint.GetStep();
            int ParentIndex = TargetPoint.GetIndex();
            for (int i = ResultPathLength - 1; i >= 0; i--)
            {
                OutPath[i] = ParentIndex;

                const Point& ParentPoint = MapState[ParentIndex];
                ParentIndex = ParentPoint.GetParentIndex();
            }
        }
    }

    return ResultPathLength;
}
