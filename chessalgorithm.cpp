#include "chessalgorithm.hpp"
#include "chessboard.hpp"

ChessAlgorithm::ChessAlgorithm(QObject *parent) :
  QObject{parent},
  _board{nullptr}
{

}

void ChessAlgorithm::newGame()
{
  setupBoard();
}

void ChessAlgorithm::setupBoard()
{
  setBoard(new ChessBoard{8, 8, this});
}

void ChessAlgorithm::setBoard(ChessBoard* board)
{
  if (board == _board) {
    return;
  }

  if (_board) {
    delete _board;
  }

  _board = board;
  emit boardChanged();
}
