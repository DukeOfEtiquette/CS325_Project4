#pragma once
#include <string>
#include <vector>

class TSPNode
{
public:
	TSPNode();
	~TSPNode();

	std::vector<int> xy;
	std::string m_name;
	TSPNode* next;
	int order;
};

