#include <stdio.h>
struct student{
    int num;
    char name[20];
    int age;
    int cj1;
    int cj2;
    int cj3;
    int zcj;
};
int main(){
    struct student stu[3],temp;
for (int  i = 0; i < 3; i++)
{
    scanf("%d%s%d%d%d%d%d",&stu[i].num,stu[i].name,&stu[i].age,&stu[i].cj1,&stu[i].cj2,&stu[i].cj3,&stu[i].zcj);
}
int arr[2];
arr[0]=stu[0].cj1;
arr[1]=stu[1].cj1;
arr[2]=stu[2].cj1;
int i, j, tmp;  
    for (i = 0; i < 2; i++) {  
        for (j = 0; j < 1 - i ; j++) {  
            if (arr[j] < arr[j+1])
             {  
                tmp = arr[j];  
                arr[j] = arr[j+1];  
                arr[j+1] = tmp;  
                temp=stu[j];
                stu[j]=stu[j+1];
                stu[j+1]=temp;
             }  
        }  
    }  


for (int  i = 0; i < 3; i++)
{
    printf("%d %s %d %d %d %d %d\n",stu[i].num,stu[i].name,stu[i].age,stu[i].cj1,stu[i].cj2,stu[i].cj3,stu[i].zcj);
}
	return 0;
}
