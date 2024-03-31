#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101

typedef struct{
float coef;
int expon;
}polynomial;


char compare(int a,int b)
{
    if(a>b)return '>';
    else if(a==b) return '=';
    else return '<';
}

polynomial terms[MAX_TERMS];


void attach(float coef,int expon,int avail)
{
    if(avail>MAX_TERMS){
        fprintf(stderr,"항의개수가 너무 많음 \n");
        exit(1);
    }
    terms[avail].coef=coef;
    terms[avail].expon=expon;

}

void poly_add2(int As,int Ae,int Bs,int Be,int *Cs,int *Ce )
{
    float tempcoef;
    int avail=Be+1;
    *Cs=avail;
    while(As<=Ae && Bs<=Be)
    switch (compare(terms[As].expon,terms[Bs].expon)){
case '>':
    attach(terms[As].coef,terms[As].expon,avail);
    As++;
    avail++;
    break;
case '=':
    tempcoef=terms[As].coef+terms[Bs].coef;
    if(tempcoef)
        attach(tempcoef,terms[As].expon,avail);
    As++;
    Bs++;
    avail++;
    break;
case '<':
    attach(terms[Bs].coef,terms[Bs].expon,avail);
    Bs++;
    avail++;
    break;
}
for(;As<=Ae;As++){
    attach(terms[As].coef,terms[As].expon,avail);
    avail++;
}
for(;Bs<Be;Bs++){
    attach(terms[Bs].coef,terms[Bs].expon,avail);
    avail++;
}
*Ce=avail-1;
}

void poly_sub2(int As,int Ae,int Bs,int Be,int *Cs,int *Ce )
{
    float tempcoef;
    int avail=Be+1;
    *Cs=avail;
    while(As<=Ae && Bs<=Be)
    switch (compare(terms[As].expon,terms[Bs].expon)){
case '>':
    attach(terms[As].coef,terms[As].expon,avail);
    As++;
    avail++;
    break;
case '=':
    tempcoef=terms[As].coef-terms[Bs].coef;
    attach(tempcoef,terms[As].expon,avail);
    As++;
    Bs++;
    avail++;
    break;
case '<':
    attach(-terms[Bs].coef,terms[Bs].expon,avail);
    Bs++;
    avail++;
    break;
}
for(;As<=Ae;As++){
    attach(terms[As].coef,terms[As].expon,avail);
    avail++;
}
for(;Bs<Be;Bs++){
    attach(terms[Bs].coef,terms[Bs].expon,avail);
    avail++;
}
*Ce=avail-1;
}

void print_poly(int s,int e)
{
    for(int i=s;i<=e;i++){
        if(terms[i].coef!=0)
        printf("%+3.1fx^%d ",terms[i].coef,terms[i].expon);
    }
    printf("\n");

}

int main()
{

    int n_A,n_B;
    int As,Ae,Bs,Be,Cs,Ce;
    int addsub;

    printf("<다항식 A>\n 항의 개수 :");
    scanf("%d",&n_A);
    for(int i=0;i<n_A;i++)
    {
        printf("차수가 높은 항부터 계수/차수 입력 :");
        scanf("%f %d",&terms[i].coef,&terms[i].expon);
    }
    printf("<다항식 B>\n 항의 개수 :");
    scanf("%d",&n_B);
    for(int i=n_A;i<(n_A+n_B);i++)
    {
        printf("차수가 높은 항부터 계수/차수 입력 :");
        scanf("%f %d",&terms[i].coef,&terms[i].expon);
    }
    printf("다항식 연산 1)덧셈 2)뺄셈:");
    scanf("%d",&addsub);

    As=0;
    Ae=n_A-1;
    Bs=n_A;
    Be=n_A+n_B-1;


    print_poly(As,Ae);
    print_poly(Bs,Be);
      switch(addsub)
    {
    case 1:
        printf("---------------------\nA,B합:\n");
        poly_add2(As,Ae,Bs,Be,&Cs,&Ce);
        print_poly(Cs,Ce);
        break;
    case 2:
        printf("---------------------\nA,B차:\n");
        poly_sub2(As,Ae,Bs,Be,&Cs,&Ce);
        print_poly(Cs,Ce);
        break;
    default:
        printf("잘못된값 입력 ");
        break;

    }

    return 0;
}
