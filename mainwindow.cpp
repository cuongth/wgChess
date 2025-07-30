#include "mainwindow.h"
#include "chessview.h"
#include "chessalgorithm.h"

#include "./ui_mainwindow.h"
#include <QLayout>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_view = new ChessView;
    m_algorithm = new ChessAlgorithm(this);
    m_algorithm->newGame();
    m_view->setBoard(m_algorithm->board());
    setCentralWidget(m_view);
    m_view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_view->setFieldSize(QSize(75, 75));
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

MainWindow::~MainWindow() { delete ui; }
