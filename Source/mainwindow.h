#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "view.h"
#include <QGraphicsScene>
#include "treeleaf.h"
#include "info.h"

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
	void addPerson();

};

#endif // MAINWINDOW_H
