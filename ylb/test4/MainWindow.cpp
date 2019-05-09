#include "MainWindow.h"
#include "qlayout.h"
#include <QLabel>
#include <QPushbutton>
#include <QBitmap>
#include <QPainter>
#include <QStatusBar>
#include <QMouseEvent>
#include "windowsx.h"
#include "CommonHelper.h"
int g_index;
QSystemTrayIcon *pSystemTray;

MainWindow::MainWindow()
{
	InitUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setMarginWidth(const int &iWidth)
{
	m_iMarginWidth = iWidth;
}

void MainWindow::serResizable(bool bCanResize)
{
	m_bCanResize = bCanResize;
}

void MainWindow::InitUI()
{	
	this->setMinimumSize(QSize(1280, 1024));//设置最小大小
	this->setWindowFlags(Qt::FramelessWindowHint);// 隐藏标题栏
	this->setObjectName("MainWindow");
	//setAttribute(Qt::WA_TranslucentBackground);
	QPalette pa_title1;
	pa_title1.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/blackbk.jpg"));
	setPalette(pa_title1);
    setAutoFillBackground(true);
	m_pCenterWidget = new QWidget;
	m_pMainLayout = new QVBoxLayout;
	m_pCenterWidget->setLayout(m_pMainLayout);
	this->setCentralWidget(m_pCenterWidget);
	m_pMainLayout->setAlignment(Qt::AlignTop);//Layout置顶
	m_pMainLayout->setMargin(0);//边框离边界距离为零
	m_pMainLayout->setSpacing(0);//标题栏，状态栏，主窗口间隔为零
	m_iMarginWidth = 3;
	m_bCanResize = true;
	setWindowIcon(QIcon(":/MainWindow/Resources/6.png"));
	InitTitle();
	InitTool();
	InitContent();
	InitState();
    InitTray();
}

void MainWindow::InitTitle()
{
	pTitleBar = new TitleBar(this);
	pTitleBar->setObjectName("pTitleBar");
	installEventFilter(pTitleBar);
	m_pMainLayout->addWidget(pTitleBar);
	//pTitleBar->setStyleSheet("background-color:blue;");//有问题的背景
	//pTitleBar->setStyleSheet("background-color:rgb(41, 36, 33);");
	g_index = 1;
	connect(m_pblack, SIGNAL(clicked(bool)), this, SLOT(blackclick()));
	connect(m_pgreen, SIGNAL(clicked(bool)), this, SLOT(greenclick()));
	connect(m_pred, SIGNAL(clicked(bool)), this, SLOT(redclick()));
	connect(m_ppink, SIGNAL(clicked(bool)), this, SLOT(pinkclick()));
	connect(m_pblue, SIGNAL(clicked(bool)), this, SLOT(blueclick()));
	connect(m_pyellow, SIGNAL(clicked(bool)), this, SLOT(yellowclick()));
	QPalette pa_title;
	pa_title.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/black.png"));
	pTitleBar->setPalette(pa_title);
	pTitleBar->setAutoFillBackground(true);

}

void MainWindow::InitContent()
{
	contentWidget = new ContentWidget(this);	
	contentWidget->setFixedHeight(800);
	m_pMainLayout->addWidget(contentWidget);
	/*QPalette pa_title;
	pa_title.setColor(QPalette::Background, QColor(255, 255, 255));
	contentWidget->setPalette(pa_title);
	contentWidget->setAutoFillBackground(true);*/
}

void MainWindow::InitState()
{
	//statusBar()->showMessage(QStringLiteral("状态"));
	StateBar *stateWidget = new StateBar(this);
	m_pMainLayout->addWidget(stateWidget);
}

void MainWindow::InitTool()
{
	pToolBar = new ToolBar(this);
	m_pMainLayout->addWidget(pToolBar);
}

void MainWindow::InitTray()
{
	pSystemTray = new QSystemTrayIcon(this);
	pSystemTray->setObjectName("pSystemTray");
	TrayMenu *pTrayMenu = new TrayMenu(this);
	// 设置系统托盘的上下文菜单
	pSystemTray->setContextMenu(pTrayMenu);
	// 设置系统托盘提示信息、托盘图标
	pSystemTray->setToolTip(QString::fromLocal8Bit("FOB检测工具"));
	pSystemTray->setIcon(QIcon(":/MainWindow/Resources/6.png"));
	// 连接信号槽
	connect(pTrayMenu, SIGNAL(quit()), this, SLOT(quitSlot()));
	connect(pSystemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));
	// 显示系统托盘
	pSystemTray->show();
	// 显示系统托盘提示信息
	pSystemTray->showMessage(QString::fromLocal8Bit("FOB检测工具"), 
		QString::fromLocal8Bit("显示内容"));
	
}

