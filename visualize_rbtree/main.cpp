#include "Mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Mainwindow w;
	w.resize(800, 600);
	w.show();
	return a.exec();
}
