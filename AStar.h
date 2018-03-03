#pragma once
#define _USE_MATH_DEFINES
#include <queue>
#include <vector>
#include <functional>
#include <limits>
#include <cmath>
#include "TGraph.h"


struct PriorityQueue {
    typedef std::pair<double, int64_t> element;
    std::priority_queue<element, std::vector<element>, std::greater<element>> elements;
    inline bool empty() { return elements.empty(); }
    inline void put(double priority, int64_t vrtxID) {
        elements.emplace(priority, vrtxID);
    }
    inline int64_t get() {
        int64_t best = elements.top().second;
        elements.pop();
        return best;
    }
    inline int64_t top() {
        int64_t best = elements.top().second;
        return best;
    }
    inline int64_t size() { return elements.size(); }
};


class BidirectionalAStar {
public:
    TGraph graph;
    double result;
    int64_t startID;
    int64_t goalID;
    int64_t connectNodeID;

    std::vector<bool> forwardCloseSet;
    std::vector<int64_t> forwardCameFrom;
    std::vector<double> forwardCost;

    std::vector<bool> reverseCloseSet;
    std::vector<int64_t> reverseCameFrom;
    std::vector<double> reverseCost;

    std::vector<int64_t> path;
    
    BidirectionalAStar(TGraph& graph, int64_t startID, int64_t goalID);
    void find(bool fullOutput);
    ~BidirectionalAStar();

private:
    void  savePath();
    double forwardHeuristic(int64_t vrtxID);
    double reverseHeuristic(int64_t vrtxID);
    double calculateDistance(double, double, double, double);
    double distanceStartGoal;
};

