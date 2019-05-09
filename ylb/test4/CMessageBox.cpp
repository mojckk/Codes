#include "CMessageBox.h"
CMessageBox::CMessageBox(QWidget *parent)
{
	InitUI(QStringLiteral("¾¯¸æ"), "");
	QList<QAbstractButton *> list = m_pButtonBox->buttons();
	if (list.size() <= 1)
		this->exec();
}
CMessageBox::~CMessageBox(){}
CMessageBox::CMessageBox(QString title, QString content, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
	InitUI(title, content, buttons, defaultButton);
	QList<QAbstractButton *> list = m_pButtonBox->buttons();
	if (list.size() <= 1)
		this->exec();
}

void CMessageBox::mousePressEvent(QMouseEvent * event)
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
void CMessageBox::InitUI(QString title, QString content, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
	this->setModal(true);
	if (g_index == 1)
	{
		this->setWindowIcon(QIcon(":/MainWindow/Resources/6.png"));
	}
	else if (g_index == 2)
	{
		this->setWindowIcon(QIcon(":/new/prefix1/C1/4.png"));
	}
	else if (g_index == 3)
	{
		this->setWindowIcon(QIcon(":/new/prefix1/C2/5.png"));
	}
	else if (g_index == 4)
	{
		this->setWindowIcon(QIcon(":/new/prefix1/C3/5.png"));
	}
	else if (g_index == 5)
	{
		this->setWindowIcon(QIcon(":/new/prefix1/C4/5.png"));
	}
	else if (g_index == 6)
	{
		this->setWindowIcon(QIcon(":/new/prefix1/C5/5.png"));
	}
	this->setFixedSize(300, 200);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setContentsMargins(0, 0, 0, 0);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->setSpacing(0);
	mainLayout->setMargin(0);
	mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
	this->setLayout(mainLayout);
	QPalette pp;
	pp.setColor(QPalette::Background, QColor("#fafafa"));
	this->setAutoFillBackground(true);
	this->setPalette(pp);
	QWidget *m_pTitleWidget = new QWidget;
	m_pTitleWidget->setFixedSize(300, 42);
	QHBoxLayout *titleLayout = new QHBoxLayout;
	m_pTitleWidget->setLayout(titleLayout);
	titleLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	titleLayout->setSpacing(0);
	titleLayout->setContentsMargins(0, 0, 0, 0);

	mainLayout->addWidget(m_pTitleWidget);
	QLabel *m_pTitleIconLabel = new QLabel;
	m_pTitleLabel = new QLabel;
	QPushButton *m_pCloseButton = new QPushButton;

	m_pTitleIconLabel->setFixedSize(35, 35);
	m_pTitleIconLabel->setScaledContents(true);
	if (g_index == 1)
	{
		m_pTitleIconLabel->setPixmap(QPixmap(":/MainWindow/Resources/6.png"));
		QPalette pa_title;
		pa_title.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/black.png"));
		m_pTitleWidget->setPalette(pa_title);
		m_pTitleWidget->setAutoFillBackground(true);
	}
	else if (g_index == 2)
	{
		m_pTitleIconLabel->setPixmap(QPixmap(":/new/prefix1/C1/4.png"));
		QPalette pa_title;
		pa_title.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/green.png"));
		m_pTitleWidget->setPalette(pa_title);
		m_pTitleWidget->setAutoFillBackground(true);
	}
	else if (g_index == 3)
	{
		m_pTitleIconLabel->setPixmap(QPixmap(":/new/prefix1/C2/5.png"));
		QPalette pa_title;
		pa_title.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/blue.png"));
		m_pTitleWidget->setPalette(pa_title);
		m_pTitleWidget->setAutoFillBackground(true);
	}
	else if (g_index == 4)
	{
		m_pTitleIconLabel->setPixmap(QPixmap(":/new/prefix1/C3/5.png"));
		QPalette pa_title;
		pa_title.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/red.png"));
		m_pTitleWidget->setPalette(pa_title);
		m_pTitleWidget->setAutoFillBackground(true);
	}
	else if (g_index == 5)
	{
		m_pTitleIconLabel->setPixmap(QPixmap(":/new/prefix1/C4/5.png"));
		QPalette pa_title;
		pa_title.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/pink.png"));
		m_pTitleWidget->setPalette(pa_title);
		m_pTitleWidget->setAutoFillBackground(true);
	}
	else if (g_index == 6)
	{
		m_pTitleIconLabel->setPixmap(QPixmap(":/new/prefix1/C5/5.png"));
		QPalette pa_title;
		pa_title.setBrush(QPalette::Background, QPixmap(":/MainWindow/Resources/golden.png"));
		m_pTitleWidget->setPalette(pa_title);
		m_pTitleWidget->setAutoFillBackground(true);
	}
	
	titleLayout->addSpacing(10);
	titleLayout->addWidget(m_pTitleIconLabel);
	titleLayout->addSpacing(10);
	QFont ft_title;
	ft_title.setPixelSize(23);
	ft_title.setFamily(QStringLiteral("Î¢ÈíÑÅºÚ"));
	ft_title.setBold(true);
	QPalette pa_title;
	pa_title.setColor(QPalette::Foreground, Qt::white);
	m_pTitleLabel->setFixedSize(150, 50);
	m_pTitleLabel->setText(title);
	m_pTitleLabel->setFont(ft_title);
	m_pTitleLabel->setPalette(pa_title);
	titleLayout->addWidget(m_pTitleLabel);

	titleLayout->addStretch(1);
	m_pCloseButton->setFixedSize(30, 30);
	m_pCloseButton->setStyleSheet("QPushButton{background-image: url(:/MainWindow/Resources/sys_dlg_close3.png);border: none;}"
		"QPushButton:hover{background-image: url(:/MainWindow/Resources/sys_dlg_close2.png);}"
		"QPushButton:pressed{background-image: url(:/MainWindow/Resources/sys_dlg_close1.png);}");
	connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(CloseSlot()));
	titleLayout->addWidget(m_pCloseButton);
	titleLayout->addSpacing(10);

	m_pTitleWidget->setAutoFillBackground(true);
	QFont ft;
	ft.setPixelSize(20);
	ft.setFamily(QStringLiteral("Î¢ÈíÑÅºÚ"));
	ft.setWeight(QFont::Bold);
	ft.setLetterSpacing(QFont::PercentageSpacing, 100);

	m_pButtonBox = new QDialogButtonBox(this);
	m_pButtonBox->setFont(ft);
	m_pButtonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));
	QList<QAbstractButton *> list = m_pButtonBox->buttons();
	for (int i = 0; i < list.size(); i++)
	{ 
		list[i]->setFixedSize(80, 40);
		list[i]->setFont(ft);
		list[i]->setStyleSheet("QPushButton{ border:1px solid #e1e1e2; background: white;}"
			"QPushButton::hover{border:1px solid #e1e1e2; background: #f6f6f8;}"
			"QPushButton::pressed{border:1px solid #e1e1e2; background: white;}");
	}

	m_pIconLabel = new QLabel(this);
	m_pLabel = new QLabel(this);

	if (g_index == 1)
	{
		QPixmap pixmap(":/MainWindow/Resources/blackww.png");
		m_pIconLabel->setPixmap(pixmap);
	}
	else if (g_index == 2)
	{
		QPixmap pixmap(":/MainWindow/Resources/greenww.png");
		m_pIconLabel->setPixmap(pixmap);
	}
	else if (g_index == 3)
	{
		QPixmap pixmap(":/MainWindow/Resources/blueww.png");
		m_pIconLabel->setPixmap(pixmap);
	}
	else if (g_index == 4)
	{
		QPixmap pixmap(":/MainWindow/Resources/redww.png");
		m_pIconLabel->setPixmap(pixmap);
	}
	else if (g_index == 5)
	{
		QPixmap pixmap(":/MainWindow/Resources/pinkww.png");
		m_pIconLabel->setPixmap(pixmap);
	}
	else if (g_index == 6)
	{
		QPixmap pixmap(":/MainWindow/Resources/goldww.png");
		m_pIconLabel->setPixmap(pixmap);
	}
	
	
	m_pIconLabel->setFixedSize(80, 80);
	m_pIconLabel->setScaledContents(true);

	m_pLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_pLabel->setObjectName("whiteLabel");
	m_pLabel->setOpenExternalLinks(true);
	
	m_pLabel->setFont(ft);
	m_pLabel->setText(content);	

	QWidget *mainWidget = new QWidget;
	mainWidget->setFixedSize(300, 150);
	QGridLayout *m_pGridLayout = new QGridLayout();
	m_pGridLayout->addWidget(m_pIconLabel, 0, 0, 2, 1, Qt::AlignVCenter);
	m_pGridLayout->addWidget(m_pLabel, 0, 1, 2, 1);
	m_pGridLayout->addWidget(m_pButtonBox, m_pGridLayout->rowCount(), 0, 1, m_pGridLayout->columnCount());
	m_pGridLayout->setSizeConstraint(QLayout::SetNoConstraint);
	m_pGridLayout->setHorizontalSpacing(10);
	m_pGridLayout->setVerticalSpacing(10);
	m_pGridLayout->setContentsMargins(10, 10, 10, 10);
	mainWidget->setLayout(m_pGridLayout);

	mainLayout->addWidget(mainWidget);
	connect(m_pButtonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
}
void CMessageBox::paintEvent(QPaintEvent *event)
{
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(0, 0, this->width() - 1, this->height() - 1);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	//painter.fillPath(path, QBrush(Qt::white));

	QColor color(0, 0, 0, 50);

	color.setAlpha(150 - qSqrt(1) * 50);
	painter.setPen(color);
	painter.drawPath(path);
}
void CMessageBox::onButtonClicked(QAbstractButton *button)
{
	int nResult = m_pButtonBox->standardButton(button);
	if (nResult == QDialogButtonBox::Yes || nResult == QDialogButtonBox::Ok)
	{
		this->accept();
	}
	this->hide();
}
