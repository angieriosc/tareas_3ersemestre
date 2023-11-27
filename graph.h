#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;

class Graph{

    private:
    int edgesList;
    int edgesMat;
    int nodes;
    vector<int> *adjList;
    int *adjMatrix;

    public:
    Graph();
    Graph(int);
    void loadGraphList(string, int);
    void addEdgeAdjList(int,int);
    string printAdjList();
    void loadGraphMat(string, int,int);
    void addEdgeAdjMat(int,int);
    string printAdjMat();
    string DFS(int, int);
    string depthHelper(int,int,stack<int>&,list<int>&,vector<vector<int>>&);
    string BFS(int,int);
    string breadthHelper(int, int, queue<int> &, list<int> &, vector<vector<int>> &);
    bool contains(list<int>, int);
    string print_visited(list<int>);
    string print_path(vector<vector<int>>&, int, int);
};

Graph::Graph(int nodo){
   	nodes = nodo;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

Graph::Graph(){
    edgesList = edgesMat = 0;
}

bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

string Graph::printAdjList() {
    string result;

    for (int i = 0; i < nodes; i++) {
        result += "vertex " + to_string(i) + " : ";

        sort(adjList[i].begin(), adjList[i].end());

        for (int j = 0; j < adjList[i].size(); j++) {
            result += to_string(adjList[i][j]) + " ";
        }

  
    }

    return result;
}

void Graph::addEdgeAdjList(int u, int v) {
    if (u >= 0 && u < nodes && v >= 0 && v < nodes) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        edgesList++;
    }
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
  }
	return aux.str();
}

string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
    aux << q.front() << " ";
    q.pop_front();
  }
	return aux.str();
}


string Graph::printAdjMat() {
    string result;
    for (int c = 0; c < nodes; c++) {
        for (int j = 0; j < nodes; j++) {
            result += to_string(adjMatrix[c * nodes + j]) + " ";
        }   
    }
    return result;
}

void Graph::addEdgeAdjMat(int u, int v) {
    if (u >= 0 && u < nodes && v >= 0 && v < nodes) {
        adjMatrix[u * nodes + v] = 1;
        adjMatrix[v * nodes + u] = 1; 
        edgesMat++;
    }
}

void Graph::loadGraphMat(string data, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
	int u, v, i = 0;
	while (i < data.size()) {
		u = (int)data[i+1] - 48;
		v = (int)data[i+3] - 48;
		i = i + 6;
		addEdgeAdjMat(u,v);
	}
}

void Graph::loadGraphList(string data, int a){
	adjList = new vector<int>[a];
	nodes = a;
	int u, v, i = 0;
	while ( i < data.size()) {
			u = (int)data[i+1] - 48;
			v = (int)data[i+3] - 48;
			i = i + 6;
			addEdgeAdjList(u,v);
	}
}

string Graph::DFS(int start, int end) {
    vector<vector<int>> path(nodes, vector<int>(1, -1));
    stack<int> pila;
    list<int> visitados;
    pila.push(start);
    string ans = depthHelper(start, end, pila, visitados, path);
    ans = ans + print_path(path, start, end);
    return ans;
}

string Graph:: depthHelper(int current, int end, std::stack<int>& pila, std::list<int>& visitados, std::vector<std::vector<int>>& path) {
   if (current == end){
        return print_visited(visitados);
   } else if (pila.empty()){
        return "node no encontrado";
   } else {
        current = pila.top();
        pila.pop();
        visitados.push_back(current);
        for (int i = 0; i < adjList[current].size(); i++)
           if (!contains(visitados, adjList[current][i])){
                pila.push(adjList[current][i]);
                path[adjList[current][i]][0] = current;
           }
        return depthHelper(current, end, pila, visitados, path);
   }
}

string Graph::BFS(int start, int end) {
    queue<int> fila;
    list<int> visitados;
    vector<vector<int>> path(nodes, vector<int>(1, -1));

    fila.push(start);
    string ans = breadthHelper(start, end, fila, visitados, path);
    ans = ans + print_path(path, start, end);
    return ans;
}

string Graph::breadthHelper(int current, int goal, queue<int> &fila, list<int> &visitados, vector<vector<int>> &path){
        if(current == goal){
            return print_visited(visitados);
        } else if (fila.empty()){
            return "Nodo no existe";
        }else{
            current = fila.front();
            fila.pop();
            visitados.push_back(current);
            
            for (int i = 0; i < adjList[current].size(); i++){
                if (!contains(visitados, adjList[current][i])){    
                    fila.push(adjList[current][i]);    
                    if (path[adjList[current][i]][0] == -1){
                        path[adjList[current][i]][0] = current;
                    }
                }
            }
            return breadthHelper(current, goal, fila, visitados, path);
   }
}

#endif /* GRAPH_H_ */