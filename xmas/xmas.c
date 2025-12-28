#include <stdio.h>
#include <string.h>
int main() {char t[28][30];for(int i=0;i<28;i++){memset(t[i],95,30);t[i][29]=0;}for(int a=0,b=0,i=0,j=0;a<12;a++,b=(b+1)%8,i=(i+1)%9,j=(j+1)%6){t[i][13-i]=t[j+8][9-j]=t[b+14][8-b]=t[1][13]=42;t[j+2][12-j]=t[i+5][13-i]=t[a+10][13-a]=t[j+22][12]=t[21][j*2+2]=t[7][9]=t[13][8]=t[27][13]=111;}for(int i=0;i<28;i++){for(int j=0;j<13;j++){t[i][26-j]=t[i][j];}}for(int i=0;i<28;i++)puts(t[i]);return 0;}
