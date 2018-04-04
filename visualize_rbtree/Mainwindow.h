#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets/QMainWindow>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qscrollarea.h>

#include "draw.h"

class QTimer;

class Mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	bool initialclick = false;
	QPushButton * initialization;

	QLineEdit * elem;
	QPushButton *insert;

	QLineEdit *todelete;
	QPushButton *buttondelete;

	QLineEdit *elemsecond;

	DrawWidget *d;
	Mainwindow(QWidget *parent = Q_NULLPTR);
	~Mainwindow();
	public slots:
	void insertclicked();
	void deleteclicked();
	void initialclicked();
};


#endif