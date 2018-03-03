#include <iostream>
#include <string>
#include <fstream>
#include "TGraph.h"
#include "Parser.h"
#include "AStar.h"


int32_t main(int32_t argc, char* argv[]) {
    try {
        if (argc < 8) {
            throw std::string("Too few arguments.");
        }
        TGraph graph;
        if (std::string(argv[1]) == "preprocess") {
            uint32_t nodesFileID, edgesFileID, outputFileID;
            for (int32_t i = 2; i < argc; ++i) {
                std::string arg(argv[i]);
                if (arg == "--nodes")
                    nodesFileID = i + 1;
                else if (arg == "--edges")
                    edgesFileID = i + 1;
                else if (arg == "--output")
                    outputFileID = i + 1;
            }
            ReadNodes(argv[nodesFileID], graph);
            ReadEdges(argv[edgesFileID], graph);
            WritePreprocessedGraph(argv[outputFileID], graph);
        }
        else if (std::string(argv[1]) == "search") {
            uint32_t inputFileID, graphFileID, outputFileID;
            bool fullOutput = false;
            int64_t startID, goalID;
            for (int32_t i = 2; i < argc; ++i) {
                std::string arg(argv[i]);
                if (arg == "--graph")
                    graphFileID = i + 1;
                else if (arg == "--input")
                    inputFileID = i + 1;
                else if (arg == "--output")
                    outputFileID = i + 1;
                else if (arg == "--full-output") {
                    fullOutput = true;
                }
            }
            ReadPreprocessedGraph(argv[graphFileID], graph);
            std::streampos currPoss = 0;
            while (ReadInputFile(argv[inputFileID], currPoss, startID, goalID)) {
                BidirectionalAStar astar(graph, startID, goalID);
                astar.find(fullOutput);
                if (fullOutput)
                   WriteFullOutput(argv[outputFileID], astar);
                else
                    WriteOutput(argv[outputFileID], astar);
                
            }
        }
    }
    catch (std::string& err) {
        std::cerr << err;
    }
    return 0;
}