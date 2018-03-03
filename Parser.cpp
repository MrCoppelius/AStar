#include "Parser.h"



bool isEmpty(std::ifstream& file){
    return file.peek() == std::ifstream::traits_type::eof();
}

void ReadNodes(char* fileName,  TGraph& grpah) {
    std::ifstream file(fileName, std::ios::in);
    if (!file.is_open()) {
        throw std::string("Couldn't open file.");
    }
    if (isEmpty(file)) {
        file.close();
        throw std::string("File is empty.");
    }
    int64_t ID;
    double latitude, longitude;
    while (!file.eof()) {
        file >> ID >> latitude >> longitude;
        grpah.addNode(TVertex(ID, latitude, longitude));
    }
    file.close();
    return;
}

void ReadEdges(char* fileName, TGraph& grpah) {
    std::ifstream file(fileName, std::ios::in);
    if (!file.is_open()) {
        throw std::string("Couldn't open file.");
    }
    if (isEmpty(file)) {
        file.close();
        throw std::string("File is empty.");
    }
    int32_t count;
    int64_t src, dst;
    while (!file.eof()) {
        file >> count;
        file >> src;
        for (int32_t i = 1; i < count; ++i) {
            file >> dst;
            grpah.addEdge(src, dst);
            src = dst;
        }
    }
    file.close();
    return;
}


void WritePreprocessedGraph(char* fileName, TGraph& graph) {
    std::ofstream file(fileName, std::ios::binary | std::ios::trunc);
    if (!file.is_open()) {
        throw std::string("Couldn't open file.");
    }
    int64_t size = (int64_t)graph.size();
    file.write((char*)&size, sizeof(int64_t));
    for (int32_t i = 0; i < graph.size(); ++i) {
        file.write((char*)&graph[i].id, sizeof(int64_t));
        file.write((char*)&graph[i].latitude, sizeof(double));
        file.write((char*)&graph[i].longitude, sizeof(double));
        size = (int64_t)graph[i].neighbors.size();
        file.write((char*)&size, sizeof(int64_t));
        int32_t size = graph[i].neighbors.size();
        for (int32_t j = 0; j < size; ++j) {
            file.write((char*)&graph[i].neighbors[j].first, sizeof(int64_t));
            file.write((char*)&graph[i].neighbors[j].second, sizeof(double));
        }
    }
    file.close();
    return;
}

void ReadPreprocessedGraph(char* fileName, TGraph& graph) {
    std::ifstream file(fileName, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        throw std::string("Couldn't open file.");
    }
    if (isEmpty(file)) {
        file.close();
        throw std::string("File is empty.");
    }
    int64_t size;
    file.read((char*)&size, sizeof(int64_t));
    for (int32_t i = 0; i < size; ++i) {
        TVertex elem;
        file.read((char*)&elem.id, sizeof(int64_t));
        file.read((char*)&elem.latitude, sizeof(double));
        file.read((char*)&elem.longitude, sizeof(double));
        int64_t neighborsLen;
        file.read((char*)&neighborsLen, sizeof(int64_t));
        for (int32_t j = 0; j < neighborsLen; ++j) {
            int64_t id;
            double length;
            file.read((char*)&id, sizeof(int64_t));
            file.read((char*)&length, sizeof(double));
            elem.neighbors.push_back(std::make_pair(id, length));
        }
        graph.addNode(elem);
    }
    file.close();
    return;
}


bool ReadInputFile(char* fileName, std::streampos& curPoss, int64_t& startID, int64_t& goalID) {
    std::ifstream file(fileName, std::ios::in);
    if (!file.is_open()) {
        throw std::string("Couldn't open file.");
    }
    if (isEmpty(file)) {
        file.close();
        throw std::string("File is empty.");
    }
    if (curPoss == (std::streampos)std::ifstream::traits_type::eof()) {
        file.close();
        return false;
    }
    file.seekg(curPoss);
    file >> startID >> goalID;
    curPoss = file.tellg();
    file.close();
    return true;
}

void WriteOutput(char* fileName, BidirectionalAStar& astar) {
    std::ofstream file(fileName, std::ios::out | std::ios::app);
    if (!file.is_open()) {
        throw std::string("Couldn't open file.");
    }
    file << astar.result << std::endl;
    file.close();
    return;
}

void WriteFullOutput(char* fileName, BidirectionalAStar& astar) {
    std::ofstream file(fileName, std::ios::out | std::ios::app);
    if (!file.is_open()) {
        throw std::string("Couldn't open file.");
    }  
    file << astar.result << ' ' << astar.path.size();
    for (int64_t i : astar.path) {
        file << ' ' << astar.graph[i].id;
    }
    file << std::endl;
    file.close();
    return;
}