#ifndef CHESSALGORITHM_H
#define CHESSALGORITHM_H

#include <QObject>

class ChessBoard;
class ChessAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit ChessAlgorithm(QObject* parent = nullptr);
    ChessBoard *board() const;
signals:
    void boardChanged(ChessBoard *);
public slots:
    virtual void newGame();
protected:
    virtual void setupBoard();
    void setBoard(ChessBoard *board);
private:
    ChessBoard *m_board;
};

#endif // CHESSALGORITHM_H
