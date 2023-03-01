#include "queue.h"

/** ！！要求使用栈实现队列，因此只能使用stack.h中的函数。不允许直接访问stack的底层实现！！**/

/**
 * 初始化队列
 * @param Q 操作队列
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * 清空队列 操作队列
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q 操作队列
 * @return 返回队列已使用长度
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * 判断队列是否为空
 * @param Q 操作队列
 * @return 如果为空返回1，否则返回0
 */
int QueueEmpty(Queue Q)
{
    //TODO
    return (StackLength(Q.stack1) + StackLength(Q.stack2) == 0) ? 1 : 0;
}

/**
 * 入队操作，将元素插入队列，需要处理队列满的情况（队列元素数目最多为 MaxSize）
 * @param Q 操作队列
 * @param e 插入的元素
 * @return 如果插入成功返回1，否则返回0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        认真思考，从哪个栈Push元素，时间复杂度如何？能否降低
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
 * 出队操作，从队列中取出一个元素
 * @param Q 操作队列
 * @param e 接受出队元素
 * @return 如果成功取出返回1，否则返回0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        认真思考，从哪个栈Pop元素，时间复杂度如何？能否降低
    */
    //TODO

    //平均时间复杂度O(1)
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
 * 获取队列头（不删除元素）
 * @param Q 操作队列
 * @param e 接受队列头元素
 * @return 如果成功获取返回1，否则返回0
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
 * 获取队列的一个数组拷贝，顺序为从队列头到队列尾
 * @param Q 操作队列
 * @param seq 栈中元素的一个拷贝
 */
void QueueToArray(Queue Q, DataType *seq)
{
    /*
        取决于你的栈如何设计，元素存在哪个队列里。
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
