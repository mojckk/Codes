#pragma once
#include <QMenu>
#include <qsystemtrayicon.h>
class TrayMenu : public QMenu
{
	Q_OBJECT

public:
	explicit TrayMenu(QWidget *parent = 0);
	~TrayMenu();
signals:
	// �Զ����ź�
	void quit();
private:
	// ��Ӳ˵���
	void initActions();
private:
	QAction *m_pQuitAction;
private slots:
   
};
