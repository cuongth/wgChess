#include "foxandhounds.h"
#include "chessboard.h"

FoxAndHounds::FoxAndHounds(QObject* parent) : ChessAlgorithm{parent}
{}

FoxAndHounds::~FoxAndHounds()
{}

void FoxAndHounds::newGame()
{
    setupBoard();
    board()->setFen("3p4/8/8/8/8/8/8/P1P1P1P1 w");
    m_fox = QPoint(5, 8);
    setCurrentPlayer(Player1);
}

bool FoxAndHounds::move(int colFrom, int rankFrom, int colTo, int rankTo)
{
    if (currentPlayer() == NoPlayer)
        return false;
    char source = board()->data(colFrom, rankFrom);
    if (currentPlayer() == Player1 &&
        (source != 'P' || rankTo <= rankFrom))
        return false;
    if (currentPlayer() == Player2 && source != 'p')
        return false;
    // only move to 1 left/right column
    if (colTo != colFrom+1 && colTo != colFrom-1)
        return false;
    // move within the board
    if (colTo < 1 || colTo > board()->columns())
        return false;
    if (rankTo < 1 || rankTo > board()->ranks())
        return false;
    // to black field
    if ((colTo+rankTo) % 2)
        return false;
    // destination should be empty
    char destination = board()->data(colTo, rankTo);
    if (destination != ' ')
        return false;

    board()->movePiece(colFrom, rankFrom, colTo, rankTo);
    // make the move
    if (currentPlayer() == Player2)
        m_fox = QPoint(colTo, rankTo);
    // win condition
    if (currentPlayer() == Player2 && rankTo == 1)
        setResult(Player2Win);
    else if (currentPlayer() == Player1 && !foxCanMove())
        setResult(Player1Win);
    else
        setCurrentPlayer(currentPlayer() == Player1
                         ? Player2 : Player1);

    return true;
}

bool FoxAndHounds::foxCanMove() const
{
    if (emptyByOffset(-1, -1) || emptyByOffset(-1, 1)
        || emptyByOffset(1, -1) || emptyByOffset(1, 1))
        return true;
    return false;
}

bool FoxAndHounds::emptyByOffset(int x, int y) const
{
    const int colDest = m_fox.x() + x;
    const int rankDest = m_fox.y() + y;
    if (colDest < 1 || colDest > board()->columns()
        || rankDest < 1 || rankDest > board()->ranks())
        return false;
    return (board()->data(colDest, rankDest) == ' ');
}


