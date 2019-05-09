#include "PaintLabel.h"
#include <QPainter>
#include <QDebug>
#include <QtWidgets/qframe.h>
#include <QWidget>
#include "Tool_Bar.h"
#include "MainWindow.h"
PaintLabel::PaintLabel(QWidget *parent) :QLabel(parent)
{
	/*connect(m_pRotatelButton, SIGNAL(clicked()), this, SLOT(rotatelPic1()));
	connect(m_pRotaterButton, SIGNAL(clicked()), this, SLOT(rotaterPic1()));*/
}

void PaintLabel::paintEvent(QPaintEvent * event)
{
	
	//if (i == 1)
	//{
	//	QPixmap pix = imageViewer->pixmap;
	//	QPainter painter(this);
	//	painter.rotate(-90);
	//	painter.drawPixmap(0, 0,pix);
 //    }
	//if (i == 2)
	//{
	//	QPixmap pix = imageViewer->pixmap;
	//	QPainter painter(this);
	//	painter.rotate(90);
	//	painter.drawPixmap(0, 0,pix);
	//}
	//QLabel::paintEvent(event);
}

void PaintLabel::rotaterPic1()
{
	i = 2;
}
void PaintLabel::rotatelPic1()
{
	i = 1;
}


