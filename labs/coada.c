#include <stdio.h>
int main() {
    int ad[1000][1000];
    
    int n, m, k;
    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ad[i][j] = 0;
        }
    }
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i< m; ++i) {
        int ai, bi;
        scanf("%d%d", &ai, &bi);
        ad[ai][bi] = k;
        ad[bi][ai] = k;
    }
    
    int nod = 0;
    int coada[1000], s = 0, b = 0, viz[1000] = {0};
    coada[s++] = nod;
    viz[0] = 1;
    while(s - b > 0) {
        nod = coada[b];
        b++; //pop
        //printf("%d %d\n", s, b);
        for(int i = 0; i < n; ++i) {
            if (i == nod)
                continue;
            if (ad[nod][i] > 0 && viz[i] == 0) {
                coada[s++] = i;
                viz[i] = viz[nod] + k;
            }
        }
    }
    
    for (int i = 0; i < n; ++i)
        printf("%d ", viz[i]);
    return 0;
}