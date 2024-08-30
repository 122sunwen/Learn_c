#include <stdio.h>
#include <stdlib.h>
char filename[50];
typedef struct student
{
    int id;
    char name[10];
    int age;
    double c_score;
    double english_score;
    double mathanaly_score;
    double total_score;
    struct student *next;
} stu;
int saves(int m, stu s[]);
int menu()
{
    printf("\n\n***************————————————————————学生成绩管理系统—————————————————————————***************\n\n");
    printf("              -[1]录入学生成绩          -[2]删除学生成绩\n");
    printf("              -[3]查看学生成绩          -[4]以学号查找学生成绩\n");
    printf("              -[5]修改学生成绩          -[6]以学生姓名查找学生成绩\n");
    printf("              -[7]保存学生成绩          -[8]学生成绩报告\n");
    printf("              -[9]单科成绩排名          -[A/a]退出\n");
    printf("              -[0]刷新菜单\n");
    printf("**************—————————————————欢迎使用学生成绩管理系统————————————————————**************\n");
    printf("请输入数字或字母:\n");
}
int contnum(FILE *fp)
{
    char ch[2];
    int num = 0;
    ch[0] = -1;
    rewind(fp);
    while ((ch[1] = fgetc(fp)) != -1)
    {

        if (ch[1] == '\n' && ch[0] != '\n')
            num++;
        ch[0] = ch[1];
    }
    if (ch[0] != '\n' && ch[0] != -1)
        num++;
    // if(num>0){printf("此表已有%d个学生，分别是：/n",num);}else{printf("没有学生信息，是否添加：是(y)，否(N)");}
    return num;
}
int input()
{
    FILE *fp;
    int win = 0;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("打开文件失败!");
        exit(0);
    }
    int m = contnum(fp);
    stu s[m];
    rewind(fp);
    if (m > 0)
    {
        for (int i = 0; i < m; i++)
        {
            fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
        }
    }
    else
    {
        printf("没有学生信息。");
    }
    char c = 'y';
    int k, z = 1, t = 0;
    stu *head, *p;
    head = malloc(sizeof(stu));
    head->next = NULL;
    p = head;
    p = p->next;
    stu *new;
    while (1)
    {
        printf("是否继续输入学生信息：(y)yes,(n)no\n");
        getchar();
        scanf("%c", &c);
        if (c == 'y')
        {
            printf("请输入学号：");
            getchar();
            scanf("%d", &k);
        }
        else
        {
            stu s1[m + win];
            while (p != NULL)
            {
                for (int i = 0; i < m; i++)
                {
                    s1[i] = s[i];
                }
                for (int i = m; i < m + win; i++)
                {
                    s1[i].age = p->age, s1[i].id = p->id, s1[i].c_score = p->c_score, s1[i].english_score = p->english_score, s1[i].mathanaly_score = p->mathanaly_score;
                    for (int j = 0; j < 10; j++)
                    {
                        s1[i].name[j] = p->name[j];
                    }
                }
                p = p->next;
            }
            saves(m + win, s1);
            p = head;
            p = p->next;
            break;
        }
        if (m > 0)
        {
            for (int i = 0; i < m; i++)
            {
                if (k == s[i].id)
                {
                    printf("已经有此信息!\n");
                    t = 1;
                    break;
                }
                else
                {
                    t = 0;
                }
            }
        }
        if (t == 0)
        {
            while (p != NULL)
            {
                if (p->id == k)
                {
                    z = 0;
                    break;
                }
                else
                {
                    z = 1;
                    p = p->next;
                }
            }
        }
        if (z == 0)
        {
            printf("已经有此信息!");
            // break;
        }
        if(t==0&&z!=0)
        {
            win++;
            p = head;
            new = malloc(sizeof(stu));
            new->next = NULL;
            new->id = k;
            printf("input name:");
            fflush(stdin);
            scanf("%s", new->name);
            printf("\n请输入年龄,c,english,math:");
            fflush(stdin);
            scanf("%d,%lf,%lf,%lf", &new->age, &new->c_score, &new->english_score, &new->mathanaly_score);
            p->next = new;
            p = new;
        }
    }
}

