#include "move.h"

Position move(Position currentPos, Direction arah)
{
  Position posisiBaru;

  switch (arah)
  {
  case WEST:
    posisiBaru.row = currentPos.row;
    posisiBaru.col = currentPos.col - 1;
    break;
  case NORTHWEST:
    posisiBaru.row = currentPos.row - 1;
    posisiBaru.col = currentPos.col - 1;
    break;
  case NORTH:
    posisiBaru.row = currentPos.row - 1;
    posisiBaru.col = currentPos.col;
    break;
  case NORTHEAST:
    posisiBaru.row = currentPos.row - 1;
    posisiBaru.col = currentPos.col + 1;
    break;
  case EAST:
    posisiBaru.row = currentPos.row;
    posisiBaru.col = currentPos.col + 1;
    break;
  case SOUTHEAST:
    posisiBaru.row = currentPos.row + 1;
    posisiBaru.col = currentPos.col + 1;
    break;
  case SOUTH:
    posisiBaru.row = currentPos.row + 1;
    posisiBaru.col = currentPos.col;
    break;
  case SOUTHWEST:
    posisiBaru.row = currentPos.row + 1;
    posisiBaru.col = currentPos.col - 1;
    break;
  default:
    posisiBaru = currentPos;
    break;
  }

  return posisiBaru;
}

int isPositionValid(Position pos, Size matrixSize)
{
  return pos.row >= 0 && pos.col >= 0 
    && matrixSize.rows > pos.row && matrixSize.cols > pos.col;
}