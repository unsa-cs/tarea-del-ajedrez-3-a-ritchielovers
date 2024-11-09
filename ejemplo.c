#include "chess.h"
#include "figures.h"
#include "gc.h"

void display(){
  char** Pawn = reverse(pawn);
  interpreter(Pawn);
  garbageCollector();
}
