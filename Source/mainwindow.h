#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "view.h"
#include <QGraphicsScene>

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void createScene();
private:
	QGraphicsScene * scene;

signals:

public slots:
	void ShowContextMenu(const QPoint& pos);
	void addFather();
//	void addMother();
//	void addChild();
//	void changeData();
};

#endif // MAINWINDOW_H
