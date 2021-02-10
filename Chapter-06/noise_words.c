#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS   (sizeof noisetab / sizeof noisetab[0])

/* types */
struct list {
	int number;
	struct list *next;
};

struct tnode {
	char *word;
	struct list *lines;
	struct tnode *left;
	struct tnode *right;
};

struct key {
	char *word;
	int  count;
};

/* functions */
int getword(char *, int);
struct tnode *talloc(void);
char *strDup(char *);
struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
void printList(struct list *);
struct key *binsearch(char *, struct key *, int);
void freetree(struct tnode *);

/* globals */
int    buf[BUFSIZE];
int    bufp = 0;

struct key noisetab[] = {
	{ "a", 0 },
	{ "and", 0 },
	{ "is", 0 },
	{ "of", 0},
	{ "on", 0},
	{ "the", 0 },
	{ "to", 0 },
	{ "was", 0},
	{ "were", 0},
	{ "with", 0},
};
int getword(char *word, int lim){
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isblank(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; ++w)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
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
struct tnode *talloc(void){
	return malloc(sizeof(struct tnode));
}
char *strDup(char *s){
	char *p;

	p = malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}
struct list *addlist(struct list *p, int ln){
	if (!p) {
		p = malloc(sizeof(struct list));
		p->number = ln;
		p->next = NULL;
	} else if (p->number != ln)
		p->next = addlist(p->next, ln);
	return p;
}
struct tnode *addtree(struct tnode *p, char *w, int ln){
	int cond;
	struct list *first = NULL;

	if (!p) {
		p = talloc();
		p->word = strDup(w);
		p->lines = addlist(first, ln);
		p->left = p->right = NULL;
	} else if (!(cond = strcmp(w, p->word)))
		p->lines = addlist(p->lines, ln);
	else if (cond < 0)
		p->left = addtree(p->left, w, ln);
	else
		p->right = addtree(p->right, w, ln);
	return p;
}
void treeprint(struct tnode *p){
	if (!p)
		return;
	treeprint(p->left);
	printf(" %s ", p->word);
	printList(p->lines);
	printf("\n");
	treeprint(p->right);
}
void printList(struct list *p)
{
	if (!p)
		return;
	printf("%d ", p->number);
	printList(p->next);
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
void freelist(struct list *node){
	if (!node)
		return;
	freelist(node->next);
	free(node);
}
void freetree(struct tnode *node){
	void freelist(struct list *);

	if (!node)
		return;
	freetree(node->left);
	freetree(node->right);
	free(node->word);
	freelist(node->lines);
	free(node);
}

int main(void){
	struct tnode *root;
	char word[MAXWORD];
	int lineno = 1;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && !binsearch(word, noisetab, NKEYS))
			root = addtree(root, word, lineno);
		else if (word[0] == '\n')
			++lineno;
	treeprint(root);
	freetree(root);
	root = NULL;
	return 0;
}
