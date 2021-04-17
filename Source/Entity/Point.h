#pragma once
#include <climits>
#include <string>

#include "Vector2D.h"

/**
 * Wrapper over the map element,
 * an entity to store the current state of the particular node on a graph
 */

class Point
{
public:
    Point() : Location(Vector2D::ZeroVector), MyIndex(-1), ParentIndex(-1)
        , Step(INT_MAX), bIsTraversable(false), bIsChecked(false)
    {
    }

    Point(int InIndex, Vector2D InLocation, unsigned char Traversability)
        : Location(InLocation)
        , MyIndex(InIndex)
        , Step(INT_MAX)
        , bIsTraversable(Traversability != 0)
        , bIsChecked(false)
    {
    }

    ~Point() {}

    const Vector2D& GetLocation() const { return Location; }

    bool IsEqual(int OtherIndex) const { return MyIndex == OtherIndex; } /** equality of points by index */
    bool IsChecked() const { return bIsChecked; } /** returns false to avoid loop if this point has already checked */
    bool NeedToCheck() const { return !bIsChecked && bIsTraversable; } /** returns true if the point is traversable and wasn't checked yet */
    void MarkChecked() { bIsChecked = true; } /** Mark Point as processed to avoid loop */
    void MarkAsStart() { Step = 0; ParentIndex = -1; } /** set up point as a Start Point of the path-finding */

    int GetIndex() const { return MyIndex; }
    int GetParentIndex() const { return ParentIndex; }
    int GetStep() const { return Step; }
    std::string GetStepDebugSymbol() const
    {
        if (bIsTraversable && bIsChecked)
        {
            const std::string StringStep = std::to_string(Step);
            return "|" + StringStep + "|";
        }
        return "|--|";
    }

    void SetParent(const Point* ParentPoint) /** save information about the parent, and increase the step */
    {
        if (bIsTraversable)
        {
            ParentIndex = ParentPoint->MyIndex;
            Step = ParentPoint->Step + 1;
        }
    }

private:
    Vector2D Location; /**2D location of the point on the map*/

    int MyIndex = -1;  /** Index in the one-dimensional array of the map */
    int ParentIndex = -1; /** Index of the parent Point in the one-dimensional array of the map */

    int Step = INT_MAX; /** Number of the iteration in the path-finding process, the step of the start point is equal to nil*/
    bool bIsTraversable = false; /** blocked / unblocked state of the point*/
    bool bIsChecked = false; /** current state of the point | the point marked as checked if it had used in the path-finding calculation*/
};

