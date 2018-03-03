#include "AStar.h"


BidirectionalAStar::BidirectionalAStar(TGraph& graph, int64_t startID, int64_t goalID) {
    (*this).graph = graph;
    (*this).forwardCameFrom.resize(graph.size());
    (*this).forwardCloseSet.resize(graph.size());
    (*this).forwardCost.resize(graph.size(), std::numeric_limits<double>::infinity());
    (*this).reverseCameFrom.resize(graph.size());
    (*this).reverseCloseSet.resize(graph.size());
    (*this).reverseCost.resize(graph.size(), std::numeric_limits<double>::infinity());
    (*this).startID = graph.getNewID(startID);
    (*this).goalID = graph.getNewID(goalID);
    if ((*this).startID == -1 || (*this).goalID == -1)
        throw std::string("Node\\nodes with this ID not found.");
    (*this).distanceStartGoal = calculateDistance(graph[(*this).startID].latitude, graph[(*this).startID].longitude,
        graph[(*this).goalID].latitude, graph[(*this).goalID].longitude);
 }


BidirectionalAStar::~BidirectionalAStar(){

}

double BidirectionalAStar::calculateDistance(double srcLat, double srcLon, double destLat, double destLon) {
    double srcLatRad = (srcLat *  M_PI) / 180;
    double srcLonRad = (srcLon *  M_PI) / 180;
    double destLatRad = (destLat *  M_PI) / 180;
    double destLonRad = (destLon *  M_PI) / 180;
    double tmp = std::pow(std::sin((srcLatRad - destLatRad) / 2), 2) +
        std::cos(srcLatRad) * std::cos(destLatRad) * std::pow(std::sin((srcLonRad - destLonRad) / 2), 2);
    return (6371 * 1000 * 2 * std::atan2(sqrt(tmp), sqrt(1.0 - tmp)));
}

double BidirectionalAStar::forwardHeuristic(int64_t vrtxID) {
    double toStart = calculateDistance(graph[vrtxID].latitude, graph[vrtxID].longitude,
        graph[startID].latitude, graph[startID].longitude);
    double toGoal = calculateDistance(graph[vrtxID].latitude, graph[vrtxID].longitude,
        graph[goalID].latitude, graph[goalID].longitude);
    return ((toGoal - toStart) / 2 + distanceStartGoal / 2);
}

double BidirectionalAStar::reverseHeuristic(int64_t vrtxID) {
    double toStart = calculateDistance(graph[vrtxID].latitude, graph[vrtxID].longitude,
        graph[startID].latitude, graph[startID].longitude);
    double toGoal = calculateDistance(graph[vrtxID].latitude, graph[vrtxID].longitude,
        graph[goalID].latitude, graph[goalID].longitude);
    return ((toStart - toGoal) / 2 + distanceStartGoal / 2);
}



void BidirectionalAStar::find(bool fullOutput) {
    if (startID == goalID) {
        result = 0;
        return;
    }

    PriorityQueue forwardOpenSet;
    PriorityQueue reverseOpenSet;

   
    forwardOpenSet.put(0, startID);
    forwardCameFrom[startID] = startID;
    forwardCost[startID] = 0;
    reverseOpenSet.put(0, goalID);
    reverseCameFrom[goalID] = goalID;
    reverseCost[goalID] = 0;


    int64_t current;
    double bestCurrentCost = std::numeric_limits<double>::infinity();
    while (!forwardOpenSet.empty() && !reverseOpenSet.empty()) {
        if (bestCurrentCost != std::numeric_limits<double>::infinity()) {
            int64_t topForward = forwardOpenSet.top();
            int64_t topReverse = reverseOpenSet.top();
            double assessedCost = forwardCost[topForward] + reverseCost[topReverse]
                + forwardHeuristic(topForward);
            + reverseHeuristic(topReverse);
            if (assessedCost >= bestCurrentCost + distanceStartGoal) {
                result = bestCurrentCost;
                if (fullOutput)
                    savePath();
                return;
            }
        }
        current = forwardOpenSet.get();
        forwardCloseSet[current] = true;
        for (auto& next : graph[current].neighbors) {
            if (!forwardCloseSet[next.first]) {
                double tentativeCost = next.second + forwardCost[current];
                if (forwardCost[next.first] > tentativeCost) {
                    forwardCost[next.first] = tentativeCost;
                    forwardCameFrom[next.first] = current;
                    forwardOpenSet.put(forwardHeuristic(next.first) + tentativeCost,
                        next.first);
                    if (reverseCloseSet[next.first]) {
                        double len = reverseCost[next.first] + tentativeCost;
                        if (bestCurrentCost > len) {
                            bestCurrentCost = len;
                            connectNodeID = next.first;
                        }
                    }
                }

            }
        }
        current = reverseOpenSet.get();
        reverseCloseSet[current] = true;
        for (auto& next : graph[current].neighbors) {
            if (!reverseCloseSet[next.first]) {
                double tentativeCost = next.second + reverseCost[current];
                if (reverseCost[next.first] > tentativeCost) {
                    reverseCost[next.first] = tentativeCost;
                    reverseCameFrom[next.first] = current;
                    reverseOpenSet.put(reverseHeuristic(next.first) + tentativeCost,
                        next.first);
                    if (forwardCloseSet[next.first]) {
                        double len = forwardCost[next.first] + tentativeCost;
                        if (bestCurrentCost > len) {
                            bestCurrentCost = len;
                            connectNodeID = next.first;
                        }
                    }
                }

            }
        }
    }
    connectNodeID = -1;
    result = -1;
    return;
}


void BidirectionalAStar::savePath() {
    if (connectNodeID == -1) {
        return;
    }
    int64_t id = connectNodeID;
    path.push_back(id);
    for (;;) {
        if (goalID == startID || id == startID)
            break;
        id = forwardCameFrom[id];
        path.push_back(id);
    }
    std::reverse(path.begin(), path.end());
    id = connectNodeID;
    for (;;) {
        if (goalID == startID || id == goalID)
            break;
        id = reverseCameFrom[id];
        path.push_back(id);
    }
}