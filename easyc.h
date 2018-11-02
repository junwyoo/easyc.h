#ifndef EASYC_H_
#define EASYC_H_

#define startEC __ecStart(__FUNCTION__)



#define LIST_INIT 32 // initial list size
#define NODE_LIMIT 10000 // List entry limit, can extend to x16
#define MAX_VAR_LEN 512
#define DECIMAL_MAX 13


#define IF(condition) {if(condition){
#define ELIF }else if{
#define ELSE }else {
#define END }}

//#define FOR(x, y) {int i=x;do{if(i==y){break;}i++;
//#define END_FOR }while(1);}

#define FOR(x, y) {int i=x;while(i++<y){



typedef struct _node Node;
typedef struct _list List;
typedef struct _helperNode Helper;
typedef enum _bool Bool;

/*----------------------------------functions----------------------------*/

// core functions

void __ecStart(const char* caller);
void __freeList(List* list);
void __garbageCollector();
void* __safeMalloc(size_t n);

// list management functions

void newVar(const char* var, const char* caller);
int addVar(List* lis, int amount);

int intOrFl(const char* var);
int getType(const size_t value, const size_t* addr);

// LAMBDA

void apply(const char* func);

/*--------------------------------structs--------------------------------*/

// nodes

typedef struct _node{ // elements in the variable
	size_t* data;
	Node* next;
	Node* nextSame; //next of same type
}Node;

typedef struct _helperNode{ // start of node (similar to head)
	Node* head; //points to head
	Node* tail; //points to tail
	Helper* anotherHelper;
}Helper;

// lists (collection of nodes)

typedef struct _list{ // One variable
	char listInfo; // 0000 0000 ( 0001 0000:
	char order; // 3:order, 2:last-first created type, 2:last added type, 1:next
	unsigned short n_nodes; //~65535 but limit to 10000 for performance
// 4bytes free
	char* listName;
	Helper* head;
}List;

typedef struct _listCollection{
	unsigned short n_available; // ~6553
	unsigned short n_added; //
	List** lists; //a,b,c,...z, _, wild
}Collection;



/*-------------------------------------enums--------------------------------*/

typedef enum _bool{
	false,
	true
}Bool;

//typedef enum _{
//};

typedef enum _type{
	Int=0,
	Str,
	Flt,
	Obj
}Type;

typedef enum _keyword{
	print=0,
	iif,  // ':'58 or 3A
	elif,
	els,
	func,
	class
}Keyword;

/*------------------------------------global-------------------------------*/

Collection mainLists;


#endif //#ifndef EASYC_H_
