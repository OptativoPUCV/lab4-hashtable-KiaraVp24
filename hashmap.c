#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    if(map == NULL || key == NULL) return ;
    long pos = hash(key,map->capacity);
    while(map->buckets[pos] != NULL && map->buckets[pos]->key != NULL) {
        pos = (pos+1) % map->capacity;
    }
    map->buckets[pos] = createPair(key,value);
    map->size++;
    if(map->size >= map->capacity*0.7) enlarge(map);
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    Pair ** buckets = (Pair **)malloc(sizeof(Pair*)*map->capacity*2);
    for(long i = 0; i < map->capacity; i++) {
        buckets[i] = NULL;
    }
    for(long i = 0; i < map->capacity; i++) {
        Pair * p = map->buckets[i];
        if(p != NULL && p->key != NULL) {
            long pos = hash(p->key,map->capacity*2);
            while(buckets[pos] != NULL) {
              
            }
        }
    }
}


HashMap * createMap(long capacity) {

    return NULL;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
