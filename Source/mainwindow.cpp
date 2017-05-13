#include "mainwindow.h"
#include <QHBoxLayout>
#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QMessageBox>
#include "treeleaf.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	createScene();

	View *view = new View(tr("Name"));
	view->view()->setScene(scene);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(view);
	setLayout(layout);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
			  this, SLOT(ShowContextMenu(const QPoint&)));
}

MainWindow::~MainWindow()
{
	delete scene;
}

void MainWindow::ShowContextMenu(const QPoint &pos)
{
	// for most widgets
	QPoint globalPos = this->mapToGlobal(pos);
	// for QAbstractScrollArea and derived classes you would use:
	// QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

	QMenu myMenu;
	myMenu.addAction("Добавить отца",this,SLOT(addFather()));
	myMenu.addAction("Добавить мать");
	myMenu.addAction("Добавить ребенка");
	myMenu.addAction("Изменить данные");

	// ...

	myMenu.exec(globalPos);

}

void MainWindow::addFather()
{
	QMessageBox mb(" Name",
						"Hardware failure.\n\nDisk error detected\nDo you want to stop?",
						QMessageBox::Question,
						QMessageBox::Yes | QMessageBox::Default,
						QMessageBox::No | QMessageBox::Escape,
						QMessageBox::NoButton);
	mb.exec();
}



void MainWindow::createScene()
{
	scene = new QGraphicsScene;

	QGraphicsItem *item = new TreeLeaf(tr("Иванов Иван Иванович"),tr(":/1.jpeg"), 0, 0);
	item->setPos(QPointF(0, 0));
	scene->addItem(item);

	item = new TreeLeaf(tr("Петров Петр Петрович"),tr(":/2.jpg"), 0, 0);
	item->setPos(QPointF(400, 0));
	scene->addItem(item);


	item = new TreeLeaf(tr("Сидоров Сидр Сидорович"),tr(":/3.jpg"), 0, 0);
	item->setPos(QPointF(800, 0));
	scene->addItem(item);


	item = new TreeLeaf(tr("Афанасьев Афанасий Афанасьевич"),tr(":/4.jpg"), 0, 0);
	item->setPos(QPointF(1200, 0));
	scene->addItem(item);


	scene->addRect(-100,-100,1,1,QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));
	scene->addRect(1600,500,1,1,QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));

//	QPixmap pic(tr(":/Resources/no_photo.jpg"));
//	int w = pic.width();
//	int h = pic.height();
//	scene->addPixmap(pic)->setPos((3*w/2)+1,0+1);
//	scene->addPixmap(pic)->setPos(0+1,h*1.5+1);
//	scene->addPixmap(pic)->setPos(3*w+1,h*1.5+1);

//	scene->addRect((3*w/2),0,w+2,h+2);
//	scene->addRect(0,h*1.5,w+2,h+2);
//	scene->addRect(3*w,h*1.5,w+2,h+2);

//	scene->addLine(2*w,h,2*w,h*5/4);
//	scene->addLine(0.5*w,h*5/4,3.5*w,h*5/4);
//	scene->addLine(0.5*w,h*5/4,0.5*w,h*1.5);
//	scene->addLine(3.5*w,h*5/4,3.5*w,h*1.5);

}
