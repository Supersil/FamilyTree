#include "treeleaf.h"


#include <QtWidgets>

TreeLeaf::TreeLeaf(QString Name, QString photoPath, int x, int y)
{
	this->x = x;
	this->y = y;
	this->name = Name;
	this->photo.load(photoPath);
	photo.scaledToWidth(50);
//	photo = new QLabel;
//	photo->setBackgroundRole(QPalette::Base);
//	photo->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//	photo->setScaledContents(true);

//	QImage img(photoPath);
//	photo->setPixmap(QPixmap::fromImage(img));

//	setFlags(ItemIsSelectable | ItemIsMovable);
//	setAcceptHoverEvents(true);
}

QRectF TreeLeaf::boundingRect() const
{
	return QRectF(-photo.width()/2, -photo.height()/2, photo.width(), photo.height());
}

QPainterPath TreeLeaf::shape() const
{
	 QPainterPath path;
	 return path;
}

void TreeLeaf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(widget);
	painter->drawPixmap(0,0,photo.width(),photo.height(),photo);
	painter->drawText(0,0+photo.height(),name);

}

void TreeLeaf::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	 QGraphicsItem::mousePressEvent(event);
	 update();
}

void TreeLeaf::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
		  update();

	 QGraphicsItem::mouseMoveEvent(event);
}

void TreeLeaf::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	 QGraphicsItem::mouseReleaseEvent(event);
	 update();
}
