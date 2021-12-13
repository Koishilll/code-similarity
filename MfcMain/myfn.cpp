#include "pch.h"

void openFileToEditbox(CWnd *editbox) {
    CFileDialog fileDlg(true);
    fileDlg.m_ofn.lpstrInitialDir = _T(".");
    CString strFilePath;

    // 显示打开文件对话框
    if (IDOK == fileDlg.DoModal()) {
        strFilePath = fileDlg.GetPathName();
    }
    std::wifstream ifs { strFilePath };
    CString code;
    wchar_t buf[5005];

    while (ifs) {
        ifs.getline(buf, 5000);
        // ifs.read(buf, 10000);
        // int count = ifs.gcount();
        code.Append(buf);
        code.Append(_T("\r\n"));
    }
    editbox->SetWindowText(code);
}
