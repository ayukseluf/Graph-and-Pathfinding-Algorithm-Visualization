#include "Graph.h"

// --------------------------- Constructor ------------------------------

Graph::Graph(unsigned int nodeCount, string fileName)
{
    this->nodeCount = nodeCount;
    lastSourceNodeID = INT_MAX; // Set to dummy value

    // Read file and build nodes
    std::ifstream file(fileName);
    string line = "";
    short nextEdgeID = 0;
    while (getline(file, line))
    {
        // Load source node's ID and coordinates
        stringstream edgeData(line);
        std::string sourceID = "";
        getline(edgeData, sourceID, ' ');
        std::string sourceX = "";
        getline(edgeData, sourceX, ' ');
        std::string sourceY = "";
        getline(edgeData, sourceY, ' ');

        // Construct source node
        nodes.push_back(Node(stoi(sourceID), stof(sourceX), stof(sourceY)));

        // Load source node's adjacency list annd construct edges
        std::string targetID = "";
        std::string targetWeight = "";
        while (getline(edgeData, targetID, ' '))
        {
            getline(edgeData, targetWeight, ' ');
            nodes[stoi(sourceID)].setAdjacentNodes(stoi(targetID), stof(targetWeight));
            edgesInGraph.push_back(Edge(stoi(sourceID), stoi(targetID), stof(targetWeight), nextEdgeID));
            nextEdgeID++;
            edgesInGraph.push_back(Edge(stoi(targetID), stoi(sourceID), stof(targetWeight), nextEdgeID));
            nodes[stoi(sourceID)].setAdjacentEdges(edgesInGraph[nextEdgeID]);
            nextEdgeID++;
        }
    }

   // Make the graph undirected by ensuring that if node A is in node B's adjacency list, node B will also be in 
   // node A's adjacency list
   for (Node from : nodes)
   {
       for (pair< unsigned int, float > to : from.getAdjacentNodes())
       {
           if (!nodes[to.first].isAdjacent(from.getNodeID()))
               nodes[to.first].setAdjacentNodes(from.getNodeID(), to.second);
       }
       
   }
}

// ---------------------------- Accessors -------------------------------

// Returns ID of node at passed coordinates or -1 if no node at that position
unsigned int Graph::getSelectedNodeID(float x, float y) const
{
    for (Node n : nodes)
    {
        if (ofDist(x, y, n.getX(), n.getY()) <= 3)
            return n.getNodeID();
    }

    return -1;
}

// Returns coordinates associated with nodeID
std::pair<float, float> Graph::getCordsFromID(unsigned int nodeID) const
{
    return std::make_pair(nodes[nodeID].getX(), nodes[nodeID].getY());
}

unsigned int Graph::getLastSourceNodeID() const
{
    return lastSourceNodeID;
}

// ------------------------ Helper Functions ---------------------------

void Graph::drawNodes() const
{
    for (Node n : nodes)
        n.Draw();
}

void Graph::drawEdges() const
{
    for (Edge e : edgesInGraph)
        ofDrawLine(getCordsFromID(e.getFrom()).first, getCordsFromID(e.getFrom()).second, getCordsFromID(e.getTo()).first, getCordsFromID(e.getTo()).second);
}

void Graph::Dijkstra(unsigned int sourceID)
{
    // Reset variables from last call
    lastSourceNodeID = sourceID;
    predecessorNodesID.clear();
    distances.clear();

    Node currNode = nodes[sourceID];

    // Visited will start empty and unvisited will be full
    set <unsigned int> visited;
    set <unsigned int> unvisited;

    for (Node n : nodes) 
        unvisited.insert(n.getNodeID());
    
    // Initialize distance vector to a max value, and vectors holding previous nodes and edges to -1
    for (unsigned int i = 0; i < nodes.size(); i++) 
    {
        distances.push_back(10000000000000.00);
        predecessorNodesID.push_back(-1);
    }
    
    // The distance to the source should be zero
    distances[sourceID] = 0;

    while (unvisited.begin() != unvisited.end()) 
    {
        //Look through all the adjacent distances to see if there is a shorter path
        for (auto n : currNode.getAdjacentNodes()) 
        {
            // If less than distance then replace
            if (distances[currNode.getNodeID()] + n.second < distances[n.first]) 
            {
                distances[n.first] = distances[currNode.getNodeID()] + n.second;
                predecessorNodesID[n.first] = currNode.getNodeID();
            }
        }
        
        //Add the node into visited nodes
        visited.insert(currNode.getNodeID());

        // Delete the node because it has been visited
        unvisited.erase(currNode.getNodeID());

        // Searches through the distance vector for the smallest weight as the next current Node
        if (unvisited.begin() != unvisited.end()) 
        {
            auto it = unvisited.begin();
            float min = 1000000000000.00;
            unsigned int minNodeID = *it;
            for (; it != unvisited.end(); it++) 
            {
                if (distances[*it] < min) 
                {
                    min = distances[*it];
                    minNodeID = *it;
                }
            }
            currNode = nodes[minNodeID];
        }
    }
}

// Returns stack of edges in shortest path from source to target node
std::stack<Edge> Graph::establishPath(unsigned int finalID) 
{
    stack<Edge> edges;
    unsigned int currNodeID = finalID;
    while (currNodeID != lastSourceNodeID)
    {
        unsigned int precedingNodeID = currNodeID;
        currNodeID = predecessorNodesID[currNodeID];
        for (Edge e : edgesInGraph)
        {
            if (e.getFrom() == currNodeID && e.getTo() == precedingNodeID)
            {
                edges.push(e);
                break;
            }
        }
    }
    return edges;
}