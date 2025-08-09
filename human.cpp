#include "human.h"
#include "chessboard.h"

Human::Human(QObject* parent) : ChessAlgorithm{parent}
{}

Human::~Human()
{}

bool Human::move(int colFrom, int rankFrom, int colTo, int rankTo)
{
    if (currentPlayer() == NoPlayer)
        return false;
    //char source = board()->data(colFrom, rankFrom);
    // TODO: validate move
    board()->movePiece(colFrom, rankFrom, colTo, rankTo);
    setCurrentPlayer(currentPlayer() == Player1
                    ? Player2 : Player1);
    return true;
}


