#ifndef CHESSVIEW_HPP
#define CHESSVIEW_HPP

#include <QWidget>
#include <QPointer>
#include <QIcon>
#include <QMap>

class ChessBoard;

class ChessView : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QSize fieldSize READ fieldSize WRITE setFieldSize NOTIFY fieldSizeChanged)
public:
  explicit ChessView(QWidget *parent = nullptr);

  void setBoard(ChessBoard* board);

  ChessBoard* board() const;
  QSize fieldSize() const;
  void setFieldSize(QSize fieldSize);
  void setPiece(char type, const QIcon& icon);
  QIcon piece(char type) const;

  // QWidget interface
public:
  QSize sizeHint() const override;

signals:

  void fieldSizeChanged(QSize fieldSize);

public slots:

protected:
  virtual void drawRank(QPainter* painter, int rank);
  virtual void drawColumn(QPainter* painter, int column);
  virtual void drawField(QPainter* painter, int column, int rank);
  virtual void drawPiece(QPainter* painter, int column, int rank);

  // QWidget interface
protected:
  void paintEvent(QPaintEvent* event) override;

private:
  QRect fieldRect(int column, int rank) const;

private:
  QPointer<ChessBoard> _board;
  QSize _fieldSize;
  QMap<char, QIcon> _pieces;
};

#endif // CHESSVIEW_HPP
