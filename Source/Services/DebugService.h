#pragma once
#include <iostream>
#include <vector>


#include "../Core/PathfindingProcess.h"
#include "../Entity/Point.h"

#define DEBUG_DRAWER_ENABLED 1  /** define to enable debug drawing*/
#define DEBUG_PRINTER_ENABLED 0 /** define to enable debug printing*/

/**
 *  Few methods to help understand what happens in the calculation process,
 *  draws the map and prints path's nodes
 *
 */
struct DebugHelper
{
    /** Draws point steps */
    static void DrawSteps(const std::vector<Point>& MapState, const int MapWidth, const int MapHeight)
    {
#if (DEBUG_DRAWER_ENABLED)
        const int CanvasSize = (MapWidth * MapHeight);
        auto Canvas = new std::string[CanvasSize];

        auto CurCanvas = [&Canvas, MapWidth, MapHeight](int x, int y) -> std::string* { return &Canvas[x + MapWidth * y]; };
        auto DrawCanvas = [MapHeight, MapWidth, &CurCanvas]() {for (int y = 0; y < MapHeight; y++)
        {
            for (int x = 0; x < MapWidth; x++)
            {
                std::cout << *CurCanvas(x, y);
            }
            std::cout << std::endl;
            for (int x = 0; x < MapWidth; x++)
            {
                std::cout << "----";
            }
            std::cout << std::endl;

        }};

        for (const Point& Point : MapState)
        {
            const int IndexX = Point.GetLocation().X;
            const int IndexY = Point.GetLocation().Y;
            *CurCanvas(IndexX, IndexY) = Point.GetStepDebugSymbol();
        }

        DrawCanvas();
#endif
    }

    /** Prints path-finding result*/
    static void PrintPath(const int StepCounter, int* Path, bool Forced = false)
    {
#if (DEBUG_PRINTER_ENABLED)
        printf("Steps : %d", StepCounter);
        std::cout << std::endl;

        if (StepCounter == 0)
        {
            std::cout << Path[0] << std::endl;
        }

        for (int i = 0; i < StepCounter; i++)
        {
            std::cout << Path[i] << std::endl;
        }
#endif
    }

    /** Draws map, start and target points, and the path that was found previously */
    static void DrawPath(const int StartX, const int StartY, const int TargetX, const int TargetY,
        const unsigned char* Map, const int MapWidth, const int MapHeight, int* Path, int PathLength)
    {
#if (DEBUG_DRAWER_ENABLED)
        const int CanvasSize = (MapWidth * MapHeight);
        auto* Canvas = new unsigned char[CanvasSize];

        auto CurCanvas = [&Canvas, MapWidth, MapHeight](int x, int y) -> unsigned char* { return &Canvas[x + MapWidth * y]; };
        auto FillCanvas = [CanvasSize, &CurCanvas](unsigned char Sprite) { for (int i = 0; i < CanvasSize; i++) { *CurCanvas(i, 0) = Sprite; }};
        auto DrawCanvas = [MapHeight, MapWidth, &CurCanvas]() {for (int y = 0; y < MapHeight; y++) { for (int x = 0; x < MapWidth; x++) { std::cout << *CurCanvas(x, y); } std::cout << std::endl; }};

        FillCanvas(0xB0);

        for (int Index = 0; Index < CanvasSize; Index++)
        {
            if (Map[Index] == 0)
            {
                const int IndexX = Index % MapWidth;
                const int IndexY = Index / MapWidth;
                *CurCanvas(IndexX, IndexY) = '+';
            }
        }

        for (int i = 0; i < PathLength; i++)
        {
            const int Index = Path[i];
            const int IndexX = Index % MapWidth;
            const int IndexY = Index / MapWidth;
            *CurCanvas(IndexX, IndexY) = 'P';
        }
        *CurCanvas(StartX, StartY) = 'S';
        *CurCanvas(TargetX, TargetY) = 'F';

        DrawCanvas();
#endif
    }
};

/**List of prepared tests to validate the algorithm*/
class DebugService
{
public:

    void RunTest_1()
    {
        std::cout << "RunTest_1 STARTED" << std::endl;
        unsigned char Map[] = {
            1, 1, 1, 1,
            0, 1, 0, 1,
            0, 1, 1, 1
        };
        int OutPath[3];

        PathfindingProcess TestFinder;
        const int StepCounter = TestFinder.FindPath(0, 0, 1, 2, Map, 4, 3, OutPath);

        if (StepCounter >= 0)
        {
            if (OutPath[0] == 1
                && OutPath[1] == 5
                && OutPath[2] == 9)
            {
                DebugHelper::PrintPath(StepCounter, OutPath, false);
                DebugHelper::DrawPath(0, 0, 1, 2, Map, 4, 3, OutPath, StepCounter);
                std::cout << "RunTest_1 COMPLETED SUCCESSFUL " << std::endl;
            }
            else
            {
                std::cout << "RunTest_1 CRASHED" << std::endl;
            }
        }
        else
        {
            std::cout << "RunTest_1 FAILED" << std::endl;
        }
    }

