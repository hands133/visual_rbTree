#pragma once
#ifndef DRAW_H
#define DRAW_H

#include <qwidget.h>
#include <qpainter.h>

#include "linkedrbTree.h"

std::string;

class DrawWidget : public QWidget {
	Q_OBJECT

public: 
	linkedrbTree *red_black_tree;

	DrawWidget(QWidget *p = 0);
	void paintEvent(QPaintEvent *);
};

#endif
