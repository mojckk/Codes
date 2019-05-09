#include "Tool_Bar.h"
#pragma comment(lib, "user32.lib")

QPushButton *m_pOpenButton;
QPushButton *m_pJudgeButton;
QPushButton *m_pDeleteButton;
QPushButton *m_pEnlargeButton;
QPushButton *m_pShrinkButton;
QPushButton *m_pRotatelButton;
QPushButton *m_pRotaterButton;
QPushButton *m_pPrintButton;
QPushButton *m_pSaveButton;
QPushButton *m_pAllButton;
QImageViewer *imageViewer;
extern QProgressBar *m_pProgressBar;
bool g_isReadImg = false;
bool g_isImgNULL = true;

ToolBar::ToolBar(QWidget *parent)
	: QWidget(parent)
{
	IniUI();
}
ToolBar::~ToolBar()
{
}

void ToolBar::IniUI()
{
	setFixedHeight(70);
	setStyleSheet("border:1px solid black;");
	imageViewer = new QImageViewer(this);

	m_pOpenButton = new QPushButton(this);
	m_pJudgeButton = new QPushButton(this);
	m_pDeleteButton = new QPushButton(this);
	m_pEnlargeButton = new QPushButton(this);
	m_pShrinkButton = new QPushButton(this);
	m_pRotatelButton = new QPushButton(this);
	m_pRotaterButton = new QPushButton(this);
	m_pPrintButton = new QPushButton(this);
	m_pSaveButton = new QPushButton(this);
	m_pAllButton = new QPushButton(this);

	m_pOpenButton->setObjectName("m_pOpenButton");
	m_pJudgeButton->setObjectName("m_pJudgeButton");
	m_pDeleteButton->setObjectName("m_pDeleteButton");
	m_pEnlargeButton->setObjectName("m_pEnlargeButton");
	m_pShrinkButton->setObjectName("m_pShrinkButton");
	m_pRotatelButton->setObjectName("m_pRotatelButton");
	m_pRotaterButton->setObjectName("m_pRotaterButton");
	m_pPrintButton->setObjectName("m_pPrintButton");
	m_pSaveButton->setObjectName("m_pSaveButton");
	m_pAllButton->setObjectName("m_pAllButton");

	m_pOpenButton->setFixedSize(195, 60);
	m_pJudgeButton->setFixedSize(160, 60);

	m_pEnlargeButton->setFixedSize(60, 60);
	m_pShrinkButton->setFixedSize(60, 60);
	m_pDeleteButton->setFixedSize(60, 60);
	m_pRotatelButton->setFixedSize(60, 60);
	m_pRotaterButton->setFixedSize(60, 60);

	m_pAllButton->setFixedSize(160, 60);
	m_pPrintButton->setFixedSize(60, 60);
	m_pSaveButton->setFixedSize(60, 60);

	m_pOpenButton->setToolTip(QStringLiteral("��FOBͼƬ"));
	m_pJudgeButton->setToolTip(QStringLiteral("�жϽ��"));
	m_pEnlargeButton->setToolTip(QStringLiteral("�Ŵ�"));
	m_pShrinkButton->setToolTip(QStringLiteral("��С"));
	m_pDeleteButton->setToolTip(QStringLiteral("ɾ��"));
	m_pRotatelButton->setToolTip(QStringLiteral("����90��"));
	m_pRotaterButton->setToolTip(QStringLiteral("����90��"));
	m_pPrintButton->setToolTip(QStringLiteral("�鿴���"));
	m_pSaveButton->setToolTip(QStringLiteral("������"));
	m_pAllButton->setToolTip(QStringLiteral("ȫ���ж�"));

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
	//m_pEnlargeButton->setStyleSheet("border:none;");

	QHBoxLayout *pLayout = new QHBoxLayout(this);
	pLayout->setSpacing(0);
	pLayout->setContentsMargins(0, 0, 0, 0);
	pLayout->addSpacing(5);
	pLayout->addWidget(m_pOpenButton);
	pLayout->addWidget(m_pJudgeButton);
	pLayout->addStretch();/*�����ʾ����*/
	pLayout->addWidget(m_pEnlargeButton);
	pLayout->addWidget(m_pShrinkButton);
	pLayout->addWidget(m_pDeleteButton);
	pLayout->addWidget(m_pRotatelButton);
	pLayout->addWidget(m_pRotaterButton);
	pLayout->addStretch();/*�����ʾ����*/
	pLayout->addWidget(m_pAllButton);
	pLayout->addWidget(m_pPrintButton);
	pLayout->addWidget(m_pSaveButton);
	setLayout(pLayout);

	connect(m_pOpenButton, SIGNAL(clicked(bool)), this, SLOT(openPic()));
	connect(m_pJudgeButton, SIGNAL(clicked(bool)), this, SLOT(judgePic()));
	connect(m_pEnlargeButton, SIGNAL(clicked(bool)), this, SLOT(enlargePic()));
	connect(m_pShrinkButton, SIGNAL(clicked(bool)), this, SLOT(shrinkPic()));
	connect(m_pDeleteButton, SIGNAL(clicked(bool)), this, SLOT(deletePic()));
	connect(m_pRotatelButton, SIGNAL(clicked(bool)), this, SLOT(rotatelPic()));
	connect(m_pRotaterButton, SIGNAL(clicked(bool)), this, SLOT(rotaterPic()));

	/*connect(m_pRotatelButton, SIGNAL(clicked(bool)), this, SIGNAL(rotatel()));
	connect(m_pRotaterButton, SIGNAL(clicked(bool)), this, SIGNAL(rotater()));*/

	connect(m_pAllButton, SIGNAL(clicked(bool)), this, SLOT(allCheck()));
	connect(m_pPrintButton, SIGNAL(clicked(bool)), this, SLOT(readAwn()));
	connect(m_pSaveButton, SIGNAL(clicked(bool)), this, SLOT(savePic()));
}

