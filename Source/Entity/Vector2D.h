#pragma once

/**
 * Representation of the Vector in the Cartesian coordinate system
 */
class Vector2D
{
public:
    static const Vector2D ZeroVector; /** Zero Vector Direction (0, 0) */
    static const Vector2D TopVector; /** Top Vector Direction (0, 1) */
    static const Vector2D BottomVector; /** Bottom Vector Direction (0, -1) */
    static const Vector2D LeftVector; /** Left Vector Direction (-1, 0) */
    static const Vector2D RightVector; /** Right Vector Direction (1, 0) */

    Vector2D() : X(0), Y(0) {}
    Vector2D(int InX, int InY) : X(InX), Y(InY) {}

    bool IsEqual(const Vector2D& Other) const { return X == Other.X && Y == Other.Y; }
    bool IsInRange(const int MinXY, const int MaxX, const int MaxY) const
    {
        return X >= MinXY && X <= MaxX && Y >= MinXY && Y <= MaxY;
    }
    int GetMapIndex(int MapWidth) const { return X + Y * MapWidth; }

    /** Get the result of the subtraction of vectors */
    Vector2D operator-(const Vector2D& Other) const
    {
        return Vector2D(X - Other.X, Y - Other.Y);
    }

    /**Get the result of the addition of vectors */
    Vector2D operator+(const Vector2D& Other) const
    {
        return Vector2D(X + Other.X, Y + Other.Y);
    }

    /** Transformation of the cartesian position to the index of the one-dimensional array */
    int ConvertToMapIndex(int MapWidth) const { return X + Y * MapWidth; }

    /*Make Vector2D from map data*/
    static Vector2D MakeFromMapIndex(int MapIndex, int MapWidth)
    {
        const int X = MapIndex % MapWidth;
        const int Y = MapIndex / MapWidth;
        return Vector2D(X, Y);
    }

    int X;
    int Y;
};

