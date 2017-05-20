#include "treeleaf.h"

#include <QtWidgets>
#include <QMenu>
#include <QApplication>
TreeLeaf::TreeLeaf(QString fio, QString path, int xx, int yy): photo(path),
x(xx), y(yy)
{
	name = fio;
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
	menu.addAction("Remove");
	menu.addAction("Mark");
	QAction *selectedAction = menu.exec(event->screenPos());
	if (selectedAction->text().contains("Remove"))
		delete this;

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

	painter->drawImage(0,0,photo.scaled(300,380));

	painter->drawText(QRectF(0,380,300,20),name,to);
	painter->drawRect(0,0,300,400);

}



void TreeLeaf::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	Person me(QDate(1992,06,12),QObject::tr("Силков Александр Андреевич"),
					 QObject::tr("Создатель программы"),QObject::tr("Москва"),
					 QObject::tr(":/me.jpg"));

	Info dlg(me);
	dlg.exec();
}



