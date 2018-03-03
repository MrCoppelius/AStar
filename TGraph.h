#pragma once
#define _USE_MATH_DEFINES 
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include "TVertex.h"

class TGraph {
public:
    TGraph();	
    void addNode(TVertex);
    void addEdge(int64_t, int64_t);
    int64_t getNewID(int64_t);
    TVertex& operator[](int64_t);
    int64_t size();
    ~TGraph();
    
private:
    double calculateDistance(double, double, double, double);
    std::vector<TVertex> graph;
};



