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
	movability = false;
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
	QAction * replaceble = new QAction(&menu);
//	replaceble->setObjectName(tr("Перемещаемый объект"));
	replaceble->setText(tr("Перемещаемый объект"));
	replaceble->setCheckable(true);
	replaceble->setChecked(movability);
	connect(replaceble,SIGNAL(changed()),this,SLOT(changeMovability()));
	menu.addAction(replaceble);//,this,SLOT(changeMovability()));
	menu.addAction("Установить родительскую связь");
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
	if (selectedAction->text().contains("связь"))
		emit connectParent(this);
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

QVariant TreeLeaf::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemPositionChange && scene()) {
		QPointF oldPos	= mapToScene(0,0);
		QPointF newPos = value.toPointF();
		QPointF delta(newPos.x() - oldPos.x(),newPos.y() - oldPos.y());

		int delta_y = newPos.y()/100;
		delta_y -= (int)oldPos.y()/100;
		if (delta_y !=0)
			newPos.setY(oldPos.y());
      emit moved(this,delta);
      return newPos;
	 }
	 return QGraphicsItem::itemChange(change, value);
}


void TreeLeaf::changeMovability()
{
	movability = !(movability);
	setFlag(QGraphicsItem::ItemIsMovable,movability);
}

QPointF TreeLeaf::top()
{
	QPointF pos = mapToScene(0,0);
	return QPointF(pos.x()+150,pos.y());
}

QPointF TreeLeaf::btm()
{
	QPointF pos = mapToScene(0,0);
	return QPointF(pos.x()+150,pos.y()+400);
}


