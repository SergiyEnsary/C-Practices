#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>                   /* for malloc && atoi */
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS (int) (sizeof keytab / sizeof keytab[0])

/* types */
struct tnode {                     /* the tree node: */
	char *word;                    /* points to the text */
	int match;                     /* number of occurrences */
	struct tnode *left;            /* left child */
	struct tnode *right;           /* right child */
};

struct key {
	char *word;
	int count;
};

/* functions */
int getword(char *, int);
struct key *binsearch(char *, struct key *, int);
struct tnode *addtree(struct tnode *, char *, size_t n);
struct tnode *talloc(void);        /* alocate memory to new tree node */
char *strDup(char *);              /* copy string into safe place */
void checkmatch(char *, struct tnode *, size_t, int *);
void printtree(struct tnode *);
void freetree(struct tnode *);

/* globals */
int buf[BUFSIZE];                   /* buffer from ungetch */
int bufp = 0;                       /* next free position in buf */

struct key keytab[] ={
	{ "auto", 0 },
	{ "break", 0 },
	{ "case", 0 },
	{ "char", 0 },
	{ "const", 0 },
	{ "continue", 0 },
	{ "default", 0 },
	{ "do", 0 },
	{ "double", 0 },
	{ "else", 0 },
	{ "enum", 0 },
	{ "extern", 0 },
	{ "float", 0 },
	{ "for", 0 },
	{ "goto", 0 },
	{ "if", 0 },
	{ "int", 0 },
	{ "long", 0 },
	{ "register", 0 },
	{ "return", 0 },
	{ "short", 0 },
	{ "signed", 0 },
	{ "sizeof", 0 },
	{ "static", 0 },
	{ "struct", 0 },
	{ "switch", 0 },
	{ "typeof", 0 },
	{ "union", 0 },
	{ "unsigned", 0 },
	{ "void", 0 },
	{ "volatile", 0 },
	{ "while", 0 },
};

struct tnode *addtree(struct tnode *p, char *w, size_t n){
	int cond;
	static int found;

	if (!p) {
		p = talloc();
		p->word = strDup(w);
		p->match = *(&found);
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) < 0) {
		checkmatch(w, p, n, &found);
		p->left = addtree(p->left, w, n);
	} else if (cond > 0) {
		checkmatch(w, p, n, &found);
		p->right = addtree(p->right, w, n);
	}
	found = 0;
	return p;
}
void checkmatch(char *w, struct tnode *p, size_t n, int *found){
	if (!strncmp(w, p->word, n))
		p->match = *found = 1;
}

void printree(struct tnode *p)
{
	if (!p)
		return;
	printree(p->left);
	if (p->match)
		printf(" %s\n", p->word);
	printree(p->right);
}

struct tnode *talloc(void)
{
	return malloc(sizeof(struct tnode));
}

void freetree(struct tnode *node){
	if (!node)
		return;
	freetree(node->left);
	freetree(node->right);
	free(node->word);
	free(node);
}

char *strDup(char *s){
	char *p;

	p = malloc(strlen(s) + 1);
	if (p)
		strcpy(p, s);
	return p;
}

struct key *binsearch(char *word, struct key *tab, int n){
	int cond;
	struct key *low = &tab[0];
	struct key *high = &tab[n];
	struct key *mid;

	while (low < high) {
		mid = low + (high - low) / 2;
		if ((cond = strcmp(word, mid->word)) < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return NULL;
}

int getword(char *word, int lim){
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == '_' || c == '#') {
		for ( ; --lim > 0; ++w)
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
	} else if (c == '\'')
		while ((c = getch()) != '\'')
			;
	else if (c == '\"')  {
		while ((c = getch()) != '\"')
			if (c == '\\')
				getch();
	} else if (c == '/' && (c = getch()) == '*')
		while ((c = getch()) != EOF)
			if (c == '*' && (c = getch()) == '/')
				break;
	*w ='\0';
	return c;
}

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int main(int argc, char *argv[]){
	struct tnode *root;
	char word[MAXWORD];
	size_t nChar;

	nChar = (--argc == 1) ? atoi(*++argv) : 6;
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if ((isalpha(word[0]) || word[0] == '_') && strlen(word) >= nChar &&
				!binsearch(word, keytab, NKEYS))
			root = addtree(root, word, nChar);
	printree(root);
	freetree(root);
	root = NULL;
	return 0;
}
