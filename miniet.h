#ifndef MINIET_H
#define MINIET_H
class QLineEdit;
#include <QtWidgets/QMainWindow>
#include "ui_miniet.h"

class miniET : public QMainWindow
{
	Q_OBJECT

public:
	QString getOpenFileName(miniET*, QString, QString, QString);
	miniET(QWidget *parent = 0);
	~miniET();
	private slots:
	void Btn_OpenClick1();
	void Btn_OpenClick2();
	void Btn_OpenClick3();
	void Btn_OpenClick4();
	void Btn_OpenClick5();
	void Btn_OpenClick6();
	void Btn_OpenClick7();
	void Btn_OpenClick8();
	void Btn_OpenClick9();
private:
	Ui::miniETClass ui;
	int e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18;
};

#endif // MINIET_H
