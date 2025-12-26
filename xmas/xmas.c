#include <stdio.h>
#include <string.h>

int main() {
    char t[28][30];
    for(int i=0;i<28;i++){
        memset(t[i],95,30);
        t[i][29]=0;
    }
    for(int i=0;i<9;i++){
        t[i][13-i]=42;
    }
    for(int i=0;i<28;i++){
        for(int j=0;j<13;j++){
            t[i][26-j]=t[i][j];
        }
    }
    for(int i=0;i<28;i++)puts(t[i]);
    return 0;
}
