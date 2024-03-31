#include <iostream>
using namespace std;

#define V 5

int min(int key[], bool visited[]){
    int min = INT32_MAX, minIndex;

    for(int i = 0; i < V; i++){
        if(!visited[i] && key[i] < min){
            min = key[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void printMST(int parent[], int graph[V][V])
{   
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t"
             << graph[i][parent[i]] << " \n";
}

void Prims(int graph[V][V]){
    int parent[V];
    int key[V];
    bool visited[V];

    for(int i = 0; i < V; i++){
        key[i] = INT32_MAX;
        visited[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for(int i = 0; i < V - 1; i++){
        int u = min(key, visited);
        visited[u] = true;

        for(int j = 0; j < V; j++){
            if(graph[u][j] && !visited[j] && graph[u][j] < key[j]){
                key[j] = graph[u][j];
                parent[j] = u;
            }
        }
    }

    printMST(parent, graph);
}

int main(){
    int graph[V][V] = { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };
 
    Prims(graph);
 
    return 0;
}