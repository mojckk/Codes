#include "TrayMenu.h"


TrayMenu::TrayMenu(QWidget *parent)
	: QMenu(parent)
{
	initActions();
}

TrayMenu::~TrayMenu()
{
}

void TrayMenu::initActions()
{
	// 创建菜单项
	
	m_pQuitAction = new QAction(QIcon(":/MainWindow/Resources/user_menu_exit.png"), QString::fromLocal8Bit("   退出"), this);
	// 添加菜单项
	//addSeparator();
	addAction(m_pQuitAction);

	// 连接信号-信号（仅列举连接显示窗口的信号）
	connect(m_pQuitAction, SIGNAL(triggered(bool)), this, SIGNAL(quit()));
}


