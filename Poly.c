#include<stdio.h>
void main()
{
        int n1,n2;
        struct polynomial{
                int coeff;
                int exp;
                }p1[10],p2[10],p3[20];
        int i;        
        printf("Enter the number of terms in first polynomial");
        scanf("%d",&n1);
         for( i=0;i<n1;i++)
         {
                 printf("Enter the coeffient");
                 scanf("%d",&p1[i].coeff);
                 printf("Enter the exponent");
                 scanf("%d",&p1[i].exp);
         }
         printf("Enter the number of terms in second polynomial");
        scanf("%d",&n2);
         for( i=0;i<n2;i++)
         {
                 printf("Enter the coeffient");
                 scanf("%d",&p2[i].coeff);
                 printf("Enter the exponent");
                 scanf("%d",&p2[i].exp);
         }
         for(i=0;i<n1-1;i++)
                         printf("%d(x)^%d + ",p1[i].coeff,p1[i].exp);
         printf("%d(x)^%d",p1[i].coeff,p1[i].exp);
         printf("\n\n");
         for(i=0;i<n2-1;i++)
                         printf("%d(x)^%d + ",p2[i].coeff,p2[i].exp);
         printf("%d(x)^%d",p2[i].coeff,p2[i].exp);
         printf("\n\n");
         i=0;
         int j=0,k=0;
         while(i<n1 && j<n2)
         {
                 if(p1[i].exp==p2[j].exp)
                 {
                         p3[k].exp=p1[i].exp;
                         p3[k].coeff=p1[i].coeff+p2[j].coeff;
                         i++,j++,k++;
                 }
                 else if(p1[i].exp>p2[j].exp)
                 {
                         p3[k].exp=p1[i].exp;
                         p3[k].coeff=p1[i].coeff;
                         i++,k++;
                 }
                 else
                 {
                         p3[k].exp=p2[j].exp;
                         p3[k].coeff=p2[j].coeff;
                         j++,k++;
                 }
         }
         while(i<n1)
         {
                 p3[k].exp=p1[i].exp;
                 p3[k].coeff=p1[i].coeff;
                 i++,k++;
         }
         while(j<n2)
         {
                 p3[k].exp=p2[j].exp;
                 p3[k].coeff=p2[j].coeff;
                 j++,k++;
         }
         for(i=0;i<k-1;i++)
                         printf("%d(x)^%d + ",p3[i].coeff,p3[i].exp);
         printf("%d(x)^%d",p3[i].coeff,p3[i].exp);        
 }
