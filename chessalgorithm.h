#ifndef CHESSALGORITHM_H
#define CHESSALGORITHM_H

#include <QObject>

class ChessBoard;
class ChessAlgorithm : public QObject
{
    Q_OBJECT
public:
    enum Result {NoResult, Player1Win, Draw, Player2Win,
        WhiteWin, BlackWin};
    Q_ENUM(Result);
    enum Player {NoPlayer, Player1, Player2};
    Q_ENUM(Player);

    explicit ChessAlgorithm(QObject* parent = nullptr);
    ChessBoard *board() const;
    inline Result result() const { return m_result;}
    inline Player currentPlayer() const { return m_currentPlayer;}
signals:
    void boardChanged(ChessBoard *);
    void gameOver(Result);
    void currentPlayerChanged(Player);
public slots:
    virtual void newGame();
    virtual bool isPlayerPiece(char data);
    virtual bool move(int colFrom, int rankFrom, int colTo, int rankTo);
    bool move(const QPoint &from, const QPoint &to);
protected:
    virtual void setupBoard();
    void setBoard(ChessBoard *board);
    void setResult(Result);
    void setCurrentPlayer(Player);
private:
    ChessBoard *m_board;
    Result m_result;
    Player m_currentPlayer;
};

#endif // CHESSALGORITHM_H
