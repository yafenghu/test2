#include "miniet.h"
#include <QtWidgets/QApplication>
#define	_CRT_SECURE_NO_WARNINGS
#if defined(WIN32)
#include <windows.h>
#else
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dpcdecl.h" 
#include "depp.h"
#include "dmgr.h"
#include "miniet.h"
#include "QMessageBox.h"
#include <QLineEdit> //�ı����ͷ�ļ�

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);//����һ��QApplication ���󣬹���Ӧ�ó������Դ��
	miniET w;
	w.show();
	return a.exec();//�ó��������Ϣѭ�����ȴ����ܵĲ˵��������������ȵ����룬������Ӧ��
}