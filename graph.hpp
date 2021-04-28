#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <list>
using namespace std;

class graph{
    protected:
        map<string, map<string, double>> _graph;
        set<string> _nodes;
        map<string,set<string>> _outEdges;

    public:
        bool checkExist(const string& node);
        void print(std::list<std::string> const &list);
        double getConv(const string &src, const string &dst);
        set<string> &_nodes(){}
        map<string, map<string, double>> &_graph();
        graph(map<string, map<string, double>> graph, set<string> nodes):_graph(graph), _nodes(nodes){};
        void addNode(const string &_node);
        void addEdge(const string &src, const string &dst, double weight);
        double getWeight(const string &src, const string &dst);

};



