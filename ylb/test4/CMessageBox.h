#ifndef __CMESSAGEBOX_H
#define __CMESSAGEBOX_H
#include <QtWidgets>
extern int g_index;

class CMessageBox : public QDialog
{
	Q_OBJECT
public:
	CMessageBox(QWidget *parent = Q_NULLPTR);
	~CMessageBox();
	CMessageBox(QString title, QString content, QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButton defaultButton = QMessageBox::Ok);
private:
	void InitUI(QString title, QString content, QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButton defaultButton = QMessageBox::Ok);
	QLabel *m_pIconLabel;
	QLabel *m_pTitleLabel;
	QPushButton *m_pCloseButton;

	QLabel *m_pLabel;
	QDialogButtonBox *m_pButtonBox;
protected:
	virtual void mousePressEvent(QMouseEvent * event);
	virtual void paintEvent(QPaintEvent *event);
private slots:
	void CloseSlot() { this->close(); }
	void onButtonClicked(QAbstractButton*);
};
#endif

