#include <iostream>
#include "AVL.h"

int main()
{
    avl::Point2D a(0, 0);
    avl::Point2D b(1, 1);
    float distance;

    try
    {
        avl::PointToPointDistance(a, b, 1.0f, distance, atl::NIL);
    }
    catch(const atl::Error& e)
    {
        std::cout << e.Kind() << ": " << e.Message() << std::endl;
        return 1;
    }

    std::cout << "Distance: " << distance << std::endl;

    return 0;
}