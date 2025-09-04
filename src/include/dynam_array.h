#pragma once 

//DYNAMIC STRING ARRAYS
typedef struct {
  int length;
  void **items;
} dynamicArray;

void sa_push_back(dynamicArray *arr, void *el) {
  arr->items = realloc(arr->items, (arr->length + 1) * sizeof(void *));
  void* newElem=malloc(sizeof(void*));
  memcpy(newElem, el,  sizeof(void*));
  arr->items[arr->length++] = newElem;
}

void sa_free(dynamicArray *arr) {
  for (int i = 0; i < arr->length; i++) {
    free(arr->items[i]);
  }
  free(arr->items);
}


