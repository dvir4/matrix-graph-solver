#include <iostream>
#include "MyTestClientHandler.h"
#include "StringReverser.h"
#include "Solver.h"
#include "MyClientHandler.h"
#include "MazeSolver.h"
#include "BestFirstSearch.h"
#include "FileCacheManager.h"
#include "CacheManager.h"
#include "Astar.h"
#include "DFS.h"
#include "convertor.h"
#include "matrixConvertor.h"
#include "ParallelServer.h"
#include "BFS.h"


int main(int argc, char* argv[]) {

    if(argc != 2){
        return 1;
    }

    ISearcher<vector<State<pair<int, int>> *>, pair<int, int>> *searcher =
            new Astar<vector<State<pair<int, int>> *>, pair<int, int>>();
    Solver<Searchable<pair<int, int>> *, string> *solver = new MazeSolver(searcher);
    convertor<Searchable<pair<int, int>> *, string> *convertor = new matrixConvertor();
    CacheManager<Searchable<pair<int, int>> *, string> *cacheManager = new FileCacheManager<Searchable<pair<int, int>> *, string>("probToSol.txt", convertor);
    ClientHandler *clientHandler = new MyClientHandler<Searchable<pair<int, int>> *, string>(solver, cacheManager, convertor);

    Server *parallelServer = new ParallelServer();
    parallelServer->open(stoi(argv[1]), clientHandler);

    delete parallelServer;
    delete clientHandler;
    delete cacheManager;
    delete convertor;
    delete solver;
    delete searcher;

    return 0;
}