#include<stdio.h>;
char inp[10];
int q0();
int q1();
int q2();
int q3();

int main(){
    int res;
    printf("enter");
    scanf("%s", inp);
    current= -1;
    res= q0();
    if(res==1)
    {
        printf("string accepted");
    }
    else{
        printf("not accepted");
    }
    return 0;
}
int q0(){
    
}
