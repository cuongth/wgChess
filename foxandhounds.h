#ifndef FOXANDHOUNDS_H
#define FOXANDHOUNDS_H

#include "chessalgorithm.h"

#include <QPoint>

class FoxAndHounds : public ChessAlgorithm
{ // we don't need Q_OBJECT metadata
public:
    explicit FoxAndHounds(QObject* parent = nullptr);
    ~FoxAndHounds();
    void newGame() override;
    bool move(int colFrom, int rankFrom, int colTo, int rankTo) override;
protected:
    bool foxCanMove() const;
    bool emptyByOffset(int x, int y) const;
private:
    QPoint m_fox;
};

#endif // FOXANDHOUNDS_H
