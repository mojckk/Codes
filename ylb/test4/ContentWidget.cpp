#include "ContentWidget.h"

QLabel *m_pPicLabel;
ContentWidget::ContentWidget(QWidget *parent) { InitUI(); }
ContentWidget::~ContentWidget() {}

void ContentWidget::InitUI()
{
	setFixedHeight(66666);
	m_pNextButton = new QPushButton(this);
	m_pLastButton = new QPushButton(this);
	m_pPicLabel = new QLabel(this);

	//m_pPicLabel->installEventFilter(this);

	m_pNextButton->setObjectName("m_pNextButton");
	m_pLastButton->setObjectName("m_pLastButton");
	m_pPicLabel->setObjectName("m_pPicLabel");
	m_pPicLabel->clear();
	m_pPicLabel->setFixedSize(900,680);
	m_pPicLabel->setAlignment(Qt::AlignCenter);
	m_pNextButton->setFixedSize(100, 100);
	m_pLastButton->setFixedSize(100, 100);
	m_pNextButton->setToolTip(QStringLiteral("下一张"));
	m_pLastButton->setToolTip(QStringLiteral("上一张"));

	QHBoxLayout *pLayout = new QHBoxLayout(this);
	pLayout->setSpacing(0);
	pLayout->setContentsMargins(0, 0, 0, 0);
	pLayout->addSpacing(5);
	pLayout->addStretch();
	pLayout->addWidget(m_pLastButton);
	pLayout->addWidget(m_pPicLabel);
	pLayout->addWidget(m_pNextButton);
	pLayout->addStretch();
	setLayout(pLayout);

	m_pLastButton->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/ln2.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/last1.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/last1.png);}");
	m_pNextButton->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/ln2.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/next1.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/next1.png);}");

	connect(m_pNextButton, SIGNAL(clicked()), this, SLOT(NextSlot()));
	connect(m_pLastButton, SIGNAL(clicked()), this, SLOT(LastSlot()));
}

void ContentWidget::loadImageResource(void)
{
	m_pPicLabel->setPixmap(imageViewer->pixmap);
	m_pPicLabel->resize(imageViewer->size);
	//setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - QImageViewer"));
}

void ContentWidget::LastSlot()
{
	int ret = imageViewer->last();
	g_isReadImg = true;
	if (ret) {
		CMessageBox warn(QString(QStringLiteral("警告")),
			QStringLiteral("请打开FOB图片!"), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	QFileInfo fi = QFileInfo(m_filename);
	m_pfilename = fi.fileName();
	m_pIndex->clear();
	m_pIndex->setText(m_pfilename);
	loadImageResource();
}
void ContentWidget::NextSlot()
{
	int ret = imageViewer->next();
	g_isReadImg = true;
	if (ret) {
		CMessageBox warn(QString(QStringLiteral("警告")), 
			QStringLiteral("请打开FOB图片!"), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	QFileInfo fi = QFileInfo(m_filename);
	m_pfilename = fi.fileName();
	m_pIndex->clear();
	m_pIndex->setText(m_pfilename);
	loadImageResource();
}
void ContentWidget::mousePressEvent(QMouseEvent *event)
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