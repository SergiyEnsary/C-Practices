#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {	/*table entry: */
	struct nlist *next;	/* next entry in chain */
	char *name;		/* defined name */
	char *defn;		/* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];	/* pointer table */

/* definition: form hash value for string s */
unsigned hash(char *s){
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* definition: look for s in hashtab */
struct nlist *lookup(char*s){
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;	/* found */
	return NULL;			/* not found*/
}

char *_strdup(char *s){
	char *p;

	p = malloc(strlen(s)+1); 	/* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* definition: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn){
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {	/* not found */
		np = malloc(sizeof(*np));
		if (np == NULL || (np->name = _strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else	/* already there */
		free( np->defn);	/* free previous defn */
	if ((np->defn = _strdup(defn)) == NULL)
		return NULL;
	return np;
}

void print(struct nlist *ptr){
	if (ptr != NULL) {
		printf("Name: %s defn: %s\n", ptr->name, ptr->defn);
		print(ptr->next);
	}
}

struct nlist *undef(char *name, struct nlist *first){
	struct nlist *ptr, *prev;
        int index = hash(name);

	ptr = hashtab[index];
	if (ptr == NULL) {
		printf("Name not found\n");
		return NULL;
	}
	if (first == ptr) {
		free(ptr->name);
		free(ptr->defn);
		ptr = NULL;
		if (hashtab[index]->next != NULL)
			return hashtab[index] = hashtab[index]->next;
		return NULL;
	}
	prev = first;
	while (prev->next != ptr)
		prev = prev->next;
	if (prev->next->next == NULL) {	/* Is the last element */
		free(prev->next->name);
		free(prev->next->defn);
		prev->next = hashtab[index] = NULL;
		return first;
	}
	free(ptr->name);
        free(ptr->defn);
        ptr = hashtab[index] = NULL;
	prev->next = prev->next->next;
	return first;
}

int main(void){
	struct nlist *ptr;

	ptr = install("A", "0");	/* head */
	ptr->next = install("IN", "1");
	ptr->next->next = install("O", "2");
	ptr->next->next->next = install("D", "30");
	ptr->next->next->next->next = install("C", "22");
	ptr = undef("IN", ptr);
	ptr = undef("A", ptr);
	print(ptr);
	return 0;
}
