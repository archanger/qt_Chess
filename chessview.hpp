#ifndef CHESSVIEW_HPP
#define CHESSVIEW_HPP

#include <QWidget>
#include <QPointer>

class ChessBoard;

class ChessView : public QWidget
{
  Q_OBJECT
public:
  explicit ChessView(QWidget *parent = nullptr);

  void setBoard(ChessBoard* board);

  ChessBoard* board() const;

signals:

public slots:

private:
  QPointer<ChessBoard> _board;
};

#endif // CHESSVIEW_HPP
