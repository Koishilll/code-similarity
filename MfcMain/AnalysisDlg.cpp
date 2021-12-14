// AnalysisDlg.cpp: 实现文件
//

#include "pch.h"
#include "MfcMain.h"
#include "afxdialogex.h"
#include "AnalysisDlg.h"


// CAnalysisDlg 对话框

IMPLEMENT_DYNAMIC(CAnalysisDlg, CDialogEx)

CAnalysisDlg::CAnalysisDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CAnalysisDlg::~CAnalysisDlg()
{
}

void CAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAnalysisDlg, CDialogEx)
END_MESSAGE_MAP()


// CAnalysisDlg 消息处理程序
