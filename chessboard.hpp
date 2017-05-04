#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <QObject>

class ChessBoard : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int ranks READ ranks NOTIFY ranksChanged)
  Q_PROPERTY(int columns READ columns NOTIFY columnsChanged)
public:
  explicit ChessBoard(int ranks, int columns, QObject *parent = nullptr);

  int ranks() const;
  int columns() const;

signals:
  void ranksChanged();
  void columnsChanged();

public slots:

protected:
  void setRanks(int ranks);
  void setColumns(int columns);

private:
  int _ranks;
  int _columns;
};

#endif // CHESSBOARD_HPP
