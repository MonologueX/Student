#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
typedef struct tagStudent
{
	char szName[10];		//����
	int nAge;				//�Ա�
	int nStuNum;			//ѧ��
	float nScore;				//�ɼ�
}Student;

typedef struct tagNode
{
	Student stu;			//ѧ����Ϣ
	struct tagNode* pNext;	//ָ����һ��ѧ��
}Node;

Node *g_pHead = NULL;			//�����һ��ѧ��

//¼��ѧ����Ϣ
void InputStudent()
{
	printf("\n������ѧ����Ϣ:���� ѧ�� ���� �ɼ�\n");

	Node* p;
	p = g_pHead;
	while (g_pHead != NULL && p->pNext != NULL)
	{
		p = p->pNext;
	}

	//Ϊ�µ�ѧ������һ���ռ�
	Node* pNewNode = (Node*)malloc(sizeof(Node));
	pNewNode->pNext = NULL;

	if (g_pHead == NULL)
	{
		g_pHead = pNewNode;
		p = g_pHead;
	}
	else
	{
		p->pNext = pNewNode;//p����һ���ڵ�ΪpNewNode
	}

	//�����µ�ѧ������
	scanf("%s %d %d %d", pNewNode->stu.szName, &pNewNode->stu.nStuNum, &pNewNode->stu.nAge, &pNewNode->stu.nScore);

	system("cls");
	printf("\n������ӳɹ�....\n");

}



//��ӡѧ����Ϣ
void PrintStudent()
{
	system("cls");
	printf("��ӡ����ѧ����Ϣ\n");

	Node* p;
	p = g_pHead;

	while (p != NULL)
	{
		printf("ѧ��:%d\t����:%s\t����:%d\t�ɼ�:%d\n",
			p->stu.nStuNum,
			p->stu.szName,
			p->stu.nAge,
			p->stu.nScore);

		p = p->pNext;
	}
}

//����ѧ����Ϣ
void SaveStudent()
{
	system("cls");

	FILE *pFile = fopen("�½��ı��ĵ�.txt", "w");
	if (pFile == 0)
	{
		printf("���ļ�ʧ��\n");
		return;
	}
	//д������
	Node *p;
	p = g_pHead;
	while (p != NULL)
	{
		fprintf(pFile, "%d %s %d %d\n", p->stu.nStuNum, p->stu.szName, p->stu.nAge, p->stu.nScore);

		p = p->pNext;
	}
	printf("���ݱ���ɹ�\n");
	//�ر��ļ�
	fclose(pFile);
}

//��ȡѧԱ��Ϣ
void ReadStudent()
{
	system("cls");
	//����ɾ���������ݣ�Ȼ����ļ��ж�ȡ����
	Node *p, *p2;
	p = p2 = g_pHead;

	while (p2 != NULL)
	{
		//���ɾ�������е�����
		p = p->pNext;
		free(p2);
		p2 = p;
	}

	g_pHead = NULL;

	//���ļ�
	FILE *pFile = fopen("�½��ı��ĵ�.txt", "r");

	if (pFile == 0)
	{
		printf("���ļ�ʧ��\n");
		return;
	}

	//��ȡ����
	while (!feof(pFile))
	{
		//����ռ��Դ洢����
		Node *pTemp = (Node*)malloc(sizeof(Node));
		//���ļ��ж�ȡ
		fscanf(pFile, "%d %s %d %d\n", &pTemp->stu.nStuNum, &pTemp->stu.szName, &pTemp->stu.nAge, &pTemp->stu.nScore);

		//��������
		if (g_pHead == NULL)
		{
			g_pHead = pTemp;
			p = g_pHead;
		}
		else
		{
			p->pNext = pTemp;//p����һ���ڵ�Ϊtemp
			p = p->pNext;
			p->pNext = NULL;
		}
	}

	//�ر��ļ�
	fclose(pFile);
}

