#include "chessalgorithm.h"
#include "chessboard.h"

#include <QPoint>

ChessAlgorithm::ChessAlgorithm(QObject* parent)
    : QObject{parent}, m_board{nullptr},
    m_result{NoResult}, m_currentPlayer{NoPlayer}
{}

ChessBoard *ChessAlgorithm::board() const
{
    return m_board;
}

void ChessAlgorithm::newGame()
{
    setupBoard();
    board()->setFen(
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    setCurrentPlayer(Player1);
}

// Player1 picks up white piece
// Player2 picks up black piece
bool ChessAlgorithm::isPlayerPiece(char data)
{
    QChar ch(data);
    if (ch.isLower() && (currentPlayer() == Player1))
        return false;
    if (ch.isUpper() && (currentPlayer() == Player2))
        return false;
    return true;
}

bool ChessAlgorithm::move(int colFrom, int rankFrom, int colTo, int rankTo)
{
    Q_UNUSED(colFrom);
    Q_UNUSED(rankFrom);
    Q_UNUSED(colTo);
    Q_UNUSED(rankTo);
    // TODO: validate a move
    return false;
}

bool ChessAlgorithm::move(const QPoint &from, const QPoint &to)
{
    return move(from.x(), from.y(), to.x(), to.y());
}

void ChessAlgorithm::setupBoard()
{
    setBoard(new ChessBoard(8, 8, this));
}

void ChessAlgorithm::setBoard(ChessBoard *board)
{
    if (board == m_board) return;
    if (m_board) delete m_board;
    m_board = board;
    emit boardChanged(m_board);
}

void ChessAlgorithm::setResult(Result val)
{
    if (result() == val) return;
    if (result() == NoResult)
    {
        m_result = val;
        emit gameOver(m_result);
    }
    else
    {
        m_result = val;
    }
}

void ChessAlgorithm::setCurrentPlayer(Player p)
{
    if (currentPlayer() == p) return;
    m_currentPlayer = p;
    emit currentPlayerChanged(m_currentPlayer);
}