    void RunTest_2()
    {
        std::cout << "RunTest_2 STARTED" << std::endl;
        unsigned char Map[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
        int OutPath[7];
        PathfindingProcess TestFinder;
        const int StepCounter = TestFinder.FindPath(2, 0, 0, 2, Map, 3, 3, OutPath);

        if (StepCounter < 0)
        {
            std::cout << "RunTest_2 COMPLETED" << std::endl;
        }
        else
        {
            std::cout << "RunTest_2 CRASHED" << std::endl;
        }
    }
    /** Big Map Test*/
    void RunTest_3()
    {
        std::cout << "RunTest_3 STARTED" << std::endl;
        unsigned char Map[] = {
            /* 0*/   1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//38
            /* 1*/   0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//37
            /* 2*/   1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//36
            /* 3*/   1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//35
            /* 4*/   1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//34
            /* 5*/   0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//33
            /* 6*/   1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//32
            /* 7*/   0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//31
            /* 8*/   1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//30
            /* 9*/   0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//29
            /*10*/   1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//28
            /*11*/   1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//27
            /*12*/   1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//26
            /*13*/   1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//25
            /*14*/   1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//24
            /*15*/   1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//23
            /*16*/   0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//22
            /*17*/   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//21
            /*18*/   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//20
            /*19*/   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//19
            /*20*/   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//18
            /*21*/   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//17
            /*22*/   1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//16
            /*23*/   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//15
            /*24*/   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//14
            /*25*/   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,//13
            /*26*/   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,//12
            /*27*/   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,//11
            /*28*/   1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,//10
            /*29*/   1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,//9
            /*30*/   1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,//8
            /*31*/   1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,//7
            /*32*/   1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,//6
            /*33*/   1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,//5
            /*34*/   1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1,//4
            /*35*/   1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//3
            /*36*/   1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//2
            /*37*/   1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//1
            /*38*/   1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//0
            //       0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,

        };
        int OutPath[240];
        PathfindingProcess TestFinder;
        const int StepCounter = TestFinder.FindPath(0, 0, 55, 38, Map, 56, 39, OutPath);


        if (StepCounter >= 0)
        {
            DebugHelper::PrintPath(StepCounter, OutPath, false);
            std::cout << "----------------------" << StepCounter << "-------------------------" << std::endl;
            DebugHelper::DrawPath(0, 0, 55, 38, Map, 56, 39, OutPath, StepCounter);
            std::cout << "------------------------------------------------" << std::endl;
        }
        else
        {
            std::cout << "---------------RunTest_3 TEST FAILED--------------------" << std::endl;
            DebugHelper::DrawPath(0, 0, 55, 38, Map, 56, 39, OutPath, 0);
            std::cout << "-------------------------------------------------" << std::endl;
        }
    }

    /** Random Test*/
    void RunTest_4(float DifficultyValue)
    {
        const int StartPointX = 0;
        const int StartPointY = 0;

        const int TargetPointX = 19;
        const int TargetPointY = 19;

        const int MapWidth = 20;
        const int MapHeight = 20;
        unsigned char Map[400];

        for (unsigned char& i : Map)
        {
            const float RandValue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            const int PathValue = RandValue >= DifficultyValue ? 1 : 0;
            i = static_cast<char>(PathValue);
        }
        const int StartIndex = StartPointX + StartPointY * MapWidth;
        const int TargetIndex = TargetPointX + TargetPointY * MapWidth;

        Map[StartIndex] = static_cast<char>(1);
        Map[TargetIndex] = static_cast<char>(1);

        int OutPath[4000];
        PathfindingProcess TestFinder;
        const int StepCounter = TestFinder.FindPath(StartPointX, StartPointY, TargetPointX, TargetPointY, Map, MapWidth, MapHeight, OutPath);

        if (StepCounter >= 0)
        {
            DebugHelper::PrintPath(StepCounter, OutPath, false);
            std::cout << "----------------------" << StepCounter << "-------------------------" << std::endl;
            DebugHelper::DrawPath(StartPointX, StartPointY, TargetPointX, TargetPointY, Map, MapWidth, MapHeight, OutPath, StepCounter);
            std::cout << "------------------------------------------------" << std::endl;
        }
        else
        {
            std::cout << "---------------RunTest_4 TEST FAILED--------------------" << std::endl;
            DebugHelper::DrawPath(StartPointX, StartPointY, TargetPointX, TargetPointY, Map, MapWidth, MapHeight, OutPath, 0);
            std::cout << "-------------------------------------------------" << std::endl;
        }
    }

    /** Random Test Executor*/
    void RunRandomMapTest()
    {
        for (int i = 0; i < 10; i++)
        {
            srand(i * 5);
            RunTest_4(0.15f);
        }
    }
};

