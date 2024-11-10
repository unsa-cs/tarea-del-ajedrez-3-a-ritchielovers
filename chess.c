#include <stdio.h>
#include <stdlib.h>
#include "chess.h"
#include "gc.h"

char** allocateMemory(int rows, size_t cols){
  char** newFig;
  memoryAlloc((void**)&newFig, sizeof(char*)*(rows + 1)); 
  //&newFig = &(**newFig)
  fprintf(stderr,"[DEBUG] Memory for newFig : %p\n", &newFig);
  for(int i = 0; i < rows; i++){
    memoryAlloc((void**)&newFig[i], sizeof(char)*(cols + 1));
  //&newFig[i] == &(*(*(newFig[i])))
    fprintf(stderr, "[DEBUG] Memory for string : %p\n", &newFig[i]);
  }
  return newFig;
}

void unlinkMemory(char** fig){ //fig = newFig (variables distintas)
  countMemoryEntries();
  for(int i = 0; fig[i]; i++)
    unregisterPointer((void**)&fig[i]); //fig[i] == newFig[i] (mismo contenido)
  countMemoryEntries();
  unregisterPointer((void**)&fig); //  &fig != &newFig (memorias distintas)
  countMemoryEntries();
}

char** reverse(char** fig){
  int rows = 0;
  while(fig[++rows]);
  
  int cols = 0;
  while(fig[0][++cols]);

  char** newFig = allocateMemory(rows, cols);
  fprintf(stderr, "Memory of newFig in reverse function: %p\n", &newFig);
  for(int i = 0; fig[i]; i++){
    for(int j = 0; fig[0][j]; j++)
      newFig[i][j] = fig[i][j];
    newFig[i][cols] = 0;
  }
  newFig[rows] = 0;
  unlinkMemory(newFig);
  return newFig;
}
