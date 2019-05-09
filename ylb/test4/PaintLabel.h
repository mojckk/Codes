
#ifndef PAINTLABEL_H
#define PAINTLABEL_H
#include <QLabel> 
#include "qimageviewer.h"

extern QImageViewer *imageViewer;
extern QPushButton *m_pRotatelButton;
extern QPushButton *m_pRotaterButton;
class PaintLabel :public QLabel 
{ 
      Q_OBJECT
public:   
	
	explicit PaintLabel(QWidget *parent = 0);    
	void paintEvent(QPaintEvent *event); 
	public slots:
    void rotatelPic1();
    void rotaterPic1();
	
protected:
	int i;
};
#endif


