#include "pch.h"

// import std.core;
// import util.mymap;
// import util.myvec;


/**
 * @brief 打开文件到文本框里
 * @param editbox 文本框
 */
void openFileToEditbox(CWnd *editbox) {
    CFileDialog fileDlg(true);
    fileDlg.m_ofn.lpstrInitialDir = L".";
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
        (code += buf) += L"\r\n";
    }
    editbox->SetWindowTextW(code);
}


/**
 * @brief 扫描下一个令牌并返回
 * @param code 代码字符串
 * @param pos 扫描开始的位置
 * @return std::pair<CString, size_t> 字符串和本次扫描的终止位置
 */
auto getNextToken(CString &code, size_t pos) {
    // 定义小型函数 (lambda)
    size_t len = code.GetLength();
    auto peek = [&]()->wchar_t { return pos >= len ? 0 : code[pos]; };
    auto get1 = [&]()->wchar_t { return pos >= len ? 0 : code[pos++]; };

    CString word, temp;
    // 去除空白字符
    while (isspace(peek())) {
        // ((temp = L"1. <") += peek()) += L">\n";
        // TRACE(temp);
        get1();
    }

    wchar_t wch = peek();
    // 如果是字母开头的字母数字串, 识别为标识符
    if (isalpha(wch)) {
        while (isalnum(peek())) {
            // ((temp = L"2. <") += peek()) += L">\n";
            // TRACE(temp);
            word += get1();
        }

    // 其他情况下丢弃, 直到下一个空白符
    } else {
        while (not isspace(peek()) and pos < len) {
            // ((temp = L"3. <") += peek()) += L">\n";
            // TRACE(temp);
            get1();
        }
    }

    return std::pair { word, pos };
}


/**
 * @brief 将分析结果写入弹出的对话框
 * @param infobox 弹出的对话框
 * @param codebox1 代码 1
 * @param codebox2 代码 2
 */
void analyse(CWnd *infobox, CWnd *codebox1, CWnd *codebox2) {
    CString output;

    // 对两个代码分别进行一次扫描
    for (auto box : { codebox1, codebox2 }) {
        CString words, word, gotText;
        size_t size = 0, len;
        // mymap<string, int> wordMap;
        // myvec<int> wordVec;

        box->GetWindowTextW(gotText);
        gotText += L"\r\n";
        len = gotText.GetLength();

        // 循环取得下一个单词
        while (true) {
            // static int times = 0;
            // TRACE("第 %d 次打印\n", ++times);
            std::tie(word, size) = getNextToken(gotText, size);
            if (size >= len) { break; }
            if (word != L"") { (words += word) += L"\r\n"; }
        }
        words += L"\r\n";
        output += box == codebox1 ? L"代码 1 " : L"代码 2 ";
        (output += L"的分词是: \r\n") += words;
    }

    // 写入分析结果
    infobox->SetWindowTextW(output);
}
