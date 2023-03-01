#include "queue.h"

/** ����Ҫ��ʹ��ջʵ�ֶ��У����ֻ��ʹ��stack.h�еĺ�����������ֱ�ӷ���stack�ĵײ�ʵ�֣���**/

/**
 * ��ʼ������
 * @param Q ��������
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * ��ն��� ��������
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q ��������
 * @return ���ض�����ʹ�ó���
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * �ж϶����Ƿ�Ϊ��
 * @param Q ��������
 * @return ���Ϊ�շ���1�����򷵻�0
 */
int QueueEmpty(Queue Q)
{
    //TODO
    return (StackLength(Q.stack1) + StackLength(Q.stack2) == 0) ? 1 : 0;
}

/**
 * ��Ӳ�������Ԫ�ز�����У���Ҫ��������������������Ԫ����Ŀ���Ϊ MaxSize��
 * @param Q ��������
 * @param e �����Ԫ��
 * @return �������ɹ�����1�����򷵻�0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        ����˼�������ĸ�ջPushԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //TODO
    if(StackLength(Q->stack1) + StackLength(Q->stack2) == MaxSize)
    {
        return 0;
    }
    else
    {
        return Push(&Q->stack1,e);
    }
}

/**
 * ���Ӳ������Ӷ�����ȡ��һ��Ԫ��
 * @param Q ��������
 * @param e ���ܳ���Ԫ��
 * @return ����ɹ�ȡ������1�����򷵻�0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        ����˼�������ĸ�ջPopԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //TODO

    //ƽ��ʱ�临�Ӷ�O(1)
    int f = 0;
    if(StackLength(Q->stack1) + StackLength(Q->stack2) == 0)
    {
        return 0;
    }
    else if(StackLength(Q->stack2) == 0)
    {
        while(Q->stack1.top > 0)
        {
            Pop(&Q->stack1,&f);
            Push(&Q->stack2,f);
        }
        return Pop(&Q->stack1,e);
    }
    else
    {
        return Pop(&Q->stack2,e);
    }
}

/**
 * ��ȡ����ͷ����ɾ��Ԫ�أ�
 * @param Q ��������
 * @param e ���ܶ���ͷԪ��
 * @return ����ɹ���ȡ����1�����򷵻�0
 */
int GetHead(Queue Q, DataType *e)
{
    //TODO
    int f = 0;
    if(StackLength(Q.stack1) + StackLength(Q.stack2) == 0)
    {
        return 0;
    }
    else if(StackLength(Q.stack2) == 0)
    {
        while(Q.stack1.top >= 0)
        {
            Pop(&Q.stack1,&f);
            Push(&Q.stack2,f);
        }
        return GetTop(Q.stack2,e);
    }
    else
    {
        return GetTop(Q.stack2,e);
    }
}

/**
 * ��ȡ���е�һ�����鿽����˳��Ϊ�Ӷ���ͷ������β
 * @param Q ��������
 * @param seq ջ��Ԫ�ص�һ������
 */
void QueueToArray(Queue Q, DataType *seq)
{
    /*
        ȡ�������ջ�����ƣ�Ԫ�ش����ĸ������
    */
    //TODO
    DataType Arr1[MaxSize],Arr2[MaxSize];
    int i = 0,j = 0;
    StackToArray(Q.stack1,Arr1);
    StackToArray(Q.stack2,Arr2);
    while(i < StackLength(Q.stack2))
    {
        seq[i] = Arr2[StackLength(Q.stack2) - (i + 1)];
        i++;
    }
    while(j < StackLength(Q.stack1))
    {
        seq[StackLength(Q.stack2) + j] = Arr1[j];
        j++;
    }
    return;
}
