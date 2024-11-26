#ifndef TETRIS_TETROMINOS
#define TETRIS_TETROMINOS

struct Tetromino {
  char shape[4][4];

  void Draw(int x, int y, int scale, Color* colors); 

  void Rotate(int r);

  Tetromino Rotated(int r);
};

inline Tetromino tetrominos[7] = {
  // o
  Tetromino {
    0,0,0,0,
    0,2,2,0,
    0,2,2,0,
    0,0,0,0
  },
  // i
  Tetromino {
    0,0,3,0,
    0,0,3,0,
    0,0,3,0,
    0,0,3,0
  },
  // s
  Tetromino {
    0,0,0,0,
    0,0,4,4,
    0,4,4,0,
    0,0,0,0
  },
  // z
  Tetromino {
    0,0,0,0,
    5,5,0,0,
    0,5,5,0,
    0,0,0,0
  },
  // L
  Tetromino {
    0,0,0,0,
    0,6,0,0,
    0,6,0,0,
    0,6,6,0
  },
  // J
  Tetromino {
    0,0,0,0,
    0,0,7,0,
    0,0,7,0,
    0,7,7,0
  },
  // T
  Tetromino {
    0,0,0,0,
    0,8,8,8,
    0,0,8,0,
    0,0,0,0
  }
};

#endif