#include <stdio.h>

#include "list.h"

typedef struct{
	int id;
	int sum;
}Student;

void Dump(list_t* list){
	printf("\tDump:\n");
	// node_t* it = list->next;
	// while(it!=NULL) {
	//     Student* student = (Student*)&(it->payload);
	// 	printf("\tid:%d sum=%d count:%d\n", student->id, student->sum, list->size );
	// 	it = it->next;
	// }
}

int main(int argc, char const *argv[]){
	printf("Hello World\n");

	list_t* list = list_alloc();

	// + 3 -2 + 3 = 4
	// add 3 items
	do{
		node_t* node = list_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 100;
		student->id = 1;
		list_push_back(list, node);
	}while(0);

	do{
		node_t* node = list_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 200;
		student->id = 2;
		list_push_back(list, node);
	}while(0);

	do{
		node_t* node = list_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 300;
		student->id = 3;
		list_push_back(list, node);
	}while(0);

	printf("1.size:%zu\n", list_size(list) );

	// remove 2 items
	do{
		node_t* node = list_pop_front(list);
		if(node){
			Student* student = (Student*)&(node->payload);
			printf("\tid:%d sum=%d count:%zu\n", student->id, student->sum, list_size(list) );
		}
	}while(0);

	do{
		node_t* node = list_pop_front(list);
		if(node){
			Student* student = (Student*)&(node->payload);
			printf("\tid:%d sum=%d count:%zu\n", student->id, student->sum, list_size(list)  );
		}
	}while(0);

	printf("2.size:%zu\n", list_size(list) );
	// add 3 items
	do{
		node_t* node = list_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 400;
		student->id = 4;
		list_push_back(list, node);
	}while(0);

	do{
		node_t* node = list_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 500;
		student->id = 5;
		list_push_back(list, node);
	}while(0);

	do{
		node_t* node = list_node_alloc(sizeof(Student));
		Student* student = (Student*) &(node->payload);
		student->sum = 600;
		student->id = 6;
		list_push_back(list, node);
	}while(0);

	printf("3.size:%zu\n", list_size(list) );

	// iterate
	do{
		list_iterator_t* it = list_iterator_alloc(list);
		node_t* node = NULL;
		do{
			node= list_iterator_next(it);
			if(node == NULL) break;
			Student* student = (Student*)&(node->payload);
			printf("\tIterator id:%d sum=%d count:%zu\n", student->id, student->sum, list_size(list) );
			if (student->id==4 ) {
				list_iterator_remove_node(it);
			}
			if (student->id==5 ) {
				list_iterator_remove_node(it);
			}
			if( student->id == 6 )
				list_iterator_remove_node(it);
		}while( node != NULL);
	}while(0);

	//

	// pop all
	do{
		node_t* node = list_pop_front(list);
		if(node){
			Student* student = (Student*)&(node->payload);
			printf("\tpop all id:%d sum=%d count:%zu\n", student->id, student->sum, list_size(list) );
			continue;
		}

		assert(0 && "Never go to here!");
	}while( list_size(list) > 0);

	printf("4.size:%zu\n", list_size(list) );
	return 0;
}
