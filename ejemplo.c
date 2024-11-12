#include "chess.h"
#include "figures.h"
#include "gc.h"

void display(){
  char** Pawn = reverse(pawn);
  char** U = repeatH(up(Pawn,pawn),4);
  interpreter(U);
  garbageCollector();
}
