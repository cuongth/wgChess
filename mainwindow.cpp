#include "mainwindow.h"
#include "chessboard.h"
#include "foxandhounds.h"
#include "human.h"

#include "./ui_mainwindow.h"
#include <QLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
    m_clickPoint{QPoint()}, m_selectedField(nullptr),
    m_algorithm(nullptr)
{
    ui->setupUi(this);

    m_view = new ChessView;
    connect(m_view, &ChessView::clicked,
            this, &MainWindow::viewClicked);

    m_view->setPiece('P', QIcon(":/pieces/Chess_plt45.svg")); // pawn
    m_view->setPiece('K', QIcon(":/pieces/Chess_klt45.svg")); // king
    m_view->setPiece('Q', QIcon(":/pieces/Chess_qlt45.svg")); // queen
    m_view->setPiece('R', QIcon(":/pieces/Chess_rlt45.svg")); // rook
    m_view->setPiece('N', QIcon(":/pieces/Chess_nlt45.svg")); // knight
    m_view->setPiece('B', QIcon(":/pieces/Chess_blt45.svg")); // bishop

    m_view->setPiece('p', QIcon(":/pieces/Chess_pdt45.svg")); // pawn
    m_view->setPiece('k', QIcon(":/pieces/Chess_kdt45.svg")); // king
    m_view->setPiece('q', QIcon(":/pieces/Chess_qdt45.svg")); // queen
    m_view->setPiece('r', QIcon(":/pieces/Chess_rdt45.svg")); // rook
    m_view->setPiece('n', QIcon(":/pieces/Chess_ndt45.svg")); // knight
    m_view->setPiece('b', QIcon(":/pieces/Chess_bdt45.svg")); // bishop

    connect(ui->actionFoxHounds, &QAction::triggered,
            this, &MainWindow::startFoxHounds);
    connect(ui->actionHuman, &QAction::triggered,
            this, &MainWindow::startHuman);

    startHuman(); // by default, White vs Black game.

    setCentralWidget(m_view);
    m_view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_view->setFieldSize(QSize(75, 75));
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(ui->actionLarge, &QAction::triggered,
            this, &MainWindow::largerBoard);
    connect(ui->actionSmall, &QAction::triggered,
            this, &MainWindow::smallerBoard);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::viewClicked(const QPoint &field)
{
    if (m_clickPoint.isNull())
    {
        const char pieceVal = m_view->board()->data(field.x(), field.y());
        if (pieceVal != ' ' && m_algorithm->isPlayerPiece(pieceVal))
        {
            m_view->removeAllHighlights();
            m_selectedField = nullptr;

            m_clickPoint = field;
            m_selectedField = new ChessView::FieldHighlight(
                field.x(), field.y(), QColor(255, 0, 0, 50));
            m_view->addHighlight(m_selectedField);
        } // nothing happens if you click on empty field or piece of other player.
    }
    else
    {
        if (m_clickPoint != field)
        {
            if (m_algorithm->move(m_clickPoint, field))
            {
                m_selectedField = new ChessView::FieldHighlight(
                    field.x(), field.y(), QColor(255, 0, 0, 50));
                m_view->addHighlight(m_selectedField);
            }
        }
        else
        {
        // if you clicked again at clicked field, highlight is removed.
        // now you can pick up another piece. We haven't counted your move.
            m_view->removeHighlight(m_selectedField);
            delete m_selectedField;
            m_selectedField = nullptr;
        }
        m_clickPoint = QPoint();
    }
}

void MainWindow::gameOver(ChessAlgorithm::Result result)
{
    QString text;
    switch(result) {
        case ChessAlgorithm::Player1Win:
            text = "Hounds wins!";
            break;
        case ChessAlgorithm::Player2Win:
            text = "Fox wins!";
            break;
        case ChessAlgorithm::WhiteWin:
            text = "White wins";
            break;
        case ChessAlgorithm::BlackWin:
            text = "Black wins";
            break;
        default:
            text = "It's a draw";
    }

    QMessageBox::information(this, "Game over",
            QStringLiteral("The game has ended. %1").arg(text));
}

void MainWindow::startFoxHounds()
{
    actionGame<FoxAndHounds>();
}

void MainWindow::startHuman()
{
    actionGame<Human>();
}

void MainWindow::largerBoard()
{
    QSize fieldSize = m_view->fieldSize();
    m_view->setFieldSize(fieldSize+QSize(10, 10));
}

void MainWindow::smallerBoard()
{
    QSize fieldSize = m_view->fieldSize();
    m_view->setFieldSize(fieldSize-QSize(10, 10));
}
