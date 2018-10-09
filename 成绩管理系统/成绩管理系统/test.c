#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
typedef struct tagStudent
{
	char szName[10];		//姓名
	int nAge;				//性别
	int nStuNum;			//学号
	float nScore;				//成绩
}Student;

typedef struct tagNode
{
	Student stu;			//学生信息
	struct tagNode* pNext;	//指向下一个学生
}Node;

Node *g_pHead = NULL;			//定义第一个学生

//录入学生信息
void InputStudent()
{
	printf("\n请输入学生信息:姓名 学号 年龄 成绩\n");

	Node* p;
	p = g_pHead;
	while (g_pHead != NULL && p->pNext != NULL)
	{
		p = p->pNext;
	}

	//为新的学生分配一个空间
	Node* pNewNode = (Node*)malloc(sizeof(Node));
	pNewNode->pNext = NULL;

	if (g_pHead == NULL)
	{
		g_pHead = pNewNode;
		p = g_pHead;
	}
	else
	{
		p->pNext = pNewNode;//p的下一个节点为pNewNode
	}

	//输入新的学生数据
	scanf("%s %d %d %d", pNewNode->stu.szName, &pNewNode->stu.nStuNum, &pNewNode->stu.nAge, &pNewNode->stu.nScore);

	system("cls");
	printf("\n数据添加成功....\n");

}



//打印学生信息
void PrintStudent()
{
	system("cls");
	printf("打印所有学生信息\n");

	Node* p;
	p = g_pHead;

	while (p != NULL)
	{
		printf("学号:%d\t姓名:%s\t年龄:%d\t成绩:%d\n",
			p->stu.nStuNum,
			p->stu.szName,
			p->stu.nAge,
			p->stu.nScore);

		p = p->pNext;
	}
}

//保存学生信息
void SaveStudent()
{
	system("cls");

	FILE *pFile = fopen("新建文本文档.txt", "w");
	if (pFile == 0)
	{
		printf("打开文件失败\n");
		return;
	}
	//写入数据
	Node *p;
	p = g_pHead;
	while (p != NULL)
	{
		fprintf(pFile, "%d %s %d %d\n", p->stu.nStuNum, p->stu.szName, p->stu.nAge, p->stu.nScore);

		p = p->pNext;
	}
	printf("数据保存成功\n");
	//关闭文件
	fclose(pFile);
}

//读取学员信息
void ReadStudent()
{
	system("cls");
	//首先删除链表数据，然后从文件中读取数据
	Node *p, *p2;
	p = p2 = g_pHead;

	while (p2 != NULL)
	{
		//卒个删除链表中的数据
		p = p->pNext;
		free(p2);
		p2 = p;
	}

	g_pHead = NULL;

	//打开文件
	FILE *pFile = fopen("新建文本文档.txt", "r");

	if (pFile == 0)
	{
		printf("打开文件失败\n");
		return;
	}

	//读取数据
	while (!feof(pFile))
	{
		//分配空间以存储数据
		Node *pTemp = (Node*)malloc(sizeof(Node));
		//从文件中读取
		fscanf(pFile, "%d %s %d %d\n", &pTemp->stu.nStuNum, &pTemp->stu.szName, &pTemp->stu.nAge, &pTemp->stu.nScore);

		//创建链表
		if (g_pHead == NULL)
		{
			g_pHead = pTemp;
			p = g_pHead;
		}
		else
		{
			p->pNext = pTemp;//p的下一个节点为temp
			p = p->pNext;
			p->pNext = NULL;
		}
	}

	//关闭文件
	fclose(pFile);
}

//统计所有学生人数
int CountStudent()
{
	system("cls");
	int nCount = 0;

	//先把文件中的数据读取到链表中
	ReadStudent();

	Node *p;
	p = g_pHead;

	while (p != NULL)
	{
		nCount++;
		p = p->pNext;
	}

	return nCount;
}

