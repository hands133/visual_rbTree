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
#include <qtextcodec.h>

#include "arrayList.h"

Mainwindow::Mainwindow(QWidget *parent) : QMainWindow(parent)
{
	QRegExp number_only("[0-9\.]+$");
	QRegExpValidator *numonly = new QRegExpValidator(number_only, this);
	/*
	正则表达式试用阶段
	QRegExp numaddspace("[0-9\.]+$");
	QRegExpValidator *numspace = new QRegExpValidator(numaddspace, this);
	*/
	elem = new QLineEdit(this);	//插入的first
	elem->setPlaceholderText(QString("The key"));
	elem->setValidator(numonly);
	elemsecond = new QLineEdit(this);//插入的second
	elemsecond->setPlaceholderText(QString("The element"));
	insert = new QPushButton(this);	//插入按钮
	insert->setText("Insert");	//插入按钮名称
	connect(insert, SIGNAL(clicked()), this, SLOT(insertclicked()));

	findElement = new QLineEdit(this);	//查找元素的输入框
	findElement->setPlaceholderText(QString("the key you want"));
	findElement->setValidator(numonly);
	find = new QPushButton(this);	//查找元素按钮
	find->setText("Search");		//设置查找按钮名称
	connect(find, SIGNAL(clicked()), this, SLOT(findclicked()));
	//用QLabel显示查找的结果
	label = new QLabel(this);
	label->setFont(QFont("Times New Roman", 10, QFont::Normal));
	label->setStyleSheet("color:black");
	label->setText("Searching result : ");

	todelete = new QLineEdit(this);	//删除的输入框theKey
	todelete->setPlaceholderText(QString("the key you dislike"));
	todelete->setValidator(numonly);
	buttondelete = new QPushButton(this);	//删除按钮
	buttondelete->setText("Remove");	//设置删除按钮名称
	connect(buttondelete, SIGNAL(clicked()), this, SLOT(deleteclicked()));

	initialElements = new QLineEdit(this);
	initialElements->setPlaceholderText(QString("numbers seperated by space"));
	initialization = new QPushButton(this);	//初始化按钮
	initialization->setText("Initialization");	//设置初始化按钮名称
	connect(initialization, SIGNAL(clicked()), this, SLOT(initialclicked()));

	numberOfrandom_insert = new QLineEdit(this);
	numberOfrandom_insert->setPlaceholderText(QString("numbers of nodes inserted"));
	numberOfrandom_insert->setValidator(numonly);
	random_insert = new QPushButton(this);
	random_insert->setText("Randomly insert");
	connect(random_insert, SIGNAL(clicked()), this, SLOT(random_insertclicked()));

	d = new DrawWidget(this);	//绘图界面

	QScrollArea *scrollArea = new QScrollArea(this);
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(d);
	scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setMinimumSize(800, 600);
	scrollArea->widget()->resize(800, 600);

	QVBoxLayout *insertLayout1 = new QVBoxLayout;
	insertLayout1->addWidget(elem);
	insertLayout1->addWidget(elemsecond);

	QHBoxLayout *insertLayout = new QHBoxLayout;
	insertLayout->addLayout(insertLayout1);
	insertLayout->addWidget(insert);

	QHBoxLayout * initialLayout = new QHBoxLayout;
	initialLayout->addWidget(initialElements);
	initialLayout->addWidget(initialization);


	QHBoxLayout * eraseLayout = new QHBoxLayout;
	eraseLayout->addWidget(todelete);
	eraseLayout->addWidget(buttondelete);

	QHBoxLayout * searchLayout1 = new QHBoxLayout;
	searchLayout1->addWidget(findElement);
	searchLayout1->addWidget(find);

	QVBoxLayout * searchLayout = new QVBoxLayout;
	searchLayout->addLayout(searchLayout1);
	searchLayout->addWidget(label);

	QHBoxLayout * randomInsert = new QHBoxLayout;
	randomInsert->addWidget(numberOfrandom_insert);
	randomInsert->addWidget(random_insert);

	QVBoxLayout * vlayout = new QVBoxLayout;
	vlayout->addLayout(insertLayout);
	vlayout->addLayout(eraseLayout);
	vlayout->addLayout(searchLayout);
	vlayout->addLayout(initialLayout);
	vlayout->addLayout(randomInsert);

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
	QString qstring = initialElements->text();
	//对输入的字符串进行处理
	if (qstring.compare(QString("")) == 0)
		return;
	QByteArray ba = qstring.toLatin1();
	char *elements = ba.data();
	int all = qstring.length();
	int element = 0;
	arrayList<int> *byte_of_key = new arrayList<int>(all);
	pair<int, string> insertion;
	int insertpos = 0;
	for (int i = 0; i <= all; i++){
		//将所有的整数插入arrayList
		if (elements[i] == ' ' || i == all) {
			//如果遇到空格，计算整数
			for (int j = 0; j < byte_of_key->size(); j++)
				element = element * 10 + byte_of_key->get(j);
			insertion.first = element;
			insertion.second = " ";
			d->red_black_tree->insert(insertion);
			element = 0;
			byte_of_key->clearAll();
			insertpos = 0;
		}
		else {
			//没有遇到空格，向链式数组插入数字位数
			byte_of_key->insert(insertpos, elements[i] - '0');
			insertpos++;
		}

	}
	d->update();
}

void Mainwindow::findclicked() {
	//查找按钮点击事件
	QString input = findElement->text();
	if (input.compare(QString("")) == 0)
		return;
	int theKey = input.toInt();
	if (d->red_black_tree->size() == 0)
		label->setText("Searching result : There's no element in the tree.");
	else
		label->setText(QString("Searching result : ") + QString::fromStdString(d->red_black_tree->find(theKey)));
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
	QString num = elem->text();
	if (num.compare(QString("")) == 0)
		return;
	QString insertsecond = elemsecond->text();
	pair<int, string> insert;
	insert.first = num.toInt();
	insert.second = insertsecond.toStdString();
	d->red_black_tree->insert(insert);
	d->update();
	
}

void Mainwindow::deleteclicked() {
	QString num = todelete->text();
	if (num.compare(QString("")) == 0)
		return;
	int theKey = num.toInt();
	d->red_black_tree->erase(theKey);
	d->update();
}

void Mainwindow::random_insertclicked() {
	QString numbers = numberOfrandom_insert->text();
	int num = numbers.toInt();
	srand((unsigned)time(NULL));
	pair<int, string> insertion;
	for (int i = 0; i < num; i++) {
		insertion.first = rand() % num;
		insertion.second = " ";
		d->red_black_tree->insert(insertion);
	}
	d->update();
}