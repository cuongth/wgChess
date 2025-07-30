#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
protected:
    Ui::MainWindow* ui;
private:
    ChessView *m_view;
    ChessAlgorithm *m_algorithm;
};
#endif // MAINWINDOW_H
