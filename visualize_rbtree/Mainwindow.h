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
	QLineEdit * elem;		//����Ԫ��pair<int,string>��first
	QLineEdit *elemsecond;	//����Ԫ��pair<int,string>��second
	QPushButton *insert;	//���밴ť

	QLabel * label;			//������ʾ���ҵ���Ԫ�ص�second
	QPushButton * find;		//���Ұ�ť
	QLineEdit *findElement;	//����Ԫ�������

	QLineEdit *todelete;		//ɾ��Ԫ��theElement
	QPushButton *buttondelete;	//ɾ����ť

	QPushButton * initialization;	//��ʼ����ť
	QLineEdit *initialElements;		//��ʼ��Ԫ��

	QPushButton * random_insert;	//������밴ť
	QLineEdit * numberOfrandom_insert;	//�������Ԫ�ظ���

	DrawWidget *d;		//��ͼ���

	QWidget * widget;
	Mainwindow(QWidget *parent = Q_NULLPTR);
	~Mainwindow();
	public slots:
	void insertclicked();	//�������¼�
	void deleteclicked();	//ɾ������¼�
	void initialclicked();	//��ʼ������¼�
	void findclicked();		//���ҵ���¼�
	void random_insertclicked();	//����������¼�
};


#endif