#include "TSPGraph.h"
#include <fstream>
#include "TSPNode.h"
#include <cmath>
#include <deque>
#include <string>

// fix for to_string http://stackoverflow.com/questions/12975341/to-string-is-not-a-member-of-std-says-so-g
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


TSPGraph::TSPGraph(std::string fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());
	std::string id, x, y;
	m_size = 0;

	if (!file.is_open())
	{
		std::cout << "Invalid file\n";
		return;
	}

	do
	{
		file >> id >> x >> y;

		AddNode(id, x, y);
		m_size++;

	}while(!file.eof());

	m_graph.pop_back();
	m_size--;

	std::cout << "City count = " << m_size - 1 << std::endl;
}

void TSPGraph::AddNode(std::string name, std::string x, std::string y)
{
	//Create node
	//Add x and y to node
	//Add node to graph
	TSPNode* node = new TSPNode();
	node->xy.push_back(stoi(x));
	node->xy.push_back(stoi(y));
	node->m_name = name;

	m_graph.push_back(node);
}

void TSPGraph::PrintGraph()
{
	for(int i = 0; i < m_size; i++)
	{
		std::cout << m_graph[i]->m_name << " " << m_graph[i]->xy[0];
		std::cout << " " << m_graph[i]->xy[1] << std::endl;
	}
}

int TSPGraph::NodeDistance(TSPNode* cur, TSPNode* next)
{
	int newDistance = sqrt(pow((cur->xy[0] - next->xy[0]), 2) + pow((cur->xy[1] - next->xy[1]), 2));

	return newDistance;
}

TSPGraph::~TSPGraph()
{
	for (int i = 0; i < m_size; i++)
	{
		delete m_graph[i];
	}
}

int TSPGraph::two_change()
{
    std::deque <TSPNode*> new_path;
    int min_distance = get_solution_distance();
    bool start_over = false;
    time_t timer1,
           timer2;
	time(&timer1);
	double second = 0;
	int end_time = 180;

    while(second < end_time)
    {
		time(&timer2);
        second = difftime(timer2,timer1);
        start_over = false;
        for (int i = 1; i < m_size && !start_over; ++i)
        {
            for (int j = i+1; j < m_size - 1 && !start_over; ++j)
            {
                //only check moves that will reduce distance
                if (NodeDistance(m_graph[i - 1], m_graph[j]) + NodeDistance(m_graph[i], m_graph[j+1]) < NodeDistance(m_graph[i-1], m_graph[i]) + NodeDistance(m_graph[j], m_graph[j+1]))
                {
                    swap_two(i, j);
                    min_distance = get_solution_distance();
                    start_over = true;
                }

                else
                    start_over = false;
            }
        }

        if (!start_over)
            break;
    }
			if (second > end_time - 1)
				std::cout << "Took too long, exiting with best resut so far." << std::endl;
    return min_distance;
}

int TSPGraph::get_solution_distance()
{
    int total_dist = 0;
    for (int i = 0; i < m_size - 1; i++)
    {
        //std::cout << "i: " << i << "m_size = " << m_size << std::endl;
        total_dist += NodeDistance(m_graph[i], m_graph[i + 1]);
    }

    total_dist += NodeDistance(m_graph[0], m_graph[m_size - 1]);

    return total_dist;
}

int TSPGraph::swap_two(int i, int k)
{
    std::deque <TSPNode*> temp;
    int count = 0;

    //Reverse order
    for (int x = k; x >= i; --x)
    {
        temp.push_back(m_graph[x]);
    }

    for (int x = i; x <= k; ++x)
    {
        m_graph[x] = temp[count];
        ++count;
    }
    temp.clear();
    //fix_positions();          //used for neighbor list algorithm
    return 1;
}
