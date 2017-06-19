#ifndef TREELEAF_H
#define TREELEAF_H

#include <QObject>
#include <QGraphicsItem>
#include <QString>
#include <QImage>
#include "person.h"
#include "info.h"
#include <QWidget>

class MyGraphicsItem: public QGraphicsItem, public QObject
{
};

class TreeLeaf: public MyGraphicsItem
{
	Q_OBJECT
public:
	TreeLeaf(QString fio, QString path, int xx,int yy, QWidget * par, QWidget *parent =0);
	~TreeLeaf();
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
	QList<QGraphicsLineItem * > connections;
	QPointF top();
	QPointF btm();

protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

signals:
	void destroyed_leaf(TreeLeaf*);
	void addDad(TreeLeaf*);
	void addMom(TreeLeaf*);
	void addChild(TreeLeaf*);
	void showInfo(TreeLeaf*);
	void moved(TreeLeaf*,QPointF delta);
	void connectParent(TreeLeaf *);
private:
	QString name;
	QImage photo;
	int x;
	int y;
	QWidget * p;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
	bool movability;
public slots:
	void changeInfo(Person *);
	void changeMovability();
};

#endif // TREELEAF_H
