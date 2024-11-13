#include "chess.h"
#include "figures.h"
#include "gc.h"
void display() {
  char** Knight = reverse(knight);
  char** super = superImpose(Knight,whiteSquare);
  char** rotateLKnight = rotateL(Knight);
  interpreter(rotateLKnight);
  garbageCollector();
}
