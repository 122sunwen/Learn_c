#include<stdio.h>
int max(int x,int y,int z)
{
    int k;      
    if(x>y&&x>z)     
        k=x;    
    else if(y>z)
        k=y;
    else
        k=z;    
    return k; 
}

int main()
{
    int max(int x,int y,int z);       //对被调函数max进行引用性声明
    int a,b,c,d;                  //定义整型变量a,b,c
    scanf("%d %d %d",&a,&b,&c);       //输入变量a和b的值
    d=max(a,b,c);          
    printf("max=%d",d);    
    return 0;
}