//ͳ������ѧ������
int CountStudent()
{
	system("cls");
	int nCount = 0;

	//�Ȱ��ļ��е����ݶ�ȡ��������
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

//����ѧ����Ϣ
Node* FindStudent()
{
	system("cls");
	int nStuNum;
	printf("������Ҫ���ҵ�ѧ����ѧ��:\n");

	scanf("%d", &nStuNum);

	//�ȴ��ļ��ж�ȡ��������
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

	//����������Ҳû���ҵ���Ϣ
	if (p == NULL)
	{
		printf("û�и�ѧ������Ϣ\n");
		return NULL;
	}

	return NULL;
}

//�޸�ĳ��ѧ������Ϣ
void ModifyStudent()
{
	system("cls");
	int nStuNum;
	printf("������Ҫ�޸�ѧ����Ϣ��ѧ��:\n");
	scanf("%d", &nStuNum);

	//�Ȱ��ļ��е����ݶ�ȡ��������
	ReadStudent();

	Node* p;
	p = g_pHead;

	while (p != NULL)
	{
		if (p->stu.nStuNum == nStuNum)
		{
			printf("������Ҫ�޸ĵ���Ϣ������ ѧ�� ���� �ɼ�\n");
			scanf("%s %d %d %d", p->stu.szName, &p->stu.nStuNum, &p->stu.nAge, &p->stu.nScore);
			printf("�޸ĳɹ�!\n");
			break;
		}

		p = p->pNext;
	}

	if (p == NULL)
	{
		printf("û�и�ѧ����Ϣ!\n");
	}
}

//ɾ��ѧ����Ϣ
void DeleteStudent()
{
	system("cls");
	int nStuNum;
	printf("������Ҫɾ��ѧ����Ϣ��ѧ��:\n");

	scanf("%d", &nStuNum);
	//�Ȱ��ļ��е����ݶ�ȡ������
	ReadStudent();

	Node *p, *p2;

	p = g_pHead;
	//�ж��Ƿ���ͷ���
	if (g_pHead->stu.nStuNum == nStuNum)
	{
		p2 = g_pHead;
		g_pHead = g_pHead->pNext;//ͷָ��ָ��ɾ��Ԫ�غ����Ԫ��
		free(p2);//�ͷŽڵ�
		return;
	}
	//����ͷ���

	while (p->pNext != NULL)
	{
		if (p->pNext->stu.nStuNum == nStuNum)
		{
			p2 = p->pNext;
			p->pNext = p->pNext->pNext;//ɾ���ýڵ�ָ�������˽ڵ�
			free(p2);
			return;
		}

		p = p->pNext;//ָ����һ���ڵ�
		if (p->pNext == NULL)
		{
			//�ж��Ƿ�������Ľ�β
			break;
		}
	}

	if (p->pNext == NULL)
	{
		printf("û�и�ѧ����Ϣ\n");
	}
}

int main()
{
	while (1)
	{
		printf("==============��ӭʹ�ø�Уѧ���ɼ�����ϵͳV1.0==============\n");
		printf("\t=======��ѡ�����б�=======\n");
		printf("\t\t1.¼��ѧ����Ϣ\n");
		printf("\t\t2.��ӡѧ����Ϣ\n");
		printf("\t\t3.����ѧ����Ϣ\n");
		printf("\t\t4.��ȡѧ����Ϣ\n");
		printf("\t\t5.ͳ������ѧ������\n");
		printf("\t\t6.����ѧ����Ϣ\n");
		printf("\t\t7.�޸�ѧ����Ϣ\n");
		printf("\t\t8.ɾ��ѧ����Ϣ\n");
		printf("\t\t0.�˳�ϵͳ\n");

		char ch;

		//scanf("%c", &ch);
		ch = _getch();

		switch (ch)
		{
		case '1'://¼��ѧ����Ϣ
			InputStudent();
			break;
		case '2'://��ӡѧ����Ϣ
			PrintStudent();
			break;
		case '3'://����ѧ����Ϣ
			SaveStudent();
			break;
		case '4'://��ȡѧԱ��Ϣ
			ReadStudent();
			break;
		case '5'://ͳ������ѧ������
			printf("��ǰѧ��������Ϊ:%d\n", CountStudent());
			break;
		case '6'://����ѧ����Ϣ
		{
					 Node *pNode = FindStudent();
					 if (pNode != NULL)
					 {
						 printf("ѧ��:%d\t����:%s\t����:%d\t�ɼ�:%d\n", pNode->stu.nStuNum, pNode->stu.szName, pNode->stu.nAge, pNode->stu.nScore);
					 }
					 break;
		}
		case '7'://�޸�ĳ��ѧ������Ϣ
			ModifyStudent();
			break;
		case '8'://ɾ��ѧ����Ϣ
			DeleteStudent();
			break;
		case '0':
			printf("��ӭ�ٴ�ʹ�ã�\n");
			return 0;
			break;
		default:
			printf("���������������������룡\n");
			break;
		}
	}
	system("pause");
	return 0;
}