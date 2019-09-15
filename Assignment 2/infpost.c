#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define maxn 10001

typedef struct token{
    int type;
    int prec;
    char operator;
    char operand;
} token;

typedef struct stack {
   token stck[maxn];
   long top;
} stack;

int isEmpty(stack *s){
    return s->top==0;
}

void push(stack *s, token v){
    s->top++;
    s->stck[s->top]=v;
}

token pop(stack *s){
    s->top--;
    return s->stck[s->top+1];
}

token get_token(char f){
    token x;
    switch(f){
        case '(':x.type=1;x.operator=f;x.prec=10;break;
        case ')':x.type=1;x.operator=f;x.prec=10;break;
        case '^':x.type=1;x.operator=f;x.prec=8;break;
        case '/':x.type=1;x.operator=f;x.prec=7;break;
        case '%':x.type=1;x.operator=f;x.prec=7;break;
        case '*':x.type=1;x.operator=f;x.prec=7;break;
        case '+':x.type=1;x.operator=f;x.prec=6;break;
        case '-':x.type=1;x.operator=f;x.prec=6;break;
        default:x.type=0;x.operand=f;break;
    }
    return x;
}

int main() {
    char *str=malloc(1100);
    char *strx=str+1;
    str[0]='(';
    scanf("%s", strx);
    int lenx=strlen(strx);
    str[lenx+1]=')';
    str[lenx+2]='\0';
    lenx=strlen(str);
    char *post=malloc(lenx+1);
    stack s;
    s.top=0;
    int i=0;
    token x, temp;
    for(int y=0; y<lenx; y++){
        x=get_token(str[y]);
        if(!x.type){
            post[i]=x.operand;
            i+=1;
        }
        else{
            if(x.operator=='(')
                push(&s, x);
            while(!isEmpty(&s) && s.stck[s.top].prec>x.prec && x.prec!=10 && s.stck[s.top].prec!=10){
                temp=pop(&s);
                post[i]=temp.operator;
                i+=1;
            }
            if(x.prec!=10)
                push(&s, x);
            if(x.operator==')'){ 
                temp=pop(&s);
                while(temp.operator!='('){
                    post[i]=temp.operator;
                    i+=1;
                    temp=pop(&s);
                }
            }   
        }
    }
    post[i]='\0';
    printf("%s\n",post);
    return 0;
}
