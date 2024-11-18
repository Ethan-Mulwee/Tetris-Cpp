#include <raylib.h>

struct Cell {
  bool state = false;
  Color color;
};

template<int width, int height>
class Board {
  public:
    Cell cells[width][height];
};