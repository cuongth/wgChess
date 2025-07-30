#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>

class ChessBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ranks READ ranks NOTIFY ranksChanged)
    Q_PROPERTY(int columns READ columns NOTIFY columnsChanged)
public:
    explicit ChessBoard(int ranks = 8, int columns = 8, QObject* parent = nullptr);
    int ranks() const {return m_ranks;}
    int columns() const {return m_columns;}
    char data(int column, int rank) const;
    void setData(int columm, int rank, char value);
    void movePiece(int fromC, int fromR, int toC, int toR);
    void setFen(const QString &fen);
signals:
    void ranksChanged(int);
    void columnsChanged(int);
    void boardReset();
    void dataChanged(int c, int r);
protected:
    void setRanks(int r);
    void setColumns(int c);
    void initBoard();
    bool setDataInternal(int column, int rank, int value);
private:
    int m_ranks, m_columns;
    QVector<char> m_boardData;
};

#endif // CHESSBOARD_H
