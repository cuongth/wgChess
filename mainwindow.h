#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chessview.h"
#include "chessalgorithm.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class ChessView;
class ChessAlgorithm;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
public slots:
    void viewClicked(const QPoint& field);
private slots:
    void gameOver(ChessAlgorithm::Result);
    void startFoxHounds();
    void startHuman();
    void largerBoard();
    void smallerBoard();
protected:
    Ui::MainWindow* ui;
private:
    ChessView *m_view;
    ChessAlgorithm *m_algorithm;
    QPoint m_clickPoint;
    ChessView::FieldHighlight *m_selectedField;

    template<typename T>
    void actionGame();
};

template<typename T>
void MainWindow::actionGame()
{
    static_assert(std::is_base_of_v<ChessAlgorithm, T>,
            "T must be derived from ChessAlgorithm");
    bool repaintBoard = false;
    if (m_algorithm) {
        m_algorithm->disconnect(this);
        delete m_algorithm;
        repaintBoard = true;
    }
    m_algorithm = new T(this);
    m_algorithm->newGame();
    m_view->removeAllHighlights();
    if (m_selectedField)
        m_selectedField = nullptr;
    m_view->setBoard(m_algorithm->board());

    connect(m_algorithm, &ChessAlgorithm::gameOver,
            this, &MainWindow::gameOver);

    if (repaintBoard)
        m_view->update();

}
#endif // MAINWINDOW_H
