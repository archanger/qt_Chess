#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "chessalgorithm.hpp"
#include "chessview.hpp"

#include <QLayout>

void _fillView(ChessView& view);

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui{new Ui::MainWindow},
  _view{new ChessView}
{
  ui->setupUi(this);

  _fillView(*_view);

  _algorithm = new ChessAlgorithm{this};
  _algorithm->newGame();
  _view->setBoard(_algorithm->board());
  setCentralWidget(_view);
  _view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  _view->setFieldSize(QSize{50,50});
  layout()->setSizeConstraint(QLayout::SetFixedSize);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void _fillView(ChessView& view) {
  view.setPiece('P', QIcon{":/pieces/Chess_plt45.svg"});
  view.setPiece('K', QIcon{":/pieces/Chess_klt45.svg"});
  view.setPiece('Q', QIcon{":/pieces/Chess_qlt45.svg"});
  view.setPiece('R', QIcon{":/pieces/Chess_rlt45.svg"});
  view.setPiece('N', QIcon{":/pieces/Chess_nlt45.svg"});
  view.setPiece('B', QIcon{":/pieces/Chess_blt45.svg"});

  view.setPiece('p', QIcon{":/pieces/Chess_pdt45.svg"});
  view.setPiece('k', QIcon{":/pieces/Chess_kdt45.svg"});
  view.setPiece('q', QIcon{":/pieces/Chess_qdt45.svg"});
  view.setPiece('r', QIcon{":/pieces/Chess_rdt45.svg"});
  view.setPiece('n', QIcon{":/pieces/Chess_ndt45.svg"});
  view.setPiece('b', QIcon{":/pieces/Chess_bdt45.svg"});
}
