#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct term
{
    int coef, xexp, yexp, zexp;
    struct term *link;
}tm;

void create(tm *);
void display(tm *);
void evaluate(tm *);
void add(tm *, tm *, tm *);

int main()
{
    tm p1 = {.link = &p1}, p2 = {.link = &p2}, p3 = {.link = &p3};
    int ch;
    while (1)
    {
        printf("1. Evaluate\n2. Polynomial addition\n3. Exit\nChoice: "); scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                if (p1.link != &p1) p1.link = &p1;
                create(&p1);
                printf("Terms in polynomials are...\n"); display(&p1);
                evaluate(&p1);
                break;
            case 2:
                if (p1.link != &p1) p1.link = &p1;
                if (p2.link != &p2) p2.link = &p2;
                if (p3.link != &p3) p3.link = &p3;
                create(&p1); create(&p2);
                printf("Terms in poly1 are : "); display(&p1);
                printf("Terms in poly2 are : "); display(&p2);
                add(&p1, &p2, &p3);
                printf("Resultant polynomial : "); display(&p3);
                break;
            case 3:
                return 0;
        }
    }
}
void create(tm *p)
{
    int n, i;
    tm *t;
    printf("Enter number of terms : "); scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        t = (tm *)malloc(sizeof(tm));
        printf("Enter coef, xexp, yexp and zexp of the term : ");
        scanf("%d%d%d%d", &(t->coef), &(t->xexp), &(t->yexp), &(t->zexp));
        // front insertion
        t->link = p->link;
        p->link = t;
    }
}
void evaluate(tm *p)
{
    int x, y, z, res = 0;
    tm *t;
    printf("Enter value of x,y and z :"); scanf("%d%d%d", &x, &y, &z);
    for (t = p->link; t != p; t = t->link)
        res = res + t->coef * pow(x, t->xexp) * pow(y, t->yexp) * pow(z, t->zexp);
    printf("Evaluation of polynomial is %d\n", res);
}
int compare(tm *p, tm *q)
{
    return ((p->xexp == q->xexp) && (p->yexp == q->yexp) && (p->zexp == q -> zexp));
}
void attach(int s, tm *p, tm *r)
{
    tm *t = (tm *)malloc(sizeof(tm));
    t->coef = (s != 0) ? s : p->coef;
    t->xexp = p->xexp;
    t->yexp = p->yexp;
    t->zexp = p->zexp;
    // insert front
    t->link = r->link;
    r->link = t;
}
void delete(tm *p, tm *tp)
{
    tm *prev = p, *next = p->link;
    while (next != tp)
    {
        prev = next;
        next = next->link;
    }
    prev->link = next->link;
    free(next);
}
void add(tm *p, tm *q, tm *r)
{
    int val;
    tm *tp, *tq, *temp = NULL;
    for (tp = p->link; tp != p; tp = tp->link)
    {
        for (tq = q->link; tq != q; tq = tq->link)
        {
            val = compare(tp, tq);
            if (val) break;
        }
        switch (val)
        {
        case 0:
            attach(val, tp, r);
            break;
        case 1:
            val = tp->coef + tq->coef;
            attach(val, tp, r);
            delete (q, tq);
            break;
        }
        temp = tp;
        delete (p, temp);
    }
    // Remaining terms in P2 will be added to resultant polynomial
    for (tq = q->link; tq != q; tq = tq->link) attach(0, tq, r);
}
void display(tm *p)
{
    tm *t;
    if (p->link == p)
    {
        printf("Polynomial is empty\n");
        return;
    }
    for (t = p->link; t != p; t = t->link)
        printf("%dx^%dy^%dz^%d + ", t->coef, t->xexp, t->yexp, t->zexp);
    printf("\b\b \n");
}
