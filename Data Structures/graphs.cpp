#include <iostream>
#include <vector>
#include <list>
using namespace std;

// Adjacency Matrix

class Graph {
    int vertices;
    bool** adjMat;
    list<int> *adjLists;
    bool* visited;
    char type;

    public:
        Graph(int vertices, char type){
            this->vertices = vertices;
            this->type = type;

            if(type == 'm'){
                adjMat = new bool*[vertices];
                for(int i = 0; i < vertices; i++){
                    adjMat[i] = new bool[vertices];
                    for(int j = 0; j < vertices; j++){
                        adjMat[i][j] = false;
                    }
                }
            }
            else if(type == 'l'){
                adjLists = new list<int>[vertices];
                visited = new bool[vertices];
            }
        }

        ~Graph(){
            if(type == 'm'){
                for(int i = 0; i < vertices; i++){
                    delete[] adjMat[i];
                }
                delete[] adjMat;
            }
            else if(type == 'l'){
                delete[] adjLists;
                delete[] visited;
            }
        }

        void addEdge(int i, int j){
            adjMat[i][j] = true;
            adjMat[j][i] = true;
        }

        void deleteEdge(int i, int j){
            adjMat[i][j] = false;
            adjMat[j][i] = false;
        }

        void toString() {
            for (int i = 0; i < vertices; i++) {
            cout << i << " : ";
            for (int j = 0; j < vertices; j++)
                cout << adjMat[i][j] << " ";
            cout << "\n";
            }
        }

        void addEdgeList(int a, int b){
            adjLists[a].push_back(b);
            // adjLists[b].push_back(a);
        };

        void printGraph() {
            for (int d = 0; d < vertices; ++d) {
                cout << "\n Vertex "
                << d << ":";
                for (auto x : adjLists[d])
                cout << " -> " << x;
                printf("\n");
            }
        }

        void DFS(int vertex){
            visited[vertex] = true;
            list<int> adj = adjLists[vertex];

            cout << vertex << " ";

            list<int>::iterator i;
            for(i = adj.begin(); i != adj.end(); i++){
                if(!visited[*i]){
                    DFS(*i);
                }
            }
        }

        void BFS(int vertex){
            visited[vertex] = true;
            list<int> queue;
            queue.push_back(vertex);

            list<int>::iterator i;

            while(!queue.empty()){
                int currVertex = queue.front();
                queue.pop_front();
                cout << currVertex << " ";

                for(i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); i++){
                    if(!visited[*i]){
                        visited[*i] = true;
                        queue.push_back(*i);
                    }
                }
            }
        }
};

int main(){ 
    // Graph gm(4, 'm');
    // gm.addEdge(3,2);
    // gm.addEdge(1,2);
    // gm.addEdge(2,2);
    // gm.toString();

    Graph gl(5, 'l');
    gl.addEdgeList(0, 4);
    gl.addEdgeList(3, 4);
    gl.addEdgeList(3, 2);
    gl.addEdgeList(1, 2);
    gl.printGraph();
    // gl.DFS(0);
    gl.BFS(0);
}