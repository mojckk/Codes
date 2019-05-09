#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H
#include <qmainwindow.h>
#include <Title_Bar.h>
#include "windows.h"
#include <Tool_Bar.h>
#include <ContentWidget.h>
#include <State_Bar.h>
#include <qsystemtrayicon.h>
#include <QMenu>
#include "TrayMenu.h"
#include "PaintLabel.h"
extern QPushButton *m_pblack;
extern QPushButton *m_pgreen;
extern QPushButton *m_pred;
extern QPushButton *m_ppink;
extern QPushButton *m_pblue;
extern QPushButton *m_pyellow;
extern QPushButton *m_pAllButton;

extern QLabel *m_pIconLabel;
extern QLabel *m_pTitleLabel;
extern QLabel *m_pNameLabel;
extern QTextBrowser  *m_pText;
extern QScrollArea *m_ScrollArea;

extern QPushButton *m_pOpenButton;
extern QPushButton *m_pJudgeButton;
extern QPushButton *m_pDeleteButton;
extern QPushButton *m_pEnlargeButton;
extern QPushButton *m_pShrinkButton;
extern QPushButton *m_pRotatelButton;
extern QPushButton *m_pRotaterButton;
extern QPushButton *m_pPrintButton;
extern QPushButton *m_pSaveButton;

extern QPushButton *m_pMinimizeButton;
extern QPushButton *m_pMaximizeButton;
extern QPushButton *m_pCloseButton;
extern QPushButton *m_pClothButton;

extern QLabel *m_pLabel;
extern QLabel *m_pPicLabel;
class QVBoxLayout;
class QWidget;
class QLabel;
class QPushButton;
class QStatusBar;
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();
	void setMarginWidth(const int &);//设置鼠标可以在界面边缘多大范围内拖动改变界面大小
	void serResizable(bool);//设置是否可以拖动改变大小
	TitleBar *pTitleBar;
	ContentWidget *contentWidget;
	QWidget *m_pCenterWidget;//大窗体
	ToolBar *pToolBar;
private:
	void InitUI();
	void InitTitle();
	void InitContent();
	void InitState();
	void InitTool();
	void InitTray();

	QVBoxLayout *m_pMainLayout;
	QPushButton *m_closeBtn;
	int m_iMarginWidth;
	bool m_bCanResize;
protected:
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	bool winEvent(MSG *message, long*result);
	
public slots:
	void onActivated(QSystemTrayIcon::ActivationReason reason);
	void quitSlot();
	void blackclick();
	void blueclick();
	void greenclick();
	void redclick();
	void pinkclick();
	void yellowclick(); 
signals:
	
};
#endif // !__MAINWINDOW_H


