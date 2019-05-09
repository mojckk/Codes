#ifndef TITLE_BAR
#define TITLE_BAR

#include <QWidget>
#include <iconhelper.h>
#include "SkinWidget.h"
class QLabel;
class QPushButton;
class IdentityDialog;

class TitleBar : public QWidget
{
	Q_OBJECT

public:
	explicit TitleBar(QWidget *parent = 0);
	~TitleBar();

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *event);// 双击标题栏进行界面的最大化/还原
	virtual void mousePressEvent(QMouseEvent *event);// 进行鼠界面的拖动
	virtual bool eventFilter(QObject *obj, QEvent *event);// 设置界面标题与图标
	//virtual void paintEvent(QPaintEvent *e);
private slots:
	void onClicked();

private:
	void updateMaximize();// 进行最小化、最大化/还原、关闭操作
	//QLabel *m_pIconLabel;
	//QLabel *m_pTitleLabel;
	//QLabel *m_pNameLabel;

	//QPushButton *m_pMinimizeButton;
	//QPushButton *m_pMaximizeButton;
	//QPushButton *m_pCloseButton;
	//QPushButton *m_pClothButton;

	SkinWidget *m_pSkinWidget;
};

#endif