void modify_0328();
void sort_by_total_score_0328();
void query_name_0328();
void sort_by_id_0328();
void sort_by_c_score_0328();
void sort_by_english_score_0328();
void sort_by_mathanaly_score_0328();
void query_0328();
void delete_0328();
void sort_0328();
void show();
void baogao();
int main()
{
    stu *s;
    FILE *fp;
    char option;
    printf("请输入文件名：");
    printf("\n");
    scanf("%s", filename);
    fp = fopen(filename, "a+");
    if (fp == NULL)
        exit(0);
    int m;
    fclose(fp);
    while (1)
    {
        menu();
        fflush(stdin);
        scanf("%c", &option);
        switch (option)
        {
        case '1':
            input();
            getchar();
            break;
        case '2':
            delete_0328();
            getchar();
            break;
        case '3':
            show();
            getchar();
            break;
        case '4':
            query_0328();
            getchar();
            break;
        case '5':
            modify_0328();
            getchar();
            break;
        case '6':
            query_name_0328();
            break;
        case '7':
            getchar();
            break;
        case '8':
            baogao();
            getchar();
            break;
        case '9':
            sort_0328();
            getchar();
            break;
        case '0':
            break;
        case 'A':
            exit(0);
        case 'a':
            exit(0);
        }
    }
}
void delete_0328()
{
    FILE *fp;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("打开文件失败!");
        exit(0);
    }
    int m = contnum(fp);
    stu s[m];
    rewind(fp);
    if (m > 0)
    {
        for (int i = 0; i < m; i++)
        {
            fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
        }
        char a = 'y';
        while (a == 'y')
        {
            printf("请输入你所需要删除的学号：");
            int delnum;
            int k = 0;
            fflush(stdin);
            scanf("%d", &delnum);
            for (int i = 0; i < m; i++)
            {
                if (delnum == s[i].id)
                {
                    k = 1;
                    printf("已删除.");
                    for (int j = i; j < m - 1; j++)
                    {
                        s[j] = s[j + 1];
                    }
                    m -= 1;
                    saves(m, s);
                    printf("是否继续删除?");
                    fflush(stdin);
                    scanf("%c", &a);
                    break;
                }
            }
            if (k != 1)
            {
                printf("没有信息");
                printf("是否继续删除?");
                fflush(stdin);
                scanf("%c", &a);
            }
        }
    }
    else
    {
        printf("文件中没有数据。");
    }
}
int saves(int m, stu s[])
{
    int i = 0;
    FILE *fp;
    fp = fopen(filename, "w");
    if (m != 0)
    {
        for (i = 0; i < m; i++)
        {
            fprintf(fp, "%d %s %d %lf %lf %lf\n", s[i].id, s[i].name, s[i].age, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
        }
    }
    fclose(fp);
}
void query_0328()
{
    FILE *fp;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("打开文件失败!");
        exit(0);
    }
    int m = contnum(fp);
    stu s[m];
    rewind(fp);
    if (m > 0)
    {
        for (int i = 0; i < m; i++)
        {
            fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
        }
        char a = 'y';
        while (a == 'y')
        {
            printf("请输入你所需要查询的学号：");
            int delnum;
            int k = 0;
            fflush(stdin);
            scanf("%d", &delnum);
            for (int i = 0; i < m; i++)
            {
                if (delnum == s[i].id)
                {
                    k = 1;
                    printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
                    printf("是否继续查询?");
                    fflush(stdin);
                    scanf("%c", &a);
                    break;
                }
            }
            if (k != 1)
            {
                printf("没有信息");
                printf("是否继续查询?");
                fflush(stdin);
                scanf("%c", &a);
            }
        }
        fclose(fp);
    }
    else
    {
        printf("文件中没有数据。");
    }
}
void modify_0328()
{
    FILE *fp;
    int win = 0;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("打开文件失败!");
        exit(0);
    }
    int m = contnum(fp);
    stu s[m];
    rewind(fp);
    if (m > 0)
    {
        for (int i = 0; i < m; i++)
        {
            fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
        }
        char a = 'y';
        while (a == 'y')
        {
            printf("请输入你所需要修改的学号：");
            int delnum;
            int k = 0;
            int t = 0;
            fflush(stdin);
            scanf("%d", &delnum);
            for (int i = 0; i < m; i++)
            {
                if (s[i].id == delnum)
                {
                    k = i;
                    t = 1;
                    break;
                }
            }
            if (t == 1)
            {
                printf("请输入你所需要修改的项目：");
                int loop;
                fflush(stdin);
                scanf("%d", &loop);
                switch (loop)
                {
                case 1:
                    printf("\n");
                    scanf("%s", s[k].name);
                    saves(m, s);
                    break;
                case 2:
                    printf("\n");
                    scanf("%d", s[k].age);
                    saves(m, s);
                    break;
                case 3:
                    printf("\n");
                    scanf("%lf", s[k].c_score);
                    saves(m, s);
                    break;
                case 4:
                    printf("\n");
                    scanf("%lf", s[k].english_score);
                    saves(m, s);
                    break;
                case 5:
                    printf("\n");
                    scanf("%lf", s[k].mathanaly_score);
                    saves(m, s);
                    break;
                }
                printf("保存完成");
            }
            else
            {
                printf("不存在信息!\n");
            }
            printf("是否继续修改：\n");
            scanf("%c", &a);
        }
        fclose(fp);
    }
}
void sort_0328()
{
    printf("请选择以什么形式排序，(1)学号,(2)C,(3)English,(4)mathanaly_score,(5)总成绩\n");
    int k, student_index;
    scanf("%d", &k);
    switch (k)
    {
    case 1:
        sort_by_id_0328();
        break;
    case 2:
        sort_by_c_score_0328();
        break;
    case 3:
        sort_by_english_score_0328();
        break;
    case 4:
        sort_by_mathanaly_score_0328();
        break;
    case 5:
        sort_by_total_score_0328();
        break;
    }
}
void sort_by_id_0328()
{
    FILE *fp;
    int win = 0;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("打开文件失败!");
        exit(0);
    }
    int m = contnum(fp);
    stu s[m];
    rewind(fp);
    if (m > 0)
    {
        for (int i = 0; i < m; i++)
        {
            fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            // printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
        }
        for (int i = 0; i < m - 1; i++)
        {
            for (int j = i + 1; j < m; j++)
            {
                if (s[i].id < s[j].id)
                {
                    stu c = s[i];
                    s[i] = s[j];
                    s[j] = c;
                }
            }
        }
        for (int i = 0; i < m; i++)
        {
            // fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
        }
    }
    else
    {
        printf("没有学生信息。");
    }
    fclose(fp);
}
void sort_by_c_score_0328()
{
    FILE *fp;
    int win = 0;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("打开文件失败!");
        exit(0);
    }
    int m = contnum(fp);
    stu s[m];
    rewind(fp);
    if (m > 0)
    {
        for (int i = 0; i < m; i++)
        {
            fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            // printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
        }
        for (int i = 0; i < m - 1; i++)
        {
            for (int j = i + 1; j < m; j++)
            {
                if (s[i].c_score < s[j].c_score)
                {
                    stu c = s[i];
                    s[i] = s[j];
                    s[j] = c;
                }
            }
        }
        for (int i = 0; i < m; i++)
        {
            // fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
        }
    }
    else
    {
        printf("没有学生信息。");
    }
    fclose(fp);
}
void sort_by_english_score_0328()
{
    FILE *fp;
    int win = 0;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("打开文件失败!");
        exit(0);
    }
    int m = contnum(fp);
    stu s[m];
    rewind(fp);
    if (m > 0)
    {
        for (int i = 0; i < m; i++)
        {
            fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            // printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
        }
        for (int i = 0; i < m - 1; i++)
        {
            for (int j = i + 1; j < m; j++)
            {
                if (s[i].english_score < s[j].english_score)
                {
                    stu c = s[i];
                    s[i] = s[j];
                    s[j] = c;
                }
            }
        }
        for (int i = 0; i < m; i++)
        {
            // fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
        }
    }
    else
    {
        printf("没有学生信息。");
    }
    fclose(fp);
}
void sort_by_mathanaly_score_0328()
{
    FILE *fp;
    int win = 0;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("打开文件失败!");
        exit(0);
    }
    int m = contnum(fp);
    stu s[m];
    rewind(fp);
    if (m > 0)
    {
        for (int i = 0; i < m; i++)
        {
            fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            // printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
        }
        for (int i = 0; i < m - 1; i++)
        {
            for (int j = i + 1; j < m; j++)
            {
                if (s[i].mathanaly_score < s[j].mathanaly_score)
                {
                    stu c = s[i];
                    s[i] = s[j];
                    s[j] = c;
                }
            }
        }
        for (int i = 0; i < m; i++)
        {
            // fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
        }
    }
    else
    {
        printf("没有学生信息。");
    }
    fclose(fp);
}
void show()
{
    FILE *fp;
    int win = 0;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("打开文件失败!");
        exit(0);
    }
    int m = contnum(fp);
    stu s[m];
    rewind(fp);
    if (m > 0)
    {
        for (int i = 0; i < m; i++)
        {
            fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
        }
    }
    else
    {
        printf("没有学生信息。");
    }
    fclose(fp);
}
void query_name_0328()
{
    FILE *fp;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("打开文件失败!");
        exit(0);
    }
    int m = contnum(fp);
    stu s[m];
    rewind(fp);
    if (m > 0)
    {
        for (int i = 0; i < m; i++)
        {
            fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
        }
        char a = 'y';
        while (a == 'y')
        {
            printf("请输入你所需要查询的姓名：");
            char name1[10];
            int k = 0;
            fflush(stdin);
            scanf("%s", name1);
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    if (name1[j] == s[i].name[j])
                    {
                        k = 1;
                    }
                    else
                    {
                        k = 0;
                        break;
                    }
                }
                if (k == 1)
                {
                    printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
                    printf("是否继续查询?");
                    fflush(stdin);
                    scanf("%c", &a);
                    break;
                }
            }
            if (k != 1)
            {
                printf("没有信息");
                printf("是否继续查询?");
                fflush(stdin);
                scanf("%c", &a);
            }
        }
    }
    else
    {
        printf("文件中没有数据。");
    }
    fclose(fp);
}
void baogao()
{
    FILE *fp;
    int win = 0;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("打开文件失败!");
        exit(0);
    }
    int m = contnum(fp);
    stu s[m];
    rewind(fp);
    if (m > 0)
    {
        for (int i = 0; i < m; i++)
        {
            fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            // printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
            s[i].total_score = s[i].c_score + s[i].english_score + s[i].mathanaly_score;
        }
        double and;
        double most;
        double least;
        double k1 = 0, k2 = 0, k3 = 0, k4 = 0, k5 = 0, k6 = 0;
        for (int j = 0; j < m; j++)
        {
            if (s[j].c_score < 60)
            {
                k1 += 1;
            }
            if (s[j].c_score >= 90)
            {
                k4 += 1;
            }
            if (s[j].english_score < 60)
            {
                k2 += 1;
            }
            if (s[j].english_score >= 90)
            {
                k5 += 1;
            }
            if (s[j].mathanaly_score < 60)
            {
                k3 += 1;
            }
            if (s[j].mathanaly_score >= 90)
            {
                k6 += 1;
            }
        }
        printf("c语言60分以下占比%lf\n", k1 / m);
        for (int j = 0; j < m; j++)
        {
            if (s[j].c_score < 60)
            {
                printf("%d %d %s %lf %lf %lf\n", s[j].age, s[j].id, s[j].name, s[j].c_score, s[j].english_score, s[j].mathanaly_score);
            }
        }
        printf("英语60分以下占比%lf\n", k2 / m);
        for (int j = 0; j < m; j++)
        {
            if (s[j].english_score < 60)
            {
                printf("%d %d %s %lf %lf %lf\n", s[j].age, s[j].id, s[j].name, s[j].c_score, s[j].english_score, s[j].mathanaly_score);
            }
        }
        printf("数学60分以下占比%lf\n", k3 / m);
        for (int j = 0; j < m; j++)
        {
            if (s[j].mathanaly_score < 60)
            {
                printf("%d %d %s %lf %lf %lf\n", s[j].age, s[j].id, s[j].name, s[j].c_score, s[j].english_score, s[j].mathanaly_score);
            }
        }
        printf("c语言90分以上占比%lf\n", k4 / m);

        for (int j = 0; j < m; j++)
        {
            if (s[j].c_score >= 90)
            {
                printf("%d %d %s %lf %lf %lf\n", s[j].age, s[j].id, s[j].name, s[j].c_score, s[j].english_score, s[j].mathanaly_score);
            }
        }
        printf("英语90分以上占比%lf\n", k5 / m);

        for (int j = 0; j < m; j++)
        {
            if (s[j].english_score >= 90)
            {
                printf("%d %d %s %lf %lf %lf\n", s[j].age, s[j].id, s[j].name, s[j].c_score, s[j].english_score, s[j].mathanaly_score);
            }
        }
        printf("数学90分以上占比%lf\n", k6 / m);
        for (int j = 0; j < m; j++)
        {
            if (s[j].mathanaly_score >= 90)
            {
                printf("%d %d %s %lf %lf %lf\n", s[j].age, s[j].id, s[j].name, s[j].c_score, s[j].english_score, s[j].mathanaly_score);
            }
        }
        most = s[0].total_score;
        least = s[0].total_score;
        for (int i = 0; i < m; i++)
        {
            if (s[i].total_score > most)
            {
                most = s[i].total_score;
            }
            if (s[i].total_score < least)
            {
                least = s[i].total_score;
            }
        }
        printf("最高分%lf,最低分%lf", most, least);
    }
    else
    {
        printf("没有学生信息");
    }
    fclose(fp);
}
void sort_by_total_score_0328()
{
    FILE *fp;
    int win = 0;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("打开文件失败!");
        exit(0);
    }
    int m = contnum(fp);
    stu s[m];
    rewind(fp);
    if (m > 0)
    {
        for (int i = 0; i < m; i++)
        {
            fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            // printf("%d %d %s %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score);
            s[i].total_score = s[i].c_score + s[i].english_score + s[i].mathanaly_score;
        }
        for (int i = 0; i < m - 1; i++)
        {
            for (int j = i + 1; j < m; j++)
            {
                if (s[i].total_score < s[j].total_score)
                {
                    stu c = s[i];
                    s[i] = s[j];
                    s[j] = c;
                }
            }
        }
        for (int i = 0; i < m; i++)
        {
            // fscanf(fp, "%d %s %d %lf %lf %lf\n", &s[i].id, s[i].name, &s[i].age, &s[i].c_score, &s[i].english_score, &s[i].mathanaly_score);
            printf("%d %d %s %lf %lf %lf %lf\n", s[i].age, s[i].id, s[i].name, s[i].c_score, s[i].english_score, s[i].mathanaly_score, s[i].total_score);
        }
    }
    else
    {
        printf("没有学生信息");
    }
    fclose(fp);
}
