#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
void clear(void);
double top = 0;

int main(void){
    int type;
    double op1, op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
                push(atof(s));
                break;
        case '+':
                push(pop() + pop());
                break;
        case '*':
                push(pop() * pop());
                break;
        case '-':
                op2 = pop();
                push(pop() - op2);
                break;
        case '/':
                op2 = pop();
        if (op2 != 0.0)
                        push(pop() / op2);
                else
                        printf("error: zero divisor\n");
                break;
        case '%':
                op2 = pop();
                if (op2 != 0.0)
                        push(fmod(pop(), op2));
                else
                        printf("error: zero divisor\n");
                break;
        case '\n':
                printf("\t%.8g\n", pop());
                break;
        case 'p':
                if (top <= 0)
                        printf("No elements on the top of stack\n");
                else
                        push(top);
                break;
        case 'c':
                clear();
                break;
        case 's':
                op1 = pop();
                op2 = pop();
                push(op1);
                push(op2);
                break;
        default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}
#define MAXVAL 100

int sp = 0;
double val[MAXVAL];
void push(double f){
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}
double pop(void){
    if (sp > 0)
        return top = val[--sp];
    else {
        printf("error: stack empty\n");
        return top = 0.0;
    }
}
void clear(void){
    while (sp > 0)
        val[sp--] = 0.0;
        ;
    val[sp] = top = 0.0;
}
#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[]){
    int i;
	char c;

	scanf("%c", &c);
    while ((s[0] = c)  == ' ' || c == '\t')
		scanf("%c", &c);
    s[1] = '\0';
    if (!isdigit(c) && (c != '.' &&  c != '-'))
        return c;
    i = 0;
    if (c == '-') {
        while ((scanf("%c",&c))) {
            if (c == '\n') {
                ungetch(c);
                return '-';
            }
            if (isdigit(c)) {
                s[++i] = '-';
                s[i] = c;
                break;
            }
        }
    }
    if (isdigit(c)) /* collect integer part */
            while (isdigit(s[++i] = c = getch()))
                    ;
    if (c == '.')   /* collect fractional part */
            while (isdigit(s[++i] = c = getch()))
                    ;
    s[i] = '\0';
    if (c != EOF)
          ungetch(c);
    return NUMBER;
}
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
