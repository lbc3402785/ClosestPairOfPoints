#ifndef BASIC_H
#define BASIC_H
/********************************************************************************************
dist function
*********************************************************************************************/
#include <algorithm>
#include <cmath>
#include <vector>
//Computes the Euclidean distance between two points.
template<typename Point2DT>
typename Point2DT::type distance(Point2DT& p1, Point2DT& p2)
{
    //Casting each int value to long long int so that the values can be safely multiplied,
    // i.e., without the risk of "overflowing" the capacity of int.
    assert(p1.dimension()==p2.dimension());
    typename Point2DT::type sum=0;
    for(size_t k=0;k<p1.dimension();++k){
        sum+=(p1[k]-p2[k])*(p1[k]-p2[k]);
    }

    return std::sqrt( sum );
}
template <typename T>
struct Point{
public:
    virtual int dimension()=0;
};
template <typename T>
struct Point2D:public Point<T>
{
public:
    std::vector<T> data;
    typedef T type;
    T& x(){return data[0];}
    T& y(){return data[1];}
    int dimension(){return data.size();}
    T operator [] (int i)const {return data[i];}
    Point2D(int dimension = 2) {
        data.resize(dimension);
    }
};

template <typename T>
struct Point3D:public Point<T>
{
public:
    std::vector<T> data;
    typedef T type;
    T& x(){return data[0];}
    T& y(){return data[1];}
    T& z(){return data[2];}
    int dimension(){return data.size();}
    T operator [] (int i)const {return data[i];}
    Point3D(int dimension = 3) {
        data.resize(dimension);
    }
};

#endif // BASIC_H
