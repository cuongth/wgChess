#include "chessboard.h"

ChessBoard::ChessBoard(int ranks, int columns, QObject* parent)
    : QObject{parent}, m_ranks{ranks}, m_columns{columns}
{
    // setFen function will emit boardReset signal.
    m_boardData.fill(' ', m_ranks * m_columns);
}

char ChessBoard::data(int column, int rank) const
{
    return m_boardData.at((rank-1)*columns() + (column-1));
}

void ChessBoard::setData(int column, int rank, char value)
{
    if (setDataInternal(column, rank, value))
        emit dataChanged(column, rank);
}

void ChessBoard::movePiece(int fromC, int fromR, int toC, int toR)
{
    // FIXME: what happens when moving empty piece i.e.
    // data(fromC, fromR) == ' '
    setData(toC, toR, data(fromC, fromR));
    setData(fromC, fromR, ' ');
}

void ChessBoard::setFen(const QString &fen)
{
    int id = 0;
    int skip = 0;
    const int columnsCount = columns();
    QChar ch;
    for (int rank = ranks(); rank > 0; --rank)
    {
        for (int column = 1; column <= columnsCount; ++column)
        {
            if (skip > 0)
            {
                ch = ' ';
                skip--;
            }
            else
            {
                ch = fen.at(id++);
                if (ch.isDigit())
                {
                    skip = ch.toLatin1() - '0';
                    ch = ' ';
                    skip--;
                }
            }
            setDataInternal(column, rank, ch.toLatin1());
        }
        QChar next = fen.at(id++);
        if (next != '/' && next != ' ')
        {
            initBoard();
            return; // fail on error
        }
    }
    emit boardReset();
}

void ChessBoard::setRanks(int r)
{
    if (m_ranks == r) return;
    m_ranks = r;
    initBoard();
    emit ranksChanged(m_ranks);
}

void ChessBoard::setColumns(int c)
{
    if (m_columns == c) return;
    m_columns = c;
    initBoard();
    emit columnsChanged(m_columns);
}

void ChessBoard::initBoard()
{
    m_boardData.fill(' ', ranks()*columns());
    emit boardReset();
}

bool ChessBoard::setDataInternal(int column, int rank, int value)
{
    int id = (rank-1)*columns() + column - 1;
    if (m_boardData.at(id) == value) return false;
    m_boardData[id] = value;
    return true;
}
