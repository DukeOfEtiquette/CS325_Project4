#pragma once
#include <map>
#include <iostream>
#include <string>
#include "TSPNode.h"
#include <sstream>
#include <signal.h>
#include <deque>

class TSPGraph
{
public:
	TSPGraph(std::string fileName);
	~TSPGraph();

	//Member variables
	//std::map<std::string, TSPNode*> m_graph;
	std::deque <TSPNode*> m_graph;
	int m_distance;
	int m_size;

	//Functions
	void AddNode(std::string name, std::string x, std::string y);
	void PrintGraph();
	int NodeDistance(TSPNode* cur, TSPNode* next);
    int two_change();
    int get_solution_distance();
    int swap_two(int i, int k);

	//Typedefs
	typedef std::map<std::string, TSPNode*>::iterator graphIt;
};

void end_opt(int signum);