bool MainWindow::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
	return winEvent((MSG*)message, result);
	return false;
}

bool MainWindow::winEvent(MSG * message, long * result)
{
	switch (message->message)
	{
	case WM_NCHITTEST:
		int iPosX = GET_X_LPARAM(message->lParam) - this->frameGeometry().x();//鼠标位置x
		int iPosY = GET_Y_LPARAM(message->lParam) - this->frameGeometry().y();//鼠标位置y

		*result = HTCLIENT;//客户区    HTCAPTION为标题区

		if (!m_bCanResize)
		{
			return true;//返回为真，此时仍可拖动，但无法改变大小
		}

		if (iPosX >= 0 && iPosX <= m_iMarginWidth)
		{
			*result = HTLEFT;//左
			int iHeight = this->height();
			if (iPosY >= 0 && iPosY <= m_iMarginWidth)
			{
				*result = HTTOPLEFT;//左上
			}
			if (iPosY >= iHeight - m_iMarginWidth && iPosY <= iHeight)
			{
				*result = HTBOTTOMLEFT;//左下
			}
			return true;
		}

		int iWidth = this->width();
		int iHeight = this->height();
		if (iPosX >= iWidth - m_iMarginWidth && iPosX <= iWidth)
		{
			*result = HTRIGHT;//右
			if (iPosY >= 0 && iPosY <= m_iMarginWidth)
			{
				*result = HTTOPRIGHT;//右上
				return true;
			}
			if (iPosY >= iHeight - m_iMarginWidth && iPosY <= iHeight)
			{
				*result = HTBOTTOMRIGHT;//右下
				return true;
			}
			return true;
		}
		if (iPosY >= 0 && iPosY <= m_iMarginWidth)
		{
			*result = HTTOP;//上
			return true;
		}
		if (iPosY >= iHeight - m_iMarginWidth && iPosY <= iHeight)
		{
			*result = HTBOTTOM;//下
			return true;
		}
		return true;
	}
	return false;
}