//查找学生信息
Node* FindStudent()
{
	system("cls");
	int nStuNum;
	printf("请输入要查找的学生的学号:\n");

	scanf("%d", &nStuNum);

	//先从文件中读取到链表中
	ReadStudent();
	Node* p;
	p = g_pHead;
	while (p != NULL)
	{
		if (p->stu.nStuNum == nStuNum)
		{
			return p;
		}

		p = p->pNext;
	}

	//遍历完链表也没有找到信息
	if (p == NULL)
	{
		printf("没有该学生的信息\n");
		return NULL;
	}

	return NULL;
}

//修改某个学生的信息
void ModifyStudent()
{
	system("cls");
	int nStuNum;
	printf("请输入要修改学生信息的学号:\n");
	scanf("%d", &nStuNum);

	//先把文件中的数据读取到链表中
	ReadStudent();

	Node* p;
	p = g_pHead;

	while (p != NULL)
	{
		if (p->stu.nStuNum == nStuNum)
		{
			printf("请输入要修改的信息：姓名 学号 年龄 成绩\n");
			scanf("%s %d %d %d", p->stu.szName, &p->stu.nStuNum, &p->stu.nAge, &p->stu.nScore);
			printf("修改成功!\n");
			break;
		}

		p = p->pNext;
	}

	if (p == NULL)
	{
		printf("没有该学生信息!\n");
	}
}

//删除学生信息
void DeleteStudent()
{
	system("cls");
	int nStuNum;
	printf("请输入要删除学生信息的学号:\n");

	scanf("%d", &nStuNum);
	//先把文件中的数据读取到链表
	ReadStudent();

	Node *p, *p2;

	p = g_pHead;
	//判断是否是头结点
	if (g_pHead->stu.nStuNum == nStuNum)
	{
		p2 = g_pHead;
		g_pHead = g_pHead->pNext;//头指针指向删除元素后的首元素
		free(p2);//释放节点
		return;
	}
	//不是头结点

	while (p->pNext != NULL)
	{
		if (p->pNext->stu.nStuNum == nStuNum)
		{
			p2 = p->pNext;
			p->pNext = p->pNext->pNext;//删除该节点指针跳过此节点
			free(p2);
			return;
		}

		p = p->pNext;//指向下一个节点
		if (p->pNext == NULL)
		{
			//判断是否到了链表的结尾
			break;
		}
	}

	if (p->pNext == NULL)
	{
		printf("没有该学生信息\n");
	}
}

int main()
{
	while (1)
	{
		printf("==============欢迎使用高校学生成绩管理系统V1.0==============\n");
		printf("\t=======请选择功能列表=======\n");
		printf("\t\t1.录入学生信息\n");
		printf("\t\t2.打印学生信息\n");
		printf("\t\t3.保存学生信息\n");
		printf("\t\t4.读取学生信息\n");
		printf("\t\t5.统计所有学生人数\n");
		printf("\t\t6.查找学生信息\n");
		printf("\t\t7.修改学生信息\n");
		printf("\t\t8.删除学生信息\n");
		printf("\t\t0.退出系统\n");

		char ch;

		//scanf("%c", &ch);
		ch = _getch();

		switch (ch)
		{
		case '1'://录入学生信息
			InputStudent();
			break;
		case '2'://打印学生信息
			PrintStudent();
			break;
		case '3'://保存学生信息
			SaveStudent();
			break;
		case '4'://读取学员信息
			ReadStudent();
			break;
		case '5'://统计所有学生人数
			printf("当前学生总人数为:%d\n", CountStudent());
			break;
		case '6'://查找学生信息
		{
					 Node *pNode = FindStudent();
					 if (pNode != NULL)
					 {
						 printf("学号:%d\t姓名:%s\t年龄:%d\t成绩:%d\n", pNode->stu.nStuNum, pNode->stu.szName, pNode->stu.nAge, pNode->stu.nScore);
					 }
					 break;
		}
		case '7'://修改某个学生的信息
			ModifyStudent();
			break;
		case '8'://删除学生信息
			DeleteStudent();
			break;
		case '0':
			printf("欢迎再次使用！\n");
			return 0;
			break;
		default:
			printf("您的输入有误，请重新输入！\n");
			break;
		}
	}
	system("pause");
	return 0;
}