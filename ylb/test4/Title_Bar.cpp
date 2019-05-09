#include "Title_Bar.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QImage>
#include <QDialog>
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#include "CMessageBox.h"

QLabel *m_pIconLabel;
QLabel *m_pTitleLabel;
QLabel *m_pNameLabel;

QPushButton *m_pMinimizeButton;
QPushButton *m_pMaximizeButton;
QPushButton *m_pCloseButton;
QPushButton *m_pClothButton;

SkinWidget *m_pSkinWidget;
TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	setFixedHeight(50);

	m_pIconLabel = new QLabel(this);
	m_pTitleLabel = new QLabel(this);
	m_pMinimizeButton = new QPushButton(this);
	m_pMaximizeButton = new QPushButton(this);
	m_pCloseButton = new QPushButton(this);
	m_pClothButton = new QPushButton(this);

	m_pIconLabel->setObjectName("m_pIconLabel");
	m_pTitleLabel->setObjectName("m_pTitleLabel");	
	m_pMinimizeButton->setObjectName("m_pMinimizeButton");
	m_pMaximizeButton->setObjectName("m_pMaximizeButton");
	m_pCloseButton->setObjectName("m_pCloseButton");
	m_pClothButton->setObjectName("m_pClothButton");

	m_pIconLabel->setFixedSize(40, 40);
	QImage *ppm = new QImage(":/MainWindow/Resources/6.png");
	m_pIconLabel->setPixmap(QPixmap::fromImage(*ppm));
	m_pIconLabel->setScaledContents(true);

	m_pMinimizeButton->setFixedSize(35, 35);
	m_pMaximizeButton->setFixedSize(35, 35);
	m_pCloseButton->setFixedSize(35, 35);
	m_pClothButton->setFixedSize(35, 35);

	m_pTitleLabel->setText(QStringLiteral(" FOB检测工具"));
	m_pTitleLabel->setStyleSheet("color:white");//文本颜色  
	m_pTitleLabel->setFont(QFont("Microsoft YaHei", 18, QFont::Bold));

	m_pMinimizeButton->setToolTip(QStringLiteral("最小化"));
	m_pMaximizeButton->setToolTip(QStringLiteral("最大化"));
	m_pCloseButton->setToolTip(QStringLiteral("关闭"));
	m_pClothButton->setToolTip(QStringLiteral("皮肤"));

	IconHelper::Instance()->SetIcon(m_pCloseButton, QChar(0xf00d), 16);
	IconHelper::Instance()->SetIcon(m_pMinimizeButton, QChar(0xf068), 18);
	IconHelper::Instance()->SetIcon(m_pMaximizeButton, QChar(0xf2d0), 16);
	IconHelper::Instance()->SetIcon(m_pClothButton, QChar(0xf004), 14);

	QHBoxLayout *pLayout = new QHBoxLayout(this);
	pLayout->setSpacing(0);
	pLayout->setContentsMargins(0, 0, 0, 0);
	pLayout->addSpacing(5);
	pLayout->addWidget(m_pIconLabel);
	pLayout->addWidget(m_pTitleLabel);
	pLayout->addWidget(m_pClothButton);
	pLayout->addWidget(m_pMinimizeButton);
	pLayout->addWidget(m_pMaximizeButton);
	pLayout->addWidget(m_pCloseButton);
	setLayout(pLayout);
	
	connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pClothButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

	m_pSkinWidget = new SkinWidget(this);
}

TitleBar::~TitleBar()
{

}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event);//避免编译器警告

	emit m_pMaximizeButton->clicked();
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
	if (ReleaseCapture())
	{
		QWidget *pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
	event->ignore();
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
	switch (event->type())
	{
	case QEvent::WindowStateChange:
	case QEvent::Resize:
		updateMaximize();
		return true;
	}
	return QWidget::eventFilter(obj, event);
}


void TitleBar::onClicked()
{
	QPushButton *pButton = qobject_cast<QPushButton *>(sender());
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		if (pButton == m_pMinimizeButton)
		{
			pWindow->showMinimized();
		}
		else if (pButton == m_pMaximizeButton)
		{
			pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
		}
		else if (pButton == m_pCloseButton)
		{
			/*CMessageBox warn(QString(QStringLiteral("退出提示")), QStringLiteral("你确定要退出该软件吗?"),
				QMessageBox::Yes, QMessageBox::Yes);
			int ret = warn.exec();
			if (ret == QMessageBox::Yes)*/
				pWindow->close();
			/*else
				return;*/
		}
		else if (pButton == m_pClothButton)
		{
			QPoint pos = mapToGlobal(this->pos());
			QRect rect = this->geometry();
			QPoint myPos(rect.right() + pos.x() - 335, pos.y() + 40);
			m_pSkinWidget->move(myPos);
			m_pSkinWidget->show();
		}
	}
}

void TitleBar::updateMaximize()
{
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		bool bMaximize = pWindow->isMaximized();
		if (bMaximize)
		{
			m_pMaximizeButton->setToolTip(QStringLiteral("还原"));
			m_pMaximizeButton->setProperty("maximizeProperty", "restore");
			IconHelper::Instance()->SetIcon(m_pMaximizeButton, QChar(0xf2d2), 14);
		}
		else
		{
			m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
			m_pMaximizeButton->setToolTip(QStringLiteral("最大化"));
			IconHelper::Instance()->SetIcon(m_pMaximizeButton, QChar(0xf2d0), 16);
		}
		m_pMaximizeButton->setStyle(QApplication::style());
	}
}
