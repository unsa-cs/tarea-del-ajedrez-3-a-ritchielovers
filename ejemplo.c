#include "chess.h"
#include "figures.h"
#include "gc.h"

void display() {
  char **Pawn = reverse(pawn);
  char **U = repeatH(Pawn, 4);
  char **J = repeatV(U, 3);
  interpreter(J);
  garbageCollector();
}
