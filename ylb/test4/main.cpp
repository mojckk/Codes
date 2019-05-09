#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "CommonHelper.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CommonHelper::setStyle(":/MainWindow/Resources/style.qss");
	MainWindow w;
	w.move((a.desktop()->width() - w.width()) / 2, (a.desktop()->height() - w.height()) / 2);
	w.show();
	return a.exec();
}