void ToolBar::judgePic()
{	

	if (g_isReadImg)
	{
		m_pText->clear();
		m_pProgressBar->reset();
		g_isImgNULL = false;

		int size = 6;
		QString cola("black");
		QString strMsga(QStringLiteral("����"));
		QString aligna1("center");
		QString stra = QString("<p align=\"%4\"><font size=\"%1\" color=\"%2\">%3</font></p>").arg(size).arg(cola).arg(strMsga).arg(aligna1);
		int size1 = 1;
		QString cola1("white");
		QString strMsga1(" aaaa");
		QString aligna11("center");
		QString stra0 = QString("<p align=\"%4\"><font size=\"%1\" color=\"%2\">%3</font></p>").arg(size1).arg(cola1).arg(strMsga1).arg(aligna11);

		int sizeb = 6;
		QString colb("black");
		QString strMsgb(QStringLiteral("����"));
		QString alignab("center");
		QString strb = QString("<p align=\"%4\"><font size=\"%1\" color=\"%2\">%3</font></p>").arg(sizeb).arg(colb).arg(strMsgb).arg(alignab);

		int sizec = 6;
		QString colc("black");
		QString strMsgc(QStringLiteral("����"));
		QString alignac("center");
		QString strc = QString("<p align=\"%4\"><font size=\"%1\" color=\"%2\">%3</font></p>").arg(sizec).arg(colc).arg(strMsgc).arg(alignac);

		int sized = 6;
		QString cold("black");
		QString strMsgd(QStringLiteral("FOB������Ⱦ"));
		QString alignad("center");
		QString strd = QString("<p align=\"%4\"><font size=\"%1\" color=\"%2\">%3</font></p>").arg(sized).arg(cold).arg(strMsgd).arg(alignad);

		int sizee = 6;
		QString cole("black");
		QString strMsge(QStringLiteral("δ������"));
		QString alignae("center");
		QString stre = QString("<p align=\"%4\"><font size=\"%1\" color=\"%2\">%3</font></p>").arg(sizee).arg(cole).arg(strMsge).arg(alignae);

		int sizef = 6;
		QString colf("black");
		QString strMsgf(QStringLiteral("���ʧ��"));
		QString alignaf("center");
		QString strf = QString("<p align=\"%4\"><font size=\"%1\" color=\"%2\">%3</font></p>").arg(sizef).arg(colf).arg(strMsgf).arg(alignaf);

		QByteArray tmp = (imageViewer->filename).toLocal8Bit();
		char* fname = tmp.data();
		int result = DectFob(fname, 1);
		if (result == 15)
		{
			CMessageBox warn(QString(QStringLiteral("����")), QStringLiteral(".ini�ļ���ʧ"),
				QMessageBox::Ok, QMessageBox::Ok);
				QWidget *pWindow = this->window();
				pWindow->close();
		}
		switch (result)
		{
		case 1:
			m_pText->append(stra0);
			m_pText->append(stra);		
			break;
		case 2:
			m_pText->append(stra0);
			m_pText->append(strb);
			break;
		case 3:
			m_pText->append(stra0);
			m_pText->append(strc);
			break;
		case 74:
			m_pText->append(stra0);
			m_pText->append(strd);
			break;
		case 72:
			m_pText->append(stra0);
			m_pText->append(stre);
			break;
		default:
			m_pText->append(stra0);
			m_pText->append(strf);
			break;
		}
		g_isReadImg = false;
		//���ý�����
		m_pProgressBar->setMinimum(0);  // ��Сֵ
		m_pProgressBar->setMaximum(1);  // ���ֵ							
		m_pProgressBar->setAlignment(Qt::AlignVCenter| Qt::AlignHCenter);  // �ı����뷽ʽ
		m_pProgressBar->setValue(1);  // ��ǰ����
		double dProgress = (m_pProgressBar->value() - m_pProgressBar->minimum()) * 100.0
			/ (m_pProgressBar->maximum() - m_pProgressBar->minimum());
		m_pProgressBar->setFormat(QString::fromLocal8Bit("������").arg(QString::number(dProgress, 'f', 1)));
		m_pProgressBar->setVisible(true);
	}
	else{
		CMessageBox warn(QString(QStringLiteral("����")), QStringLiteral("δ�򿪻����ͼƬ"),
			QMessageBox::Ok);
		return;
	}
}

