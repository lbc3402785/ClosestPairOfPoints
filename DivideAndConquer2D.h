#ifndef DIVIDEANDCONQUER2D_H
#define DIVIDEANDCONQUER2D_H
#include <stdlib.h>
#include <vector>
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
Merge function
*********************************************************************************************/
//A helper function for MergeSort
template<typename Point2DT>
void Merge(Point2DT *M, int p, int q, int r, int compareOption)
{
    // for MergeSort
    Point2DT L[10001]; //+1 to account for sentinel value
    Point2DT R[10001]; //+1 to account for sentinel value
    int n1 = q - p; //Last index of left array
    int n2 = r - q - 1; //Last index of right array

    //Construct the left half of array M
    for (int i = 0; i <= n1; i++)
        L[i] = M[p + i];

    //Construct the right half of array M
    for (int j = 0; j <= n2; j++)
        R[j] = M[q + j + 1];

    //Depending on the value of compareOption, combine the left and right halves of array
    // back into M.
    if (compareOption == 1)
    {
        L[n1 + 1].x = RAND_MAX + RAND_MAX; //The sentinel value
        R[n2 + 1].x = RAND_MAX + RAND_MAX; //The sentinel value

        int i = 0;
        int j = 0;

        for (int k = p; k <= r; k++)
        {
            if (L[i].x <= R[j].x)
            {
                M[k] = L[i];
                i++;
            }
            else
            {
                M[k] = R[j];
                j++;
            }
        }
    }
    else { //sort based on Y-coordinate
        L[n1 + 1].y = RAND_MAX + RAND_MAX; //The sentinel value
        R[n2 + 1].y = RAND_MAX + RAND_MAX; //The sentinel value

        int i = 0;
        int j = 0;

        for (int k = p; k <= r; k++)
        {
            if (L[i].y <= R[j].y)
            {
                M[k] = L[i];
                i++;
            }
            else
            {
                M[k] = R[j];
                j++;
            }
        }
    }
}

