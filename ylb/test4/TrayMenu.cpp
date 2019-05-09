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
	// �����˵���
	
	m_pQuitAction = new QAction(QIcon(":/MainWindow/Resources/user_menu_exit.png"), QString::fromLocal8Bit("   �˳�"), this);
	// ��Ӳ˵���
	//addSeparator();
	addAction(m_pQuitAction);

	// �����ź�-�źţ����о�������ʾ���ڵ��źţ�
	connect(m_pQuitAction, SIGNAL(triggered(bool)), this, SIGNAL(quit()));
}


