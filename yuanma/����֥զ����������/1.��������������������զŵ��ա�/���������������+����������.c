/*
****数据结构之单链表的创建和删除
****by:千百度
****date:2017-5-30
*/
#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof(struct student)  //计算节点长度

typedef struct student
{
	int num;//学号
	char name[8];//姓名
	struct student* next;//结构指针指向下一个节点
}STU;
//创建链表
STU* create(void)
{
	STU *head=NULL,*p1,*p0;
	//head头节点，p1上一节点，p0下一节点
	int i=0;//节点数
	printf("请输入学号和名字，学号输入0结束\n");
	do{
		p0=(STU*)malloc(LEN);
		
		scanf("%d %s",&p0->num,&p0->name);
		if (i++==0)//如果节点数为0
	    	head=p0;//将头节点指向新建的节点
		else
		    p1->next=p0;//下个节点指向新建的节点
		p0->next=NULL;//最后的节点指向NULL
		p1=p0;//节点的给p1保存然后继续开辟节点
	} while(p0->num);
	return head;
}
//销毁链表
void destroylist(STU *head)  
{  
    struct student *p;  
    if(head==NULL)  
        printf("链表为空\n");  
    while(head)  
    {
        p=head->next;  
        free(head);  
        head=p;
    }
}
void print(struct student *head)  
{  
    STU *s = head;
    printf ("输出链表:\n");  
	while (s->num)
	{
		printf("学号:%5d  名字:%s\n",s->num,s->name);
		s=s->next;
	}
}

int main(void)
{
	STU *p=create();
	print(p);
	destroylist(p);
	return 0;
}