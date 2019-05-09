#include "SkinWidget.h"
QPushButton *m_pblack;
QPushButton *m_pgreen;
QPushButton *m_pred;
QPushButton *m_ppink;
QPushButton *m_pblue;
QPushButton *m_pyellow;
SkinWidget::SkinWidget(QWidget *parent)
{
	InitUI();
}
SkinWidget::~SkinWidget() {}

void SkinWidget::InitUI()
{
	this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
	this->setFixedSize(300, 230);
	
	setWindowOpacity(1);//透明度
	setAttribute(Qt::WA_TranslucentBackground);//无边框透明

	QFont ft_subject;
	ft_subject.setPixelSize(14);
	ft_subject.setFamily(QStringLiteral("微软雅黑"));
	ft_subject.setBold(false);
	QPalette pa_subject;
	pa_subject.setColor(QPalette::ButtonText, Qt::white);
	
	m_pblack = new QPushButton(this);
	m_pgreen = new QPushButton(this);
	m_pred = new QPushButton(this);
	m_ppink = new QPushButton(this);
	m_pblue = new QPushButton(this);
	m_pyellow = new QPushButton(this);

	m_pblack->setFixedSize(80, 80);
	m_pgreen->setFixedSize(80, 80);
	m_pred->setFixedSize(80, 80);
	m_ppink->setFixedSize(80, 80);
	m_pblue->setFixedSize(80, 80);
	m_pyellow->setFixedSize(80, 80);


	subjectWidget = new QWidget;
	subjectWidget->setFixedSize(280, 180);
	QGridLayout *subjectLayout = new QGridLayout;
	// 设置水平间距
	subjectLayout->setHorizontalSpacing(10);
	// 设置垂直间距
	subjectLayout->setVerticalSpacing(10);
	// 设置外间距
	subjectLayout->setContentsMargins(5, 20, 5, 5);

	subjectLayout->addWidget(m_pblack, 1, 0, 1,1); 
	subjectLayout->addWidget(m_pgreen, 1, 1, 1, 1);
	subjectLayout->addWidget(m_pred, 1, 2, 1, 1);
	subjectLayout->addWidget(m_ppink, 2, 0, 1, 1);
	subjectLayout->addWidget(m_pblue, 2, 1, 1, 1);
	subjectLayout->addWidget(m_pyellow, 2, 2, 1, 1);

	m_pblack->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/skin_subject_black_logo.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/skin_subject_black_logo1.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/skin_subject_black_logo1.png);}");
	m_pgreen->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/skin_subject_green_logo.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/skin_subject_green_logo1.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/skin_subject_green_logo1.png);}");
	m_ppink->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/skin_subject_pink_logo.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/skin_subject_pink_logo1.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/skin_subject_pink_logo1.png);}");
	m_pred->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/skin_subject_red_logo.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/skin_subject_red_logo1.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/skin_subject_red_logo1.png);}");
	m_pblue->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/skin_subject_blue_logo.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/skin_subject_blue_logo1.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/skin_subject_blue_logo1.png);}");
	m_pyellow->setStyleSheet("QPushButton{border-image: url(:/MainWindow/Resources/skin_subject_golden_logo.png);}"
		"QPushButton:hover{border-image: url(:/MainWindow/Resources/skin_subject_golden_logo1.png);}"
		"QPushButton:pressed{border-image: url(:/MainWindow/Resources/skin_subject_golden_logo1.png);}");
	m_pblack->setToolTip(QStringLiteral("炫酷黑"));
	m_pgreen->setToolTip(QStringLiteral("清新绿"));
	m_pred->setToolTip(QStringLiteral("官方红"));
	m_ppink->setToolTip(QStringLiteral("可爱粉"));
	m_pblue->setToolTip(QStringLiteral("天际蓝"));
	m_pyellow->setToolTip(QStringLiteral("夕阳金"));
	this->setLayout(subjectLayout);
	//SetSkin(m_skinType);

	connect(m_pblack, SIGNAL(clicked(bool)), this, SLOT(blackclick()));
	connect(m_pgreen, SIGNAL(clicked(bool)), this, SLOT(greenclick()));
	connect(m_pred, SIGNAL(clicked(bool)), this, SLOT(redclick()));
	connect(m_ppink, SIGNAL(clicked(bool)), this, SLOT(pinkclick()));
	connect(m_pblue, SIGNAL(clicked(bool)), this, SLOT(blueclick()));
	connect(m_pyellow, SIGNAL(clicked(bool)), this, SLOT(yellowclick()));
}

void SkinWidget::paintEvent(QPaintEvent * e)
{
	if (g_index == 1)
	{
		QPixmap pixmap(":/MainWindow/Resources/skin_widget_bbk.png");
		QPainter painter(this);
		painter.drawPixmap(0, 0, pixmap);
    }
	else if (g_index == 2)
	{
		QPixmap pixmap(":/new/prefix1/C1/skin_widget_gbk.png");
		QPainter painter(this);
		painter.drawPixmap(0, 0, pixmap);
	}
	else if (g_index == 3)
	{
		QPixmap pixmap(":/new/prefix1/C2/skin_widget_blbk.png");
		QPainter painter(this);
		painter.drawPixmap(0, 0, pixmap);
	}
	else if (g_index == 4)
	{
		QPixmap pixmap(":/new/prefix1/C3/skin_widget_rbk.png");
		QPainter painter(this);
		painter.drawPixmap(0, 0, pixmap);
	}
	else if (g_index == 5)
	{
		QPixmap pixmap(":/new/prefix1/C4/skin_widget_bbk.png");
		QPainter painter(this);
		painter.drawPixmap(0, 0, pixmap);
	}
	else if(g_index == 6)
	{
		QPixmap pixmap(":/new/prefix1/C5/skin_widget_glbk.png");
		QPainter painter(this);
		painter.drawPixmap(0, 0, pixmap);
	}
}
void SkinWidget::blueclick()
{
	g_index = 3;
	update();
}
void SkinWidget::greenclick()
{
	g_index = 2;
	update();
}
void SkinWidget::redclick()
{
	g_index = 4;
	update();
}
void SkinWidget::pinkclick()
{
	g_index = 5;
	update();
}
void SkinWidget::yellowclick()
{
	g_index = 6;
	update();
}
void SkinWidget::blackclick()
{
	g_index = 1;
	update();
}