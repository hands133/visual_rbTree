#include "draw.h"
#include <math.h>

#include <qpainter.h>

DrawWidget::DrawWidget(QWidget *p) :QWidget(p) {
	red_black_tree = new linkedrbTree();
}

void DrawWidget::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);

	int nodes = red_black_tree->size();

	int Horizental = 800;
	int Vertical = (nodes == 0) ? 0 : (500 / (red_black_tree->treeHight() + 1));
	double radius;
	int verticalOffset = 80;
	if (nodes == 1)
		radius = 60;
	else
		radius = 80 * nodes*log(nodes) / sqrt(1 + nodes * nodes * nodes);

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
				painter.drawLine(iter->position.first*Horizental / (nodes + 1) + radius / 2,
					iter->position.second*Vertical+ radius / 2 -  Vertical + verticalOffset,
					parent->position.first*Horizental / (nodes + 1) + radius / 2,
					parent->position.second*Vertical + radius / 2 - Vertical + verticalOffset);
			}
			iter = red_black_tree->succ(iter);
			parent = red_black_tree->findParent(iter);
		}
	}
	pen.setWidth(2);
	pen.setColor(Qt::white);
	painter.setPen(pen);

	//遍历第二遍找到节点
	if (nodes == 0) {
		painter.setBrush(Qt::black);
		painter.drawEllipse(200, 100, 60, 60);
		painter.setFont(font);
		painter.setPen(Qt::white);
		painter.drawText(220, 135, QString("NIL"));
	}
	else {
		//找到中序遍历最开始的节点
		red_black_tree->calPosition();	//计算每个节点的位置
		rbTreeNode<int, string> *iter = red_black_tree->getroot();
		while (iter->leftChild != red_black_tree->getNil())
			iter = iter->leftChild;
		while (iter != red_black_tree->getNil()) {
			painter.setBrush((iter->nodeColor == red)?Qt::red : Qt::black);
			painter.drawEllipse(iter->position.first*Horizental / (nodes + 1),
				iter->position.second*Vertical - Vertical + verticalOffset, radius, radius);


			painter.drawText(iter->position.first*Horizental / (nodes + 1) + radius / 2 - 15,
				iter->position.second*Vertical + radius / 2 + 5 - Vertical + verticalOffset,
				QString::number(iter->element.first) + QString(":")
				+QString::fromStdString(iter->element.second));
			iter = red_black_tree->succ(iter);
		}
	}
}