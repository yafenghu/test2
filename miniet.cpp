#include "miniet.h"
#define	_CRT_SECURE_NO_WARNINGS
#if defined(WIN32)
#include <windows.h>
#else
#endif
#include <QFile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "dpcdecl.h" 
#include "depp.h"
#include "dmgr.h"
#include "miniet.h"
#include "ui_miniet.h"
#include "QMessageBox.h"
#include <QLineEdit> //文本框的头文件
#include"qtextstream.h"
#include"Qtextstream"
const int cchSzLen = 1024;
const int cbBlockSize = 1000;
BOOL			fGetReg;
BOOL			fPutReg;
BOOL			fGetRegRepeat;
BOOL			fPutRegRepeat;
BOOL			fDvc;
BOOL			fFile;
BOOL			fCount;
BOOL			fByte;
BYTE	        idReg;
BYTE	        idData, idRec;
char			szAction[cchSzLen];
char			szRegister[cchSzLen];
char			szDvc[cchSzLen] = { "CmodS6" };
char			szFile[cchSzLen];
char			szCount[cchSzLen];
char			szByte[cchSzLen];
HIF				hif = hifInvalid;
FILE *			fhin = NULL;
FILE *			fhout = NULL;
BOOL		FParseParam(int cszArg, char * rgszArg[]);
void		ShowUsage(char * sz);
BOOL		FInit();
void		ErrorExit();
void		DoDvcTbl();
void		DoPutReg();
void		DoGetReg();
void		DoPutRegRepeat();
void		DoGetRegRepeat();
void		StrcpyS(char* szDst, size_t cchDst, const char* szSrc);
int         flag = 0;
int         flag1 = 0;
int         flag2 = 0;
int         flag3 = 0;
int         flag4 = 0;
int         flags = 0;//使能标志位
int e[1000];
BYTE  a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, sr1, sr2, sr3;
miniET::miniET(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	if (!DmgrOpen(&hif, szDvc))
	{
		QMessageBox msg;//文本显示
		msg.setText("DmgrOpen failed (check the device name you provided)!");//
		msg.exec();
		ErrorExit();
	}
	if (!DeppEnable(hif))
	{
		QMessageBox msg;//文本显示
		msg.setText("DeppEnable failed!!");//
		msg.exec();
		ErrorExit();
	}
	flag = 1;
}
miniET::~miniET()
{
	if (hif != hifInvalid)
	{
		// DEPP API Call: DeppDisable
		DeppDisable(hif);

		// DMGR API Call: DmgrClose
		DmgrClose(hif);
	}
}
void miniET::Btn_OpenClick1()
{
	QMessageBox msg;//文本显示
	int k1 = 0;//解决只能写入第一次数值的问题
	int m = 0;//判断是否正确写进数
	while (flag1 == 0 || k1 == 0)
	{
		for (int i = 4; i < 8; i++)
		{
			QLineEdit*lineEdit_i = new QLineEdit(this);
			bool ok;
			e[4] = ui.lineEdit_4->text().toInt(&ok, 16);
			e[5] = ui.lineEdit_5->text().toInt(&ok, 16);
			e[6] = ui.lineEdit_6->text().toInt(&ok, 16);
			e[7] = ui.lineEdit_7->text().toInt(&ok, 16);
		}
		for (BYTE n = 4; n < 8; n++)
		{
			if (!DeppPutReg(hif, n, e[n], fFalse))
			{
				msg.setText("DeppPutReg failed\n");
				msg.exec();
			}
			m++;
		}
		flag1 = 1;//写完寄存器跳出循环
		k1 = 1;//写完寄存器跳出循环
	}
	if (m == 4)//a4 == e4&&a5 == e5&&a6 == e6&&a7 == e7
	{
		QLineEdit*lineEdit_16 = new QLineEdit(this);
		bool ok;
		e16 = ui.lineEdit_16->text().toInt(&ok, 16);
		if (DeppPutReg(hif, 0, e16, fFalse))
		{
			msg.setText("Complete. Register set!");//编辑要显示的文本
			msg.exec();
		}
	}
	else
	{
		flag1 = 0;//若出错误则返回
		msg.setText("Data set failed!!");//若不一致则报错
		msg.exec();
	}
}
void miniET::Btn_OpenClick2()
{
	QMessageBox msg;//文本显示
	int k2 = 0;
	int m = 0;//判断是否正确写进数
	if (flag2 == 0 || k2 == 0)
	{
		for (int i = 8; i < 16; i++)
		{
			QLineEdit*lineEdit_i = new QLineEdit(this);
			bool ok;
			e[8] = ui.lineEdit_8->text().toInt(&ok, 16);
			e[9] = ui.lineEdit_9->text().toInt(&ok, 16);
			e[10] = ui.lineEdit_10->text().toInt(&ok, 16);
			e[11] = ui.lineEdit_11->text().toInt(&ok, 16);
			e[12] = ui.lineEdit_12->text().toInt(&ok, 16);
			e[13] = ui.lineEdit_13->text().toInt(&ok, 16);
			e[14] = ui.lineEdit_14->text().toInt(&ok, 16);
			e[15] = ui.lineEdit_15->text().toInt(&ok, 16);
		}
		for (BYTE n = 8; n < 16; n++)
		{
			if (!DeppPutReg(hif, n, e[n], fFalse))
			{
				msg.setText("DeppPutReg failed\n");
				msg.exec();
			}
			m++;
		}
		flag2 = 1;//写完寄存器跳出循环
		k2 = 1;//写完寄存器跳出循环
	}
	if (m == 8)
	{
		QLineEdit*lineEdit_17 = new QLineEdit(this);
		bool ok;
		e17 = ui.lineEdit_17->text().toInt(&ok, 16);
		if (DeppPutReg(hif, 0, e17, fFalse))
		{
			msg.setText("Complete. Register set!");//编辑要显示的文本
			msg.exec();
		}
	}
	else
	{
		flag2 = 0;
		msg.setText("Data set failed!!");//若不一致则报错
		msg.exec();
	}
}
void miniET::Btn_OpenClick3()
{
	QMessageBox msg;//文本显示
	int k3 = 0;
	int m = 0;//判断是否正确写进数
	while (flag3 == 0 || k3 == 0)
	{
		for (int i = 1; i < 4; i++)
		{
			QLineEdit*lineEdit_i = new QLineEdit(this);
			bool ok;
			e[1] = ui.lineEdit1->text().toInt(&ok, 16);
			e[2] = ui.lineEdit_2->text().toInt(&ok, 16);
			e[3] = ui.lineEdit_3->text().toInt(&ok, 16);
		}
		for (BYTE n = 1; n < 4; n++)
		{
			if (!DeppPutReg(hif, n, e[n], fFalse))
			{
				msg.setText("DeppPutReg failed\n");
				msg.exec();
			}
			m++;
		}
		flag3 = 1;//写完寄存器跳出循环
		k3 = 1;//写完寄存器跳出循环
	}
	if (m == 3)
	{
		msg.setText("Complete. Register set!");//编辑要显示的文本
		msg.exec();
	}
	else
	{
		flag3 = 0;
		msg.setText("Data set failed!!");//若不一致则报错
		msg.exec();
	}
}
void miniET::Btn_OpenClick4()
{
	QMessageBox msg;//文本显示
	int k4 = 0;
	int flag4 = 0;
	if (flag4 == 0 || k4 == 0)
	{
		DeppGetReg(hif, 0, &sr1, fFalse);
		DeppGetReg(hif, 0, &sr2, fFalse);
		flag4 = 1;
		k4 = 1;
	}
	if (sr1 != sr2)
	{
		flag4 = 0;
	}
	else
	{
		QString str[100];
#define N 8
		int a[N];
		int i;
		for (i = 0; i != N; ++i)
		{
			a[N - 1 - i] = sr1 % 2;
			sr1 /= 2;
		}
		for (i = 0; i != N; ++i)
		{
			str[i] = QString::number(a[i]);
			ui.textBrowser_2->moveCursor(QTextCursor::End);//将光标移至上次输出的文末
			ui.textBrowser_2->insertPlainText(str[i]);
			if ((i + 1) % 4 == 0)
				ui.textBrowser_2->insertPlainText(" ");
		}
		ui.textBrowser_2->insertPlainText(";\n");
	}
}
void miniET::Btn_OpenClick5()
{
	QMessageBox msg;//文本显示
	QTextEdit*textEdit = new QTextEdit(this);
	int k6 = 0;
	BYTE get1[100], get2[100];
	QLineEdit*lineEdit_i = new QLineEdit(this);
	bool ok;
	e18 = ui.lineEdit_18->text().toInt(&ok, 16);
	DeppPutReg(hif, 0, e18, fFalse);
	if (flag4 == 0)
	{
		if (!DeppGetReg(hif, 0, &sr3, fFalse))//读SR存到sr3中)
		{
			msg.setText("DeppGetReg SR failed!!");//
			msg.exec();
		}
		flag4 = 1;
	}//读SR判断是否为0
	int k = 0;
	int bit = 0;
	bit = sr3 & 1;//判断SR的最后一位是否为1
	if (bit == 1)//不为零开始回读数据判断正确性
	{
		for (BYTE j = 8; j < 16; j++)
		{
			DeppGetReg(hif, j, &get1[j], fFalse);
			DeppGetReg(hif, j, &get2[j], fFalse);
			if (get1[j] == get2[j])
			{
				k++;//记下一致的个数
			}
		}
		flag4 = 1;
	}
	if (k == 8 || k6 == 0)//若两次读取数据一致，则开始显示解调结果
	{
		BYTE get3[100];
		int c[7];
		QString str[100];
		for (BYTE j = 8; j < 16; j++)//将解调结果显示出来
		{
			if (!DeppGetReg(hif, j, &get3[j], fFalse))
			{
				msg.setText("DeppGetReg failed!!");
				ErrorExit();
			}
			c[j - 8] = get3[j];
			char hs[8];
			char h[8];
			ltoa(get3[j], h, 16);
			sprintf(hs, "%s", h);
			str[j] = QString(hs);
		}
		float a = 0.0f;//浮点数的转换
		float e = 0.0f;
		unsigned char * b = (unsigned char*)&a;
		unsigned char * d = (unsigned char*)&e;
		int m = 0;
		for (m = 0; m < 4; m++)
		{
			b[m] = (unsigned char)c[m];
			d[m] = (unsigned char)c[m + 4];
		}
		QString data1 = QString("%1").arg(a);
		QString data2 = QString("%1").arg(e);//浮点数的转换
		for (BYTE t = 15; t > 7; t--)//将解调结果显示出来
		{
			ui.textEdit->insertPlainText(str[t]);//高位到低位显示
			ui.textEdit->moveCursor(QTextCursor::End);//将光标移至上次输出的文末
			ui.textEdit->insertPlainText(" ");
		}
		ui.textEdit->insertPlainText(";");
		ui.textEdit->insertPlainText(data2);
		ui.textEdit->insertPlainText(" ");
		ui.textEdit->insertPlainText(data1);
		ui.textEdit->insertPlainText("\n");//写完一组数据之后换行
		k6 = 1;
	}
	else
	{
		QMessageBox msg;//文本显示	
		msg.setText("Data set failed!!");//若不一致则报错
		msg.exec();
		flag4 = 0;
	}
}
void miniET::Btn_OpenClick6()
{
	ui.textBrowser_2->clear();
}
void miniET::Btn_OpenClick7()
{
	ui.textEdit->clear();
}
void miniET::Btn_OpenClick8()
{
	clock_t start, finish;
	double duration;
	QMessageBox msg;//文本显示
	ui.textEdit->clear();//在按下批量测量按键之后将文本框中内容清空！！！！！！！！！！！！
	int flag5 = 0;//保证第一次可以写寄存器
	int k3 = 0;
	int regD1[100000];//由行数分配空间
	int fff = 0;
	int i = 1;//读出的第一个数据放在regD1[1]
	int k = 0;
	start = clock();/////////////////////////////////////////////计时开始标志
	FILE *fpr = fopen("C:/demo.coe", "r");//要读取的文件，以只读方式打开
	if (fpr == NULL)
	{
		msg.setText("Can't open file!!");//若无法打开，报错
		msg.exec();
		return;
	}
	else
	{
		QString st1[100];
		fscanf(fpr, "%*[^\n]%*c"); // 跳到下一行，跳过第一行的文件注释
	lp2:	fscanf(fpr, "%*[^\n]%*c"); // 跳到下一行,第一次执行程序会跳过前两行的注释部分，之后只跳到下一行
		i = 1;//读出的第一个数据放在regD1[1]
	lp1:	if (fscanf(fpr, "%2x", &regD1[i]) != EOF)
	{
		QString st[100];
		if (1 <= i&&i <= 4)//读取4组数据
		{
			if (i == 1)
			{
				if (!DeppPutReg(hif, 9, BYTE(regD1[1]), fFalse))//将数据写进寄存器9
				{
					msg.setText("DeppPutReg failed!!");
					msg.exec();
				}
			}
			if (i == 2)
			{
				if (!DeppPutReg(hif, 8, BYTE(regD1[2]), fFalse))//将数据写进相应的寄存器8
				{
					msg.setText("DeppPutReg failed!!");
					msg.exec();
				}
			}
			if (i == 3)
			{
				if (!DeppPutReg(hif, 7, BYTE(regD1[3]), fFalse))//将数据写进相应的寄存器7
				{
					msg.setText("DeppPutReg failed!!");
					msg.exec();
				}
			}
			if (i == 4)
			{
				if (!DeppPutReg(hif, 1, BYTE(regD1[4]), fFalse))//将数据写进相应的寄存器1
				{
					msg.setText("DeppPutReg failed!!");
					msg.exec();
				}
			}
			fff = 1;//fff=0说明能读取数据
			if (i == 4)//所有数据已经写进寄存器
			{
				QMessageBox msg;//文本显示
				int k6 = 0;
				BYTE get1[100], get2[100];
				if (!DeppPutReg(hif, 0, 07, fFalse))
				{
					msg.setText("DeppPutReg SFR07 failed!!");//写SFR
					msg.exec();
				}
				QLineEdit*lineEdit_i = new QLineEdit(this);
				bool ok;
			lp3:		if (flag4 == 0)
			{
				if (!DeppGetReg(hif, 0, &sr3, fFalse))//读SR存到sr3中
				{
					msg.setText("DeppGetReg SR failed!!");//
					msg.exec();
				}
				flag4 = 1;
			}//读SR判断是否为0
						int k = 0;
						int bit = 0;
						bit = sr3 & 1;//判断SR(0)是否为1
						if (bit == 1)//不为零开始回读数据判断正确性
						{
							flag4 = 1;
						}
						else
						{
							flag4 = 0;
							goto lp3;
						}
						if (k6 == 0)//开始显示解调结果
						{

							BYTE get3[15];
							int c[7];
							QString str[100];
							for (BYTE j = 8; j < 16; ++j)//将解调结果显示出来
							{
								if (!DeppGetReg(hif, j, &get3[j], fFalse))
								{
									msg.setText("DeppGetReg failed!!");
									ErrorExit();
								}
								c[j - 8] = get3[j];
								char hs[8];
								char h[8];
								ltoa(get3[j], h, 16);
								sprintf(hs, "%s", h);
								str[j] = QString(hs);
							}


							float a = 0.0f;//浮点数的转换
							float e = 0.0f;
							unsigned char * b = (unsigned char*)&a;
							unsigned char * d = (unsigned char*)&e;
							for (int m = 0; m < 4; ++m)
							{
								b[m] = (unsigned char)c[m];
								d[m] = (unsigned char)c[m + 4];
							}
							QString data1 = QString("%1").arg(a);
							QString data2 = QString("%1").arg(e);//浮点数的转换
							QTextEdit*textEdit = new QTextEdit(this);
							for (BYTE t = 15; t > 7; --t)//将解调结果显示出来
							{
								ui.textEdit->insertPlainText(str[t]);//高位到低位显示
								ui.textEdit->moveCursor(QTextCursor::End);//将光标移至上次输出的文末
								ui.textEdit->insertPlainText(" ");
							}
							ui.textEdit->insertPlainText(";");
							ui.textEdit->insertPlainText(data2);
							ui.textEdit->insertPlainText(" ");
							ui.textEdit->insertPlainText(data1);
							k6 = 1;//一次解调结果显示完，将标志位置一
							if (!DeppPutReg(hif, 0, 0, fFalse))
							{
								msg.setText("DeppPutReg REG0 failed!!");//写SFR
								msg.exec();
							}
						}
						else
						{
							QMessageBox msg;//文本显示	
							msg.setText("Data set failed!!");//若不一致则报错
							msg.exec();
							flag4 = 0;
						}
			}
			i++;//i++在这里在这里！！
				///////判断REG0（4）在这里
			if (i == 5)
			{
			lp4:		if (!DeppGetReg(hif, 0, &sr3, fFalse))//读SR存到sr3中
			{
				msg.setText("DeppGetReg SR failed!!");//
				msg.exec();
			}
						int bit = 0;
						bit = sr3 & 8;//判断SR(3)是否为1
						if (bit != 0)//为零开始下一次解调
						{
							goto lp4;
						}
                        //不为零继续读取判断
 		    }
			goto lp1;
		}

		else
		{
			ui.textEdit->insertPlainText("\n");//写完一组数据之后换行
			k++;
			flag4 = 0;
			goto lp2;
		}
	}
			else
			{
				if (fff == 1)
				{

					finish = clock();////////////////////////////////////////////////////////////////////////////////////////
					duration = (double)(finish - start) / CLK_TCK;///////////////////////////////////////////////////////////
					ui.textBrowser_2->insertPlainText(QString::number(duration, 10, 4));
					ui.textBrowser_2->insertPlainText("\n");//////////////////////////////////////////////////////////////////////////					
					msg.setText("Complete. Register set!!");
					msg.exec();
					return;


				}
				else
				{
					msg.setText("Data read failed!!");
					msg.exec();
					return;
				}
			}
			fclose(fpr);
	}

}
void miniET::Btn_OpenClick9()
{
	QMessageBox msg;//文本显示
	FILE *fpw = fopen("C:/result.coe", "w");//打开只读文件，若原有内容则清零
	fclose(fpw);//关闭文件,此操作用于对result.coe文件进行清零操作
	QTextEdit*textEdit = new QTextEdit(this);
	QString strText = ui.textEdit->toPlainText();
	QString str;
	QTextStream ts(&strText);
	QString fileName = "C:/result.coe";//写入文件的目录
	str.append(str);
	QFile file(fileName);
	while (!ts.atEnd())
	{
		str = ts.readLine();
		if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
		{
			QTextStream in(&file);
		}
		else
		{
			msg.setText("Complete. File set.!");
			msg.exec();
		}
		QTextStream in(&file);
		in << str << "\n";
	}
	file.close();
}
void DoGetReg() {
	BYTE	idReg;
	BYTE	idData;
	char *	szStop;
	idReg = (BYTE)strtol(szRegister, &szStop, 10);

	// DEPP API Call: DeppGetReg
	if (!DeppGetReg(hif, idReg, &idData, fFalse)) {
		printf("DeppGetReg failed\n");
		ErrorExit();
	}
	printf("Complete. Recieved data %d\n", idData);
	return;
}
void DoPutReg() {
	BYTE	idReg;
	BYTE	idData;
	char *	szStop;
	idReg = (BYTE)strtol(szRegister, &szStop, 10);
	idData = (BYTE)strtol(szByte, &szStop, 10);
	// DEPP API Call: DeppPutReg
	if (!DeppPutReg(hif, idReg, idData, fFalse)) {
		printf("DeppPutReg failed\n");
		return;
	}
	printf("Complete. Register set.\n");
	return;
}
void ShowUsage(char * szProgName) {

	printf("\nDigilent DEPP demo\n");
	printf("Usage: %s <action> <register> -d <device name> [options]\n", szProgName);

	printf("\n\tActions:\n");
	printf("\t-g\t\t\t\tGet register byte\n");
	printf("\t-p\t\t\t\tPut Register byte\n");
	printf("\t-l\t\t\t\tStream file into register\n");
	printf("\t-s\t\t\t\tStream register into file\n");

	printf("\n\tOptions:\n");
	printf("\t-f <filename>\t\t\tSpecify file name\n");
	printf("\t-c <# bytes>\t\t\tNumber of bytes to read/write\n");
	printf("\t-b <byte>\t\t\tValue to load into register\n");

	printf("\n\n");
}
void ErrorExit() {
	if (hif != hifInvalid) {
		// DEPP API Call: DeppDisable
		DeppDisable(hif);

		// DMGR API Call: DmgrClose
		DmgrClose(hif);
	}

	if (fhin != NULL) {
		fclose(fhin);
	}

	if (fhout != NULL) {
		fclose(fhout);
	}

	exit(1);
}
