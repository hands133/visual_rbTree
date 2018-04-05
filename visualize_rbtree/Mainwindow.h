#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets/QMainWindow>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qscrollarea.h>
#include <qtextedit.h>
#include <qlabel.h>

#include "draw.h"

class QTimer;

class Mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	QLineEdit * elem;		//插入元素pair<int,string>的first
	QLineEdit *elemsecond;	//插入元素pair<int,string>的second
	QPushButton *insert;	//插入按钮

	QLabel * label;			//用于显示查找到的元素的second
	QPushButton * find;		//查找按钮
	QLineEdit *findElement;	//查找元素输入框

	QLineEdit *todelete;		//删除元素theElement
	QPushButton *buttondelete;	//删除按钮

	QPushButton * initialization;	//初始化按钮
	QLineEdit *initialElements;		//初始化元素

	QPushButton * random_insert;	//随机插入按钮
	QLineEdit * numberOfrandom_insert;	//随机插入元素个数

	DrawWidget *d;		//绘图面板

	QWidget * widget;
	Mainwindow(QWidget *parent = Q_NULLPTR);
	~Mainwindow();
	public slots:
	void insertclicked();	//插入点击事件
	void deleteclicked();	//删除点击事件
	void initialclicked();	//初始化点击事件
	void findclicked();		//查找点击事件
	void random_insertclicked();	//随机插入点击事件
};


#endif