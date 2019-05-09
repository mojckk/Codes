#ifndef __CONTENT_WIDGET_H
#define __CONTENT_WIDGET_H
#include <QtWidgets>
#include <QGraphicsView>
#include <Tool_Bar.h>
#include "qimageviewer.h"
#include "CMessageBox.h"
#include "PaintLabel.h"
class QLabel;
class QPushButton;
extern QImageViewer *imageViewer;

extern bool g_isReadImg;
extern QString m_filename;
extern QLineEdit *m_pIndex;
class ContentWidget : public QWidget
{
	Q_OBJECT
public:
	ContentWidget(QWidget *parent = Q_NULLPTR);
	~ContentWidget();
private:
	void InitUI();
	void loadImageResource(void);
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	QWidget *Hwidget;
	QString m_pfilename;
	QGraphicsView *graphicsView;
    QPushButton *m_pNextButton;
	QPushButton *m_pLastButton;
private slots:
	void NextSlot();
	void LastSlot();
};
#endif
