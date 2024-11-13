#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

char **join(char **figure1, char **figure2) {
  int height1 = sizeHeight(figure1), height2 = sizeHeight(figure2);
  assert(height1 == height2);
  int figureWidth = sizeWidth(figure1) + sizeWidth(figure2);
  char **newFigure = NULL;
  allocateMemory(&newFigure,height1,figureWidth);

  int i = 0;
  while (figure1[i]) {
    int k = 0, j = 0;
    while (figure1[i][j]) {
      newFigure[i][j] = figure1[i][j];
      j++;
    }
    while (figure2[i][k]) {
      newFigure[i][j++] = figure2[i][k++];
    }
    newFigure[i][j]=0;
    i++;
  }
  newFigure[i]=0;
  unlinkMemory(&newFigure);
  return newFigure;
}

char **up(char **figure1, char **figure2) {
  int width1 = sizeWidth(figure1), width2 = sizeWidth(figure2);
  assert(width1 == width2);
  int height1 = sizeHeight(figure1);
  int figureHeight = sizeHeight(figure2)+ sizeHeight(figure1);
  char **newFigure = NULL;
  allocateMemory(&newFigure,figureHeight,width1);
  for (int i = 0; i < figureHeight-1; ++i) {
    if (i < height1-1) {
      newFigure[i] = figure1[i];
    } else {
      newFigure[i] = figure2[i - (height1-1)];
    }
    newFigure[i][width1]=0;
  }
  newFigure[figureHeight]=0;
  unlinkMemory(&newFigure);
  return newFigure;
}

char **repeatH(char **figure, int repeater) {
  int figureWidth = sizeWidth(figure) * repeater;
  int figureHeight = sizeHeight(figure);

  char** new_Figure = NULL;
  allocateMemory(&new_Figure, figureHeight,figureWidth);
  int i = 0;
  while (figure[i]) {
    int iterator = 0;
    for (int j = 0; j < repeater; j++) {
      int k = 0;
      while (figure[i][k]) {
        new_Figure[i][iterator++] = figure[i][k++];
      }
    }
    new_Figure[i++][iterator] = 0;
  }
  new_Figure[i]=0;
  unlinkMemory(&new_Figure);
  return new_Figure;
}

char **repeatV(char **figure, int repeater) {
  int height = sizeHeight(figure);
  int figureHeight = height * repeater;
  int figureWidth = sizeWidth(figure);

  char **new_figure = NULL;
  allocateMemory(&new_figure, figureHeight, figureWidth);

  for (int i = 0; i < figureHeight; i++) {
    for (int j = 0; j < figureWidth; j++) {
      new_figure[i][j] = figure[i % height][j];
    }
    new_figure[i][figureWidth]=0; 
  }
    
  new_figure[figureHeight]=0;
  unlinkMemory(&new_figure);
  return new_figure;
}

char** superImpose(char** figure1, char** figure2) {
  int width1 = sizeWidth(figure1), width2 = sizeWidth(figure2);
  int height1 = sizeHeight(figure1), height2 = sizeHeight(figure2);
  int figurewidth = width1 < width2 ? width1 : width2;
  int figureheight = height1 < height2 ? height1 : height2;
  char** new_figure = NULL;
  allocateMemory(&new_figure, figureheight, figurewidth);

  for (int i = 0; i < figureheight; i++) {
    for (int j = 0; j < figurewidth; j++) {
      if (figure1[i][j] == ' '){
        new_figure[i][j] = figure2[i][j];
      }else{
        new_figure[i][j] = figure1[i][j];
      }
    }
    new_figure[figurewidth]=0;
  }
  new_figure[figureheight]=0;
  unlinkMemory(&new_figure);
  return new_figure;
}

char **flipV(char **figure) {
  int figureWidth = sizeWidth(figure);
  int figureHeight = sizeHeight(figure);
  char **newFigure;
  allocateMemory(&newFigure, figureHeight, figureWidth);
  for (int i = 0; i < figureHeight; ++i) {
    for (int j = 0; j < figureWidth; ++j) {
      newFigure[i][j] = figure[i][figureWidth - 1 - j];
    }
    newFigure[i][figureWidth] = 0;
  }
  newFigure[figureHeight] = 0;
  unlinkMemory(&newFigure);
  return newFigure;
}

char **flipH(char **figure) {
  int figureWidth = sizeWidth(figure);
  int figureHeight = sizeHeight(figure);
  char **newFigure;
  allocateMemory(&newFigure, figureHeight, figureWidth);
  for (int i = 0; i < figureHeight; ++i) {
    for (int j = 0; j < figureWidth; ++j) {
      newFigure[i][j] = figure[figureHeight - 1 - i][j];
    }
    newFigure[i][figureWidth] = 0;
  }
  newFigure[figureHeight] = 0;
  unlinkMemory(&newFigure);
  return newFigure;
}

char **rotateL(char **figure) {
  int figureWidth = sizeWidth(figure);
  int figureHeight = sizeHeight(figure);
  char **newFigure;
  allocateMemory(&newFigure, figureWidth, figureHeight);
  for (int i = 0; i < figureWidth; i++) {
    for (int j = 0; j < figureHeight; j++) {
      newFigure[i][j] = figure[j][figureWidth - 1 - i];
    }
    newFigure[i][figureHeight] = 0;
  }
  newFigure[figureWidth] = 0;
  unlinkMemory(&newFigure);
  return newFigure;
}

char **rotateR(char **figure) {
  int figureWidth = sizeWidth(figure);
  int figureHeight = sizeHeight(figure);
  char **newFigure;
  allocateMemory(&newFigure, figureWidth, figureHeight);
  for (int i = 0; i < figureWidth; i++) {
    for (int j = 0; j < figureHeight; j++) {
      newFigure[i][j] = figure[figureHeight - 1 - j][i];
    }
    newFigure[i][figureHeight] = 0;
  }
  newFigure[figureWidth] = 0;
  unlinkMemory(&newFigure);
  return newFigure;
}

