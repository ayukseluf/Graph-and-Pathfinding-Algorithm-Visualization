#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define HEIGHT 10800 
#define WIDTH 19200
#define NODE_COUNT 100000

struct Graph
{
    struct Node
    {
        unsigned int ID;
        float X, Y;
        std::vector< std::pair<int, short> > adjacentNodes;
        Node(unsigned int ID, float X, float Y)
        {
            this->ID = ID;
            this->X = X;
            this->Y = Y;
        }

        float distance(float Ex, float Why)
        {
            return std::sqrt( std::pow((Ex - this->X), 2) + std::pow( (Why - this->Y), 2) );
        }
    };
    
    std::vector<Node> vectorOfNodes;

    Graph(unsigned int nodeCount)
    {
        srand(time(NULL));

        // Node generation
        

        for(unsigned int i = 0; i < nodeCount; i++)
        {
            float X = 0;
            float Y = 0;
            bool notFoundProperValue = true;
            while(notFoundProperValue)
            {
                notFoundProperValue = false;
                X = rand() % WIDTH + 15;
                Y = rand() % HEIGHT + 15;
                for(unsigned int j = 0; j < vectorOfNodes.size(); j++)
                {
                    if(X == this->vectorOfNodes[j].X || this->vectorOfNodes[j].distance(X, Y) <= 5) // Using radius to generate nodes
                    {
                        notFoundProperValue = true;
                        break;
                    }

                    if(Y == this->vectorOfNodes[j].Y) // distance comparison unnecessary since no value change in dist() calculation
                    {
                        notFoundProperValue = true;
                        break;
                    }
                }
            }
            this->vectorOfNodes.push_back(Node(i, X, Y));
        }
    }

};

int main()
{
    Graph g(NODE_COUNT);
    std::ofstream file("100000-A.txt");
    for(unsigned int i = 0; i < g.vectorOfNodes.size(); i++)
    {
        // std::cout << "ID: " << g.vectorOfNodes[i].ID << " | X: " << g.vectorOfNodes[i].X << " | Y: " << g.vectorOfNodes[i].Y << std::endl;
        file << g.vectorOfNodes[i].ID << " " << g.vectorOfNodes[i].X << " " << g.vectorOfNodes[i].Y << std::endl;
    }

}