void ToolBar::readAwn()
{
}

void ToolBar::allCheck()
{
	QString FilePath = QFileDialog::getExistingDirectory();
	if (FilePath.isEmpty())
		return;
	m_pProgressBar->setVisible(true);
	g_isImgNULL = false;
	m_pText->clear();

	QDir *dir = new QDir(FilePath);
	QStringList filter;
	filter << "*.bmp" << "*.jpg" << "*.png" << "*.jpeg";
	dir->setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));

	imageViewer->index = -1;
	imageViewer->angle = 0;
	imageViewer->size = QSize(0, 0);
	imageViewer->filename.clear();
	imageViewer->path.clear();

	imageViewer->filename = fileInfo->at(0).filePath();
	m_filename = imageViewer->filename;
	getFileInfoList();
	upgradeFileInfo(imageViewer->filename, imageViewer->angle, 10);
	m_pPicLabel->setPixmap(imageViewer->pixmap);
	m_pPicLabel->resize(imageViewer->size);
	QFileInfo fi = QFileInfo(m_filename);
	m_pfilename = fi.fileName();
	m_pIndex->clear();
	m_pIndex->setText(m_pfilename);

	QByteArray tmp = FilePath.toLocal8Bit();
	char* fname = tmp.data();
	vector<string> AllFiles;
	GetMulFormatFiles(string(fname), AllFiles, 4, ".bmp", ".jpg", ".png", ".jpeg");

	int size = 1;
	QString col("gray");
	QString strMsg(FilePath);
	QString str2 = QString("<p><font size=\"%1\" color=\"%2\">%3</font></p>").arg(size).arg(col).arg(strMsg);
	
	//����������
	int AllFilesNum = AllFiles.size();
	m_pProgressBar->setMinimum(0);  // ��Сֵ
	m_pProgressBar->setMaximum(AllFilesNum - 1);  // ���ֵ							
	m_pProgressBar->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);  // �ı����뷽ʽ
	
	for (int i = 0; i < AllFiles.size(); i++)
	{
		int size = 1;
		QString col("gray");
		QString strMsg(QString::fromLocal8Bit((AllFiles[i]+ "\n").c_str()));
		QString str1 = QString("<p><font size=\"%1\" color=\"%2\">%3</font></p>").arg(size).arg(col).arg(strMsg);
		QString strMsg3(" ");
		QString str3 = QString("<p><font size=\"%1\" color=\"%2\">%3</font></p>").arg(size).arg(col).arg(strMsg3);

		int result = DectFob(AllFiles[i].data(), 1);
		if (result == 15)
		{
			CMessageBox warn(QString(QStringLiteral("����")), QStringLiteral(".ini�ļ���ʧ"),
				QMessageBox::Ok, QMessageBox::Ok);
			QWidget *pWindow = this->window();
			pWindow->close();
		}
		switch (result)
		{
		case 1:
			m_pText->append(QStringLiteral("����-�ļ�����"));
			m_pText->append(str1);
			m_pText->append(str3);
			break;
		case 2:
			m_pText->append(QStringLiteral("����-�ļ�����"));
			m_pText->append(str1);
			m_pText->append(str3);	
			break;
		case 3:
			m_pText->append(QStringLiteral("����-�ļ�����"));
			m_pText->append(str1);
			m_pText->append(str3);
			break;
		case 74:
			m_pText->append(QStringLiteral("FOB������Ⱦ-�ļ�����"));
			m_pText->append(str1);
			m_pText->append(str3);
			break;
		case 72:
			m_pText->append(QStringLiteral("δ������-�ļ�����"));
			m_pText->append(str1);
			m_pText->append(str3);
			break;
		default:
			m_pText->append(QStringLiteral("���ʧ��-ͼƬ��Դ��"));
			m_pText->append(str2);
			m_pText->append(str3);
			break;
		}
		m_pText->repaint();

		double ProgressBarValue =  double(i) ;
		m_pProgressBar->setValue(ProgressBarValue);  // ��ǰ����
		double dProgress = (m_pProgressBar->value() - m_pProgressBar->minimum()) * 100.0
			/ (m_pProgressBar->maximum() - m_pProgressBar->minimum()) ;
		m_pProgressBar->setFormat(QString::fromLocal8Bit("�����ȣ�%1%").arg(QString::number(dProgress, 'f', 1)));		
	}	
	m_pProgressBar->setFormat(QString::fromLocal8Bit("������").arg(QString::number(0, 'f', 1)));
	
}

