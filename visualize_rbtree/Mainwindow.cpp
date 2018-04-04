#include "Mainwindow.h"
#include <ui_Mainwindow.h>

#include <stdlib.h>
#include <time.h>

#include <qtimer.h>

#include <qlineedit.h>
#include <qpushbutton.h>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <qscrollarea.h>
#include <qscrollbar.h>

Mainwindow::Mainwindow(QWidget *parent) : QMainWindow(parent)
{
	initialization = new QPushButton(this);
	initialization->setText("Initialization");
	connect(initialization, SIGNAL(clicked()), this, SLOT(initialclicked()));

	elem = new QLineEdit(this);
	insert = new QPushButton(this);
	insert->setText("Insert");
	connect(insert, SIGNAL(clicked()), this, SLOT(insertclicked()));

	elemsecond = new QLineEdit(this);

	QHBoxLayout * hlayout1 = new QHBoxLayout;
	hlayout1->addWidget(elem);
	hlayout1->addWidget(elemsecond);
	hlayout1->addWidget(insert);
	hlayout1->addWidget(initialization);

	todelete = new QLineEdit(this);
	buttondelete = new QPushButton(this);
	buttondelete->setText("Remove");
	connect(buttondelete, SIGNAL(clicked()), this, SLOT(deleteclicked()));

	QHBoxLayout * hlayout2 = new QHBoxLayout;
	hlayout1->addWidget(todelete);
	hlayout1->addWidget(buttondelete);

	QVBoxLayout *vlayout = new QVBoxLayout;
	d = new DrawWidget(this);
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	vlayout->addWidget(d);

	QWidget *widget = new QWidget(this);
	widget->setLayout(vlayout);

	this->setCentralWidget(widget);
}

Mainwindow::~Mainwindow() { d->red_black_tree->clear(); }

void Mainwindow::initialclicked() {
	initialclick = true;
	srand((unsigned)time(NULL));

	int a[] = { 1,200,-84,56,-9,0,25,49,-17,-33,-98,356,-789,7,-10,30,-44,58,557,-785,-999,111,800,-11 };

	pair<int, string> insert;
	int i = 0;
	while (i < 24) {
		insert.first = a[i];
		insert.second = " ";
		d->red_black_tree->insert(insert);
		i++;
	}
	d->update();
}

void Mainwindow::insertclicked()
{
	/*
	if(d->red_black_tree->treeSize != 0)
		d->red_black_tree->clear();
	*/
	/*
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(d->update()));
	timer->start(500);
	*/
	if (initialclick == true) {
		int a[] = { 1,200,-84,56,-9,0,25,49,-17,-33,-98,356,-789,7,-10,30,-44,58,557,-785,-999,111,800,-11 };
		for (int i = 0; i < 24; i++)
			d->red_black_tree->erase(a[i]);
		d->update();
	}
	initialclick = false;
	pair<int, string> insertion;
	/*
	for (int i = -1; i < 2; i++) {
		insertion.first = i;
		insertion.second = " ";
		d->red_black_tree->insert(insertion);
	}
	d->red_black_tree->root->leftChild->nodeColor = black;
	d->red_black_tree->root->rightChild->nodeColor = black;
	d->update();
	*/
	
	QString num = elem->text();
	QString insertsecond = elemsecond->text();
	pair<int, string> insert;
	insert.first = num.toInt();
	insert.second = insertsecond.toStdString();
	d->red_black_tree->insert(insert);
	d->update();
	
}


void Mainwindow::deleteclicked()
{
	QString num = todelete->text();
	int theKey = num.toInt();
	d->red_black_tree->erase(theKey);
	d->update();
}