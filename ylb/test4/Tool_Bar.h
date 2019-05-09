#ifndef TOOL_BAR
#define TOOL_BAR

#include <QWidget>
#include <iconhelper.h>
#include <QImage>
#include <QDialog.h>
#include <QPixmap>
#include <QDir>
#include <QSize>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFileDialog>
#include <QDebug>
#include <ContentWidget.h>
#include <iostream>
#include <qdebug.h>
#include "Tool_Bar.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QImage>
#include <QDialog>
#include <QString>
#include <qt_windows.h>
#include <opencv2/opencv.hpp>
#include "FileManage.h"
#include "qimageviewer.h"
#include "PaintLabel.h"
#include "FobDetect.h"
using namespace cv;
class QLabel;
class QPushButton;
extern QLabel *m_pPicLabel;
extern QString m_filename;
extern QTextBrowser  *m_pText;
extern QScrollArea *m_ScrollArea;
class ToolBar : public QWidget
{
	Q_OBJECT

public:
	explicit ToolBar(QWidget *parent = 0);
	~ToolBar();
	void loadImageResource(void);

	QString m_pfilename;
signals:
// 自定义信号
	/*void rotatel();
	void rotater();*/
private:
	void IniUI();
	QImage cvMat2QImage(cv::Mat& mat);
	Mat QImage2cvMat(QImage &image);
	void getFileInfoList();
	int getFileCurIndex(void);
	int upgradeFileInfo(QString &filename, int angle, int sizeScale);
private slots:
	void judgePic();
	void readAwn();
	void allCheck();
	void savePic();
	void openPic();
	void deletePic();
	void enlargePic();
	void shrinkPic();
	void rotatelPic();
	void rotaterPic();
	
};

#endif

