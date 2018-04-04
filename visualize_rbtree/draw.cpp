#include "draw.h"

#include <qpainter.h>

DrawWidget::DrawWidget(QWidget *p) :QWidget(p) {
	red_black_tree = new linkedrbTree();
}

void DrawWidget::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);

	QPainter painter(this);
	// 设置画笔颜色

	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setPointSize(12);

	painter.setFont(font);

	QPen pen;
	pen.setWidth(3);

	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform,true);

	if (red_black_tree->size() == 0 || red_black_tree->size() == 1){}
	else {
		red_black_tree->calPosition();
		rbTreeNode<int, string> *parent = red_black_tree->getroot();
		rbTreeNode<int, string> *iter = red_black_tree->getroot();
		while (iter->leftChild != red_black_tree->getNil())
			iter = iter->leftChild;
		parent = red_black_tree->findParent(iter);

		while (iter != red_black_tree->getNil()) {
			if (parent != red_black_tree->getNil()) {
				pen.setColor((iter->nodeColor == red) ? Qt::red : Qt::black);
				painter.setPen(pen);
				painter.drawLine(50 * iter->position.first + 25,80 * iter->position.second + 40,
					50 * parent->position.first + 25,80 * parent->position.second + 40);
			}
			iter = red_black_tree->succ(iter);
			parent = red_black_tree->findParent(iter);
		}
	}
	pen.setWidth(2);
	pen.setColor(Qt::white);
	painter.setPen(pen);

	//遍历第二遍找到节点
	if (red_black_tree->size() != 0) {
		//找到中序遍历最开始的节点
		red_black_tree->calPosition();	//计算每个节点的位置
		rbTreeNode<int, string> *iter = red_black_tree->getroot();
		while (iter->leftChild != red_black_tree->getNil())
			iter = iter->leftChild;
		while (iter != red_black_tree->getNil()) {
			painter.setBrush((iter->nodeColor == red)?Qt::red : Qt::black);
			painter.drawEllipse(iter->position.first*50,iter->position.second*80+10, 60, 60);


			painter.drawText(iter->position.first * 50 + 20,
				iter->position.second * 80 + 45,
				QString::number(iter->element.first));
			iter = red_black_tree->succ(iter);
		}
	}
	else{
		painter.setBrush(Qt::black);
		painter.drawEllipse(200, 100, 60, 60);
		painter.setFont(font);
		painter.setPen(Qt::white);
		painter.drawText(220, 135, QString("NIL"));
	}
}