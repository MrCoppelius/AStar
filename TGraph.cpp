#include "TGraph.h"




TGraph::TGraph() {
}

TGraph::~TGraph() {
}

int64_t TGraph::getNewID(int64_t oldID) {
    int64_t left = 0;
    int64_t right = graph.size() - 1;
    while (left <= right) {
        int64_t mid = left + (right - left) / 2;
        if (graph[mid] == oldID) {
            return mid;
        }
        if (graph[mid] < oldID) 
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
void TGraph::addNode(TVertex element) {
    (*this).graph.push_back(element);
}

void  TGraph::addEdge(int64_t srcID, int64_t destID) {
    int64_t src = (*this).getNewID(srcID);
    int64_t dest = (*this).getNewID(destID);
    if (src != -1 && dest != -1) {
        double distance = calculateDistance(graph[src].latitude, graph[src].longitude, graph[dest].latitude, graph[dest].longitude);
        graph[src].neighbors.push_back(std::make_pair(dest, distance));
        graph[dest].neighbors.push_back(std::make_pair(src, distance));
    }
}

TVertex& TGraph::operator[](int64_t index) {
    return graph[index];
}

int64_t TGraph::size() {
    return graph.size();
}

double TGraph::calculateDistance(double srcLat, double srcLon, double destLat, double destLon) {
    double srcLatRad = (srcLat *  M_PI) / 180;
    double srcLonRad = (srcLon *  M_PI) / 180;
    double destLatRad = (destLat *  M_PI) / 180;
    double destLonRad = (destLon *  M_PI) / 180;
    double tmp = std::pow(std::sin((srcLatRad - destLatRad) / 2), 2) +
        std::cos(srcLatRad) * std::cos(destLatRad) * std::pow(std::sin((srcLonRad - destLonRad) / 2), 2);
    return (6371 * 1000 * 2 * std::atan2(sqrt(tmp), sqrt(1.0 - tmp)));
}



