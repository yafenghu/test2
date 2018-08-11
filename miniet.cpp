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
#include <QLineEdit> //�ı����ͷ�ļ�
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
int         flags = 0;//ʹ�ܱ�־λ
int e[1000];
BYTE  a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, sr1, sr2, sr3;
miniET::miniET(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	if (!DmgrOpen(&hif, szDvc))
	{
		QMessageBox msg;//�ı���ʾ
		msg.setText("DmgrOpen failed (check the device name you provided)!");//
		msg.exec();
		ErrorExit();
	}
	if (!DeppEnable(hif))
	{
		QMessageBox msg;//�ı���ʾ
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
	QMessageBox msg;//�ı���ʾ
	int k1 = 0;//���ֻ��д���һ����ֵ������
	int m = 0;//�ж��Ƿ���ȷд����
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
		flag1 = 1;//д��Ĵ�������ѭ��
		k1 = 1;//д��Ĵ�������ѭ��
	}
	if (m == 4)//a4 == e4&&a5 == e5&&a6 == e6&&a7 == e7
	{
		QLineEdit*lineEdit_16 = new QLineEdit(this);
		bool ok;
		e16 = ui.lineEdit_16->text().toInt(&ok, 16);
		if (DeppPutReg(hif, 0, e16, fFalse))
		{
			msg.setText("Complete. Register set!");//�༭Ҫ��ʾ���ı�
			msg.exec();
		}
	}
	else
	{
		flag1 = 0;//���������򷵻�
		msg.setText("Data set failed!!");//����һ���򱨴�
		msg.exec();
	}
}
void miniET::Btn_OpenClick2()
{
	QMessageBox msg;//�ı���ʾ
	int k2 = 0;
	int m = 0;//�ж��Ƿ���ȷд����
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
		flag2 = 1;//д��Ĵ�������ѭ��
		k2 = 1;//д��Ĵ�������ѭ��
	}
	if (m == 8)
	{
		QLineEdit*lineEdit_17 = new QLineEdit(this);
		bool ok;
		e17 = ui.lineEdit_17->text().toInt(&ok, 16);
		if (DeppPutReg(hif, 0, e17, fFalse))
		{
			msg.setText("Complete. Register set!");//�༭Ҫ��ʾ���ı�
			msg.exec();
		}
	}
	else
	{
		flag2 = 0;
		msg.setText("Data set failed!!");//����һ���򱨴�
		msg.exec();
	}
}
void miniET::Btn_OpenClick3()
{
	QMessageBox msg;//�ı���ʾ
	int k3 = 0;
	int m = 0;//�ж��Ƿ���ȷд����
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
		flag3 = 1;//д��Ĵ�������ѭ��
		k3 = 1;//д��Ĵ�������ѭ��
	}
	if (m == 3)
	{
		msg.setText("Complete. Register set!");//�༭Ҫ��ʾ���ı�
		msg.exec();
	}
	else
	{
		flag3 = 0;
		msg.setText("Data set failed!!");//����һ���򱨴�
		msg.exec();
	}
}
void miniET::Btn_OpenClick4()
{
	QMessageBox msg;//�ı���ʾ
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
			ui.textBrowser_2->moveCursor(QTextCursor::End);//����������ϴ��������ĩ
			ui.textBrowser_2->insertPlainText(str[i]);
			if ((i + 1) % 4 == 0)
				ui.textBrowser_2->insertPlainText(" ");
		}
		ui.textBrowser_2->insertPlainText(";\n");
	}
}
void miniET::Btn_OpenClick5()
{
	QMessageBox msg;//�ı���ʾ
	QTextEdit*textEdit = new QTextEdit(this);
	int k6 = 0;
	BYTE get1[100], get2[100];
	QLineEdit*lineEdit_i = new QLineEdit(this);
	bool ok;
	e18 = ui.lineEdit_18->text().toInt(&ok, 16);
	DeppPutReg(hif, 0, e18, fFalse);
	if (flag4 == 0)
	{
		if (!DeppGetReg(hif, 0, &sr3, fFalse))//��SR�浽sr3��)
		{
			msg.setText("DeppGetReg SR failed!!");//
			msg.exec();
		}
		flag4 = 1;
	}//��SR�ж��Ƿ�Ϊ0
	int k = 0;
	int bit = 0;
	bit = sr3 & 1;//�ж�SR�����һλ�Ƿ�Ϊ1
	if (bit == 1)//��Ϊ�㿪ʼ�ض������ж���ȷ��
	{
		for (BYTE j = 8; j < 16; j++)
		{
			DeppGetReg(hif, j, &get1[j], fFalse);
			DeppGetReg(hif, j, &get2[j], fFalse);
			if (get1[j] == get2[j])
			{
				k++;//����һ�µĸ���
			}
		}
		flag4 = 1;
	}
	if (k == 8 || k6 == 0)//�����ζ�ȡ����һ�£���ʼ��ʾ������
	{
		BYTE get3[100];
		int c[7];
		QString str[100];
		for (BYTE j = 8; j < 16; j++)//����������ʾ����
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
		float a = 0.0f;//��������ת��
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
		QString data2 = QString("%1").arg(e);//��������ת��
		for (BYTE t = 15; t > 7; t--)//����������ʾ����
		{
			ui.textEdit->insertPlainText(str[t]);//��λ����λ��ʾ
			ui.textEdit->moveCursor(QTextCursor::End);//����������ϴ��������ĩ
			ui.textEdit->insertPlainText(" ");
		}
		ui.textEdit->insertPlainText(";");
		ui.textEdit->insertPlainText(data2);
		ui.textEdit->insertPlainText(" ");
		ui.textEdit->insertPlainText(data1);
		ui.textEdit->insertPlainText("\n");//д��һ������֮����
		k6 = 1;
	}
	else
	{
		QMessageBox msg;//�ı���ʾ	
		msg.setText("Data set failed!!");//����һ���򱨴�
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
	QMessageBox msg;//�ı���ʾ
	ui.textEdit->clear();//�ڰ���������������֮���ı�����������գ�����������������������
	int flag5 = 0;//��֤��һ�ο���д�Ĵ���
	int k3 = 0;
	int regD1[100000];//����������ռ�
	int fff = 0;
	int i = 1;//�����ĵ�һ�����ݷ���regD1[1]
	int k = 0;
	start = clock();/////////////////////////////////////////////��ʱ��ʼ��־
	FILE *fpr = fopen("C:/demo.coe", "r");//Ҫ��ȡ���ļ�����ֻ����ʽ��
	if (fpr == NULL)
	{
		msg.setText("Can't open file!!");//���޷��򿪣�����
		msg.exec();
		return;
	}
	else
	{
		QString st1[100];
		fscanf(fpr, "%*[^\n]%*c"); // ������һ�У�������һ�е��ļ�ע��
	lp2:	fscanf(fpr, "%*[^\n]%*c"); // ������һ��,��һ��ִ�г��������ǰ���е�ע�Ͳ��֣�֮��ֻ������һ��
		i = 1;//�����ĵ�һ�����ݷ���regD1[1]
	lp1:	if (fscanf(fpr, "%2x", &regD1[i]) != EOF)
	{
		QString st[100];
		if (1 <= i&&i <= 4)//��ȡ4������
		{
			if (i == 1)
			{
				if (!DeppPutReg(hif, 9, BYTE(regD1[1]), fFalse))//������д���Ĵ���9
				{
					msg.setText("DeppPutReg failed!!");
					msg.exec();
				}
			}
			if (i == 2)
			{
				if (!DeppPutReg(hif, 8, BYTE(regD1[2]), fFalse))//������д����Ӧ�ļĴ���8
				{
					msg.setText("DeppPutReg failed!!");
					msg.exec();
				}
			}
			if (i == 3)
			{
				if (!DeppPutReg(hif, 7, BYTE(regD1[3]), fFalse))//������д����Ӧ�ļĴ���7
				{
					msg.setText("DeppPutReg failed!!");
					msg.exec();
				}
			}
			if (i == 4)
			{
				if (!DeppPutReg(hif, 1, BYTE(regD1[4]), fFalse))//������д����Ӧ�ļĴ���1
				{
					msg.setText("DeppPutReg failed!!");
					msg.exec();
				}
			}
			fff = 1;//fff=0˵���ܶ�ȡ����
			if (i == 4)//���������Ѿ�д���Ĵ���
			{
				QMessageBox msg;//�ı���ʾ
				int k6 = 0;
				BYTE get1[100], get2[100];
				if (!DeppPutReg(hif, 0, 07, fFalse))
				{
					msg.setText("DeppPutReg SFR07 failed!!");//дSFR
					msg.exec();
				}
				QLineEdit*lineEdit_i = new QLineEdit(this);
				bool ok;
			lp3:		if (flag4 == 0)
			{
				if (!DeppGetReg(hif, 0, &sr3, fFalse))//��SR�浽sr3��
				{
					msg.setText("DeppGetReg SR failed!!");//
					msg.exec();
				}
				flag4 = 1;
			}//��SR�ж��Ƿ�Ϊ0
						int k = 0;
						int bit = 0;
						bit = sr3 & 1;//�ж�SR(0)�Ƿ�Ϊ1
						if (bit == 1)//��Ϊ�㿪ʼ�ض������ж���ȷ��
						{
							flag4 = 1;
						}
						else
						{
							flag4 = 0;
							goto lp3;
						}
						if (k6 == 0)//��ʼ��ʾ������
						{

							BYTE get3[15];
							int c[7];
							QString str[100];
							for (BYTE j = 8; j < 16; ++j)//����������ʾ����
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


							float a = 0.0f;//��������ת��
							float e = 0.0f;
							unsigned char * b = (unsigned char*)&a;
							unsigned char * d = (unsigned char*)&e;
							for (int m = 0; m < 4; ++m)
							{
								b[m] = (unsigned char)c[m];
								d[m] = (unsigned char)c[m + 4];
							}
							QString data1 = QString("%1").arg(a);
							QString data2 = QString("%1").arg(e);//��������ת��
							QTextEdit*textEdit = new QTextEdit(this);
							for (BYTE t = 15; t > 7; --t)//����������ʾ����
							{
								ui.textEdit->insertPlainText(str[t]);//��λ����λ��ʾ
								ui.textEdit->moveCursor(QTextCursor::End);//����������ϴ��������ĩ
								ui.textEdit->insertPlainText(" ");
							}
							ui.textEdit->insertPlainText(";");
							ui.textEdit->insertPlainText(data2);
							ui.textEdit->insertPlainText(" ");
							ui.textEdit->insertPlainText(data1);
							k6 = 1;//һ�ν�������ʾ�꣬����־λ��һ
							if (!DeppPutReg(hif, 0, 0, fFalse))
							{
								msg.setText("DeppPutReg REG0 failed!!");//дSFR
								msg.exec();
							}
						}
						else
						{
							QMessageBox msg;//�ı���ʾ	
							msg.setText("Data set failed!!");//����һ���򱨴�
							msg.exec();
							flag4 = 0;
						}
			}
			i++;//i++�������������
				///////�ж�REG0��4��������
			if (i == 5)
			{
			lp4:		if (!DeppGetReg(hif, 0, &sr3, fFalse))//��SR�浽sr3��
			{
				msg.setText("DeppGetReg SR failed!!");//
				msg.exec();
			}
						int bit = 0;
						bit = sr3 & 8;//�ж�SR(3)�Ƿ�Ϊ1
						if (bit != 0)//Ϊ�㿪ʼ��һ�ν��
						{
							goto lp4;
						}
                        //��Ϊ�������ȡ�ж�
 		    }
			goto lp1;
		}

		else
		{
			ui.textEdit->insertPlainText("\n");//д��һ������֮����
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
	QMessageBox msg;//�ı���ʾ
	FILE *fpw = fopen("C:/result.coe", "w");//��ֻ���ļ�����ԭ������������
	fclose(fpw);//�ر��ļ�,�˲������ڶ�result.coe�ļ������������
	QTextEdit*textEdit = new QTextEdit(this);
	QString strText = ui.textEdit->toPlainText();
	QString str;
	QTextStream ts(&strText);
	QString fileName = "C:/result.coe";//д���ļ���Ŀ¼
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
