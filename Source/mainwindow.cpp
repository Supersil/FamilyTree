#include "mainwindow.h"
#include <QHBoxLayout>
#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QMessageBox>
#include <QPolygonF>
#include <QFile>

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
	myMenu.addAction("Сохранить данные о семье",this,SLOT(saveFamily()));
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
	TreeLeaf * father = addPers(ppos, newPerson);


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

TreeLeaf * MainWindow::addPers(QPointF pos, Person *newPerson)
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
		item->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
		items.push_back(item);
		family.insert(item,newPerson);
		connect(item,SIGNAL(destroyed_leaf(TreeLeaf*)),this,SLOT(deleted_leaf(TreeLeaf*)));
		connect(item,SIGNAL(addDad(TreeLeaf*)),this,SLOT(addFather(TreeLeaf*)));
		connect(item,SIGNAL(addMom(TreeLeaf*)),this,SLOT(addMother(TreeLeaf*)));
		connect(item,SIGNAL(addChild(TreeLeaf*)),this,SLOT(addChild(TreeLeaf*)));
		connect(item,SIGNAL(showInfo(TreeLeaf*)),this,SLOT(showInformation(TreeLeaf*)));
		scene->addItem(item);
		return item;
	}
	return nullptr;
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


	scene->addRect(-10000,-10000,1,1,QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));
	scene->addRect(10000,10000,1,1,QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));

	Person *  me = new Person(QDate(1992,6,12),tr("Силков Александр Андреевич"),tr("Создатель программы"),tr("Москва"),tr(":/me.jpg"),MALE);
	addPers(QPointF(0,0),me);
	Person *  dad = new Person(QDate(1970,10,24),tr("Силков Андрей Николаевич"),tr("Папа"),tr("Москва"),tr(":/dad.jpg"),MALE);
	addPers(QPointF(300,600),dad);
	Person *  mom = new Person(QDate(1971,7,29),tr("Силкова Светлана Сергеевна"),tr("Мама"),tr("Солнцево"),tr(":/mom.jpg"),FEMALE);
	addPers(QPointF(-300,600),mom);
	Person *  granm = new Person(QDate(1950,3,5),tr("Бабенко Любовь Тихоновна"),tr("Бабушка"),tr("Льгов"),tr(":/grandm.jpg"),FEMALE);
	addPers(QPointF(-600,1200),granm);
	Person *  grand = new Person(QDate(1900,1,1),QDate(1992,6,20),false,tr("Бабенко Сергей"),tr("Дедушка"),tr("Льгов"),tr(":/no_photo.jpg"),MALE);
	addPers(QPointF(0,1200),grand);

}


void MainWindow::saveFamily()
{
	items[0]->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
	items[0]->moveBy(-100,-100);
//	QFile ofile;
//	ofile.setFileName(tr("output.dat"));
//	ofile.open(QIODevice::WriteOnly);


//	ofile.close();
}
