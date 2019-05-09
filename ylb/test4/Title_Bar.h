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
	virtual void mouseDoubleClickEvent(QMouseEvent *event);// ˫�����������н�������/��ԭ
	virtual void mousePressEvent(QMouseEvent *event);// �����������϶�
	virtual bool eventFilter(QObject *obj, QEvent *event);// ���ý��������ͼ��
	//virtual void paintEvent(QPaintEvent *e);
private slots:
	void onClicked();

private:
	void updateMaximize();// ������С�������/��ԭ���رղ���
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


