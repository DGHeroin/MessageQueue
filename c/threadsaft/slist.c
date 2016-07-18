#include "slist.h"
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct slist_priv{
    snode_t* head;
    snode_t* tail;
    size_t size;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
}slist_priv;

slist_t* slist_alloc(){
    slist_t* list = (slist_t*) malloc(sizeof(slist_t));
    assert(list != NULL && "OOM");
    list->priv = (slist_priv*) malloc(sizeof(slist_priv));
    assert(list->priv != NULL && "OOM");

    list->priv->head = NULL;
    list->priv->tail = NULL;
    list->priv->size = 0;

    pthread_mutex_init(&list->priv->mutex, NULL);
    pthread_cond_init(&list->priv->cond, NULL);
    return list;
}

void slist_release(slist_t* list){
    pthread_mutex_destroy(&list->priv->mutex);
    pthread_cond_destroy (&list->priv->cond);
    free(list->priv);
    free(list);
}

snode_t* slist_node_alloc(size_t payload_size){
    if(payload_size == 0) payload_size=1;
    snode_t* node = (snode_t*)malloc(sizeof(snode_t) - 1 + payload_size );
    assert(node != NULL && "OOM!");
    node->prev = NULL;
    node->next = NULL;

    return node;
}

void slist_node_release(snode_t* node){
    free(node);
}

void slist_push_back(slist_t* list, snode_t* node){
    pthread_mutex_lock(&list->priv->mutex);
    assert(list != NULL);
    assert(node != NULL);
    if(list->priv->size != 0){
        snode_t*tail = list->priv->tail;
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
    pthread_cond_signal(&list->priv->cond);
    pthread_mutex_unlock(&list->priv->mutex);
}

snode_t* slist_pop_front(slist_t* list){
    pthread_mutex_lock(&list->priv->mutex);
    assert(list != NULL);

    if(list->priv->size == 0){
        pthread_cond_wait( &list->priv->cond, &list->priv->mutex);
    }

    snode_t* node = list->priv->head;
    if(node != NULL){
        list->priv->head = node->next;
        list->priv->size--;
    }
    pthread_mutex_unlock(&list->priv->mutex);
    return node;
}

size_t slist_size(slist_t* list){
    return list->priv->size;
}

// list iterator
typedef struct slist_iterator_priv{
    slist_t* list;
    snode_t* node;
    int has_iterated;
}slist_iterator_priv;

slist_iterator_t* list_iterator_alloc(slist_t* list){
    slist_iterator_t* it = (slist_iterator_t*)malloc(sizeof(slist_iterator_t));
    assert(it!=NULL && "OOM");
    it->priv = (slist_iterator_priv*)malloc(sizeof(slist_iterator_priv));
    assert(it->priv != NULL && "OOM");

    it->priv->list = list;
    it->priv->has_iterated = 0;
    it->priv->node = list->priv->head;
    return it;
}
snode_t* list_iterator_next(slist_iterator_t* iterator){
    if(iterator->priv->node == NULL) return NULL;
    if(iterator->priv->has_iterated){
        iterator->priv->node = iterator->priv->node->next;
        return iterator->priv->node;
    }else{
        iterator->priv->has_iterated = 1;
        return iterator->priv->node;
    }
}
void list_iterator_release(slist_iterator_t* iterator){
    free(iterator->priv);
    free(iterator);
}
void list_iterator_remove_node( slist_iterator_t* iterator){
    if(iterator->priv->node == NULL) return;
    snode_t* l = iterator->priv->node->prev;
    snode_t* m = iterator->priv->node;
    snode_t* n = iterator->priv->node->next;

    if(m==iterator->priv->list->priv->head){
        iterator->priv->list->priv->head = n;
        iterator->priv->node = n;
    }else{
        l->next = n;
        if(n!=NULL)
            n->prev = l;
    }
    slist_node_release( m );
    iterator->priv->list->priv->size--;
}

