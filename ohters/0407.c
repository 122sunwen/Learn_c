#include<stdio.h>
#include<string.h>
int main()
{
char s[100]; //用于存放长度小于100的字符串
int i=0;
scanf("%s",s);//输入字符串s
while (s[i]!='\0')
{
   if (s[i]=='0'||s[i]=='1'||s[i]=='2'||s[i]=='3'||s[i]=='4'||s[i]=='5'||s[i]=='6'||s[i]=='7'||s[i]=='8'||s[i]=='9')
{
    for (int j = 0; j < 100; j++)
    {
        s[j]=s[j+1];
    }
}   
 i++;
}
//修改字符串并添加结束字符
printf("%s",s);//输出修改后的字符串s
return 0;
}
