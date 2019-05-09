#include "State_Bar.h"
QLabel *m_pLabel;
QLineEdit *m_pIndex;
QTextBrowser  *m_pText;
QProgressBar *m_pProgressBar;

StateBar::StateBar(QWidget *parent) 
{
	setFixedHeight(180);
	m_pLabel = new QLabel(this);
	m_pText = new QTextBrowser(this);
	m_pLabel->setObjectName("m_pLabel");

	m_pNamelabel = new QLabel(this);
	m_pNamelabel->setText(QStringLiteral("µ±Ç°Í¼Æ¬Ãû³Æ"));
	m_pNamelabel->setStyleSheet("color:white");//ÎÄ±¾ÑÕÉ«  
	m_pNamelabel->setFont(QFont("Î¢ÈíÑÅºÚ", 14, QFont::Black));
	m_pNamelabel->setWordWrap(true);
	m_pNamelabel->setAlignment(Qt::AlignVCenter);

	m_pText->setAlignment(Qt::AlignVCenter);
	m_pText->setStyleSheet("border-width:0; border-style:outset; font:12pt; font-weight:1900; font-family:Î¢ÈíÑÅºÚ;color:rgb(0,0,0); ");
	m_pText->setAlignment(Qt::AlignCenter);
	m_pIndex = new QLineEdit(this);
	m_pIndex->setReadOnly(true);										
	m_pIndex->setAlignment(Qt::AlignVCenter| Qt::AlignHCenter);
	m_pIndex->setMaxLength(100);
	m_pIndex->setStyleSheet("color:black");//ÎÄ±¾ÑÕÉ«  
	m_pIndex->setFont(QFont("Î¢ÈíÑÅºÚ", 10, QFont::Bold));
	m_pLabel->setFixedSize(350, 90);
	m_pIndex->setFixedSize(270, 25);
	m_pNamelabel->setFixedSize(270, 40);
	m_pNamelabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

	QVBoxLayout *vLayout = new QVBoxLayout();
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0, 0, 0, 0);
	vLayout->addSpacing(5);
	vLayout->addStretch();
	vLayout->addWidget(m_pNamelabel);
	vLayout->addWidget(m_pIndex);
	vLayout->addStretch();

	QVBoxLayout *vLayout1 = new QVBoxLayout();
	m_pProgressBar = new QProgressBar(this);
	m_pProgressBar->setFixedSize(230, 20);
	m_pProgressBar->setFixedSize(200, 20);
	m_pProgressBar->setOrientation(Qt::Horizontal);
	m_pProgressBar->setVisible(false);

	//m_pProgressBar->show();
	vLayout1->addStretch();
	vLayout1->addWidget(m_pText);
	vLayout1->addWidget(m_pProgressBar);
	vLayout1->addStretch();


	m_pText->setEnabled(true);
	m_pText->setFixedSize(200, 100);

	m_pIndex->setEnabled(false);
	QHBoxLayout *pLayout = new QHBoxLayout(this);
	pLayout->setSpacing(0);
	pLayout->setContentsMargins(0, 0, 0, 0);
	pLayout->addSpacing(5);
	pLayout->addStretch();
	pLayout->addStretch();
	pLayout->addStretch();
	pLayout->addStretch();
	pLayout->addStretch();
	pLayout->addStretch();
	pLayout->addWidget(m_pLabel);
	pLayout->addLayout(vLayout1);
	pLayout->addStretch();
	pLayout->addLayout(vLayout);
	pLayout->addStretch();
	pLayout->addStretch();
	pLayout->addStretch();
	pLayout->addStretch();
	pLayout->addStretch();
	pLayout->addStretch();
	setLayout(pLayout);
	
	m_pLabel->setStyleSheet("QLabel{border-image: url(:/MainWindow/Resources/anw.png);}");
}
StateBar::~StateBar()
{
}
