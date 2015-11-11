#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;
#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10

typedef struct
{
    ElemType* base;
    int length;
    int listsize;
}SqList;

Status InitList_Sq(SqList &L);
Status ListInsert_Sq(SqList &L,int i,ElemType e);
Status ListDelete_Sq(SqList &L,int i,ElemType &e);
Status ListTraverse(SqList &L, Status (*visit)(ElemType&));