void ToolBar::savePic()
{
}

void ToolBar::openPic()
{
	int ret = imageViewer->openImageFile(tr("Select image:"),
		"E:\\Documents\\Picture",
		tr("Images (*.jpg *.jpeg *.png *.bmp *.gif)"));
	if (ret) {
		CMessageBox warn(QString(QStringLiteral("����")), QStringLiteral("��ͼƬʧ��"), 
	    QMessageBox::Ok, QMessageBox::Ok);
		g_isImgNULL = true;
		return;
	}
	g_isImgNULL = false;
	g_isReadImg = true;
	loadImageResource();//��ʾ
	QFileInfo fi = QFileInfo(m_filename);
	m_pfilename = fi.fileName();
	m_pIndex->clear();
	m_pIndex->setText(m_pfilename);
}

void ToolBar::deletePic()
{
	if (!QFile(imageViewer->filename).exists()) {
		CMessageBox warn(QString(QStringLiteral("����")), QStringLiteral("���FOBͼƬ��"),
			QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	CMessageBox warn(QString(QStringLiteral("����")), QStringLiteral("ȷ��Ҫɾ����"),
		QMessageBox::Yes | QMessageBox::No,QMessageBox::Ok);

	if (warn.exec() == QDialog::Accepted) {
		int ret = imageViewer->delImageFile();
		if (ret) {
			CMessageBox warn(QString(QStringLiteral("����")), QStringLiteral("ɾ��ʧ�ܣ�"),
				QMessageBox::Ok, QMessageBox::Ok);
			return;
		}
		m_pPicLabel->clear();
		g_isImgNULL = true;
	}
	else
	{
		return;
	}
	setWindowTitle(QStringLiteral("FOB��⹤��"));
}

void ToolBar::enlargePic()
{
	int ret = imageViewer->zoomIn();
	if (ret) {
		CMessageBox warn(QString(QStringLiteral("����")), QStringLiteral("���FOBͼƬ!"),
			QMessageBox::Ok, QMessageBox::Ok);
		return;
	}

	loadImageResource();
}

void ToolBar::shrinkPic()
{
	int ret = imageViewer->zoomOut();
	if (ret) {
		CMessageBox warn(QString(QStringLiteral("����")), QStringLiteral("���FOBͼƬ!"),
			QMessageBox::Ok, QMessageBox::Ok);
		return;
	}

	loadImageResource();
}

void ToolBar::rotatelPic()
{
	if (!g_isImgNULL)
	{
		QImage img = imageViewer->pixmap.toImage();
		Mat Src = QImage2cvMat(img);
		Mat Dst;
		transpose(Src, Dst);
		flip(Dst, Dst, 0);
		QImage leftRotateImg = cvMat2QImage(Dst);
		imageViewer->pixmap = QPixmap::fromImage(leftRotateImg);
		m_pPicLabel->setPixmap(QPixmap::fromImage(leftRotateImg));
		m_pPicLabel->resize(imageViewer->size);
	}
	else
	{
		CMessageBox warn(QString(QStringLiteral("����")), QStringLiteral("���FOBͼƬ!"),
			QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
}

void ToolBar::rotaterPic()
{
	if (!g_isImgNULL)
	{
		QImage img = imageViewer->pixmap.toImage();
		Mat Src = QImage2cvMat(img);
		Mat Dst;
		transpose(Src, Dst);
		flip(Dst, Dst, 1);
		QImage leftRotateImg = cvMat2QImage(Dst);
		imageViewer->pixmap = QPixmap::fromImage(leftRotateImg);
		m_pPicLabel->setPixmap(QPixmap::fromImage(leftRotateImg));
		m_pPicLabel->resize(imageViewer->size);
	}
	else
	{
		CMessageBox warn(QString(QStringLiteral("����")), QStringLiteral("���FOBͼƬ!"),
			QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
}

void ToolBar::loadImageResource(void)
{
	m_pPicLabel->setPixmap(imageViewer->pixmap);
	m_pPicLabel->resize(imageViewer->size);
	//setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - QImageViewer"));
}

//Mat �� QImage֮����໥ת��
QImage ToolBar::cvMat2QImage(cv::Mat& mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}

		// Copy input Mat
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		//qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		//qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}


Mat ToolBar::QImage2cvMat(QImage &image)
{
	cv::Mat mat;
	qDebug() << image.format();
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;
}
//QStringList ToolBar::getDirName(QString pathsDir)
//{    /*��ȡ�ļ����µ��ļ�����*/   
//	QDir dir(pathsDir);   
//	if (!dir.exists()) 
//	{ 
//		return QStringList("");
//	}    
//	dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);    
//	QStringList allImageNameList = dir.entryList();    
//	if (allImageNameList.count() <= 0) 
//	{ 
//		return QStringList("");
//	}    
//	return allImageNameList;
//}
void ToolBar::getFileInfoList()
{
	QFileInfo info;
	QFileInfoList infoList;

	imageViewer->path = QFileInfo(imageViewer->filename).absolutePath();
	imageViewer->dir = QFileInfo(imageViewer->filename).absoluteDir();

	/* clear list */
	imageViewer->fileInfoList.clear();

	infoList = imageViewer->dir.entryInfoList(QDir::Files);
	for (int i = 0; i < infoList.count(); i++) {
		info = infoList.at(i);
		QString suffix = info.suffix();

		if (suffix == "jpg" || suffix == "bmp" || suffix == "png"
			|| suffix == "gif" || suffix == "jpeg") {
			imageViewer->fileInfoList.append(info);
		}
	}
}
int ToolBar::getFileCurIndex(void)
{
	QFileInfo info;
	int j;

	if (imageViewer->fileInfoList.count() <= 0) {
		qDebug() << "fileInfoList is NULL!";
		return -1;
	}

	for (j = 0; j < imageViewer->fileInfoList.count(); j++) {
		info = imageViewer->fileInfoList.at(j);
		if (info.fileName() == imageViewer->fileInfo.fileName()) {
			break;
		}
	}

	if (j >= imageViewer->fileInfoList.count()) {
		qDebug() << "Not find current file!";
		return -1;
	}

	imageViewer->index = j;
	return imageViewer->index;
}
int ToolBar::upgradeFileInfo(QString &filename, int angle, int sizeScale)
{
	QImage imgRotate;
	QMatrix matrix;
	QImage imgScaled;

	if (filename.isEmpty()) {
		return -1;
	}

	imageViewer->fileInfo = QFileInfo(filename);
	if (!imageViewer->image.load(filename)) {
		return -1;
	}

	/* modify angle */
	matrix.rotate(angle * 90);
	imgRotate = imageViewer->image.transformed(matrix);
	if (imageViewer->size == QSize(0, 0)) {
		imageViewer->size = imageViewer->image.size();
	}

	/* modify scale */
	imgScaled = imgRotate.scaled(imageViewer->size.width() * sizeScale / 10,
		imageViewer->size.height() * sizeScale / 10,
		Qt::KeepAspectRatio);

	/* upgrade pixmap */
	imageViewer->pixmap = QPixmap::fromImage(imgScaled);
	imageViewer->size = imageViewer->pixmap.size();

	/* upgrade index */
	imageViewer->index = getFileCurIndex();

	return 0;
}

