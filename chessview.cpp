#include "chessview.h"
#include "chessboard.h"
#include <QPainter>
#include <QMouseEvent>

ChessView::ChessView(QWidget* parent) : QWidget{parent}
{}

void ChessView::setBoard(ChessBoard *board)
{
    if (m_board == board) return;
    if (m_board)
    {
        m_board->disconnect(this);
    }
    m_board = board;
    // connect CheckBoard signals to update view
    if (board)
    {
        connect(m_board, SIGNAL(dataChanged(int,int)),
               this, SLOT(update()));
        connect(m_board, SIGNAL(boardReset()),
               this, SLOT(update()));
    }
    updateGeometry(); // the layout needs to be recalculated
}

ChessBoard *ChessView::board() const
{
    return m_board;
}

QSize ChessView::sizeHint() const
{
    if (!m_board) return QSize(100, 100);
    QSize boardSize = QSize(
        m_fieldSize.width() * m_board->columns() + 1,
        m_fieldSize.height() * m_board->ranks() + 1);
    int rankSize = fontMetrics().horizontalAdvance('M') + 4;
    int columnSize = fontMetrics().height() + 4;
    return boardSize + QSize(rankSize, columnSize);
}

QRect ChessView::fieldRect(int c, int r) const
{
    if (!m_board) return QRect();
    const QSize fs = fieldSize();
    QRect fRect = QRect(
        QPoint((c-1)*fs.width(), (m_board->ranks()-r)*fs.height()),
        fs);
    // offsdet rect by rank symbol
    int offset = fontMetrics().horizontalAdvance('M');
    // move to the right: we have left edge for rank symbols.
    return fRect.translated(offset+4, 0);
}

void ChessView::setPiece(char type, const QIcon &icon)
{
    m_pieces.insert(type, icon);
    update();
}

QIcon ChessView::piece(char type) const
{
    return m_pieces.value(type, QIcon());
}

QPoint ChessView::fieldAt(const QPoint &pt) const
{
    if (!m_board) return QPoint();
    const QSize fs = fieldSize();
    int offset = fontMetrics().horizontalAdvance('M') + 4;
    if (pt.x() < offset) return QPoint();
    int c = (pt.x() - offset) / fs.width();
    int r = pt.y() / fs.height();
    if (c < 0 || c >= m_board->columns() ||
        r < 0 || r >= m_board->ranks())
    {
        return QPoint();
    }
    return QPoint(c+1, m_board->ranks() - r);
}

void ChessView::addHighlight(Highlight *hl)
{
    m_highlights.append(hl);
    update();
}

void ChessView::removeHighlight(Highlight *hl)
{
    m_highlights.removeOne(hl);
    update();
}

void ChessView::setFieldSize(QSize arg)
{
    if (m_fieldSize == arg)
        return;
    m_fieldSize = arg;
    emit fieldSizeChanged(arg);
    updateGeometry();
}

void ChessView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    if (!m_board) return;
    QPainter painter(this);
    int r = 0, c = 0;
    painter.save();
    for (r = m_board->ranks(); r > 0; --r)
    {
        drawRank(&painter, r);
    }
    for (c = 1; c <= m_board->columns(); ++c)
    {
        drawColumn(&painter, c);
    }
    painter.restore();

    for (r = 1; r <= m_board->ranks(); ++r)
        for (c = 1; c <= m_board->columns(); ++c)
        {
            painter.save();
            drawField(&painter, c, r);
            painter.restore();
        }
    drawHighlight(&painter);
    for (r = 1; r <= m_board->ranks(); ++r)
        for (c = 1; c <= m_board->columns(); ++c)
            drawPiece(&painter, c, r);
}

void ChessView::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pt = fieldAt(event->pos());
    if (pt.isNull()) return;
    emit clicked(pt);
}

// rank symbols on left egde.
void ChessView::drawRank(QPainter *pt, int rank)
{
    QRect r = fieldRect(1, rank);
    QRect rankRect = QRect(0, r.top(), r.left(), r.height())
            .adjusted(2, 0, -2, 0);
    QString rankTxt = QString::number(rank);
    pt->drawText(rankRect,
                 Qt::AlignVCenter | Qt::AlignRight,
                 rankTxt);
}

void ChessView::drawColumn(QPainter *pt, int column)
{
    QRect r = fieldRect(column, 1);
    QRect columnRect = QRect(r.left(), r.bottom(), r.width(), height()-r.bottom())
        .adjusted(0, 2, 0, -2);
    pt->drawText(columnRect,
                Qt::AlignHCenter | Qt::AlignTop,
                QChar('a' + column-1));
}

void ChessView::drawField(QPainter *pt, int column, int rank)
{
    QRect r = fieldRect(column, rank);
    QColor fillColor = (column+rank) % 2 ?
        palette().color(QPalette::Light) : palette().color(QPalette::Mid);
    pt->setPen(palette().color(QPalette::Dark));
    pt->setBrush(fillColor);
    pt->drawRect(r);
}

void ChessView::drawPiece(QPainter *pt, int column, int rank)
{
    QRect r = fieldRect(column, rank);
    char value = m_board->data(column, rank);
    if (value != ' ')
    {
        QIcon icon = piece(value);
        if (!icon.isNull())
        {
            icon.paint(pt, r, Qt::AlignCenter);
        }
    }
}

void ChessView::drawHighlight(QPainter *pt)
{
    for (int id = 0; id < highlightCount(); ++id)
    {
        Highlight* hl = highlight(id);
        if (hl->type() == FieldHighlight::Type)
        {
            FieldHighlight *fhl = static_cast<FieldHighlight*>(hl);
            QRect rect = fieldRect(fhl->column(), fhl->rank());
            pt->fillRect(rect, fhl->color());
        }
    }
}
