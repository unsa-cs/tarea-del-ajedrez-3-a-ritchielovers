#include "chess.h"
#include "figures.h"
#include "gc.h"
void display() {
  char** Knight = reverse(knight);
  char** super = superImpose(Knight,whiteSquare);
  char** fila1 = repeatH(super,2);
  char** fila2 = flipV(repeatH(super,2));
  char** ejemplo = up(fila1, fila2);
  interpreter(ejemplo);
  garbageCollector();
}
