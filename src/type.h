#pragma once

typedef struct Position {
  int row;
  int col;
} Position;

typedef struct Size {
  int rows;
  int cols;
} Size;

typedef enum Direction {
  NORTH,
  NORTHWEST,
  WEST,
  SOUTHWEST,
  SOUTH,
  SOUTHEAST,
  EAST,
  NORTHEAST
} Direction;