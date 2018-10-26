#ifndef EASYC_H_
#define EASYC_H_

#define startEC __ecStart(__FUNCTION__)
#define DATA_UNIT (9)
#define DATA_SIZE (DATA_UNIT*5)
#define MORE_STACK 0xf66c
#define MORE_SLAVE 0xf77c

typedef struct _master Master;
typedef struct _slave Slave;
typedef struct _list List;
typedef struct _container Con;
typedef struct _stack Stack;

typedef enum _bool Bool;
typedef enum _const Const;


/*----------------------------------functions----------------------------*/

void __ecStart(const char* caller);
void __garbageCollector();
void* __safeMalloc(size_t n);
int createList(List* lis,char c, size_t data);

/*--------------------------------structs--------------------------------*/

typedef struct _list{
	char* list;
}List;
typedef struct _container{
	int size;
	List* container;
}Con;
typedef struct _slave{
	void* freeMe;
}Slave;
typedef struct _master{
	Slave* slaves;
	Master* fellas;
}Master;
typedef struct _stack{
	void* stack;
	size_t size;
	int top;
}Stack;

/*-------------------------------------enums--------------------------------*/


typedef enum _bool{
	false,
	true
}Bool;

Master ofMasters; // Use this only through ecStart                                       :)
Stack MainStack; // THIS TOO


/*-------------------------------implementation----------------------------*/

void __ecStart(const char* caller){
	if(caller ==NULL)return;
	int i=0;
	int isMain = 1;
	const char* varifier = "main";
	while(caller[i] != '\0'){
		if(caller[i] == varifier[i]){i++;continue;}
		else{isMain = 0;puts("not main");break;}}
	if(isMain){//something Good
		puts("initializing...");
		ofMasters.slaves = NULL; // No need for slaves if Masters have
		ofMasters.fellas = (Master*) malloc(sizeof(Master));
		if(ofMasters.fellas){
			fprintf(stderr,"*ERROR* cannot allocate memory space\n");
			return;
		}
		MainStack.stack = (char*) malloc(sizeof(char)*DATA_SIZE); // DATA_UNIT * 5 // 45 for now

	}else{//something Better
		puts("Ok ok..");
//		if(caller ==
	}
}


void* safeMalloc(size_t n) // return NULL if fail
{
	void* vp = (void*) malloc((unsigned int) n);
	if(vp == NULL)
		return NULL;

	return vp;
}


/*----------------------------------Lists-----------------------------------*/

int createList(List* lis, char c, size_t data)
{
	if(lis == NULL)
		return false;

	lis->list = (char*) malloc(sizeof(char)*9);
	if(lis->list == NULL)
		return false;

	*lis->list = c;
	*(lis->list+1) = (size_t) data;
	return true;
}


/*----------------------------------garbage collecting------------------------------*/

void garbageCollector(){
	if(ofMasters.slaves==NULL)return;
	while(ofMasters.slaves!=NULL)
	{if(ofMasters.slaves != NULL)free(ofMasters.slaves->freeMe);}
}
/*----------------------------------end of gc---------------------------------------*/

#endif //#ifndef EASYC_H_
