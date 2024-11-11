#include <stdio.h>
#include <stdlib.h>
#include "chess.h"
#include "gc.h"

int sizeHeight(char **fig) {
  int height = 0, i = 0;
  while (fig[i]) {
    ++height;
    ++i;
  }
  return height;
}

int sizeWidth(char **fig) {
  int width = 0, i = 0;
  while (fig[0][i]) {
    ++width;
    ++i;
  }
  return width;
}

void allocateMemory(char ***newFig, int rows, size_t cols){
  memoryAlloc((void**)newFig, sizeof(char*)*(rows + 1)); 
  fprintf(stderr,"[DEBUG] Memory for newFig : %p\n", newFig);
  for(int i = 0; i < rows; i++){
    memoryAlloc((void**)&(*newFig)[i], sizeof(char)*(cols + 1)); 
  }
}

void unlinkMemory(char*** fig){ //fig = newFig (variables distintas)
  countMemoryEntries();
  for(int i = 0; (*fig)[i]; i++)
    unregisterPointer((void**)&(*fig)[i]); //fig[i] == newFig[i] (mismo contenido)
  countMemoryEntries();
  unregisterPointer((void**)fig); //  &fig != &newFig (memorias distintas)
  countMemoryEntries();
}

char** reverse(char** fig){
  int rows = sizeHeight(fig);
  int cols = sizeWidth(fig);

  char **newFig = NULL;
  allocateMemory(&newFig,rows, cols);
  //fprintf(stderr, "Memory of newFig in reverse function: %p\n", &newFig);
  for(int i = 0; fig[i]; i++){
    for(int j = 0; fig[0][j]; j++){
      switch (fig[i][j]) {
        case '_': newFig[i][j] = '='; break;
        case '=': newFig[i][j] = '_'; break;
        case '.': newFig[i][j] = '@'; break;
        case '@': newFig[i][j] = '.'; break;
        case '#': newFig[i][j] = '#'; break;
        default: newFig[i][j] = ' '; break;
      }
    }
    newFig[i][cols] = 0;
  }
  newFig[rows] = 0;
  unlinkMemory(&newFig);
  return newFig;
}
