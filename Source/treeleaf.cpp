#include "treeleaf.h"

#include <QtWidgets>
#include <QMenu>
#include <QApplication>
#include <QObject>
#include <QPolygonF>

TreeLeaf::TreeLeaf(QString fio, QString path, int xx, int yy, QWidget *par, QWidget *parent): photo(path),
x(xx), y(yy), name(fio), p(par)
{
	setToolTip(QObject::tr("Двойное нажатие ЛКМ - открыть информацию.\nПКМ - меню."));

//	<< mapToScene(0, 0)
//   << mapToScene(-30, -50)
//   << mapToScene(30, -50)

}

TreeLeaf::~TreeLeaf()
{
	emit destroyed_leaf(this);
}

QRectF TreeLeaf::boundingRect() const
{
	 return QRectF(0, 0, 300, 400);
}

QPainterPath TreeLeaf::shape() const
{
	 QPainterPath path;
	 path.addRect(0, 0, 300, 400);
	 return path;
}

void TreeLeaf::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	QMenu menu;
	menu.addAction("Добавить отца");
	menu.addAction("Добавить мать");
	menu.addAction("Добавить ребенка");
	menu.addAction("Удалить");

	QAction *selectedAction = menu.exec(event->screenPos());
	if (selectedAction)
	{
	if (selectedAction->text().contains("Удалить"))
		delete this;
	if (selectedAction->text().contains("отца"))
		emit addDad(this);
	if (selectedAction->text().contains("мать"))
		emit addMom(this);
	if (selectedAction->text().contains("ребенка"))
		emit addChild(this);
	}


}

void TreeLeaf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	 Q_UNUSED(widget);

	QTextOption to;
	to.setAlignment(Qt::AlignCenter);
	to.setWrapMode(QTextOption::WordWrap);
	QFont font;
	font.setPixelSize(20);
	painter->setFont(font);

	painter->drawImage(x,y,photo.scaled(300,380));

	painter->drawText(QRectF(x,y+380,300,20),name,to);
	painter->drawRect(x,y,300,400);

}



void TreeLeaf::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	emit showInfo(this);
}


void TreeLeaf::changeInfo(Person * newPerson)
{
	name = newPerson->getName();
	photo = QImage(newPerson->getPhotoPath());

}


