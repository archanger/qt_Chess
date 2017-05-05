#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "chessview.hpp"

namespace Ui {
  class MainWindow;
}

class ChessAlgorithm;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void viewClicked(const QPoint& point);

private:
  Ui::MainWindow *ui;
  ChessView* _view;
  ChessAlgorithm* _algorithm;
  QPoint _clickedPoint;
  ChessView::FieldHighlight* _selectedField;
};

#endif // MAINWINDOW_HPP
