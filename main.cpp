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
#include <QLineEdit> //文本框的头文件

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);//创建一个QApplication 对象，管理应用程序的资源。
	miniET w;
	w.show();
	return a.exec();//让程序进入消息循环。等待可能的菜单，工具条，鼠标等的输入，进行响应。
}