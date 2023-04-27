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
  int i=hash(key, map -> capacity);

  while(map -> buckets[i] != NULL && strcmp(map->buckets[i] -> key, key) != 0){
    i = ((i+1)%map->capacity);
  }
  if(map->buckets[i]==NULL){
    Pair *valor= createPair(key,value);
    map->buckets[i]=i;
    map->size++;
  }
  else{
    map->buckets[i]->key=key;
    map->buckets[i]->value=value;
  }
  map->current=i;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap *mapa=(HashMap*)malloc(sizeof(HashMap));
    
    mapa->current=-1;
    mapa->buckets=(Pair **)malloc(sizeof(Pair *));;
    mapa->capacity=capacity;
    return NULL;
}

void eraseMap(HashMap * map,  char * key) {    
  int i=hash(key, map->capacity);
  int first=i;
  while(map->buckets[i] != NULL){
    if(is_equal(map->buckets[i]->key, key)==1){
      map->size--;
      map->buckets[i]->key=NULL;
      break;
    }
    i=((i+1)%map->capacity);
    if(first==i) break;
  }

}



Pair * searchMap(HashMap * map,  char * key) {   
  int i = hash( key, map->capacity);
  
  while(is_equal(key, map->buckets[i])!=0){
    i = ((i + 1) % map -> capacity);
    if(is_equal(key, map->buckets[i])==1) {
      map->current= i;
      return map-> buckets[i];
    }
    }
  return NULL;
}

Pair * firstMap(HashMap * map) {
  int i;
  for(i=0; i<map->capacity; i++){
    if(map -> buckets[i] != NULL){
      map -> current = i;
      return map -> buckets[i];
    }
  }
    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
