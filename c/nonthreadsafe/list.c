#include "list.h"
#include <stdlib.h>
#include <limits.h>

typedef struct list_priv{
    node_t* head;
    node_t* tail;
    size_t size;
}list_priv;

list_t* list_alloc(){
    list_t* list = (list_t*) malloc(sizeof(list_t));
    assert(list != NULL && "OOM");
    list->priv = (list_priv*) malloc(sizeof(list_priv));
    assert(list->priv != NULL && "OOM");

    list->priv->head = NULL;
    list->priv->tail = NULL;
    list->priv->size = 0;

    return list;
}

void list_release(list_t* list){
    free(list->priv);
    free(list);
}

node_t* list_node_alloc(size_t payload_size){
    if(payload_size == 0) payload_size=1;
    node_t* node = (node_t*)malloc(sizeof(node_t) - 1 + payload_size );
    assert(node != NULL && "OOM!");
    node->prev = NULL;
    node->next = NULL;

    return node;
}

void list_node_release(node_t* node){
    free(node);
}

void list_push_back(list_t* list, node_t* node){
    assert(list != NULL);
    assert(node != NULL);
    if(list->priv->size != 0){
        node_t*tail = list->priv->tail;
        tail->next = node;
        node->prev = tail;
        node->next = NULL;

        list->priv->tail = node;
    }else{
        list->priv->head = node;
        list->priv->tail = node;
        node->prev = NULL;
        node->next = NULL;
    }

    list->priv->size++;
}

node_t* list_pop_front(list_t* list){
    assert(list != NULL);
    node_t* node = list->priv->head;
    if(node != NULL){
        list->priv->head = node->next;
        list->priv->size--;
    }

    return node;
}

size_t list_size(list_t* list){
    return list->priv->size;
}

// list iterator
typedef struct list_iterator_priv{
    list_t* list;
    node_t* node;
    int has_iterated;
}list_iterator_priv;

list_iterator_t* list_iterator_alloc(list_t* list){
    list_iterator_t* it = (list_iterator_t*)malloc(sizeof(list_iterator_t));
    assert(it!=NULL && "OOM");
    it->priv = (list_iterator_priv*)malloc(sizeof(list_iterator_priv));
    assert(it->priv != NULL && "OOM");

    it->priv->list = list;
    it->priv->has_iterated = 0;
    it->priv->node = list->priv->head;
    return it;
}
node_t* list_iterator_next(list_iterator_t* iterator){
    if(iterator->priv->node == NULL) return NULL;
    if(iterator->priv->has_iterated){
        iterator->priv->node = iterator->priv->node->next;
        return iterator->priv->node;
    }else{
        iterator->priv->has_iterated = 1;
        return iterator->priv->node;
    }
}
void list_iterator_release(list_iterator_t* iterator){
    free(iterator->priv);
    free(iterator);
}
void list_iterator_remove_node( list_iterator_t* iterator){
    if(iterator->priv->node == NULL) return;
    node_t* l = iterator->priv->node->prev;
    node_t* m = iterator->priv->node;
    node_t* n = iterator->priv->node->next;

    if(m==iterator->priv->list->priv->head){
        iterator->priv->list->priv->head = n;
        iterator->priv->node = n;
    }else{
        l->next = n;
        if(n!=NULL)
            n->prev = l;
    }
    list_node_release( m );
    iterator->priv->list->priv->size--;
}

