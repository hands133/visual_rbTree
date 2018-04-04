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
	QLabel * label;

	QPushButton * find;
	QLineEdit *findElement;
	bool initialclick = false;
	QPushButton * initialization;

	QLineEdit * elem;
	QPushButton *insert;

	QLineEdit *todelete;
	QPushButton *buttondelete;

	QLineEdit *elemsecond;

	DrawWidget *d;

	QWidget * widget;
	Mainwindow(QWidget *parent = Q_NULLPTR);
	~Mainwindow();
	public slots:
	void insertclicked();
	void deleteclicked();
	void initialclicked();
	void findclicked();
};


#endif