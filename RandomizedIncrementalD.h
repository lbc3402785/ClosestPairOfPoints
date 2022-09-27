#ifndef RANDOMIZEDINCREMENTALD_H
#define RANDOMIZEDINCREMENTALD_H
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <assert.h>
#include "basic.h"
template<typename PointDT>
class IndexPointDT{
public:
    IndexPointDT() {

    }
    PointDT point;
    size_t index;
    IndexPointDT(size_t index,PointDT& p):index(index),point(p){

    }
};
template<typename PointDT>
class Cell{
private:
    size_t size;
    std::vector<IndexPointDT<PointDT>> cluster;
public:
    Cell(){
        size=0;
    }
    const std::vector<IndexPointDT<PointDT>> &getCluster() const
    {
        return cluster;
    }
    std::vector<IndexPointDT<PointDT>> &getCluster()
    {
        return cluster;
    }
    void add(IndexPointDT<PointDT>& p){
        cluster.emplace_back(p);
        Increment();
    }
    size_t getSize() const
    {
        return size;
    }
    std::tuple<int, int, typename PointDT::type> dist(IndexPointDT<PointDT>&p){
        std::tuple<int, int, typename PointDT::type> result;
        typename PointDT::type min=DBL_MAX;
        for(IndexPointDT<PointDT> &q:cluster){
            typename PointDT::type dst=distance<PointDT>(p.point,q.point);
            if(dst<min){
                std::get<0>(result) = p.index;
                std::get<1>(result) = q.index;
                std::get<2>(result) = dst;
                min=dst;
            }
        }
        return result;
    }
private:
    void Increment() {
        ++size;
    }
};
template<typename PointDT>
class Grid{
public:
    typename PointDT::type delta;
    virtual Cell<PointDT>* locate(IndexPointDT<PointDT>&p)=0;
    virtual Cell<PointDT> * addPoint(IndexPointDT<PointDT>&p)=0;
    virtual std::tuple<int, int, typename PointDT::type> dist(IndexPointDT<PointDT>& p)=0;
    virtual void build(typename PointDT::type delta)=0;

};
template<typename PointDT>
class Grid2D:public Grid<PointDT>{
private:
    std::map<std::pair<int,int>,Cell<PointDT>*> cellMap;
public:
    ~Grid2D(){
        typename std::map<std::pair<int,int>,Cell<PointDT>*>::iterator it=cellMap.begin();
        for(;it!=cellMap.end();++it){
            delete it->second;
        }
    }
    virtual Cell<PointDT>* locate(IndexPointDT<PointDT>&p)override{
        int i=p.point[0]/delta;
        int j=p.point[1]/delta;
        std::pair<int,int> key(i,j);
        if(cellMap.find(key)!=cellMap.end()){
            return cellMap[key];
        }else{
            return nullptr;
        }
    }
    virtual Cell<PointDT> * addPoint(IndexPointDT<PointDT>&p)override{
        Cell<PointDT>* cell=locate(p);
        if(cell!=nullptr){
            cell->add(p);
            return cell;
        }else{
            Cell<PointDT> *cell=new Cell<PointDT>();
            cell->add(p);
            int i=p.point.x()/delta;
            int j=p.point.y()/delta;
            std::pair<int,int> key(i,j);
            cellMap[key]=cell;
            return cell;
        }
    }
    virtual std::tuple<int, int, typename PointDT::type> dist(IndexPointDT<PointDT>& p)override{
        std::tuple<int, int, typename PointDT::type> result;
        std::get<0>(result) = -1;
        std::get<1>(result) = -1;
        std::get<2>(result) = DBL_MAX;
        int i=p.point.x()/delta;
        int j=p.point.y()/delta;

        typename PointDT::type min=delta;
        std::tuple<int, int, typename PointDT::type> tmp;
        int l,m;
        for(l=-1;l<=1;++l){
            for(m=-1;m<=1;++m){
                std::pair<int,int> key(i+l,j+m);
                if(cellMap.find(key)!=cellMap.end()){
                    Cell<PointDT>* cell=cellMap[key];
                    if(cell->getSize()>0){
                        tmp=cell->dist(p);
                        if(min>std::get<2>(tmp)){
                            result = tmp;
                            min=std::get<2>(tmp);
                        }
                    }
                }
            }
        }

        return result;
    }
    virtual void build(typename PointDT::type delta)override{
        this->delta=delta;
        std::map<std::pair<int,int>,Cell<PointDT>*> tmp;
        tmp.swap(cellMap);
        typename std::map<std::pair<int,int>,Cell<PointDT>*>::iterator it=tmp.begin();
        for(;it!=tmp.end();++it){
            Cell<PointDT>*cell=it->second;
            std::vector<IndexPointDT<PointDT>> &cluster=cell->getCluster();
            for(IndexPointDT<PointDT>& p:cluster){
                addPoint(p);
            }
        }
    }
};
template<typename PointDT>
class Grid3D:public Grid<PointDT>{
private:
    std::map<std::tuple<int,int,int>,Cell<PointDT>*> cellMap;
public:
    ~Grid3D(){
        typename std::map<std::tuple<int,int,int>,Cell<PointDT>*>::iterator it=cellMap.begin();
        for(;it!=cellMap.end();++it){
            delete it->second;
        }
    }
    virtual Cell<PointDT>* locate(IndexPointDT<PointDT>&p)override{
        int i=p.point[0]/delta;
        int j=p.point[1]/delta;
        int k=p.point[2]/delta;
        std::tuple<int,int,int> key(i,j,k);
        if(cellMap.find(key)!=cellMap.end()){
            return cellMap[key];
        }else{
            return nullptr;
        }
    }
    virtual Cell<PointDT> * addPoint(IndexPointDT<PointDT>&p)override{
        Cell<PointDT>* cell=locate(p);
        if(cell!=nullptr){
            cell->add(p);
            return cell;
        }else{
            Cell<PointDT> *cell=new Cell<PointDT>();
            cell->add(p);
            int i=p.point[0]/delta;
            int j=p.point[1]/delta;
            int k=p.point[2]/delta;
            std::tuple<int,int,int> key(i,j,k);
            cellMap[key]=cell;
            return cell;
        }
    }
    virtual std::tuple<int, int, typename PointDT::type> dist(IndexPointDT<PointDT>& p)override{
        std::tuple<int, int, typename PointDT::type> result;
        std::get<0>(result) = -1;
        std::get<1>(result) = -1;
        std::get<2>(result) = DBL_MAX;
        int i=p.point[0]/delta;
        int j=p.point[1]/delta;
        int k=p.point[2]/delta;
        std::tuple<int,int,int> key(i,j,k);
        typename PointDT::type min=delta;
        std::tuple<int, int, typename PointDT::type> tmp;
        int l,m,n;
        for(l=-1;l<=1;++l){
            for(m=-1;m<=1;++m){
                for(n=-1;n<=1;++n){
                    std::tuple<int,int,int> key(i+l,j+m,k+n);
                    if(cellMap.find(key)!=cellMap.end()){
                        Cell<PointDT>* cell=cellMap[key];
                        if(cell->getSize()>0){
                            tmp=cell->dist(p);
                            if(min>std::get<2>(tmp)){
                                result = tmp;
                                min=std::get<2>(tmp);
                            }
                        }
                    }
                }
            }
        }

        return result;
    }

