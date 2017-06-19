#include "parentconnectdlg.h"

ParentConnectDlg::ParentConnectDlg(QList<Person *> list)
{
	parents = new QComboBox;

	for(auto el: list)
		parents->addItem(el->getName());
	parents->setMinimumWidth(300);

	QPushButton * okBtn = new QPushButton("Ok");
	okBtn->setMaximumWidth(200);
	connect(okBtn,SIGNAL(pressed()),this,SLOT(save_and_exit()));
	QGridLayout * layout = new QGridLayout;
	layout->addWidget(parents,0,0,Qt::AlignCenter);
	layout->addWidget(okBtn,1,0,Qt::AlignCenter);
	setLayout(layout);
	setWindowTitle("Воссоединение семьи");
	personList = list;
}

void ParentConnectDlg::save_and_exit()
{
	for(auto el: personList)
		if (el->getName() == parents->currentText())
		{
			emit export_person(el);
			close();
		}
}
