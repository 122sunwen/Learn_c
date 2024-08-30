//项目一：学生信息管理系统 student system manger
//10230326 孙文 3班 
//用了和课上不同的思路，这里减少了对文件的操作，只在开始和保存时操作文件，其他时候对链表操作，这样减少了一些麻烦

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char filename[50];
typedef struct student {
	int id;                //学号
	char name[10];         //姓名
	int age;               //年龄
	float c_score;         // C语言成绩
	float english_score;   //英语成绩
	float math_score; 	   //数分成绩
	float total_score;     //总分
	struct student *next;

} stu;

// 创建新节点
stu* createNode_10230326(int id, const char *name, int age, float c_score, float english_score, float math_score) {
	stu *newNode = (stu*)malloc(sizeof(stu));
	if (!newNode) {
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	newNode->id = id;
	strncpy(newNode->name, name, sizeof(newNode->name) - 1); // 确保不会溢出
	newNode->name[sizeof(newNode->name) - 1] = '\0'; // 确保字符串结束符
	newNode->age = age;
	newNode->c_score = c_score;
	newNode->english_score = english_score;
	newNode->math_score = math_score;
	newNode->total_score = c_score + english_score + math_score;
	newNode->next = NULL;
	return newNode;
}

void appendToList_10230326(stu **head, stu *newNode) {
	if (*head == NULL) {
		*head = newNode;
	} else {
		stu *current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
}

// 解析学生信息并创建新节点
stu* createStudentFromLine_10230326(char* line) {
	// 假设 line 格式为 "id name age c_score english_score math_score"
	char *token = strtok(line, " ");
	if (token == NULL) return NULL; // 无效的输入行

	stu* newNode = (stu*)malloc(sizeof(stu));
	if (newNode == NULL) {
		// 处理内存分配失败
		return NULL;
	}

	newNode->id = atoi(token);
	token = strtok(NULL, " ");
	if (token == NULL) {
		free(newNode);
		return NULL; // 无效的输入行
	}

	strncpy(newNode->name, token, sizeof(newNode->name) - 1); // 防止缓冲区溢出
	newNode->name[sizeof(newNode->name) - 1] = '\0'; // 确保字符串末尾为 null 终止符

	token = strtok(NULL, " ");
	if (token == NULL) {
		free(newNode);
		return NULL; // 无效的输入行
	}

	newNode->age = atoi(token);
	token = strtok(NULL, " ");
	if (token == NULL) {
		free(newNode);
		return NULL; // 无效的输入行
	}

	newNode->c_score = atof(token);
	token = strtok(NULL, " ");
	if (token == NULL) {
		free(newNode);
		return NULL; // 无效的输入行
	}

	newNode->english_score = atof(token);
	token = strtok(NULL, " ");
	if (token == NULL) {
		free(newNode);
		return NULL; // 无效的输入行
	}
	newNode->math_score = atof(token);
	newNode->next = NULL;
	newNode->total_score = newNode->c_score + newNode->english_score + newNode->math_score;
	return newNode;
}

// 读取文件并将学生信息添加到链表中
void readFromFile_10230326(const char* filename, stu** head) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		perror("Error opening file");
		return;
	}

	char line[1024]; // 假设每行不会超过1024个字符
	*head = NULL; // 初始化链表头为NULL
	stu* tail = NULL; // 跟踪链表的尾部

	while (fgets(line, sizeof(line), file)) {
		// 去除行尾的换行符（如果有的话）
		line[strcspn(line, "\n")] = 0;

		stu* newNode = createStudentFromLine_10230326(line);
		if (newNode == NULL) {
			// 处理无效行或内存分配失败
			continue;
		}

		if (*head == NULL) {
			*head = newNode;
			tail = newNode;
		} else {
			tail->next = newNode;
			tail = newNode;
		}
	}

	fclose(file);
}

// 计数链表中的学生数量
int countStudent_10230326(stu *head) {
	int count = 0;
	stu *current = head;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}


