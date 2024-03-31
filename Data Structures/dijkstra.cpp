#include <iostream>
using namespace std;

#define V 9

void print(int dist[]){
    for(int i = 0; i < V; i++){
        cout << dist[i] << " ";
    }
}

int minDistance(int dist[], bool visited[]){
    int min = INT32_MAX, minIndex;
    for(int i = 0; i < V; i++){
        if(!visited[i] && dist[i] <= min){
            min = dist[i];
            minIndex = i;
        }
    }
    
    return minIndex;
}

void dijkstra(int graph[V][V], int src){
    int dist[V];
    bool visited[V];

    for(int i = 0; i < V; i++){
        dist[i] = INT32_MAX;
        visited[i] = false;
    }

    dist[src] = 0;

    for(int i = 0; i < V - 1; i++){
        int u = minDistance(dist, visited);
        visited[u] = true;
        
        for(int j = 0; j < V; j++){
            if(!visited[j] && graph[u][j] && dist[u] != INT64_MAX && dist[u] + graph[u][j] < dist[j]){
                dist[j] = dist[u] + graph[u][j];
            }
        }
    }

    print(dist);
}

int main(){
    cout << "Dijkstra";

    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    dijkstra(graph, 0);
}