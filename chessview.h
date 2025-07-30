#ifndef CHESSVIEW_H
#define CHESSVIEW_H

#include <QWidget>
#include <QPointer>
#include <QIcon>
#include <QMap>

class ChessBoard;
class ChessView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSize fieldSize
                READ fieldSize WRITE setFieldSize
                NOTIFY fieldSizeChanged)
public:
    explicit ChessView(QWidget* parent = nullptr);
    void setBoard(ChessBoard *);
    ChessBoard* board() const;
    QSize fieldSize() const {return m_fieldSize;}
    QSize sizeHint() const override;
    QRect fieldRect(int c, int r) const;
    void setPiece(char type, const QIcon& icon);
    QIcon piece(char type) const;
public slots:
    void setFieldSize(QSize fieldSize);
signals:
    void fieldSizeChanged(QSize arg);
protected:
    void paintEvent(QPaintEvent *event) override;
    virtual void drawRank(QPainter *pt, int rank);
    virtual void drawColumn(QPainter *pt, int column);
    virtual void drawField(QPainter *pt, int column, int rank);
    virtual void drawPiece(QPainter *pt, int column, int rank);
private:
    QPointer<ChessBoard> m_board;
    QSize m_fieldSize;
    QMap<char, QIcon> m_pieces;
};

#endif // CHESSVIEW_H