// 将链表中的数据写入文件  //保存学生成绩
void writeToFile_10230326(const char *filename, stu *head) {
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		perror("Error opening file for writing");
		return;
	}

	// 遍历链表
	stu *current = head;
	while (current != NULL) {
		// 将学生信息按照格式写入文件
		// 假设想要的格式为 "id name age c_score english_score math_score\n"
		fprintf(file, "%d %s %d %.2f %.2f %.2f\n",
		        current->id,
		        current->name,
		        current->age,
		        current->c_score,
		        current->english_score,
		        current->math_score);

		// 移动到下一个节点
		current = current->next;
	}
	fclose(file);
}

//输出一个学生信息函数
void print_one_student_10230326(stu* current) {
	printf("ID: %-8d\n", current->id);
	printf("Name: %-8s\n", current->name);
	printf("Age: %-3d\n", current->age);
	printf("C Score: %.2f\n", current->c_score);
	printf("English Score: %.2f\n", current->english_score);
	printf("Mathanylse Score: %.2f\n", current->math_score);
	system("pause");
	system("cls");
};
// 遍历链表并打印学生信息
void printList_10230326(stu *head) {
	stu *current = head;
	while (current != NULL) {
		printf("ID: %-8d, Name: %-6s, Age: %-3d, C Score: %.2f, English Score: %.2f, Mathanylse Score: %.2f, Total Score: %.2f\n",
		       current->id, current->name, current->age, current->c_score, current->english_score, current->math_score, current->total_score);
		current = current->next;
	}
	system("pause");
	system("cls");
}
void print_student_10230326(stu* head) {
	stu* move = head; // move 是一个指向节点的指针
	printf("现有学生信息：\n");
	while (move != NULL) {
		printf("%-8d %-8s %-3d %.2f %.2f %.2f\n",
		       move->id, move->name, move->age,
		       move->c_score, move->english_score, move->math_score);
		move = move->next;
	}
	system("pause");
	system("cls");
}


void menu_10230326() {
	printf("*****************______________学生成绩管理系统______________*****************\n");
	printf("               -[1]录入学生成绩         -[2]删除学生成绩\n");
	printf("               -[3]查看学生成绩         -[4]以学号查找学生\n");
	printf("               -[5]修改学生成绩         -[6]以姓名查找学生\n");
	printf("               -[7]保存学生成绩         -[8]学生成绩报告\n");
	printf("               -[9]单科/总分排名        -[A/a]退出\n");
	printf("               -[0]刷新菜单\n");
	printf("*****************____________欢迎使用学生成绩管理系统_____________*****************\n");
	printf("输入你想做的事件编号(0--A):    \n");
}

void deleteStudent_10230326(stu **head, int id) {
	stu *prev = NULL;
	stu *current = *head;

	// 查找要删除的节点
	while (current != NULL && current->id != id) {
		prev = current;
		current = current->next;
	}

	// 如果找到了节点
	if (current != NULL) {
		// 如果节点是头节点
		if (prev == NULL) {
			*head = current->next;
		} else {
			// 否则，更新前一个节点的next指针
			prev->next = current->next;
		}
		// 释放节点内存
		free(current);
		printf("Student with ID %d deleted successfully.(学生信息删除成功)\n", id);
	} else {
		printf("Error: Student with ID %d not found.(学生信息删除失败，未找到该学生)\n", id);
	}
	system("pause");
	system("cls");
}  //删除函数，键盘输入学生学号，调用删除函数

int isIdExists_10230326(stu *head, int id) {
	stu *current = head;
	while (current != NULL) {
		if (current->id == id) {
			return 1; // 学号已存在
		}
		current = current->next;
	}
	return 0; // 学号不存在
}

void input_student_10230326(stu **head) {
	int id;                //学号
	char name[10];         //姓名
	int age;               //年龄
	float c_score;         // C语言成绩
	float english_score;   //英语成绩
	float math_score;      //数分成绩
	do {
		printf("是否新增学生信息（Y/N）\n");
		while (getchar() != '\n');
		char choice;
		choice = getchar();
		if (choice == 'Y') {
			printf("请输入学生的学号、姓名、年龄、C语言成绩、英语成绩、数分成绩: \n");
			scanf(" %d %49s %d %f %f %f", &id, name, &age, &c_score, &english_score, &math_score);

			if (isIdExists_10230326(*head, id)) {
				printf("Error: ID %d already exists.(学生已存在，添加学生信息失败)\n", id);
			} else {
				//将新创建的结点，添加到链表的尾部
				stu *newNode = createNode_10230326(id, name, age, c_score, english_score, math_score);
				appendToList_10230326(head, newNode);
			}

		} else if (choice == 'N') {
			break;
		} else {
			printf("无效的选项\n");
		}

	} while (1);
	system("pause");
	system("cls");
}

