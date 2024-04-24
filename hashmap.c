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
    while(map->buckets[pos] != NULL && map->buckets[pos]->key != NULL && !is_equal(map->buckets[pos]->key, key)) {
        pos = (pos+1) % map->capacity;
    }
    if(map->buckets[pos] == NULL || map->buckets[pos]->key == NULL) {
        map->buckets[pos] = createPair(key,value);
        map->size++;
    } else {
        map->buckets[pos]->value = value;
    }
    if(map->size >= map->capacity*0.7) enlarge(map);
}


void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    Pair ** buckets = (Pair **)malloc(sizeof(Pair*)*map->capacity*2);
    for(long i = 0; i < map->capacity*2; i++) {
        buckets[i] = NULL;
    }
    for(long i = 0; i < map->capacity; i++) {
        Pair * p = map->buckets[i];
        if(p != NULL && p->key != NULL) {
            long pos = hash(p->key,map->capacity*2);
            while(buckets[pos] != NULL) {
                pos = (pos+1) % (map->capacity*2);
            }
            buckets[pos] = p;
        }
    }
    free(map->buckets);
    map->buckets = buckets;
    map->capacity *= 2;
}

HashMap * createMap(long capacity) {
    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
    map->buckets = (Pair **)malloc(sizeof(Pair*)*capacity);
    for(long i = 0; i < capacity; i++) {
        map->buckets[i] = NULL;
    }
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;
    return map;
}

void eraseMap(HashMap * map,  char * key) {
    long pos = hash(key, map->capacity);
    while(map->buckets[pos] != NULL) {
        if(is_equal(map->buckets[pos]->key, key)) {
            map->buckets[pos]->key = NULL;
            map->size--;
            return;
        }
        pos = (pos+1) % map->capacity;
    }
}

Pair * searchMap(HashMap * map,  char * key) {
    long pos = hash(key, map->capacity);
    while(map->buckets[pos] != NULL) {
        if(is_equal(map->buckets[pos]->key, key)) {
            map->current = pos;
            return map->buckets[pos];
        }
        pos = (pos+1) % map->capacity;
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {
    for(long i = 0; i < map->capacity; i++) {
        if(map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
            map->current = i;
            return map->buckets[i];
        }
    }
    return NULL;
}


Pair * nextMap(HashMap * map) {
    for(long i = map->current+1; i < map->capacity; i++) {
        if(map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
            map->current = i;
            return map->buckets[i];
        }
    }
    return NULL;
}
