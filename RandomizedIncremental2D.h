#ifndef RANDOMIZEDINCREMENTAL2D_H
#define RANDOMIZEDINCREMENTAL2D_H
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
template<typename Point2DT>
class RandomizedIncrement2D
{
public:

    size_t size;
    class IndexPoint2D{
    public:
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
    typename Point2DT::type dist2Cell(Point2DT& p,Cell* cell){
        std::vector<Point2DT> &cluster=cell->getCluster();
        typename Point2DT::type min=DBL_MAX;
        for(Point2DT q:cluster){
            typename Point2DT::type dst=dist(p,q);
            if(dst<min){
                min=dst;
            }
        }
        return min;
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
    std::tuple<int, int, typename Point2DT::type> dist2Grid(Grid& grid,Point2DT& p){
        std::tuple<int, int, typename Point2DT::type> result;
        int i=std::round(p.x/grid.delta);
        int j=std::round(p.y/grid.delta);
        std::pair<int,int> key(i,j);
        typename Point2DT::type min=grid.delta;
        if(grid.cellMap.find(key)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[key];
            if(cell->getSize()>0){
                typename Point2DT::type tmp=dist2Cell(p,cell);
                if(min>tmp){
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyLeft(i-1,j);
        if(grid.cellMap.find(keyLeft)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[key];
            if(cell->getSize()>0){
                typename Point2DT::type tmp=dist2Cell(p,cell);
                if(min>tmp){
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyRight(i+1,j);
        if(grid.cellMap.find(keyRight)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[key];
            if(cell->getSize()>0){
                typename Point2DT::type tmp=dist2Cell(p,cell);
                if(min>tmp){
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyUpper(i,j-1);
        if(g.cellMap.find(keyUpper)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[key];
            if(cell->getSize()>0){
                typename Point2DT::type tmp=dist2Cell(p,cell);
                if(min>tmp){
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyDown(i,j-1);
        if(grid.cellMap.find(keyDown)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[key];
            if(cell->getSize()>0){
                typename Point2DT::type tmp=dist2Cell(p,cell);
                if(min>tmp){
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyLeftUpper(i-1,j-1);
        if(grid.cellMap.find(keyLeftUpper)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[key];
            if(cell->getSize()>0){
                typename Point2DT::type tmp=dist2Cell(p,cell);
                if(min>tmp){
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyRightUpper(i+1,j-1);
        if(grid.cellMap.find(keyRightUpper)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[key];
            if(cell->getSize()>0){
                typename Point2DT::type tmp=dist2Cell(p,cell);
                if(min>tmp){
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyLeftDown(i-1,j+1);
        if(grid.cellMap.find(keyLeftDown)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[key];
            if(cell->getSize()>0){
                typename Point2DT::type tmp=dist2Cell(p,cell);
                if(min>tmp){
                    min=tmp;
                }
            }
        }
        std::pair<int,int> keyRightDown(i+1,j+1);
        if(grid.cellMap.find(keyRightDown)!=grid.cellMap.end()){
            Cell* cell=grid.cellMap[key];
            if(cell->getSize()>0){
                typename Point2DT::type tmp=dist2Cell(p,cell);
                if(min>tmp){
                    min=tmp;
                }
            }
        }
        return min;
    }
    void BuildGrid(typename Point2DT::type delta){
        Grid grid;
        grid.delta=delta;
        typename std::map<std::pair<int,int>,Cell*>::iterator it=g.cellMap.begin();
        for(;it!=g.cellMap.end();++it){
            Cell*cell=it->second;
            std::vector<Point2DT> &cluster=cell->getCluster();
            for(Point2DT q:cluster){
                InsertPoint(grid,q);
            }
        }
        g.delta=grid.delta;
        g.cellMap=std::move(grid.cellMap);
    }
    Cell* locateCell(Grid& grid,Point2DT &p){
        int i=std::round(p.x/grid.delta);
        int j=std::round(p.y/grid.delta);
        std::pair<int,int> key(i,j);
        if(grid.cellMap.find(key)!=grid.cellMap.end()){
            return grid.cellMap[key];
        }else{
            return nullptr;
        }
    }
    Cell* InsertPoint(Grid& grid,Point2DT& p){
        int i=std::round(p.x/grid.delta);
        int j=std::round(p.y/grid.delta);
        std::pair<int,int> key(i,j);
        if(grid.cellMap.find(key)!=grid.cellMap.end()){
            Cell* cell= grid.cellMap[key];
            cell->cluster.push_back(p);
            cell->size++;
            return cell;
        }else{
            Cell *cell=new Cell();
            cell->cluster.push_back(p);
            cell->size=1;
            grid.cellMap[key]=cell;
            return cell;
        }
    }
    std::tuple<int, int, typename Point2DT::type> closestPair(){
        assert(points.size()>3);
        typename Point2DT::type delta=dist(points[0],points[1]);
        BuildGrid(delta);
        InsertPoint(g,points[0]);
        InsertPoint(g,points[1]);
        for(int k=2;k<points.size();k++){
            typename Point2DT::type d=dist2Grid(points[k]);
            if(d<delta){
                BuildGrid(d);
            }
            InsertPoint(g,points[k]);
        }
    }
};

#endif // RANDOMIZEDINCREMENTAL2D_H