// 修改学生信息
void modifyStudentInfo_10230326(stu **head, int id) {
	stu *current = *head;

	while (current != NULL && current->id != id) {
		current = current->next;
	}
	if (current != NULL) {
		printf("Student found with ID: %d\n", id);
		printf("Enter new name (leave blank to keep the same)（请输入新名字，若输入空格则不修改名字）: ");
		char newName[50];
		scanf("%49s", newName); // 防止缓冲区溢出
		if (newName[0] != '\0') { 
			strcpy(current->name, newName);
		}
		// 修改年龄
		printf("Enter new age (leave 0 to keep the same)（请输入新年龄，若输入0则不修改年龄）: ");
		int newAge;
		scanf("%d", &newAge);
		if (newAge != 0) { // 如果输入了新年龄
			current->age = newAge;
		}

		// 修改C语言成绩
		printf("Enter new C score (leave 0.0 to keep the same)（请输入新成绩，若输入0.0则不修改成绩）: ");
		float newCScore;
		scanf("%f", &newCScore);
		if (newCScore != 0.0f) { // 如果输入了新成绩
			current->c_score = newCScore;
		}

		// 修改英语成绩
		printf("Enter new English score (leave 0.0 to keep the same)（请输入新成绩，若输入0.0则不修改成绩）: ");
		float newEnglishScore;
		scanf("%f", &newEnglishScore);
		if (newEnglishScore != 0.0f) { // 如果输入了新成绩
			current->english_score = newEnglishScore;
		}
		// 修改数分成绩
		printf("Enter new Mathanylse score (leave 0.0 to keep the same)（请输入新成绩，若输入0.0则不修改成绩）: ");
		float newMathScore;
		scanf("%f", &newMathScore);
		if (newMathScore != 0.0f) { // 如果输入了新成绩
			current->math_score = newMathScore;
		}

		printf("Student information modified successfully.(学生信息修改成功)\n");
	} else {
		printf("Error: Student with ID %d not found.（未找到该学生）\n", id);
	}
	system("pause");
	system("cls");
}


// 通过学号查询学生
void findStudentById_10230326(stu *head, int id) {
	stu *current = head;
	int found = 0; // 标记是否找到学生

	// 遍历链表查找学生
	while (current != NULL) {
		if (current->id == id) {
			found = 1; 
			print_one_student_10230326(current);
			break;
		}
		current = current->next;
	}
	if (!found) {
		printf("Error: Student with ID %d not found.(未找到该学生)\n", id);
	}
}
// 通过名字查询学生
void findStudentByName_10230326(stu *head, char name[50]) {
	stu *current = head;
	int found = 0; // 标记是否找到学生

	// 遍历链表查找学生
	while (current != NULL) {
		if (!strcmp( current->name, name)) {
			found = 1; 
			print_one_student_10230326(current);
			break;
		}
		current = current->next;
	}

	if (!found) {
		printf("Error: Student with Name %s not found.(未找到该学生)\n", name);
	}
}

// 定义排序选项
typedef enum {
	SORT_BY_C,
	SORT_BY_ENGLISH,
	SORT_BY_MATH,
	SORT_BY_TOTAL,
} SortOption;


// 冒泡排序辅助函数
void bubbleSort_10230326(stu **head, SortOption option) {
	stu *current, *next, *temp;
	int swapped;

	do {
		swapped = 0;
		current = *head;

		while (current != NULL && current->next != NULL) {
			next = current->next;

			// 根据选项选择排序的字段
			float score1, score2;
			switch (option) {
				case SORT_BY_C:
					score1 = current->c_score;
					score2 = next->c_score;
					break;
				case SORT_BY_ENGLISH:
					score1 = current->english_score;
					score2 = next->english_score;
					break;
				case SORT_BY_MATH:
					score1 = current->math_score;
					score2 = next->math_score;
					break;
				case SORT_BY_TOTAL:
					score1 = current->total_score;
					score2 = next->total_score;
					break;
			}

			// 如果前一个节点的成绩小于后一个节点的成绩（假设升序排序），则交换
			if (score1 < score2) {
				// 交换节点
				temp = current->next;
				current->next = next->next;
				next->next = current;

				// 如果current是头节点，更新头指针
				if (current == *head) {
					*head = next;
				} else {
					// 否则，找到current的前一个节点并更新其next指针
					stu *prev = *head;
					while (prev->next != current) {
						prev = prev->next;
					}
					prev->next = next;
				}

				swapped = 1;
			} else {
				current = current->next;
			}
		}
	} while (swapped);
}


