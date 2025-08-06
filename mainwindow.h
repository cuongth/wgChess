#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chessview.h"

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
protected:
    Ui::MainWindow* ui;
private:
    ChessView *m_view;
    ChessAlgorithm *m_algorithm;
    QPoint m_clickPoint;
    ChessView::FieldHighlight *m_selectedField;
};
#endif // MAINWINDOW_H
