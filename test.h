#ifndef TEST_H
#define TEST_H
#include <RandomizedIncrementalD.h>
//A structure to represent a point in a plane
class Test
{
public:
    Test();
    static void testAll();
    static void testBruce();
    static void testDivideAndConquer2D();
    static void testRandomizedIncremental2D();
    static void testRandomizedIncremental3D();
};

#endif // TEST_H
