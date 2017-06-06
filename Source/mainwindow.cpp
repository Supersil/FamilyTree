#include "mainwindow.h"
#include <QHBoxLayout>
#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QMessageBox>
#include <QPolygonF>

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
	QPoint MenuPos= this->mapToGlobal(pos);
	// for QAbstractScrollArea and derived classes you would use:
	// QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

	QMenu myMenu;
	myMenu.addAction("Добавить человека",this,SLOT(addPerson()));
//	if (items.size())
//		myMenu.setDisabled(1);
	myMenu.exec(MenuPos);

}

void MainWindow::addPerson()
{
	Info * createPerson = new Info;
	Person * newPerson = new Person;

	connect(createPerson,SIGNAL(export_person(Person*)),
			  newPerson,SLOT(import_data(Person*)));

	createPerson->exec();

	addPers(QPointF(0,0), newPerson);

}

void MainWindow::deleted_leaf(TreeLeaf * leaf)
{
	for(int i = 0; i < items.size(); i++)
	{
		if (items[i] == leaf)
		{
			delete family[leaf];
			family.erase(family.find(leaf));
			items.erase(items.begin()+i);
		}
	}
}

void MainWindow::addFather(TreeLeaf * child)
{
	QPointF pos = child->pos();
	QPointF ppos;
	ppos.setX(pos.x()+300);
	ppos.setY(pos.y()+600);

	Info * createPerson = new Info;
	Person * newPerson = new Person;

	connect(createPerson,SIGNAL(export_person(Person*)),
			  newPerson,SLOT(import_data(Person*)));

	createPerson->exec();
	family[child]->setFather(newPerson);
	addPers(ppos, newPerson);

	scene->addLine(pos.x()+150,pos.y()+400,pos.x()+150,pos.y()+500);
	scene->addLine(pos.x()+150,pos.y()+500,pos.x()+450,pos.y()+500);
	scene->addLine(pos.x()+450,pos.y()+500,pos.x()+450,pos.y()+600);

}

void MainWindow::addMother(TreeLeaf * child)
{
	QPointF pos = child->pos();
	QPointF ppos;
	ppos.setX(pos.x()-300);
	ppos.setY(pos.y()+600);

	Info * createPerson = new Info;
	Person * newPerson = new Person;

	connect(createPerson,SIGNAL(export_person(Person*)),
			  newPerson,SLOT(import_data(Person*)));

	createPerson->exec();
	family[child]->setMother(newPerson);
	addPers(ppos, newPerson);

	scene->addLine(pos.x()+150,pos.y()+400,pos.x()+150,pos.y()+500);
	scene->addLine(pos.x()+150,pos.y()+500,pos.x()-150,pos.y()+500);
	scene->addLine(pos.x()-150,pos.y()+500,pos.x()-150,pos.y()+600);
}

void MainWindow::addChild(TreeLeaf * parent)
{
	QPointF pos = parent->pos();
	QPointF ppos;

	Person* adult = family[parent];
	if (adult->getSex() == MALE)
	{
		ppos.setX(pos.x()-300);
		ppos.setY(pos.y()-600);
	}
	else
	{
		ppos.setX(pos.x()+300);
		ppos.setY(pos.y()-600);
	}

	Info * createPerson = new Info;
	Person * newPerson = new Person;

	connect(createPerson,SIGNAL(export_person(Person*)),
			  newPerson,SLOT(import_data(Person*)));

	createPerson->exec();
	family[parent]->addChild(newPerson);
	addPers(ppos, newPerson);

	if (adult->getSex() == MALE)
	{
		scene->addLine(pos.x()+150,pos.y(),pos.x()+150,pos.y()-100);
		scene->addLine(pos.x()+150,pos.y()-100,pos.x()-150,pos.y()-100);
		scene->addLine(pos.x()-150,pos.y()-100,pos.x()-150,pos.y()-200);
	}
	else
	{
		scene->addLine(pos.x()+150,pos.y(),pos.x()+150,pos.y()-100);
		scene->addLine(pos.x()+150,pos.y()-100,pos.x()+450,pos.y()-100);
		scene->addLine(pos.x()+450,pos.y()-100,pos.x()+450,pos.y()-200);
	}


}

void MainWindow::addPers(QPointF pos, Person *newPerson)
{
	QPolygonF polyg;
	polyg << pos << pos + QPointF(300,0) <<
			pos + QPoint(300,400) << pos + QPoint(0,400);

	QList<QGraphicsItem *> collide= scene->items(polyg);

	if (collide.size()!=0)
	{
		for(auto i : collide)
			i->setPos(i->x()-400,i->y());
	}
	if (newPerson->set)
	{
		TreeLeaf * item = new TreeLeaf(newPerson->getName(),newPerson->getPhotoPath(), 0,0,this);
		item->setPos(pos);
		items.push_back(item);
		family.insert(item,newPerson);
		connect(item,SIGNAL(destroyed_leaf(TreeLeaf*)),this,SLOT(deleted_leaf(TreeLeaf*)));
		connect(item,SIGNAL(addDad(TreeLeaf*)),this,SLOT(addFather(TreeLeaf*)));
		connect(item,SIGNAL(addMom(TreeLeaf*)),this,SLOT(addMother(TreeLeaf*)));
		connect(item,SIGNAL(addChild(TreeLeaf*)),this,SLOT(addChild(TreeLeaf*)));
		connect(item,SIGNAL(showInfo(TreeLeaf*)),this,SLOT(showInformation(TreeLeaf*)));
		scene->addItem(item);
	}
}

void MainWindow::showInformation(TreeLeaf * leaf)
{

	Person * pers = family[leaf];
	Info * dlg = new Info(pers);
	connect(dlg,SIGNAL(export_person(Person*)),
			  pers,SLOT(import_data(Person*)));
	connect(dlg,SIGNAL(export_person(Person*)),
			  leaf,SLOT(changeInfo(Person*)));
	dlg->exec();

}

void MainWindow::createScene()
{
	scene = new QGraphicsScene;

//	QGraphicsItem *item = new TreeLeaf(tr("Иванов Иван Иванович"),tr(":/1.jpeg"), 0, 0);
//	item->setPos(QPointF(0, 0));
//	scene->addItem(item);

//	item = new TreeLeaf(tr("Петров Петр Петрович"),tr(":/2.jpg"), 0, 0);
//	item->setPos(QPointF(400, 0));
//	scene->addItem(item);


//	item = new TreeLeaf(tr("Сидоров Сидр Сидорович"),tr(":/3.jpg"), 0, 0);
//	item->setPos(QPointF(800, 0));
//	scene->addItem(item);


//	item = new TreeLeaf(tr("Афанасьев Афанасий Афанасьевич"),tr(":/4.jpg"), 0, 0);
//	item->setPos(QPointF(1200, 0));
//	scene->addItem(item);


	scene->addRect(-10000,-10000,1,1,QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));
	scene->addRect(10000,10000,1,1,QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));

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