// 根据成绩排序并打印的函数
void sortAndPrintByScore_10230326(stu *head, SortOption option) {
	bubbleSort_10230326(&head, option);
	printList_10230326(head);
}

void analyzeScores_10230326(stu *head) {
	system("cls");
	int count_c_below_60 = 0, count_c_above_90 = 0;
	int count_eng_below_60 = 0, count_eng_above_90 = 0;
	int count_math_below_60 = 0, count_math_above_90 = 0;
	int count_total_below_60 = 0, count_total_above_90 = 0;
	stu *current;

	// 遍历链表统计各科和总分的60分以下和90分以上人数
	for (current = head; current != NULL; current = current->next) {
		if (current->c_score <= 60) count_c_below_60++;
		if (current->c_score >= 90) count_c_above_90++;
		if (current->english_score <= 60) count_eng_below_60++;
		if (current->english_score >= 90) count_eng_above_90++;
		if (current->math_score <= 60) count_math_below_60++;
		if (current->math_score >= 90) count_math_above_90++;
		if (current->total_score <= 60) count_total_below_60++;
		if (current->total_score >= 90) count_total_above_90++;
	}

	float total_students = countStudent_10230326(head);
	if (total_students >= 0) {
		// 打印各科和总分的60分以下占比和90分以上占比
		printf("各科和总分的60分以下占比和90分以上占比 ：\n");
		printf("C Score: Below 60: %.2f%%, Above 90: %.2f%%\n",
		       (count_c_below_60 / (float)total_students) * 100,
		       (count_c_above_90 / (float)total_students) * 100);
		printf("English Score: Below 60: %.2f%%, Above 90: %.2f%%\n",
		       (count_eng_below_60 / (float)total_students) * 100,
		       (count_eng_above_90 / (float)total_students) * 100);
		printf("Math Score: Below 60: %.2f%%, Above 90: %.2f%%\n",
		       (count_math_below_60 / (float)total_students) * 100,
		       (count_math_above_90 / (float)total_students) * 100);
		printf("Total Score: Below 60: %.2f%%, Above 90: %.2f%%\n",
		       (count_total_below_60 / (float)total_students) * 100,
		       (count_total_above_90 / (float)total_students) * 100);
		// 打印60分以下的学生信息
		printf("\nStudents with Scores Below 60(60分以下的学生信息):\n");
		printf("C Score:\n");
		for (current = head; current != NULL; current = current->next) {
			if (current->c_score <= 60) {
				printf("ID: %d, Name: %s, C Score: %.2f\n", current->id, current->name, current->c_score);
			}
		}
		printf("English Score:\n");
		for (current = head; current != NULL; current = current->next) {
			if (current->english_score <= 60) {
				printf("ID: %d, Name: %s, English Score: %.2f\n", current->id, current->name, current->english_score);
			}
		}
		printf("Math Score:\n");
		for (current = head; current != NULL; current = current->next) {
			if (current->math_score <= 60) {
				printf("ID: %d, Name: %s, Math Score: %.2f\n", current->id, current->name, current->math_score);
			}
		}
		// 打印90分以上的学生信息
		printf("\nStudents with Scores Above 90(90分以上的学生信息):\n");
		printf("C Score:\n");
		for (current = head; current != NULL; current = current->next) {
			if (current->c_score >= 90) {
				printf("ID: %d, Name: %s, C Score: %.2f\n", current->id, current->name, current->c_score);
			}
		}
		printf("English Score:\n");
		for (current = head; current != NULL; current = current->next) {
			if (current->english_score >= 90) {
				printf("ID: %d, Name: %s, English Score: %.2f\n", current->id, current->name, current->english_score);
			}
		}
		printf("Math Score:\n");
		for (current = head; current != NULL; current = current->next) {
			if (current->math_score >= 90) {
				printf("ID: %d, Name: %s, Math Score: %.2f\n", current->id, current->name, current->math_score);
			}
		}
	} else {
		printf("总人数为0,无学生成绩报告\n");
	}
	system("pause");
	system("cls");
}




