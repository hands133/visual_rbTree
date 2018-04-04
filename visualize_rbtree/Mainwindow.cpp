#include "Mainwindow.h"
#include <ui_Mainwindow.h>

#include <stdlib.h>
#include <time.h>

#include <qtimer.h>

#include <qlineedit.h>
#include <qpushbutton.h>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qgraphicseffect.h>

#include <qscrollarea.h>
#include <qscrollbar.h>
#include <qlabel.h>

Mainwindow::Mainwindow(QWidget *parent) : QMainWindow(parent)
{
	elem = new QLineEdit(this);	//插入的first
	elemsecond = new QLineEdit(this);//插入的second

	insert = new QPushButton(this);	//插入按钮
	insert->setText("Insert");	//插入按钮名称
	connect(insert, SIGNAL(clicked()), this, SLOT(insertclicked()));

	initialization = new QPushButton(this);	//初始化按钮
	initialization->setText("Initialization");	//设置初始化按钮名称
	connect(initialization, SIGNAL(clicked()), this, SLOT(initialclicked()));

	findElement = new QLineEdit(this);	//查找元素的输入框
	find = new QPushButton(this);	//查找元素按钮
	find->setText("Search");		//设置查找按钮名称
	connect(find, SIGNAL(clicked()), this, SLOT(findclicked()));
	//用QLabel显示查找的结果
	label = new QLabel(this);
	label->setFont(QFont("Times New Roman", 12, QFont::Normal));
	label->setStyleSheet("color:black");
	label->setText("Searching result : ");

	todelete = new QLineEdit(this);	//删除的输入框theKey
	buttondelete = new QPushButton(this);	//删除按钮
	buttondelete->setText("Remove");	//设置删除按钮名称
	connect(buttondelete, SIGNAL(clicked()), this, SLOT(deleteclicked()));

	d = new DrawWidget(this);	//绘图界面

	QScrollArea *scrollArea = new QScrollArea(this);
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(d);
	scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setMinimumSize(800, 600);
	scrollArea->widget()->resize(800, 600);

	QHBoxLayout *insertLayout1 = new QHBoxLayout;
	insertLayout1->addWidget(elem);
	insertLayout1->addWidget(elemsecond);

	QVBoxLayout *insertLayout = new QVBoxLayout;
	insertLayout->addLayout(insertLayout1);
	insertLayout->addWidget(insert);

	QHBoxLayout * initialLayout = new QHBoxLayout;
	insertLayout->addWidget(initialization);


	QHBoxLayout * eraseLayout = new QHBoxLayout;
	eraseLayout->addWidget(todelete);
	eraseLayout->addWidget(buttondelete);

	QHBoxLayout * searchLayout1 = new QHBoxLayout;
	searchLayout1->addWidget(findElement);
	searchLayout1->addWidget(find);

	QVBoxLayout * searchLayout = new QVBoxLayout;
	searchLayout->addLayout(searchLayout1);
	searchLayout->addWidget(label);

	QVBoxLayout *vlayout = new QVBoxLayout;
	vlayout->addLayout(insertLayout);
	vlayout->addLayout(initialLayout);
	vlayout->addLayout(eraseLayout);
	vlayout->addLayout(searchLayout);

	QGridLayout *grid = new QGridLayout;
	grid->addLayout(vlayout, 0, 0, Qt::AlignTop);
	grid->addWidget(scrollArea, 0, 1, Qt::AlignTop);
	grid->setSpacing(5);
	grid->setSizeConstraint(QGridLayout::SetFixedSize);
	/**
	QHBoxLayout * rbTree = new QHBoxLayout();
	rbTree->addWidget(d);
	
	QHBoxLayout *output = new QHBoxLayout;
	output->addLayout(rbTree);
	output->addLayout(vlayout);

	output->setSizeConstraint(QHBoxLayout::SetFixedSize);
	*/
	widget = new QWidget(this);
	widget->setLayout(grid);

	this->setCentralWidget(widget);
	setUpdatesEnabled(true);
}

Mainwindow::~Mainwindow() { d->red_black_tree->clear(); }

void Mainwindow::initialclicked() {
	initialclick = true;
	srand((unsigned)time(NULL));

	int a[] = { 1,200,-84,56,-9,0,25,49,-17,-33,-98,356,-789,7,-10,30,-44,58,557,-785,-999,111,800,-11 };
	char character[] = { 'a','b','c','d','e','f',
		'g','h','i','j','k','l','m','n',
		'o','p','q','r','s','t','u','v','w','x','y','z' };
	pair<int, string> insert;
	int i = 0;
	char str;
	while (i < 24) {
		str = i + 32;
		insert.first = a[i];
		insert.second = character[i];
		d->red_black_tree->insert(insert);
		i++;
	}
	d->repaint();
}

void Mainwindow::findclicked() {
	//查找按钮点击事件
	QString input = findElement->text();
	int theKey = input.toInt();
	if (d->red_black_tree->size() == 0)
		label->setText("Searching result : There's no element in the tree.");
	else
		label->setText(QString("Searching result : ") + QString::fromStdString(d->red_black_tree->find(theKey)));
	/*
	QLabel *label = new QLabel(this);
	label->setStyleSheet("color : black");
	label->setText(QString());
	*/
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