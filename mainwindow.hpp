#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class ChessView;
class ChessAlgorithm;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  ChessView* _view;
  ChessAlgorithm* _algorithm;
};

#endif // MAINWINDOW_HPP
