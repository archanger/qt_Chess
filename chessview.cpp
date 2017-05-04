#include "chessview.hpp"
#include "chessboard.hpp"

ChessView::ChessView(QWidget *parent) :
  QWidget{parent}
{

}

void ChessView::setBoard(ChessBoard* board)
{
  if (_board == board) {
    return;
  }

  if (_board) {
    _board->disconnect(this);
  }

  _board = board;
  updateGeometry();
}

ChessBoard* ChessView::board() const
{
  return _board;
}
