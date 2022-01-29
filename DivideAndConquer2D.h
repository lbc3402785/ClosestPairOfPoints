#ifndef DIVIDEANDCONQUER2D_H
#define DIVIDEANDCONQUER2D_H
#include <stdlib.h>
#include <vector>
#include <numeric>      // std::iota
/********************************************************************************************
dist function
*********************************************************************************************/
//Computes the Euclidean distance between two points.
template<typename Point2DT>
typename Point2DT::type dist(Point2DT p1, Point2DT p2)
{
    //Casting each int value to long long int so that the values can be safely multiplied,
    // i.e., without the risk of "overflowing" the capacity of int.
    typename Point2DT::type p1x = p1.x;
    typename Point2DT::type p2x = p2.x;
    typename Point2DT::type p1y = p1.y;
    typename Point2DT::type p2y = p2.y;

    return sqrt( (p1x - p2x) * (p1x - p2x) + (p1y - p2y) * (p1y - p2y) );
}


/********************************************************************************************
bruteForce function
*********************************************************************************************/
//Computes the closest pair of points in P in a brute force manner - by computing the
// distance each pair of points and returning the minimum distance.
template<typename Point2DT>
std::tuple<int, int, typename Point2DT::type> bruteForce(Point2DT* points,int size)
{
    double min = DBL_MAX;
    std::tuple<int, int, typename Point2DT::type> result;
    for (int i = 0; i < size-1; ++i)
    {
        for (int j = i + 1; j < size; j++)
        {
            typename Point2DT::type d = dist<Point2DT>(points[i], points[j]);
            if (d < min)
            {

                std::get<0>(result) = i;
                std::get<1>(result) = j;
                min = d;
            }
        }
    }
    std::get<2>(result) = min;
    return result;
}
template<typename Point2DT>
std::tuple<int,int,typename Point2DT::type> bruteForce(Point2DT* points,std::vector<int>& ix, int start, int end)
{
    double min = DBL_MAX;
    std::tuple<int, int, typename Point2DT::type> result;
    for (int i = start; i < end; ++i)
    {
        for (int j = i + 1; j <=end; j++)
        {
            int k = ix[i];
            int l = ix[j];
            typename Point2DT::type d=dist<Point2DT>(points[k], points[l]);
            if ( d< min)
            {

                std::get<0>(result) = k;
                std::get<1>(result) = l;
                min = d;
            }
        }
    }
    std::get<2>(result) = min;
    return result;
}
template<typename Point2DT>
class DivideAndConquer2D{
private:
    std::vector<Point2DT> points;
    size_t size;
public:
    DivideAndConquer2D(Point2DT* input, int n):size(n) {
        points.resize(n);
        memcpy(points.data(), input, sizeof(Point2DT) * n);
    }
    /********************************************************************************************
    SClosest function
    *********************************************************************************************/
    //Helper function to find the distance between the closest pair of points in S.
    std::tuple<int, int, typename Point2DT::type> SClosest(std::tuple<int, int, typename Point2DT::type> &result,std::vector<int>& S, typename Point2DT::type d)
    {
        int size = S.size();
        typename Point2DT::type min = d; // Initialize the minimum distance as d

        //If two points are found whose y coordinates are closer than the minimum distance,
        // then investigate whether those points are closer than the minimum distance, and keep
        // track of the minimum value so far.
        
        for (int i = 0; i < size-1; i++)
        {
            int k = S[i];
            for (int j = i + 1; j < size && (points[k].y - points[S[j]].y) < min; j++)
            {
                int l = S[j];
                typename Point2DT::type dij=dist(points[k], points[l]);
                if (dij < min)
                {
                    std::get<0>(result) = k;
                    std::get<1>(result) = l;
                    min = dij;
                }
            }
        }
        std::get<2>(result) = min;
        return result;
    }