int main() {
	char option;
	char name[50];
	int id;
	stu *head = NULL;
	printf("请输入保存学生信息的文件名称：");
	scanf("%49s", filename);
	readFromFile_10230326(filename, &head);
	int total_students = countStudent_10230326(head);
	menu_10230326();
	scanf(" %c", &option);
	while (1) {
		switch (option) {
			case '1':
				if (total_students > 0) {
					print_student_10230326(head);
					input_student_10230326(&head);

				} else {
					printf("此文件没有学生信息，请输入学生信息\n");
					input_student_10230326(&head);
				}
				break;
			case '2':
				printf("请输入要删除学生的学号:\n");
				scanf("%d", &id);
				deleteStudent_10230326(&head, id);
				break;
			case '3':
				if (total_students > 0) {
					printList_10230326(head);
				} else {
					printf("没有学生信息，请输入学生信息！\n");
				}
				break;
			case '4':
				printf("请输入要查找的学生学号：");
				scanf(" %d", &id);
				findStudentById_10230326(head, id);
				break;
			case '5':
				print_student_10230326(head);
				printf("请输入要修改的学生学号：");
				scanf(" %d", &id);
				modifyStudentInfo_10230326(&head, id);
				break;
			case '6':
				printf("请输入要查找的学生姓名：");
				scanf("%49s", name);
				findStudentByName_10230326(head, name);
				break;
			case '7':
				writeToFile_10230326(filename, head);
				printf("Successfully saved（保存成功！）");
				system("cls");
				break;
			case '8':
				analyzeScores_10230326(head);
				break;
			case '9':
				SortOption option;
				int opt;
				printf("Enter sorting option (1: C, 2: English, 3: Mathanylse, 4: Total): \n");
				printf("（请输入排序选项 (1:C语言成绩, 2:英语成绩, 3:数分成绩, 4:总分): ）\n");
				scanf(" %d", &opt);
				switch (opt) {
					case 1:
						option = SORT_BY_C;
						sortAndPrintByScore_10230326(head, option);
						break;
					case 2:
						option = SORT_BY_ENGLISH;
						sortAndPrintByScore_10230326(head, option);
						break;
					case 3:
						option = SORT_BY_MATH;
						sortAndPrintByScore_10230326(head, option);
						break;
					case 4:
						option = SORT_BY_TOTAL;
						sortAndPrintByScore_10230326(head, option);
						break;
					default:
						printf("Invalid option!(无效的选项)\n");
						break;
				}
				break;
			case 'a' :
				printf("是否保存更改，直接退出数据将丢失(Y/N)：");
				while (getchar() != '\n');
				char choice;
				choice = getchar();
				if (choice == 'Y') {
					writeToFile_10230326(filename, head);
					printf("Successfully saved（保存成功！）");
					printf("Bye Bye //再见！");
					exit(0);
				} else if (choice == 'N') {
					printf("Bye Bye //再见！");
					exit(0);
				} else {
					printf("无效的选项\n");
				}
				system("pause");
				break;
			case 'A' :
				printf("是否保存更改，直接退出数据将丢失(Y/N)：");
				while (getchar() != '\n');
				choice = getchar();
				if (choice == 'Y') {
					writeToFile_10230326(filename, head);
					printf("Successfully saved（保存成功！）");
					printf("Bye Bye //再见！");
					exit(0);
				} else if (choice == 'N') {
					printf("Bye Bye //再见！");
					exit(0);
				} else {
					printf("无效的选项\n");
				}
				system("pause");
				break;
			case '0':
				system("cls");
				break;
			default:
				printf("Invalid option!(无效的选项)\n");
				system("pause");
				system("cls");
				break;
		}
		menu_10230326();
		scanf(" %c", &option);
	}
	return 0;
}
