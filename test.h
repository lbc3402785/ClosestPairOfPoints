#ifndef TEST_H
#define TEST_H
#include <RandomizedIncremental2D.h>
//A structure to represent a point in a plane
template <typename T>
struct Point2D
{
    T x, y;
    typedef T type;
};
class Test
{
public:
    Test();
    static void testAll();
    static void testBruce();
    static void testDivideAndConquer2D();
    static void testRandomizedIncremental2D();
};

#endif // TEST_H
