#ifndef PANEL_H
#define PANEL_H

#include <QGraphicsWidget>
#include <QGraphicsLayoutItem>
#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>
#include <QList>

class QTimeLine;
class QLineEdit;

namespace Lines
{

class Panel : public QGraphicsWidget
{
    Q_OBJECT
public:
    Panel(QGraphicsItem *parent = 0);
    virtual ~Panel();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    static QList<Panel *> visiblePanels();

signals:
    void closed();

protected:
    void startHide();

private slots:
    void onVisibleChanged();
    void onHideFrameChanged(int f);
    void onHideFinished();

private:
    QTimeLine *m_hideTimeLine;
    static QList<Panel *> m_panels;
};

class LineEdit : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    LineEdit(QGraphicsItem *parent = 0);

    QString	text() const;
    void setText(const QString &text);

private:
    QLineEdit *m_lineEdit;
};

class PanelText : public QGraphicsTextItem, public QGraphicsLayoutItem
{
public:
    PanelText(QGraphicsItem *parent = 0);

protected:
    virtual QSizeF	sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
};

};

#endif // PANEL_H
