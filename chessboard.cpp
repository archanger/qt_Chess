#include "chessboard.hpp"

ChessBoard::ChessBoard(int ranks, int columns, QObject *parent) :
  QObject{parent},
  _ranks{ranks},
  _columns{columns}
{

}

int ChessBoard::ranks() const
{
  return _ranks;
}


int ChessBoard::columns() const
{
  return _columns;
}

void ChessBoard::setRanks(int r)
{
  if (ranks() == r) {
    return;
  }

  _ranks = r;
  emit ranksChanged();
}

void ChessBoard::setColumns(int c)
{
  if (columns() == c) {
    return;
  }
  _columns = c;
  emit columnsChanged();
}
