#include "mainwindow.h"
#include <QHBoxLayout>
#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QMessageBox>
#include <QPolygonF>
#include <QFile>
#include <QIcon>
#include "parentconnectdlg.h"

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
	setWindowTitle(tr("Генеалогия"));
	QIcon myIcon(":/tree.png");
	setWindowIcon(myIcon);
	ctrlPressed = false;
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
	myMenu.addAction("Тест сдвига",this,SLOT(moveTest()));
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
	newPerson->addChild(family[child]);
	addPers(ppos, newPerson);

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
	newPerson->addChild(family[child]);
	addPers(ppos, newPerson);

}

void MainWindow::addChild(TreeLeaf * parent)
{
	QPointF pos = parent->pos();
	QPointF ppos;

	Info * createPerson = new Info;
	Person * newPerson = new Person;

	connect(createPerson,SIGNAL(export_person(Person*)),
			  newPerson,SLOT(import_data(Person*)));

	createPerson->exec();
	family[parent]->addChild(newPerson);

	Person* adult = family[parent];
	if (adult->getSex() == MALE)
	{
		ppos.setX(pos.x()-300);
		ppos.setY(pos.y()-600);
		newPerson->setFather(adult);
	}
	else
	{
		ppos.setX(pos.x()+300);
		ppos.setY(pos.y()-600);
		newPerson->setMother(adult);
	}

	addPers(ppos, newPerson);

}

