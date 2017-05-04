#ifndef CHESSALGORITHM_HPP
#define CHESSALGORITHM_HPP

#include <QObject>

class ChessBoard;

class ChessAlgorithm : public QObject
{
  Q_OBJECT
public:
  explicit ChessAlgorithm(QObject *parent = 0);

  ChessBoard* board() const { return _board; }

signals:
  void boardChanged();

public slots:
  virtual void newGame();

protected:
  virtual void setupBoard();
  void setBoard(ChessBoard* board);

private:
  ChessBoard* _board;
};

#endif // CHESSALGORITHM_HPP
