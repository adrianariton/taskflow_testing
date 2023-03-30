#include <stdio.h>
#include <string.h>
#define Q ('?' - '0')
#define MOD ((1e9) + 7)
#define NMAX 500002

int number(int secv[NMAX], int start, int ones, int len, int qs) {
    if (len == 1)
        return 0;
    if(secv[start] == 0) {
        return number(secv, start + 1, ones, len-1, qs);
    }

    else  if(secv[start] == 1){
        secv[start + len - ones + 1] = 1;
        return number(secv, start + 1, ones - 1, len - 1, qs) + len - ones;
    } 
    ones ++;
    secv[start]=1;
    int a = 0;
    for(int i = 0; i < qs; ++i) {
        a += number(secv, start, ones + i, len, qs - 1 - i);
    }

    secv[start]=0;
    ones --;
    return a + number(secv, start, ones, len, qs -1);
}

int main() {
    int secv[NMAX], s = 0, ones =0, qs = 0;
    char c;
    char str[NMAX];
    fgets(str, NMAX, stdin);
    for(int i = 0; i < strlen(str) -1 ; ++i) {
        c = str[i];
        int a = c - '0';
        //printf("%d ", a);
        if (a==1)
            ones++;

        if (a==Q)
            qs++;
        secv[s++] = a;
    }
    printf("%d", number(secv, 0, ones, s, qs));
}