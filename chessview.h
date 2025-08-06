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
    class Highlight
    {
    public:
        Highlight() {}
        virtual ~Highlight() {}
        virtual int type() const { return 0; }
    };
    class FieldHighlight: public Highlight
    {
    public:
        enum {Type = 1};
        FieldHighlight(int column, int rank, QColor color)
            : m_field(column, rank), m_color(color)
        {}
        inline int column() const { return m_field.x(); }
        inline int rank() const { return m_field.y(); }
        inline QColor color() const { return m_color; }
        int type() const { return Type; }
    private:
        QPoint m_field;
        QColor m_color;
    };

    explicit ChessView(QWidget* parent = nullptr);
    void setBoard(ChessBoard *);
    ChessBoard* board() const;
    QSize fieldSize() const {return m_fieldSize;}
    QSize sizeHint() const override;
    QRect fieldRect(int c, int r) const;
    void setPiece(char type, const QIcon& icon);
    QIcon piece(char type) const;
    QPoint fieldAt(const QPoint& pt) const;
    void addHighlight(Highlight *hl);
    void removeHighlight(Highlight *hl);
    inline Highlight* highlight(int id)
    {
        return m_highlights.at(id);
    }
    inline int highlightCount()
    {
        return m_highlights.size();
    }
public slots:
    void setFieldSize(QSize fieldSize);
signals:
    void fieldSizeChanged(QSize arg);
    void clicked(const QPoint& pt);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void drawRank(QPainter *pt, int rank);
    virtual void drawColumn(QPainter *pt, int column);
    virtual void drawField(QPainter *pt, int column, int rank);
    virtual void drawPiece(QPainter *pt, int column, int rank);
    virtual void drawHighlight(QPainter *pt);
private:
    QPointer<ChessBoard> m_board;
    QSize m_fieldSize;
    QMap<char, QIcon> m_pieces;
    QList<Highlight*> m_highlights;
};

#endif // CHESSVIEW_H
