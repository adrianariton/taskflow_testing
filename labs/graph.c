#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int* connections;
    int connnr;
    int id;
} Node;

typedef struct Graph {
    Node* nodes;
    int nodenr;
} Graph;

int getcnr(Node nd, Graph* g) {
    int t = nd.connnr;
    for(int i = 0 ; i < nd.connnr; i ++ ) {
        if (g->nodes[nd.connections[i]].id == -1)
            t--;
    }
    return t;
}

int main() {
    int n, m;
    Graph* g = (Graph*)malloc(sizeof(Graph));
    scanf("%d%d", &n, &m);
    g->nodes = (Node*)malloc(n * sizeof(Node));
    g->nodenr = n;
    for(int i = 0 ;i < m ;++i){
        g->nodes[i].id = i;
        g->nodes[i].connections = (int*)malloc(sizeof(int));
    }
    for(int i = 0; i < m ;++i){
        int a, b;
        scanf("%d%d", &a, &b);
        g->nodes[a].connnr ++;
        if(g->nodes[a].connnr > 1)
            g->nodes[a].connections = (int*)realloc(g->nodes[a].connections, g->nodes[a].connnr * sizeof(int));
        g->nodes[a].connections[g->nodes[a].connnr - 1] = b;
    }
    int removed = 0;
    int r = 0 ;
    do {
        removed = 0;
        for(int i = 0 ; i < n ; ++i) {
            if (g->nodes[i].id == -1)
                continue;
            if (getcnr(g->nodes[i], g) == 0) {
                g->nodes[i].id = -1;
                removed ++;
            }
        }
        r+=removed;
    } while (removed > 0);
    printf("%d", n - r);
    return 0;
}
  