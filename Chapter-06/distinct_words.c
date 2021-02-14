#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD	100
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;
int	wcount = 0;
struct tnode **wordtab;
struct tnode *talloc (void);
char *str_dup (char *s);

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;

};

struct tnode *addtree (struct tnode *p, char *w);
void extract (struct tnode *p);
int freqcmp (const void *a, const void *b);
int getword (char *word, int lim);

int main (){
	struct tnode *root;
	char word[MAXWORD];
	int	i;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	wordtab = (struct tnode **) malloc(sizeof(struct tnode) * wcount);
	wcount = 0;
	extract(root);
	qsort(wordtab, wcount, sizeof wordtab[0], freqcmp);
	for (i = 0; i < wcount; i++)
		printf("%4d %s\n", wordtab[i]->count, wordtab[i]->word);
	return 0;
}

struct tnode *addtree (struct tnode *p, char *w){
	int	cond;

	if (p == NULL) {
		p = talloc();
		p->word = str_dup(w);
		p->count = 1;
		p->left = p->right = NULL;
		wcount++;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);

	return p;
}

struct tnode *talloc (void){
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *str_dup (char *s){
	char *p;

	if ((p = (char *) malloc(strlen(s) + 1)) != NULL)
		strcpy(p, s);
	return p;
}
void extract (struct tnode *p){
	if (p != NULL) {
		extract(p->left);
		wordtab[wcount++] = p;
		extract(p->right);
	}
}

int freqcmp (const void *a, const void *b){
	struct tnode **p, **q;

	p = (struct tnode **) a;
	q = (struct tnode **) b;
	return (*q)->count - (*p)->count;
}

int getch (void);
void ungetch (int c);
int getword (char *word, int lim){
	int	c;
	char *w = word;
	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}

	for ( ; --lim > 1; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

int getch (void){
    return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch (int c){
    if (bufp >= BUFSIZE)
        printf("Error: Too many characters!\n");
    else
        buf[bufp++] = c;
}
