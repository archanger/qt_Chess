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
  class Highlight {
  public:
    Highlight() {}
    virtual ~Highlight() {}
    virtual int type() const { return 0; }
  };

  class FieldHighlight: public Highlight {
  public:
    enum { Type = 1 };
    FieldHighlight(int column, int rank, QColor color) :
      _field{column, rank},
      _color{color}
    {}

    inline int column() const { return _field.x(); }
    inline int rank() const { return _field.y(); }
    inline QColor color() const { return _color; }
    int type() const { return Type; }

  private:
    QPoint _field;
    QColor _color;
  };

public:
  explicit ChessView(QWidget *parent = nullptr);

  void setBoard(ChessBoard* board);

  ChessBoard* board() const;
  QSize fieldSize() const;
  void setFieldSize(QSize fieldSize);
  void setPiece(char type, const QIcon& icon);
  QIcon piece(char type) const;
  QPoint fieldAt(const QPoint& pt) const;

  void addHighlight(Highlight* hi);
  void removeHighlight(Highlight* hi);
  inline Highlight* highlight(int index) const { return _highlights.at(index); }
  inline int highlightCount() const { return _highlights.count(); }

  // QWidget interface
public:
  QSize sizeHint() const override;

signals:
  void clicked(const QPoint& point);
  void fieldSizeChanged(QSize fieldSize);

public slots:

protected:
  virtual void drawRank(QPainter* painter, int rank);
  virtual void drawColumn(QPainter* painter, int column);
  virtual void drawField(QPainter* painter, int column, int rank);
  virtual void drawPiece(QPainter* painter, int column, int rank);
  virtual void drawHighlights(QPainter* painter);

  // QWidget interface
protected:
  void paintEvent(QPaintEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;

private:
  QRect fieldRect(int column, int rank) const;

private:
  QPointer<ChessBoard> _board;
  QSize _fieldSize;
  QMap<char, QIcon> _pieces;
  QList<Highlight*> _highlights;
};

#endif // CHESSVIEW_HPP
