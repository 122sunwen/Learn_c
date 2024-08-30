#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>  
  
// 函数：将自然数n转换为字符串并追加到result中  
void appendNumberToString(unsigned long long n, char *result, int *len) {  
    int numLen = snprintf(result + *len, 21, "%llu", n); // 假设不会超过20位数字  
    *len += numLen;  
}  
  
// 函数：在S中查找S1第一次出现的位置  
int findPositionOfSubstring(const char *S1) {  
    char currentNum[21]; // 假设自然数不会超过20位  
    char tempS[11]; // 用于存储S1的当前匹配部分  
    int tempLen = 0; // tempS的当前长度  
    int S1Len = strlen(S1);  
    int position = 0; // 记录S1在S中的位置  
    unsigned long long currentNumValue = 0; // 当前正在处理的数字  
  
    while (true) {  
        // 将下一个数字添加到currentNum中  
        currentNumValue++;  
        appendNumberToString(currentNumValue, currentNum, &tempLen);  
  
        // 如果tempS和S1的前缀匹配，则继续添加数字到tempS中  
        if (tempLen < S1Len && memcmp(tempS, S1, tempLen) == 0) {  
            tempS[tempLen] = currentNum[tempLen];  
            tempLen++;  
        }  
        // 如果tempS和S1完全匹配，则返回位置  
        else if (tempLen == S1Len && memcmp(tempS, S1, S1Len) == 0) {  
            return position + tempLen - S1Len;  
        }  
        // 如果不匹配，重置tempS并更新位置  
        else {  
            tempLen = 0;  
            position += strlen(currentNum);  
        }  
    }  
      
    // 如果永远没有找到（实际上不可能，因为S是无限的），则返回一个错误值  
    return -1;  
}  
  
int main() {  
    char S1[11]; // 假设S1的长度不超过10，所以数组大小为11（包括结束符'\0'）  
    printf("Enter a number string S1 (length <= 10): ");  
    scanf("%10s", S1); // 读取最多10个字符作为S1  
  
    int position = findPositionOfSubstring(S1);  
    if (position != -1) {  
        printf("The first position of '%s' in S is: %d\n", S1, position);  
    } else {  
        printf("The string '%s' was not found in S.\n", S1);  
    }  
  
    return 0;  
}