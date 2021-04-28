#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <list>
#include <stack>
using namespace std;

class graph{
    protected:
        map<string, map<string, double>> the_graph;
        set<string> nodes;
        map<string,set<string>> edges_from;

    public:
        bool checkExist(const string& node){
            return (nodes.count(node) > 0);
        }
        void addOut(const string &src, const string &dst){
            if (edges_from.count(src) > 0)
            {
                edges_from[src].insert(dst);
            }else{
                set<string> temp{dst};
                edges_from[src] = temp;
            }
        }
        void addEdge(const string &src, const string &dst, double weight){
            addNode(src);addNode(dst);
            the_graph[src][dst] = weight;
            the_graph[dst][src] = ((double)1)/weight;
            addOut(src,dst);
            addOut(dst,src);
        }
        void addNode(const string &_node){
            nodes.insert(_node);
        }
        double getWeight(const string &src, const string &dst){
            if(the_graph[src][dst] <= 0){
                return -1;
            }
            return the_graph[src][dst];
        }

        // void print(std::list<std::string> const &list)
        // {
        //     for (auto const &i : list)
        //     {
        //         std::cout << i << " |-> ";
        //     }
        //     cout << endl;
        // }

        double getConv(const string &src, const string &dst){
            stack<string> s;
            set<string> visited;
            map<string, double> con;
            s.push(src);
            con[src] = 1;
            while(!s.empty()){
                string cur = s.top();
                s.pop();
                if(visited.count(cur) < 1){
                    visited.insert(cur);
                    if (cur == dst){
                        return con[cur];
                    }
                    for (string str : edges_from[cur])
                    {
                        if (visited.count(str) < 1)
                        {
                            con[str] = getWeight(cur, str) * con[cur];
                            s.push(str);
                        }
                    }
                }
            }
            return -1;
        }
};



