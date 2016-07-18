#ifndef SLIST_H
#define SLIST_H

#include <stddef.h>
#include <assert.h>

/*
list
*/
struct slist_priv;
typedef struct slist_t{
    struct slist_priv* priv;
}slist_t;
/*
list iterator
*/
struct slist_iterator_priv;
typedef struct slist_iterator_t{
    struct slist_iterator_priv* priv;
}slist_iterator_t;

/*
list node
*/
typedef struct snode_t{
    struct snode_t* prev;
    struct snode_t* next;
    /* Try to understand payload[1]，
       Don't hesitate to contact me (ade.li.indie(at)gmail.com)
    */
    char payload[1];
}snode_t;

//
// list functions
//
slist_t* slist_alloc();
void slist_release(slist_t*);

slist_iterator_t* slist_iterator_alloc();
snode_t* slist_iterator_next(slist_iterator_t* iterator);
void slist_iterator_release(slist_iterator_t* iterator);
void slist_iterator_remove_node(slist_iterator_t* iterator);

snode_t* slist_node_alloc(size_t payload_size);
void slist_node_release(snode_t* node);

void slist_push_back(slist_t* list, snode_t* node);
snode_t* slist_pop_front(slist_t* list);
size_t slist_size(slist_t* list);

#endif // SLIST_H
