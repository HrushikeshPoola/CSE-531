#include <iostream>
#include <vector>

using namespace std;
void BellmanFord(vector<vector<int>> graph, int vertices, int edges, int initialVertex) {
	int distances[vertices];
	distances[initialVertex] = 0;
	for(int i=0;i<vertices;i++) {
		if(i != initialVertex) distances[i] = 1e9;
	}
	for(int iter = 0; iter < vertices-1; iter++) {
		bool change = false;
		for(int i = 0; i < edges; i++) {
			int startVertex = graph[i][0];
			int endVertex = graph[i][1];
		
			int cost = graph[i][2];
			if(distances[startVertex]!= 1e9 && (distances[startVertex] + cost < distances[endVertex])) {
				distances[endVertex] = distances[startVertex] + cost;
				change = true;
			}
		}
		if(!change)break;
		
		for(int i = 0; i < edges; i++) {
			int startVertex = graph[i][0];
			int endVertex = graph[i][1];
		
			int cost = graph[i][2];
			if(distances[startVertex]!= 1e9 && (distances[startVertex] + cost < distances[endVertex])) {
				cout<<"negative weight cycle exits"<<endl;
			}
		}
		
	}
	
	for(int i=0; i < vertices; i++) {
		cout<<i<<" : "<<distances[i]<<endl;
	}
}
int main() {
	int vertices = 5;
	int edges = 8;
	vector<vector<int>> graph = {   { 0, 1, -1 }, 
        { 0, 2, 4 }, 
        { 1, 2, 3 }, 
        { 1, 3, 2 },
	    { 1, 4, 2 }, 
        { 3, 2, 5 },
        { 3, 1, 1 }, 
        { 4, 3, -3 } 
        };
	
	BellmanFord(graph,vertices,edges,0);
	return 0;
}