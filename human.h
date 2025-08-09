#ifndef HUMAN_H
#define HUMAN_H

#include "chessalgorithm.h"

class Human : public ChessAlgorithm
{ // we don't need Q_OBJECT metadata
public:
    explicit Human(QObject* parent = nullptr);
    ~Human();
    bool move(int colFrom, int rankFrom, int colTo, int rankTo) override;
};

#endif // HUMAN_H
