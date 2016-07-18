#include <stdio.h>

#include "slist.h"

typedef struct{
	int id;
	int sum;
}Student;


int main(int argc, char const *argv[]){
	printf("Hello World\n");

	slist_t* list = slist_alloc();

	// + 3 -2 + 3 = 4
	// add 3 items
	do{
		snode_t* node = slist_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 100;
		student->id = 1;
		slist_push_back(list, node);
	}while(0);

	do{
		snode_t* node = slist_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 200;
		student->id = 2;
		slist_push_back(list, node);
	}while(0);

	do{
		snode_t* node = slist_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 300;
		student->id = 3;
		slist_push_back(list, node);
	}while(0);

	printf("1.size:%zu\n", slist_size(list) );

	// remove 2 items
	do{
		snode_t* node = slist_pop_front(list);
		if(node){
			Student* student = (Student*)&(node->payload);
			printf("\tid:%d sum=%d count:%zu\n", student->id, student->sum, slist_size(list) );
		}
	}while(0);

	do{
		snode_t* node = slist_pop_front(list);
		if(node){
			Student* student = (Student*)&(node->payload);
			printf("\tid:%d sum=%d count:%zu\n", student->id, student->sum, slist_size(list)  );
		}
	}while(0);

	printf("2.size:%zu\n", slist_size(list) );
	// add 3 items
	do{
		snode_t* node = slist_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 400;
		student->id = 4;
		slist_push_back(list, node);
	}while(0);

	do{
		snode_t* node = slist_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 500;
		student->id = 5;
		slist_push_back(list, node);
	}while(0);

	do{
		snode_t* node = slist_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 600;
		student->id = 6;
		slist_push_back(list, node);
	}while(0);

	printf("3.size:%zu\n", slist_size(list) );

	do{
		snode_t* node = slist_pop_front(list);
		if(node){
			Student* student = (Student*)&(node->payload);
			printf("\tid:%d sum=%d count:%zu\n", student->id, student->sum, slist_size(list) );
			continue;
		}

		assert(0 && "Never go to here!");
	}while( slist_size(list) > 0);

	printf("4.size:%zu\n", slist_size(list) );
	return 0;
}
