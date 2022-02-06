#ifndef BASIC_H
#define BASIC_H
/********************************************************************************************
dist function
*********************************************************************************************/
//Computes the Euclidean distance between two points.
template<typename Point2DT>
typename Point2DT::type dist(Point2DT& p1, Point2DT& p2)
{
    //Casting each int value to long long int so that the values can be safely multiplied,
    // i.e., without the risk of "overflowing" the capacity of int.
    typename Point2DT::type p1x = p1.x;
    typename Point2DT::type p2x = p2.x;
    typename Point2DT::type p1y = p1.y;
    typename Point2DT::type p2y = p2.y;

    return sqrt( (p1x - p2x) * (p1x - p2x) + (p1y - p2y) * (p1y - p2y) );
}
#endif // BASIC_H
