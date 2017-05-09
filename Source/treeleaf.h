#ifndef TREELEAF_H
#define TREELEAF_H

#include <QColor>
#include <QGraphicsItem>
#include <QString>
#include <QPixmap>
#include <QLabel>

class TreeLeaf : public QGraphicsItem
{
public:
	 TreeLeaf(QString Name, QString photoPath, int x, int y);

	 QRectF boundingRect() const Q_DECL_OVERRIDE;
	 QPainterPath shape() const Q_DECL_OVERRIDE;
	 void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

protected:
	 void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	 void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	 void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
	 int x;
	 int y;
	 QString name;
//	 QLabel *photo;
	 QPixmap photo;
	 QVector<QPointF> stuff;
};


#endif // TREELEAF_H