    /********************************************************************************************
    closestPairRec function - Recursive function
    *********************************************************************************************/
    //Recursive function to find the smallest distance
    std::tuple<int, int, typename Point2DT::type> closestPairRec(std::vector<int> &ix,std::vector<int>& iy, int start, int end)
    {
        //If there are 2 or 3 points, just use brute force
        if (end -start <= 3)
        {
            return bruteForce(points.data(),ix, start,end);
        }

        //Find the middle point of the x-coordinates
        int mid = (start+end) / 2;
        Point2DT midPoint = points[ix[mid]];

        //Divide points in y sorted array around the vertical line.
        std::vector<int> Ly; //The left-half of P, sorted by y-coordinate
        Ly.reserve(end - start + 1);
        std::vector<int> Ry; //The right-half of P, sorted by y-coordinate
        Ry.reserve(end - start + 1);

        for (int i = 0; i <iy.size(); i++) {
            int index = iy[i];
            if (points[index].x <= midPoint.x) {
                Ly.push_back(index);
            }
            else {
                Ry.push_back(index);
            }
        }

        //Note: the pseudocode in Kleinberg & Tardos indicates to construct the following arrays:
        // Qx - The left-half of P, sorted by x-coordinate
        // Rx - The right-half of P, sorted by x-coordinate
        //Instead of constructing these arrays explicitly, the code below uses the arrays
        // implicitly by using "mid" to delimit the left and right halves of P.
        std::tuple<int, int, typename Point2DT::type> result;
        //Recursively find the closest pair among the points in L and R
        typename Point2DT::type dl;
        int ls, le;

        std::tie(ls,le,dl)= closestPairRec(ix,Ly,start,mid);
        typename Point2DT::type dr;
        int rs, re;
        std::tie(rs, re, dr) = closestPairRec(ix, Ry, mid + 1, end);

        //Take the minimum of the two distances
        typename Point2DT::type d;
        if (dl <= dr) {
            std::get<0>(result) = ls;
            std::get<1>(result) = le;
            std::get<2>(result) = dl;
            d = dl;
        }
        else {
            std::get<0>(result) = rs;
            std::get<1>(result) = re;
            std::get<2>(result) = dr;
            d = dr;
        }
        //S is is the set of points in P within d distance of a line passing through the
        // midpoint of the x-coordinates, sorted by y-coordinate.
        //Note: S has the property that if any two points within it are closer to each other
        // than d, then those two points are within 15 positions of each other in S.
        // Therefore, the closest pair of points in S can be computed in linear time,
        // faster than the quadratic time found in the brute force method of finding the
        // closest pair of points in a set.
        std::vector<int> S;
        S.reserve(end-start+1);
        for (int i = 0; i < iy.size(); i++)
        {
            long long int abso = 0;
            int index = iy[i];
            if ((points[index].x - midPoint.x) < 0)
            {
                abso = -(points[index].x - midPoint.x);
            }
            else
            {
                abso = (points[index].x - midPoint.x);
            }

            if (abso < d)
            {
                S.push_back(index);
            }
        }

        //Call helper function SClosest to computer the minimum distance in S
        return SClosest(result,S, d);
    }

    /********************************************************************************************
    closestPair function - Divide and conquer algorithm
    *********************************************************************************************/
    //Constructs Px (all points sorted by x-coordinate in increasing order)
    //Constructs Py (all points sorted by y-coordinate in increasing order)
    //Calls closestPairRec (recursive function) on Px/Py
    //Returns the closest pair of points

    std::tuple<int, int, typename Point2DT::type> closestPair(){
        std::vector<int> ix(size,0);
        std::vector<int> iy(size,0);
        std::iota(ix.begin(), ix.end(), 0);//递增赋值
        iota(iy.begin(), iy.end(), 0);//递增赋值
        sort(ix.begin(), ix.end(), [&](int a, int b) { return points[a].x < points[b].x; });//此处对数据判断，然后对序号排列
        sort(iy.begin(), iy.end(), [&](int a, int b) { return points[a].x < points[b].x; });//此处对数据判断，然后对序号排列
        //Call closestPairRec to find the smallest distance
        return closestPairRec(ix, iy,0,size-1);
    }
};

#endif // DIVIDEANDCONQUER2D_H
