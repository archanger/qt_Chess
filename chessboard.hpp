#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <QObject>
#include <QVector>

class ChessBoard : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int ranks READ ranks NOTIFY ranksChanged)
  Q_PROPERTY(int columns READ columns NOTIFY columnsChanged)
public:
  explicit ChessBoard(int ranks, int columns, QObject *parent = nullptr);

  int ranks() const;
  int columns() const;

  char data(int column, int rank) const;
  void setData(int column, int rank, char value);
  void movePiece(int fromColumn, int fromRank, int toColumn, int toToRank);
  void setFen(const QString& fen);

signals:
  void ranksChanged();
  void columnsChanged();
  void boardReset();
  void dataChanged(int c, int r);

public slots:


protected:
  bool setDataInternal(int column, int rank, char value);
  void setRanks(int ranks);
  void setColumns(int columns);
  void initBoard();

private:
  int _ranks;
  int _columns;
  QVector<char> _boardData;
};

#endif // CHESSBOARD_HPP
