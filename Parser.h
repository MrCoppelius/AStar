#pragma once

#include <string>
#include <fstream>
#include <stack>
#include "TGraph.h"
#include "AStar.h"

bool isEmpty(std::ifstream& file);
void ReadNodes(char* fileName, TGraph& grpah);
void ReadEdges(char* fileName, TGraph& grpah);
void WritePreprocessedGraph(char* fileName, TGraph& graph);
void ReadPreprocessedGraph(char* fileName, TGraph& graph);
bool ReadInputFile(char* fileName, std::streampos& curPoss, int64_t& startID, int64_t& goalID);
void WriteOutput(char* fileName, BidirectionalAStar& astar);
void WriteFullOutput(char* fileName, BidirectionalAStar& astar);