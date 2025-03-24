#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
} *first=NULL;

int count(struct Node *p)
{
    int l = 0;
    while(p)
    {
        l++;
        p=p->next;
    }
    return l;
}

void create(int A[], int n)
{
    int i;
    struct Node *t, *last;
    first = (struct Node*)malloc(sizeof(struct Node));
    first->data=A[0];
    first->next=NULL;
    last=first;

    for(i=1;i<n;i++)
    {
        t=(struct Node*)malloc(sizeof(struct Node));
        t->data=A[i];
        t->next=NULL;
        last->next=t;
        last=t;
    }
}

void display(struct Node *p)
{
    while(p!=NULL)
    {
        printf("%d ", p->data);
        p=p->next;
    }
}

void reverse1(struct Node *p)
{
    int *A, i=0;
    struct Node *q = p;

    A=(int *)malloc(sizeof(int)*count(p));

    while(q!=NULL)
    {
        A[i]=q->data;
        q=q->next;
        i++;
    }
    q=p;
    i--;
    while(q!=NULL)
    {
        q->data=A[i];
        q=q->next;
        i--;
    }
}

void reverse2(struct Node *p)
{
    struct Node *q=NULL, *r=NULL;

    while(p!=NULL)
    {
        r=q;
        q=p;
        p=p->next;
        q->next=r;
    }
    first=q;
}

void recursiveReverse(struct Node *q, struct Node *p)
{
    if(p)
    {
        recursiveReverse(p,p->next);
        p->next=q;
    }
    else
        first = q;
}

int main()
{
    int A[]={10,20,30,40,50};
    create(A,5);
    recursiveReverse(NULL,first);
    display(first);
    printf("\n\n");
    return 0;
}