TreeLeaf * MainWindow::addPers(QPointF pos, Person *newPerson)
{
	QPolygonF polyg;
	polyg << pos + QPointF(-100,100) << pos + QPointF(400,100) <<
			pos + QPoint(400,300) << pos + QPoint(-100,300);

	QList<QGraphicsItem *> collide= scene->items(polyg);

	if (collide.size()!=0)
	{
		ctrlPressed = true;
		TreeLeaf * collider = (TreeLeaf * )collide[0];
		TreeLeaf * child = leaves[family[collider]->child(0)];
		child->changeMovability();
		if (child->mapToScene(0,0).x() < pos.x())
			child->moveBy(-400,0);
		else
			child->moveBy(400,0);
		child->changeMovability();
		ctrlPressed = false;

	}

	if (newPerson->set)
	{
		TreeLeaf * item = new TreeLeaf(newPerson->getName(),newPerson->getPhotoPath(), 0,0,this);
		item->setPos(pos);
		item->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
		items.push_back(item);
		family.insert(item,newPerson);
		leaves.insert(newPerson,item);
		connect(item,SIGNAL(destroyed_leaf(TreeLeaf*)),this,SLOT(deleted_leaf(TreeLeaf*)));
		connect(item,SIGNAL(addDad(TreeLeaf*)),this,SLOT(addFather(TreeLeaf*)));
		connect(item,SIGNAL(addMom(TreeLeaf*)),this,SLOT(addMother(TreeLeaf*)));
		connect(item,SIGNAL(addChild(TreeLeaf*)),this,SLOT(addChild(TreeLeaf*)));
		connect(item,SIGNAL(showInfo(TreeLeaf*)),this,SLOT(showInformation(TreeLeaf*)));
		connect(item,SIGNAL(connectParent(TreeLeaf*)),this,SLOT(connectLeaves(TreeLeaf*)));
		connect(item,SIGNAL(moved(TreeLeaf*,QPointF)),this,SLOT(leafMoved(TreeLeaf*,QPointF)));
		scene->addItem(item);

		if (newPerson->dad() != nullptr)
		{
			QLineF line(item->btm(),leaves[newPerson->dad()]->top());
			QGraphicsLineItem * nline = scene->addLine(line);
			item->connections.push_back(nline);
			leaves[newPerson->dad()]->connections.push_back(nline);
		}

		if (newPerson->mom() != nullptr)
		{
			QLineF line(item->btm(),leaves[newPerson->mom()]->top());
			QGraphicsLineItem * nline = scene->addLine(line);
			item->connections.push_back(nline);
			leaves[newPerson->mom()]->connections.push_back(nline);
		}

		for(int i = 0; i < newPerson->children_num(); i++)
		{
			QLineF line(item->top(),leaves[newPerson->child(i)]->btm());
			QGraphicsLineItem * nline = scene->addLine(line);
			item->connections.push_back(nline);
			leaves[newPerson->child(i)]->connections.push_back(nline);
		}


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
	me->setFather(dad);
	dad->addChild(me);
	addPers(QPointF(300,600),dad);
	Person *  mom = new Person(QDate(1971,7,29),tr("Силкова Светлана Сергеевна"),tr("Мама"),tr("Солнцево"),tr(":/mom.jpg"),FEMALE);
	me->setMother(mom);
	mom->addChild(me);
	addPers(QPointF(-300,600),mom);
	Person *  granm = new Person(QDate(1950,3,5),tr("Бабенко Любовь Тихоновна"),tr("Бабушка"),tr("Льгов"),tr(":/grandm.jpg"),FEMALE);
	mom->setMother(granm);
	granm->addChild(mom);
	addPers(QPointF(-600,1200),granm);
	Person *  grand = new Person(QDate(1900,1,1),QDate(1992,6,20),false,tr("Бабенко Сергей"),tr("Дедушка"),tr("Льгов"),tr(":/no_photo.jpg"),MALE);
	mom->setFather(grand);
	grand->addChild(mom);
	addPers(QPointF(0,1200),grand);

}


void MainWindow::saveFamily()
{
//	QFile ofile;
//	ofile.setFileName(tr("output.dat"));
//	ofile.open(QIODevice::WriteOnly);
   QString path("family.dat");
   QFile file;
   file.setFileName(path);
   file.remove();
   for(auto it: items)
      family[it]->save_pure(path);

//	ofile.close();
}

void MainWindow::moveTest()
{
//	for(int i = 2; i < items.size(); i++)
//		items[i]->moveBy(-300,0);
//	items[1]->moveBy(300,0);
//	Person *  granm = new Person(QDate(1948,7,12),tr("Силкова Наталья Михайловна"),tr("Бабушка"),tr("Скопин"),tr(":/no_photo.jpg"),FEMALE);
//	addPers(QPointF(300,1200),granm);
//	Person *  grand = new Person(QDate(1948,7,8),QDate(1996,6,20),false,tr("Силков Николай Александрович"),tr("Дедушка"),tr("Скопин"),tr(":/no_photo.jpg"),MALE);
//	addPers(QPointF(900,1200),grand);
//	items[0]->setFlag(QGraphicsItem::ItemIsMovable);
//	items[0]->setFlag(QGraphicsItem::ItemIsSelectable);
}

void MainWindow::leafMoved(TreeLeaf * item, QPointF delta)
{

	Person * curPerson = family[item];

	QPen * pen;
//	if (!ctrlPressed)
		pen = new QPen(QBrush(QColor(0,0,0)),1);
//	else
//		pen = new QPen(QBrush(QColor(255,0,0)),3);


	for(auto it: item->connections)
	{
		scene->removeItem(it);
		if (curPerson->dad() != nullptr)
			leaves[curPerson->dad()]->connections.removeOne(it);
		if (curPerson->mom() != nullptr)
			leaves[curPerson->mom()]->connections.removeOne(it);
		for(int i = 0; i < curPerson->children_num(); i++)
			leaves[curPerson->child(i)]->connections.removeOne(it);
		delete it;
	}
	item->connections.clear();

	if (curPerson->dad() != nullptr)
	{
		QLineF line(item->btm(),leaves[curPerson->dad()]->top());
		QGraphicsLineItem * nline = scene->addLine(line,*pen);
		item->connections.push_back(nline);
		leaves[curPerson->dad()]->connections.push_back(nline);
	}

	if (curPerson->mom() != nullptr)
	{
		QLineF line(item->btm(),leaves[curPerson->mom()]->top());
		QGraphicsLineItem * nline = scene->addLine(line,*pen);
		item->connections.push_back(nline);
		leaves[curPerson->mom()]->connections.push_back(nline);
	}

	for(int i = 0; i < curPerson->children_num(); i++)
	{
		QLineF line(item->top(),leaves[curPerson->child(i)]->btm());
		QGraphicsLineItem * nline = scene->addLine(line,*pen);
		item->connections.push_back(nline);
		leaves[curPerson->child(i)]->connections.push_back(nline);
	}


	if (ctrlPressed)
	{
		if (curPerson->mom()!= nullptr)
		{
			leaves[curPerson->mom()]->changeMovability();
			leaves[curPerson->mom()]->moveBy(delta.x(),delta.y());
			leaves[curPerson->mom()]->changeMovability();
		}

		if (curPerson->dad()!= nullptr)
		{
			leaves[curPerson->dad()]->changeMovability();
			leaves[curPerson->dad()]->moveBy(delta.x(),delta.y());
			leaves[curPerson->dad()]->changeMovability();
		}
	}

//	delete pen;
	scene->update();
}


void MainWindow::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Control)
	{
		ctrlPressed = true;
	}
}


void MainWindow::keyReleaseEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Control)
	{
		ctrlPressed = false;
	}
}


bool MainWindow::ctrl()
{
	return ctrlPressed;
}


void MainWindow::connectLeaves(TreeLeaf * item)
{
	QList<Person *> list;

	for(auto leaf: items)
		list.append(family[leaf]);

	ParentConnectDlg dlg(list);
	dlg.exec();
}
