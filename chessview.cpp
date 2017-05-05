#include "chessview.hpp"
#include "chessboard.hpp"

#include <QPainter>
#include <QMouseEvent>

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
  if (board) {
    connect(board, &ChessBoard::dataChanged, this, static_cast<void(ChessView::*)()>(&ChessView::update));
    connect(board, &ChessBoard::boardReset, this, static_cast<void(ChessView::*)()>(&ChessView::update));
  }
  updateGeometry();
}

ChessBoard* ChessView::board() const
{
  return _board;
}

QSize ChessView::fieldSize() const
{
  return _fieldSize;
}

void ChessView::setFieldSize(QSize fieldSize)
{
  if (_fieldSize == fieldSize)
    return;

  _fieldSize = fieldSize;
  emit fieldSizeChanged(fieldSize);
  updateGeometry();
}

void ChessView::setPiece(char type, const QIcon& icon)
{
  _pieces.insert(type, icon);
  update();
}

QIcon ChessView::piece(char type) const
{
  return _pieces.value(type, QIcon{});
}

QPoint ChessView::fieldAt(const QPoint& pt) const
{
  if (!_board)
    return QPoint{};

  const QSize fs = fieldSize();
  int offset = fontMetrics().width('M') + 4;
  if (pt.x() < offset)
    return QPoint{};
  int c = (pt.x()-offset) / fs.width();
  int r = pt.y() / fs.height();
  if (c < 0 || c >= _board->columns() || r < 0 || r >= _board->ranks())
    return QPoint{};

  return QPoint{c+1, _board->ranks() - r};
}

void ChessView::addHighlight(ChessView::Highlight* hi)
{
  _highlights.append(hi);
  update();
}

void ChessView::removeHighlight(ChessView::Highlight* hi)
{
  _highlights.removeOne(hi);
  update();
}


QSize ChessView::sizeHint() const
{
  if (!_board) {
    return QSize{100, 100};
  }

  QSize boardSize = QSize{
      _fieldSize.width() * _board->columns() + 1,
      _fieldSize.height() * _board->ranks() + 1
  };

  int rankSize = fontMetrics().width('M') + 4;
  int columnSize = fontMetrics().height() + 4;
  return boardSize + QSize{rankSize, columnSize};
}

void ChessView::drawRank(QPainter* painter, int rank)
{
  QRect r = fieldRect(1, rank);
  QRect rankRect = QRect(0, r.top(), r.left(), r.height()).adjusted(2, 0, -2, 0);
  QString rankText = QString::number(rank);
  painter->drawText(rankRect, Qt::AlignVCenter | Qt::AlignRight, rankText);
}

void ChessView::drawColumn(QPainter* painter, int column)
{
  QRect r = fieldRect(column, 1);
  QRect columnRect = QRect(r.left(), r.bottom(), r.width(), height() - r.bottom()).adjusted(0, 2, 0, -2);
  painter->drawText(columnRect, Qt::AlignHCenter | Qt::AlignTop, QChar('a' + column - 1));
}

void ChessView::drawField(QPainter* painter, int column, int rank)
{
  QRect rect = fieldRect(column, rank);
  QColor fillColor = (column + rank) % 2 ? palette().color(QPalette::Light) : palette().color(QPalette::Mid);
  painter->setPen(palette().color(QPalette::Dark));
  painter->setBrush(fillColor);
  painter->drawRect(rect);
}

void ChessView::drawPiece(QPainter* painter, int column, int rank)
{
  QRect rect = fieldRect(column, rank);
  char value = _board->data(column, rank);
  if (value != ' ') {
    QIcon icon = piece(value);
    if (!icon.isNull()) {
      icon.paint(painter, rect,Qt::AlignCenter);
    }
  }
}

void ChessView::drawHighlights(QPainter* painter)
{
  for (int idx = 0; idx < highlightCount(); ++idx) {
    Highlight* hi = highlight(idx);
    if (hi->type() == FieldHighlight::Type) {
      FieldHighlight* fhi = static_cast<FieldHighlight*>(hi);
      QRect rect = fieldRect(fhi->column(), fhi->rank());
      painter->fillRect(rect, fhi->color());
    }
  }
}

QRect ChessView::fieldRect(int column, int rank) const
{
  if (!_board)
    return QRect{};

  const QSize fs = fieldSize();
  QRect fRect{
      QPoint{(column - 1) * fs.width(), (_board->ranks() - rank)*fs.height()},
      fs
  };

  int offset = fontMetrics().width('M');
  return fRect.translated(offset + 4, 0);
}


void ChessView::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event);
  if (!_board) {
    return;
  }

  QPainter painter{this};
  for (int r = _board->ranks(); r > 0; --r) {
    painter.save();
    drawRank(&painter, r);
    painter.restore();
  }
  for (int c = 1; c <= _board->columns(); ++c) {
    painter.save();
    drawColumn(&painter, c);
    painter.restore();
  }

  for (int r = 1; r <= _board->ranks(); ++r) {
    for (int c = 1; c <= _board->columns(); ++c) {
      painter.save();
      drawField(&painter, c, r);
      painter.restore();
    }
  }

  drawHighlights(&painter);

  for (int r = _board->ranks(); r > 0; --r) {
    for (int c = 1; c <= _board->columns(); ++c) {
      drawPiece(&painter, c, r);
    }
  }
}



void ChessView::mouseReleaseEvent(QMouseEvent* event)
{
  QPoint pt = fieldAt(event->pos());
  if(pt.isNull())
    return;
  emit clicked(pt);
}