    virtual void build(typename PointDT::type delta)override{
        this->delta=delta;
        std::map<std::tuple<int,int,int>,Cell<PointDT>*> tmp;
        tmp.swap(cellMap);
        typename std::map<std::tuple<int,int,int>,Cell<PointDT>*>::iterator it=tmp.begin();
        for(;it!=tmp.end();++it){
            Cell<PointDT>*cell=it->second;
            std::vector<IndexPointDT<PointDT>> &cluster=cell->getCluster();
            for(IndexPointDT<PointDT>& p:cluster){
                addPoint(p);
            }
        }
    }
};
template<typename PointDT>
class RandomizedIncrementD
{
private:
    Grid<PointDT>* grid;
public:
    std::vector<IndexPointDT<PointDT>> points;
    size_t size;

public:
    RandomizedIncrementD(PointDT* input, int n):size(n) {
        points.resize(n);
        for(int k=0;k<n;++k){
            IndexPointDT<PointDT> ip(k,input[k]);
            points[k]=std::move(ip);
        }
        switch(input[0].dimension()){
        case 2:
            grid=new Grid2D<PointDT>();
            break;
        case 3:
            grid = new Grid3D<PointDT>();
            break;
        }
    }
    RandomizedIncrementD(std::vector<PointDT>& input){
        size=input.size();
        points.resize(size);
        for(int k=0;k<input.size();++k){
            IndexPointDT<PointDT> ip(k,input[k]);
            points[k]=std::move(ip);
        }
    }

    void BuildGrid(typename PointDT::type delta){
        grid->build(delta);
    }
    Cell<PointDT>* locateCell(IndexPointDT<PointDT>&p){
        return grid->locate(p);
    }
    Cell<PointDT>* InsertPoint(IndexPointDT<PointDT>& p){
        return grid->addPoint(p);
    }
    std::tuple<int, int, typename PointDT::type> closestPair(){
        assert(points.size()>3);
        std::tuple<int, int, typename PointDT::type> result;
        typename PointDT::type delta=distance(points[0].point,points[1].point);
        BuildGrid(delta);
        std::get<0>(result) = 0;
        std::get<1>(result) = 1;
        std::get<2>(result) = delta;
        InsertPoint(points[0]);
        InsertPoint(points[1]);
        int i, j;
        typename PointDT::type d;
        for(int k=2;k<points.size();k++){

            std::tie(i,j,d)=grid->dist(points[k]);
            if(d<delta){
                std::get<0>(result) = i;
                std::get<1>(result) = j;
                std::get<2>(result) = d;
                BuildGrid(d);
            }
            InsertPoint(points[k]);
        }
        return result;
    }
};

#endif // RANDOMIZEDINCREMENTALD_H
