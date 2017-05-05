#include "chessboard.hpp"
#include <QVector>

ChessBoard::ChessBoard(int ranks, int columns, QObject *parent) :
  QObject{parent},
  _ranks{ranks},
  _columns{columns}
{
  initBoard();
}

int ChessBoard::ranks() const
{
  return _ranks;
}


int ChessBoard::columns() const
{
  return _columns;
}

char ChessBoard::data(int column, int rank) const
{
  return _boardData.at((rank - 1)*columns() + (column - 1));
}

void ChessBoard::setData(int column, int rank, char value)
{
  if (setDataInternal(column, rank, value))
    emit dataChanged(column, rank);
}

void ChessBoard::movePiece(int fromColumn, int fromRank, int toColumn, int toToRank)
{
  setData(toColumn, toToRank, data(fromColumn, fromRank));
  setData(fromColumn, fromRank, ' ');
}

bool ChessBoard::setDataInternal(int column, int rank, char value)
{
  int index = (rank - 1) * columns() + (column - 1);
  if (_boardData.at(index) == value)
    return false;
  _boardData[index] = value;
  return true;
}

void ChessBoard::setRanks(int r)
{
  if (ranks() == r) {
    return;
  }

  _ranks = r;
  initBoard();
  emit ranksChanged();
}

void ChessBoard::setColumns(int c)
{
  if (columns() == c) {
    return;
  }
  _columns = c;
  initBoard();
  emit columnsChanged();
}

void ChessBoard::initBoard()
{
  _boardData.fill(' ', ranks()*columns());
  emit boardReset();
}

void ChessBoard::setFen(const QString& fen)
{
  int index{0};
  int skip{0};

  const int columnCount{columns()};
  QChar ch;

  for (int rank = ranks(); rank > 0; --rank) {
    for (int column = 1; column <= columnCount; ++column) {
      if (skip > 0) {
        ch = ' ';
        skip--;
      } else {
        ch = fen.at(index);
        index++;
        if (ch.isDigit()) {
          skip = ch.toLatin1() - '0';
          ch = ' ';
          skip--;
        }
      }
      setDataInternal(column, rank, ch.toLatin1());
    }
    QChar next = fen.at(index);
    index++;
    if (next != '/' && next != ' ') {
      initBoard();
      return;
    }

  }
  emit boardReset();
}
