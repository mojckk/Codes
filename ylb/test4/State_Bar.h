#ifndef STATE_BAR_H
#define STATE_BAR_H
#include <QtWidgets>
#include <QScrollArea>
class QLabel;
class QPushButton;
class QGraphicsView;
class QLineEdit;
extern QString m_filename;
class StateBar : public QWidget
{
	Q_OBJECT
public:
	StateBar(QWidget *parent = Q_NULLPTR);
	~StateBar();
private:
protected:
	QWidget *m_MainWidget;
	QLabel *m_pNamelabel;
	
private slots:
};
#endif
