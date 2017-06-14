#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "view.h"
#include <QGraphicsScene>
#include "treeleaf.h"
#include "info.h"
#include <QPoint>
#include "person.h"
#include <QMap>

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void createScene();
private:
	QGraphicsScene * scene;
	QVector<TreeLeaf *> items;
	QMap<TreeLeaf *, Person *> family;
	QMap<Person *, TreeLeaf *> leaves;
	TreeLeaf * addPers(QPointF pos, Person * newPerson);

public slots:
	void ShowContextMenu(const QPoint& pos);
	void addPerson();
	void deleted_leaf(TreeLeaf *);
	void addFather(TreeLeaf *);
	void addMother(TreeLeaf *);
	void addChild(TreeLeaf *);
	void showInformation(TreeLeaf*);
	void saveFamily();
	void moveTest();
	void leafMoved(TreeLeaf *);
};

#endif // MAINWINDOW_H
