#ifndef _LIST_H_
#define _LIST_H_
/*

if we have

struct student_t{
    char name[100];
    int id;
}

struct node_t{
    struct node_t* prev;
    struct node_t* next;
    char payload[1];
    //
    char name[100];
    int id;
}

+----------------+
|    prev[4]     |
+----------------+
|    next[4]     |
+----------------+                +----------+
|   payload[1]   | <- overlap ->  | name[100]|
+----------------+                +----------+
                                  | id[4]    |
                                  +----------+

// init node_t
node->priv = NULL;
node->next = NULL;
student *stu = malloc( (sizeof(node_t)-1) + sizeof(student_t) )

*/
#include <stddef.h>
#include <assert.h>

//
// list data struct define
//

/*
list
*/
struct list_priv;
typedef struct list_t{
    struct list_priv* priv;
}list_t;
/*
list iterator
*/
struct list_iterator_priv;
typedef struct list_iterator_t{
    struct list_iterator_priv* priv;
}list_iterator_t;

/*
list node
*/
typedef struct node_t{
    struct node_t* prev;
    struct node_t* next;
    /* Try to understand payload[1]，
        Don't hesitate to contact me (ade.li.indie(at)gmail.com)
    */
    char payload[1];
}node_t;

//
// list functions
//
list_t* list_alloc();
void list_release(list_t*);

list_iterator_t* list_iterator_alloc();
node_t* list_iterator_next(list_iterator_t* iterator);
void list_iterator_release(list_iterator_t* iterator);
void list_iterator_remove_node(list_iterator_t* iterator);

node_t* list_node_alloc(size_t payload_size);
void list_node_release(node_t* node);

void list_push_back(list_t* list, node_t* node);
node_t* list_pop_front(list_t* list);
size_t list_size(list_t* list);

#endif // _LIST_H_

