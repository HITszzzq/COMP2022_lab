#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
    char StuID[11];
    int Grade;
    struct node *next;
} StudentLinkedListNode;


/* �����ཻ���� */
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2)
{
    // a��b�������ɽ��ֵ��ͬ
    // beforeCross1Ϊ������a�еĸ������ӵ�beforeCross1 + 1����㿪ʼ�ཻ
    // beforeCross2Ϊ������b�еĸ������ӵ�beforeCross2 + 1����㿪ʼ�ཻ
    // �ཻ�����ǽ�b�е�ǰһ���ָ��a�е��׸��ཻ���
    StudentLinkedListNode *p, *q;
    while(beforeCross1--)a=a->next;
    while(--beforeCross2)b=b->next;
    p = b->next;
    b->next = a;
    //����Ұָ����
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

void destroyCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, StudentLinkedListNode* crossNode)
{
    StudentLinkedListNode* p = crossNode->next, *q;
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    while(a != crossNode)
    {
        q = a->next;
        free(a);
        a = q;
    }
    while(b != crossNode)
    {
        q = b->next;
        free(b);
        b = q;
    }
    free(crossNode);
}

/* ��ӡ�����ڵ� */
void printLinkedListNode(StudentLinkedListNode * node)
{
    printf("{ID:%s, Grade:%d}", node->StuID, node->Grade);
    if(node->next!=NULL)
    {
        printf("->");
    }
    else
    {
        printf("\n");
    }

}

/** ����ñ�ĳɼ���� */
void outputStudentLinkedList(StudentLinkedListNode* head)
{
    // ���ڵ����ڵ�����ĺ���printLinkedListNode���ṩ
    //����ʵ�ֱ���������߼�
    //TODO
    StudentLinkedListNode *p = NULL;
    p = head;
    while(p != NULL)
    {
        printLinkedListNode(p);
        p = p->next;
    }
    free(p);
    return;
}


/** �½�һ������node������ */
StudentLinkedListNode* studentLinkedListCreate(char student_id[], int grade)
{
    //tips:malloc��ʱ��ǵ�Ϊת��Ϊ�ṹ��ָ��
    //TODO
    int i = 0;
    StudentLinkedListNode *p = NULL;
    p = (StudentLinkedListNode *)malloc(sizeof(StudentLinkedListNode));
    if(p == NULL) //�������ڴ�ʧ�ܣ�������ʾ���˳� 
    {
        printf("No enough memory to allocate!\n");
        exit(0);
    }
    else
    {
        while(student_id[i] != '\0') //�ַ�������ѭ����ʽ¼�� 
        {
            p->StuID[i] = student_id[i];
            i++;
        }
        p->StuID[i] = '\0';
        p->Grade = grade;
    }
    return p;
}


/** ���ս������ѧ���ĳɼ����,����������ͷָ�� */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node)
{
    //TODO
    if(head == NULL)
	{
		head = node;
		head->next = NULL;
	}
	else 
	{
   	 	node->next = head;	
	}
	return node;
}


/** ��ת���� */
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head)
{
    //TODO
    StudentLinkedListNode *p = NULL,*q = NULL,*r = NULL;
    p = head;
    q = p->next;
    r = q;
    head->next = NULL;
    while(q != NULL)
    {
        r = r->next;
        q->next = p;
        p = q;
        q = r;
    }
    return p;
}

/** �ҵ��ཻ�ĵ�һ����� */
StudentLinkedListNode* findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2)
{
    //class1��class2�ں�һ������ȫ�غϣ������ڴ��ַ��ͬ�������ҳ������ؿ�ʼ�ཻ�ĵ�һ����㡣
    //�벻Ҫ�򵥵�ͨ�����ṹ��ĳ�Ա���жϡ�
    //TODO
    StudentLinkedListNode *p = NULL,*q = NULL;
    int i = 0,j = 0,count;
    p = class1;
    q = class2;
    while(p != NULL)  //�ֱ����������ĳ���
    {
        p = p->next;
        i++;
    }
    while(q != NULL)
    {
        q = q->next;
        j++;
    }
    p = class1;
    q = class2;
    if(i >= j) //���ϳ������ָ�������ƶ� 
    {
        count = i - j;
        while(count > 0)
        {
            p = p->next;
            count--;
        }
    }
    else
    {
        count = j - i;
        while(count > 0)
        {
            q = q->next;
            count--;
        }
    }
    while(p != q) //��ʱ���������ָ���ĩβ��������ͬ����ָ��ͬʱ�ƶ������ҵ���ַ��ͬ�㼴��һ���ཻ��� 
    {
        p = p->next;
        q = q->next;
    }
    return p;
}

int main()
{
    freopen("./gradeImport.in","r",stdin);

    StudentLinkedListNode *class1=NULL, *class2=NULL;
    int num1, num2, i;
    char student_id[11];
    int grade;
    int beforeCross1, beforeCross2;
    StudentLinkedListNode *node;

    while(~scanf("%d%d", &num1, &num2))
    {
        class1 = class2 = NULL;
        // �洢���ݵ�����
        for(i = 0; i < num1; i++)
        {
            scanf("%s%d", student_id, &grade);
            node = studentLinkedListCreate(student_id, grade);
            class1 = studentLinkedListAdd(class1, node);
        }
        for(i = 0; i < num2; i++)
        {
            scanf("%s%d", student_id, &grade);
            node = studentLinkedListCreate(student_id, grade);
            class2 = studentLinkedListAdd(class2, node);
        }
        printf("* part1:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // ��ת����
        class1 = reverseLinkedList(class1);
        class2 = reverseLinkedList(class2);
        printf("* part2:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // �����ཻ����
        scanf("%d%d",&beforeCross1,&beforeCross2);
        createCrossLink(class1, class2, beforeCross1, beforeCross2);

        // ��ӡ�ཻ���
        node = findCrossBeginNode(class1, class2);
        printf("* part3:\n");
        printf("{ID:%s, Grade:%d}\n", node->StuID, node->Grade);

        //�����ཻ����
        destroyCrossLink(class1, class2, node);

        printf("\n");
    }
    return 0;
}
