
// MfcMainDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MfcMain.h"
#include "MfcMainDlg.h"
#include "afxdialogex.h"
#include "myfn.h"

#include "AnalysisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcMainDlg 对话框



CMfcMainDlg::CMfcMainDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MFCMAIN_DIALOG, pParent)
{
    // m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcMainDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMfcMainDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CMfcMainDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDCANCEL, &CMfcMainDlg::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_BUTTON2, &CMfcMainDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDOK, &CMfcMainDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMfcMainDlg 消息处理程序

BOOL CMfcMainDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    // TODO: 在此添加额外的初始化代码
    analysisDlg.Create(IDD_DIALOG1);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMfcMainDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMfcMainDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



void CMfcMainDlg::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    openFileToEditbox(GetDlgItem(IDC_EDIT1));
}


void CMfcMainDlg::OnBnClickedCancel()
{
    // TODO: 在此添加控件通知处理程序代码
    CDialogEx::OnCancel();
}


void CMfcMainDlg::OnBnClickedButton2()
{
    // TODO: 在此添加控件通知处理程序代码
    openFileToEditbox(GetDlgItem(IDC_EDIT2));
}


void CMfcMainDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    // CDialogEx::OnOK();
    analysisDlg.CenterWindow();
    analysisDlg.ShowWindow(SW_NORMAL);

    analyse(analysisDlg.GetDlgItem(IDC_EDIT1), 
        GetDlgItem(IDC_EDIT1), GetDlgItem(IDC_EDIT2));
}