void MainWindow::quitSlot()
{
	QWidget *pWindow = this->window();
    pWindow->close();
}
void MainWindow::onActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
		// 单击托盘显示窗口
	case QSystemTrayIcon::Trigger:
	{
		showNormal();
		raise();
		activateWindow();
		break;
	}
	// 双击
	case QSystemTrayIcon::DoubleClick:
	{
		// ...
		break;
	}
	default:
		break;
	}

};
void MainWindow::blueclick()
{
	QPalette pa_title1;
	pa_title1.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/blue.png"));
	pTitleBar->setPalette(pa_title1);
	pTitleBar->setAutoFillBackground(true);

	QImage *ppm = new QImage(":/new/prefix1/C2/5.png");
	m_pIconLabel->setPixmap(QPixmap::fromImage(*ppm));
	m_pIconLabel->setScaledContents(true);
	setWindowIcon(QIcon(":/new/prefix1/C2/5.png"));
	pSystemTray->setIcon(QIcon(":/new/prefix1/C2/5.png"));

	QPalette pa_title;
	pa_title.setBrush(QPalette::Background, QPixmap(":/new/prefix1/C2/bluebk.jpg"));
	setPalette(pa_title);
	setAutoFillBackground(true);

	m_pMinimizeButton->setFlat(true);
	m_pMaximizeButton->setFlat(true);
	m_pCloseButton->setFlat(true);
	m_pClothButton->setFlat(true);

	m_pOpenButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C2/open3.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C2/open2.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C2/open2.png);}");
	m_pJudgeButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C2/judge2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C2/judge1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C2/judge1.png);}");
	m_pEnlargeButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C2/l2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C2/l1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C2/l1.png);}");
	m_pShrinkButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C2/s2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C2/s.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C2/s.png);}");
	m_pDeleteButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C2/delete2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C2/delete1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C2/delete1.png);}");
	m_pRotatelButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C2/rotatel2 .png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C2/rotatel1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C2/rotatel1.png);}");
	m_pRotaterButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C2/rotater2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C2/rotater1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C2/rotater1.png);}");
	m_pPrintButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C2/print2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C2/print1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C2/print1.png);}");
	m_pSaveButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C2/save2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C2/save1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C2/save1.png);}");
	m_pAllButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C2/all0.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C2/all.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C2/all.png);}");

	m_pLabel->setStyleSheet("QLabel{border-image: url(:/new/prefix1/C2/anw.png);}");
}
void MainWindow::greenclick()
{
	QPalette pa_title1;
	pa_title1.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/green.png"));
	pTitleBar->setPalette(pa_title1);
	pTitleBar->setAutoFillBackground(true);

	QImage *ppm = new QImage(":/new/prefix1/C1/4.png");
	m_pIconLabel->setPixmap(QPixmap::fromImage(*ppm));
	m_pIconLabel->setScaledContents(true);
	setWindowIcon(QIcon(":/new/prefix1/C1/4.png"));
	pSystemTray->setIcon(QIcon(":/new/prefix1/C1/4.png"));
	
	QPalette pa_title;
	pa_title.setBrush(QPalette::Background, QPixmap(":/new/prefix1/C1/greenbk.png"));
	setPalette(pa_title);
	setAutoFillBackground(true);

	m_pMinimizeButton->setFlat(true);
	m_pMaximizeButton->setFlat(true);
	m_pCloseButton->setFlat(true);
	m_pClothButton->setFlat(true);

	m_pOpenButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C1/open3.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C1/open2.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C1/open2.png);}");
	m_pJudgeButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C1/judge2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C1/judge1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C1/judge1.png);}");
	m_pEnlargeButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C1/l2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C1/l1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C1/l1.png);}");
	m_pShrinkButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C1/s2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C1/s.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C1/s.png);}");
	m_pDeleteButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C1/delete2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C1/delete1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C1/delete1.png);}");
	m_pRotatelButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C1/rotatel2 .png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C1/rotatel1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C1/rotatel1.png);}");
	m_pRotaterButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C1/rotater2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C1/rotater1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C1/rotater1.png);}");
	m_pPrintButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C1/print2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C1/print1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C1/print1.png);}");
	m_pSaveButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C1/save2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C1/save1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C1/save1.png);}");
	m_pAllButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C1/all0.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C1/all.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C1/all.png);}");

	m_pLabel->setStyleSheet("QLabel{border-image: url(:/new/prefix1/C1/anw.png);}");

	//QPalette pa_title2;
	//pa_title2.setBrush(QPalette::Background, QPixmap(":/new/prefix1/C1/cbk.png"));
	//m_pPicLabel->setPalette(pa_title2);
	//m_pPicLabel->setWindowOpacity(0.5);//透明度
	//m_pPicLabel->setAutoFillBackground(true);
}
void MainWindow::redclick()
{
	QPalette pa_title1;
	pa_title1.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/red.png"));
	pTitleBar->setPalette(pa_title1);
	pTitleBar->setAutoFillBackground(true);

	QImage *ppm = new QImage(":/new/prefix1/C3/5.png");
	m_pIconLabel->setPixmap(QPixmap::fromImage(*ppm));
	m_pIconLabel->setScaledContents(true);
	setWindowIcon(QIcon(":/new/prefix1/C3/5.png"));
	pSystemTray->setIcon(QIcon(":/new/prefix1/C3/5.png"));

	QPalette pa_title;
	pa_title.setBrush(QPalette::Background, QPixmap(":/new/prefix1/C3/redbk.jpg"));
	setPalette(pa_title);
	setAutoFillBackground(true);

	m_pMinimizeButton->setFlat(true);
	m_pMaximizeButton->setFlat(true);
	m_pCloseButton->setFlat(true);
	m_pClothButton->setFlat(true);

	m_pOpenButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C3/open3.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C3/open2.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C3/open2.png);}");
	m_pJudgeButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C3/judge2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C3/judge1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C3/judge1.png);}");
	m_pEnlargeButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C3/l2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C3/l1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C3/l1.png);}");
	m_pShrinkButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C3/s2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C3/s.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C3/s.png);}");
	m_pDeleteButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C3/delete2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C3/delete1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C3/delete1.png);}");
	m_pRotatelButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C3/rotatel2 .png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C3/rotatel1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C3/rotatel1.png);}");
	m_pRotaterButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C3/rotater2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C3/rotater1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C3/rotater1.png);}");
	m_pPrintButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C3/print2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C3/print1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C3/print1.png);}");
	m_pSaveButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C3/save2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C3/save1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C3/save1.png);}");
	m_pAllButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C3/all0.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C3/all.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C3/all.png);}");

	m_pLabel->setStyleSheet("QLabel{border-image: url(:/new/prefix1/C3/anw.png);}");

}
void MainWindow::pinkclick()
{
	QPalette pa_title1;
	pa_title1.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/pink.png"));
	pTitleBar->setPalette(pa_title1);
	pTitleBar->setAutoFillBackground(true);

	QImage *ppm = new QImage(":/new/prefix1/C4/5.png");
	m_pIconLabel->setPixmap(QPixmap::fromImage(*ppm));
	m_pIconLabel->setScaledContents(true);
	setWindowIcon(QIcon(":/new/prefix1/C4/5.png"));
	pSystemTray->setIcon(QIcon(":/new/prefix1/C4/5.png"));

	QPalette pa_title;
	pa_title.setBrush(QPalette::Background, QPixmap(":/new/prefix1/C4/pinkbk.jpg"));
	setPalette(pa_title);
	setAutoFillBackground(true);

	m_pMinimizeButton->setFlat(true);
	m_pMaximizeButton->setFlat(true);
	m_pCloseButton->setFlat(true);
	m_pClothButton->setFlat(true);

	m_pOpenButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C4/open3.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C4/open2.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C4/open2.png);}");
	m_pJudgeButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C4/judge2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C4/judge1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C4/judge1.png);}");
	m_pEnlargeButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C4/l2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C4/l1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C4/l1.png);}");
	m_pShrinkButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C4/s2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C4/s.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C4/s.png);}");
	m_pDeleteButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C4/delete2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C4/delete1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C4/delete1.png);}");
	m_pRotatelButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C4/rotatel2 .png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C4/rotatel1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C4/rotatel1.png);}");
	m_pRotaterButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C4/rotater2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C4/rotater1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C4/rotater1.png);}");
	m_pPrintButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C4/print2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C4/print1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C4/print1.png);}");
	m_pSaveButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C4/save2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C4/save1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C4/save1.png);}");
	m_pAllButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C4/all0.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C4/all.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C4/all.png);}");

	m_pLabel->setStyleSheet("QLabel{border-image: url(:/new/prefix1/C4/anw.png);}");
}
void MainWindow::yellowclick()
{
	//CommonHelper::setStyle(":/MainWindow/Resources/stylegl.qss");
	QPalette pa_title1;
	pa_title1.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/golden.png"));
	pTitleBar->setPalette(pa_title1);
	pTitleBar->setAutoFillBackground(true);

	QImage *ppm = new QImage(":/new/prefix1/C5/5.png");
	m_pIconLabel->setPixmap(QPixmap::fromImage(*ppm));
	m_pIconLabel->setScaledContents(true);
	setWindowIcon(QIcon(":/new/prefix1/C5/5.png"));

	QPalette pa_title;
	pa_title.setBrush(QPalette::Background, QPixmap(":/new/prefix1/C5/yellowbk.jpg"));
	setPalette(pa_title);
	setAutoFillBackground(true);

	m_pMinimizeButton->setFlat(true);
	m_pMaximizeButton->setFlat(true);
	m_pCloseButton->setFlat(true);
	m_pClothButton->setFlat(true);

	m_pOpenButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C5/open3.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C5/open2.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C5/open2.png);}");
	m_pJudgeButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C5/judge2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C5/judge1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C5/judge1.png);}");
	m_pEnlargeButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C5/l2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C5/l1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C5/l1.png);}");
	m_pShrinkButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C5/s2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C5/s.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C5/s.png);}");
	m_pDeleteButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C5/delete2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C5/delete1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C5/delete1.png);}");
	m_pRotatelButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C5/rotatel2 .png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C5/rotatel1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C5/rotatel1.png);}");
	m_pRotaterButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C5/rotater2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C5/rotater1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C5/rotater1.png);}");
	m_pPrintButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C5/print2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C5/print1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C5/print1.png);}");
	m_pSaveButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C5/save2.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C5/save1.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C5/save1.png);}");
	m_pAllButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/C5/all0.png);}"
		"QPushButton:hover{border-image: url(:/new/prefix1/C5/all.png);}"
		"QPushButton:pressed{border-image: url(:/new/prefix1/C5/all.png);}");

	m_pLabel->setStyleSheet("QLabel{border-image: url(:/new/prefix1/C5/anw.png);}");
	pSystemTray->setIcon(QIcon(":/new/prefix1/C5/5.png"));
}
void MainWindow::blackclick()
{
	QPalette pa_title1;
	pa_title1.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/black.png"));
	pTitleBar->setPalette(pa_title1);
	pTitleBar->setAutoFillBackground(true);

	QImage *ppm = new QImage(":/MainWindow/Resources/6.png");
	m_pIconLabel->setPixmap(QPixmap::fromImage(*ppm));
	m_pIconLabel->setScaledContents(true);
	setWindowIcon(QIcon(":/MainWindow/Resources/6.png"));

	QPalette pa_title;
	pa_title.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/blackbk.jpg"));
	setPalette(pa_title);
	setAutoFillBackground(true);

	m_pOpenButton->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/open3.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/open2.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/open2.png);}");

	m_pJudgeButton->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/judge2.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/judge1.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/judge1.png);}");

	m_pEnlargeButton->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/l1.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/l2.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/l2.png);}");
	m_pShrinkButton->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/s.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/s2.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/s2.png);}");
	m_pDeleteButton->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/delete1.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/delete2.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/delete2.png);}");
	m_pRotatelButton->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/rotatel1.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/rotatel2.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/rotatel2.png);}");
	m_pRotaterButton->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/rotater1.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/rotater2.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/rotater2.png);}");
	m_pPrintButton->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/print1.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/print2.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/print2.png);}");
	m_pSaveButton->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/save1.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/save2.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/save2.png);}");
	m_pAllButton->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/all0.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/all.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/all.png);}");
	m_pMinimizeButton->setFlat(false);
	m_pMaximizeButton->setFlat(false);
	m_pCloseButton->setFlat(false);
	m_pClothButton->setFlat(false);
	m_pLabel->setStyleSheet("QLabel{border-image: url(:/MainWindow/Resources/anw.png);}");
	pSystemTray->setIcon(QIcon(":/MainWindow/Resources/6.png"));
	//QPalette pa_title2;
	//pa_title2.setBrush(QPalette::Background, QPixmap(":/new/prefix1/C1/cbk.png"));
	//m_pPicLabel->setPalette(pa_title2);
	//m_pPicLabel->setWindowOpacity(0.5);//透明度
	//m_pPicLabel->setAutoFillBackground(true);
}








