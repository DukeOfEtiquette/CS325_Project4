//
//  main.cpp
//  CS 325 Project 4
//
//  Created by Eric Walters on 12/1/15.
//  Copyright © 2015 Eric Walters. All rights reserved.
//


#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "TSPGraph.h"
//#include <typeinfo>
//#include "TSPGraph.cpp"


int main(int argc, char* argv[])
{
    std::string fileName;

	fileName = argv[1];

	std::cout << "File: " << fileName << std::endl;
    
    TSPGraph graph(fileName);
	
	if(graph.m_size == 0)
		return 0;
    
    int shortestDistance = graph.two_change();
 
    std::cout << "shortestDistance: " << shortestDistance << std::endl;
	
	fileName += ".tour"; 
	std::ofstream output;
	output.open(fileName.c_str());

	output << shortestDistance;

	for(int i = 0; i < graph.m_size; i++)
	{
		output << std::endl << graph.m_graph[i]->m_name;
	}
    
	std::cout << "Complete. File: " << fileName << "\n\n";
    return 0;
}
