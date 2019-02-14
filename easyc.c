#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>

#include "easyc.h"

#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ETRY } }while(0);
#define THROW longjmp(ex_buf__, 1)

/*-------------------------------implementation----------------------------*/

void __ecStart(const char* caller) {//gate way
	if(caller ==NULL)return;
	int i=0;
	int isMain = 1;
	const char* varifier = "main";
	while(caller[i] != '\0') {
		if(caller[i] == varifier[i]){i++;continue;}
		else{isMain = 0;puts("not main");break;}}

	if(isMain) {// call from __main__
		puts("initializing...");
		// initialize mainLists and connect to GC
		mainLists.n_added = 0;
		mainLists.n_available = LIST_INIT ;// 32
		mainLists.lists = (List**) __safeMalloc(sizeof(List*)*LIST_INIT);
		for(i=0; i<LIST_INIT; i++){  //LIST_INIT 32
			mainLists.lists[i] = (List*) __safeMalloc(sizeof(List));
			mainLists.lists[i]->head = NULL;
		}
		atexit(__garbageCollector);
	} else {// call for more lists
		puts("Ok ok..");
	}
}


void* __safeMalloc(size_t n) { // return NULL if fail
	void* vp = (void*) malloc((unsigned int) n);
	if(vp == NULL)
		return NULL;
	return vp;
}

/*----------------------------------Lists-----------------------------------*/

void newVar(const char* var, const char* caller) { // _(variable_name)
	List* lp = __safeMalloc(sizeof(List));

	// initialize Helper Node
	lp->head = (Helper*) __safeMalloc(sizeof(Helper));
	lp->head->head = lp->head->tail;
	lp->head->tail = lp->head->head;
	lp->head->anotherHelper = NULL;

	// initialize List Node
	lp->listInfo = 0x11; //0001 0001 new empty list
	lp->listName = __safeMalloc(sizeof(char)*MAX_VAR_LEN);
	strncpy(lp->listName, var, MAX_VAR_LEN);
	lp->order = 0x00; //000 00 00 0 : (order, last first-added type, last added type, next list)
	// Int, str, float, obj = 0 1 2 3

	lp->n_nodes = 0;

	mainLists.lists[0] = lp;
	return;
}

int addVar(List* lis, int amount) {
	return 0;

}

int intOrFl(const char* var) {
	printf("%s number to be analyzed\n", var);
	return 0;
}

int getType(const size_t value,const size_t* addr) {
	char target[256];
	char* floatZero = "0.0000000000000";
	int j;
	int i = sprintf(target, "%.13f", *addr);
	printf("%d %.13f %d %d read to be analyzed\n", (target[0]),*addr, addr[0],i);
	puts("");

	for(j=0; j<9; j++) {
		if(target[j] == '\0') {
			break;
		}
		if(target[j] != floatZero[j]) {
			puts("float");
			return Flt;
		}
	}

	i = sprintf(target, "%d", addr[0]);
	printf("%d --- %s-----\n", *addr, target);
	for(j=0; j<i; j++) {
		if(target[j]-'0' != addr[j]) {
			puts("string");
			return Str;
		}
	}
	puts("Int");
	return Int;
}

/*----------------------------------LAMBDA------------------------------*/

void apply(const char* func)
{
	printf("%s inside apply\n",func);
}

/*----------------------------------garbage collecting------------------------------*/

void __freeList(List* list){
	Node* np;
	Node* prev;

	if(list != NULL){
		if(list->head != NULL){
			np = list->head->head;
			while(np != NULL || np != list->head->tail){
				prev = np;
				np = np->next;
				prev->next = NULL;
				prev->nextSame = NULL;
				free(prev->data);
				free(prev);
			}
			// reached tail or NULL
			if(np == list->head->tail && np != list->head->head){
				np->next = NULL;
				np->nextSame = NULL;
				free(np->data);
				free(np);
			}
			free(list->head);
			mainLists.n_added--; // careful!
		}
	}
}

void __garbageCollector(){
	int i, n;
//	puts("collecting garbage...");
	if(mainLists.lists == NULL){
		return;
	}
//	printf("deleting %d lists...\n", mainLists.n_lists);
	n = mainLists.n_added;
	for(i=0; i<n ; i++){
		if(*mainLists.lists != NULL){
			__freeList(mainLists.lists[i]);
		}
	}
}

/*----------------------------------end of gc---------------------------------------*/

// for exception handle may use
