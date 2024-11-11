#include "chess.h"
#include "figures.h"
#include "gc.h"

void display(){
  char** Pawn = reverse(pawn);
  char** U = join(Pawn,pawn);
  interpreter(U);
  garbageCollector();
}