/********************************************************************************************
MergeSort function
*********************************************************************************************/
//Recursively sorts the array of structs M by either the x-coordinates, or the y-coordinates.
// If compareOption == 1, the array of structs will be sorted based on the x-coordinate;
// otherwise, the array of structs will be sorted based on the y-coordinate.
template<typename Point2DT>
void MergeSort(Point2DT *M, int p, int r, int compareOption)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        MergeSort(M, p, q, compareOption);
        MergeSort(M, q + 1, r, compareOption);
        Merge(M, p, q, r, compareOption);
    }
}
/********************************************************************************************
bruteForce function
*********************************************************************************************/
//Computes the closest pair of points in P in a brute force manner - by computing the
// distance each pair of points and returning the minimum distance.
template<typename Point2DT>
typename Point2DT::type bruteForce(Point2DT *P, int n)
{
    double min = DBL_MAX;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (dist<Point2DT>(P[i], P[j]) < min)
            {
                min = dist(P[i], P[j]);
            }
        }
    }
    return min;
}
template<typename Point2DT>
class DivideAndConquer2D{
public:
    /********************************************************************************************
    SClosest function
    *********************************************************************************************/
    //Helper function to find the distance between the closest pair of points in S.
    static typename Point2DT::type SClosest(Point2DT *S, int size, double d)
    {
        double min = d; // Initialize the minimum distance as d

        //If two points are found whose y coordinates are closer than the minimum distance,
        // then investigate whether those points are closer than the minimum distance, and keep
        // track of the minimum value so far.
        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size && (S[j].y - S[i].y) < min; j++)
            {
                if (dist(S[i], S[j]) < min)
                {
                    min = dist(S[i], S[j]);
                }
            }
        }

        return min;
    }

    /********************************************************************************************
    closestPairRec function - Recursive function
    *********************************************************************************************/
    //Recursive function to find the smallest distance
    static typename Point2DT::type closestPairRec(Point2DT *Px, Point2DT *Py, int n)
    {
        //If there are 2 or 3 points, just use brute force
        if (n <= 3)
        {
            return bruteForce(Px, n);
        }

        //Find the middle point of the x-coordinates
        int mid = ((n - 1) / 2);
        Point2DT midPoint = Px[mid];

        //Divide points in y sorted array around the vertical line.
        std::vector<Point2DT> Ly; //The left-half of P, sorted by y-coordinate
        Ly.resize(mid + 1);
        std::vector<Point2DT> Ry; //The right-half of P, sorted by y-coordinate
        Ry.resize(n - mid - 1);
        //Indexes of left and right subarrays
        int leftIndex = 0;
        int rightIndex = 0;

        //Construct Qy and Ry by traversing through Py
        for (int i = 0; i < n; i++)
        {
            if (Py[i].x <= midPoint.x)
            {
                if (leftIndex >= (mid + 1)) {
                    std::cerr<< leftIndex << "out of range:"<< mid + 1 << std::endl;
                    std::cerr << Px[mid-1].x << std::endl;
                    std::cerr << Px[mid].x << std::endl;
                    std::cerr << Px[mid + 1].x << std::endl;
                }
                Ly[leftIndex] = Py[i];
                leftIndex++;
            }
            else
            {
                if (rightIndex >= (n - mid - 1)) {
                    std::cerr<< rightIndex << "out of range"<< (n - mid - 1) << std::endl;
                }
                Ry[rightIndex] = Py[i];
                rightIndex++;
            }
        }

        //Note: the pseudocode in Kleinberg & Tardos indicates to construct the following arrays:
        // Qx - The left-half of P, sorted by x-coordinate
        // Rx - The right-half of P, sorted by x-coordinate
        //Instead of constructing these arrays explicitly, the code below uses the arrays
        // implicitly by using "mid" to delimit the left and right halves of P.

        //Recursively find the closest pair among the points in L and R
        typename Point2DT::type dl = closestPairRec(Px, Ly.data(), mid+1);
        typename Point2DT::type dr = closestPairRec(Px + mid+1, Ry.data(), n - mid - 1);

        //Take the minimum of the two distances
        typename Point2DT::type d = (dl < dr) ? dl : dr;

        //S is is the set of points in P within d distance of a line passing through the
        // midpoint of the x-coordinates, sorted by y-coordinate.
        //Note: S has the property that if any two points within it are closer to each other
        // than d, then those two points are within 15 positions of each other in S.
        // Therefore, the closest pair of points in S can be computed in linear time,
        // faster than the quadratic time found in the brute force method of finding the
        // closest pair of points in a set.
        std::vector<Point2DT> S;
        S.resize(n);
        int j = 0;
        for (int i = 0; i < n; i++)
        {
            long long int abso = 0;

            if ((Py[i].x - midPoint.x) < 0)
            {
                abso = -(Py[i].x - midPoint.x);
            }
            else
            {
                abso = (Py[i].x - midPoint.x);
            }

            if (abso < d)
            {
                S[j] = Py[i];
                j++;
            }
        }

        //Call helper function SClosest to computer the minimum distance in S
        return SClosest(S.data(), j, d);
    }

    /********************************************************************************************
    closestPair function - Divide and conquer algorithm
    *********************************************************************************************/
    //Constructs Px (all points sorted by x-coordinate in increasing order)
    //Constructs Py (all points sorted by y-coordinate in increasing order)
    //Calls closestPairRec (recursive function) on Px/Py
    //Returns the closest pair of points

    static typename Point2DT::type closestPair(Point2DT *P, int n){
        std::vector<Point2DT> Px;
        Px.resize(n);
        std::vector<Point2DT> Py;
        Py.resize(n);
        for (int i = 0; i < n; i++)
        {
            Px[i] = P[i];
            Py[i] = P[i];
        }

        //Use MergeSort to sort arrays
        MergeSort(Px.data(), 0, n - 1, 1); //1 for compare x
        MergeSort(Py.data(), 0, n - 1, 2); //2 for compare y

        //Call closestPairRec to find the smallest distance
        return closestPairRec(Px.data(), Py.data(), n);
    }
};

#endif // DIVIDEANDCONQUER2D_H
