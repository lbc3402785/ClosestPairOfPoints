#ifndef RANDOMIZEDINCREMENTAL2D_H
#define RANDOMIZEDINCREMENTAL2D_H
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <assert.h>
template<typename Point2DT>
class RandomizedIncrement2D
{
public:

    size_t size;
    class IndexPoint2D{
    public:
        IndexPoint2D() {

        }
        Point2DT point;
        size_t index;
        IndexPoint2D(size_t index,Point2DT& p):index(index),point(p){

        }
    };
    std::vector<IndexPoint2D> points;
    class Cell{
    private:
        size_t size;
        std::vector<IndexPoint2D> cluster;
    public:
        Cell(){
            size=0;
        }
        const std::vector<IndexPoint2D> &getCluster() const
        {
            return cluster;
        }
        std::vector<IndexPoint2D> &getCluster()
        {
            return cluster;
        }
        size_t getSize() const
        {
            return size;
        }
        void Increment() {
            ++size;
        }
    };

    class Grid{
    public:
        std::map<std::pair<int,int>,Cell*> cellMap;
        typename Point2DT::type delta;
        ~Grid(){
            typename std::map<std::pair<int,int>,Cell*>::iterator it=cellMap.begin();
            for(;it!=cellMap.end();++it){
                delete it->second;
            }
        }
    };
    Grid g;
    std::tuple<int, int, typename Point2DT::type> dist2Cell(IndexPoint2D& p,Cell* cell){
        std::tuple<int, int, typename Point2DT::type> result;
        std::vector<IndexPoint2D> &cluster=cell->getCluster();
        typename Point2DT::type min=DBL_MAX;
        for(IndexPoint2D q:cluster){
            typename Point2DT::type dst=dist(p.point,q.point);
            if(dst<min){
                std::get<0>(result) = p.index;
                std::get<1>(result) = q.index;
                std::get<2>(result) = dst;
                min=dst;
            }
        }
        return result;
    }
public:
    RandomizedIncrement2D(Point2DT* input, int n):size(n) {
        points.resize(n);
        for(int k=0;k<n;++k){
            IndexPoint2D ip(k,input[k]);
            points[k]=std::move(ip);
        }
    }
    RandomizedIncrement2D(std::vector<Point2DT>& input){
        size=input.size();
        points.resize(size);
        for(int k=0;k<input.size();++k){
            IndexPoint2D ip(k,input[k]);
            points[k]=std::move(ip);
        }
    }
    std::tuple<int, int, typename Point2DT::type> dist2Grid(Grid& grid, IndexPoint2D& p){
        std::tuple<int, int, typename Point2DT::type> result;
        std::get<0>(result) = -1;
        std::get<1>(result) = -1;
        std::get<2>(result) = DBL_MAX;
        int i=std::round(p.point.x/grid.delta);
        int j=std::round(p.point.y/grid.delta);
        std::pair<int,int> key(i,j);
        typename Point2DT::type min=grid.delta;
        int k, l;
        typename Point2DT::type tmp;
        if(grid.cellMap.find(key)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[key];
            if(cell->getSize()>0){
                std::tie(k,l,tmp)=dist2Cell(p,cell);
                if(min>tmp){
                    std::get<0>(result) = k;
                    std::get<1>(result) = l;
                    std::get<2>(result) = tmp;
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyLeft(i,j-1);
        if(grid.cellMap.find(keyLeft)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[keyLeft];
            if(cell->getSize()>0){
                std::tie(k, l, tmp) = dist2Cell(p, cell);
                if(min>tmp){
                    std::get<0>(result) = k;
                    std::get<1>(result) = l;
                    std::get<2>(result) = tmp;
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyRight(i,j+1);
        if(grid.cellMap.find(keyRight)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[keyRight];
            if(cell->getSize()>0){
                std::tie(k, l, tmp) = dist2Cell(p, cell);
                if(min>tmp){
                    std::get<0>(result) = k;
                    std::get<1>(result) = l;
                    std::get<2>(result) = tmp;
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyUpper(i-1,j);
        if(g.cellMap.find(keyUpper)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[keyUpper];
            if(cell->getSize()>0){
                std::tie(k, l, tmp) = dist2Cell(p, cell);
                if(min>tmp){
                    std::get<0>(result) = k;
                    std::get<1>(result) = l;
                    std::get<2>(result) = tmp;
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyDown(i+1,j);
        if(grid.cellMap.find(keyDown)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[keyDown];
            if(cell->getSize()>0){
                std::tie(k, l, tmp) = dist2Cell(p, cell);
                if(min>tmp){
                    std::get<0>(result) = k;
                    std::get<1>(result) = l;
                    std::get<2>(result) = tmp;
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyLeftUpper(i-1,j-1);
        if(grid.cellMap.find(keyLeftUpper)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[keyLeftUpper];
            if(cell->getSize()>0){
                std::tie(k, l, tmp) = dist2Cell(p, cell);
                if(min>tmp){
                    std::get<0>(result) = k;
                    std::get<1>(result) = l;
                    std::get<2>(result) = tmp;
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyRightUpper(i-1,j+1);
        if(grid.cellMap.find(keyRightUpper)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[keyRightUpper];
            if(cell->getSize()>0){
                std::tie(k, l, tmp) = dist2Cell(p, cell);
                if(min>tmp){
                    std::get<0>(result) = k;
                    std::get<1>(result) = l;
                    std::get<2>(result) = tmp;
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyLeftDown(i+1,j-1);
        if(grid.cellMap.find(keyLeftDown)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[keyLeftDown];
            if(cell->getSize()>0){
                std::tie(k, l, tmp) = dist2Cell(p, cell);
                if(min>tmp){
                    std::get<0>(result) = k;
                    std::get<1>(result) = l;
                    std::get<2>(result) = tmp;
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyRightDown(i+1,j+1);
        if(grid.cellMap.find(keyRightDown)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[keyRightDown];
            if(cell->getSize()>0){
                std::tie(k, l, tmp) = dist2Cell(p, cell);
                if(min>tmp){
                    std::get<0>(result) = k;
                    std::get<1>(result) = l;
                    std::get<2>(result) = tmp;
                    min=tmp;
                }
            }
        }
        return result;
    }
    void BuildGrid(typename Point2DT::type delta){
        Grid grid;
        grid.delta=delta;
        typename std::map<std::pair<int,int>,Cell*>::iterator it=g.cellMap.begin();
        for(;it!=g.cellMap.end();++it){
            Cell*cell=it->second;
            std::vector<IndexPoint2D> &cluster=cell->getCluster();
            for(IndexPoint2D q:cluster){
                InsertPoint(grid,q);
            }
        }
        g.delta=grid.delta;
        g.cellMap=std::move(grid.cellMap);
    }
    Cell* locateCell(Grid& grid, IndexPoint2D&p){
        int i=std::round(p.point.x/grid.delta);
        int j=std::round(p.point.y/grid.delta);
        std::pair<int,int> key(i,j);
        if(grid.cellMap.find(key)!=grid.cellMap.end()){
            return grid.cellMap[key];
        }else{
            return nullptr;
        }
    }
    Cell* InsertPoint(Grid& grid, IndexPoint2D& p){
        int i=std::round(p.point.x/grid.delta);
        int j=std::round(p.point.y/grid.delta);
        std::pair<int,int> key(i,j);
        if(grid.cellMap.find(key)!=grid.cellMap.end()){
            Cell* cell= grid.cellMap[key];
            cell->getCluster().push_back(p);
            cell->Increment();
            return cell;
        }else{
            Cell *cell=new Cell();
            cell->getCluster().push_back(p);
            cell->Increment();
            grid.cellMap[key]=cell;
            return cell;
        }
    }
    std::tuple<int, int, typename Point2DT::type> closestPair(){
        assert(points.size()>3);
        std::tuple<int, int, typename Point2DT::type> result;
        typename Point2DT::type delta=dist(points[0].point,points[1].point);
        BuildGrid(delta);
        std::get<0>(result) = 0;
        std::get<1>(result) = 1;
        std::get<2>(result) = delta;
        InsertPoint(g,points[0]);
        InsertPoint(g,points[1]);
        int i, j;
        typename Point2DT::type d;
        for(int k=2;k<points.size();k++){

            std::tie(i,j,d)=dist2Grid(g,points[k]);
            if(d<delta){
                std::get<0>(result) = i;
                std::get<1>(result) = j;
                std::get<2>(result) = d;
                BuildGrid(d);
            }
            InsertPoint(g,points[k]);
        }
        return result;
    }
};

#endif // RANDOMIZEDINCREMENTAL2D_H
