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