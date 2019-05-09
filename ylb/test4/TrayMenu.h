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
	// 自定义信号
	void quit();
private:
	// 添加菜单项
	void initActions();
private:
	QAction *m_pQuitAction;
private slots:
   
};
