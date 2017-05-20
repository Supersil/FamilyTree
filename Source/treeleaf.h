#ifndef TREELEAF_H
#define TREELEAF_H

#include <QGraphicsItem>
#include <QString>
#include <QImage>
#include "person.h"
#include "info.h"
class TreeLeaf: public QGraphicsItem
{
public:
	TreeLeaf(QString fio, QString path, int xx,int yy);

	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

protected:
//	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
//	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
private:
	QString name;
	QImage photo;
	int x;
	int y;

};

#endif // TREELEAF_H
