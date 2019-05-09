#ifndef __SKIN_WIDGET_H
#define __SKIN_WIDGET_H
#include <QtWidgets>
extern int g_index;
class SkinWidget : public QDialog
{
	Q_OBJECT
public:
	SkinWidget(QWidget *parent = Q_NULLPTR);
	~SkinWidget();
private:
	void InitUI();
	
protected:
	virtual void paintEvent(QPaintEvent *e);
signals:

private slots:
    void blackclick();	
    void blueclick();
    void greenclick();
    void redclick();
    void pinkclick();
    void yellowclick();
private:
	QWidget *subjectWidget;

};

#endif

