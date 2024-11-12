#include "chess.h"
#include "figures.h"
#include "gc.h"
void display() {
  char **Pawn = reverse(pawn);
  //char **U = repeatH(Pawn, 4);
  //char **J = repeatV(U, 3);
  char** super = superImpose(Pawn,whiteSquare);
  char** repetidorH = repeatH(super,2);
  char** n = join(repetidorH,pawn);
  char** upper = up(n,repeatH(Pawn,3));
  char** n2 = repeatV(n,2);
  interpreter(super);
  garbageCollector();
}
