// module;
#include "pch.h"


unsigned MurmurHash2(const void *key, size_t len, unsigned seed) {
    // 'm' 和 'r' 是离线生成的混合常量.
    // 它们不是什么魔法, 只是刚好表现很好而已.
    const unsigned m = 0x5bd1e995;
    const int r = 24;

    // 初始化散列值为一个伪随机数
    unsigned h = seed ^ (unsigned)len;

    // 每次将四个字节混入散列值
    const unsigned char *data = (const unsigned char *)key;
    while (len >= 4) {
        unsigned k = *(unsigned *)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    // 处理最后几个字节
    switch (len) {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
        h *= m;
    };

    // 再混合一次以确保最后几个字节充分混合
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}


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
    if (code == L"") { return; }
    editbox->SetWindowTextW(code);
}


auto getNextToken(CString &code, size_t pos) {

    // 这些是单独作为标识符的符号
    static const wchar_t singl[] { L"~()[]{},.;?" };
    // 这些是可能有两个连在一起的符号, 例如 ! 和 !=; = 和 ==
    static const wchar_t doubl[] { L"!%^*-+=:/" };
    // 这些是可能有 1-3 个连在一起的符号, 例如 < 和 << 和 <<=
    static const wchar_t tripl[] { L"&|<>" };
    // 这些分别单独处理
    static const wchar_t other[] { L"#\"'" };
    // 这两个当成标识符
    static const wchar_t ident[] { L"$_" };
    // 这两个是换行
    static const wchar_t newln[] { L"\r\n" };

    // 定义小型函数 (lambda)
    auto in = []<typename T>(T &ar, auto c)->bool {
        for (auto _ : ar) if (_ == c) return 1; return 0; };
    auto isident = [&](wchar_t c)->bool { return in(ident, c) or isalpha(c); };
    auto isidnum = [&](wchar_t c)->bool { return in(ident, c) or isalnum(c); };
    auto issingl = [&](wchar_t c)->bool { return in(singl, c); };
    auto isdoubl = [&](wchar_t c)->bool { return in(doubl, c); };
    auto istripl = [&](wchar_t c)->bool { return in(tripl, c); };
    auto isother = [&](wchar_t c)->bool { return in(other, c); };
    auto isnewln = [&](wchar_t c)->bool { return in(newln, c); };
    CString word, temp;
    size_t len = code.GetLength();
    auto peek = [&]()->wchar_t { return pos >= len ? 0 : code[pos]; };
    auto get1 = [&]()->wchar_t { return pos >= len ? 0 : code[pos++]; };

START:
    // 去除空白字符
    while (isspace(peek()) and pos < len) {
        // ((temp = L"1. <") += peek()) += L">\n";
        // TRACE(temp);
        get1();
        TRACE(L"-1%Ls\n", word);
    }
    if (pos >= len) { return pair { word, len }; }

    wchar_t wch = peek();
    // 如果是字母开头的字母数字串, 识别为标识符, 例如 int, _myname, stu1
    if (isident(wch)) {
        while (isidnum(peek()) and pos < len) {
            // ((temp = L"2. <") += peek()) += L">\n";
            // TRACE(temp);
            word += get1();
            TRACE(L"0%Ls\n", word);
        }

    // 如果是数字开头的字母数字串, 则识别为字面量, 例如 123, .0, 1.0e5, 6371km
    // 如果有点 . 号, 后面必须接数字
    } else if (isdigit(wch) or wch == L'.') {
        while (isidnum(peek()) or wch == L'.') {
            wch = get1();
            word += wch;
            if (wch == L'.' and not isdigit(peek())) { break; }
            TRACE(L"1%Ls\n", word);
        }

    // 检查是不是单个符号的运算符
    } else if (issingl(wch)) {
        word += get1();
        TRACE(L"2%Ls\n", word);

    // 检查是不是 1-2 个符号的运算符
    } else if (isdoubl(wch)) {
        get1();
        if (wch == L'/') {
            wchar_t wc2 = peek();

            // 如果是单行注释, 则丢弃直到行尾, 返回空字符串
            if (wc2 == L'/') {
                while (not isnewln(peek())) {
                    get1();
                }

            // 如果是多行注释, 则丢弃直到注释结束, 返回空字符串
            } else if (wc2 == L'*') {
                while (wch != L'*' or wc2 != L'/') {
                    wch = wc2; wc2 = get1();
                }

            // 如果是 /=
            } else if (wc2 == L'=') {
                word = L"/="; get1();

            // 如果是单独的 / 除号
            } else {
                word = L"/";
            }

        } else {
            wchar_t wc2 = peek();

            // (举例) 如果是 ++ 或者 +=
            if (wc2 == L'=' or wc2 == wch) {
                (word += wch) += wc2; get1();

            // 否则只是单个符号
            } else {
                word += wch;
            }
        }
        TRACE(L"3.1%Ls\n", word);

    // 检查是不是 1-3 个符号的运算符
    } else if (istripl(wch)) {
        // 只有一个符号例如 &, <
        word += get1();
        wchar_t wc2 = peek();

        // 有 2 个符号例如 &=, <=
        if (wc2 == L'=') {
            word += get1();

        // 有 2 个或者 3 个符号例如 &&, &&=, <<, <<=
        } else if (wc2 == wch) {
            word += get1();
            wchar_t wc3 = peek();
            if (wc3 == L'=') {
                word += get1();
            }
        }
        TRACE(L"3.2%Ls\n", word);

    // TODO: 处理其他情况
    } else if (isother(wch)) {
        word += get1();

        // 如果是 # 那就找紧接的标识符, 比如 #include
        if (wch == L'#') {
            goto START;

        // 如果是 " 那就找这个字符串, 接受这个 \ 转义字符
        } else if (wch == L'"') {
            while (peek() != L'"') {
                if (peek() == L'\\') {
                    get1();
                }
                word += get1();
                TRACE(L"3.3.1%Ls\n", word);
            }
            word += get1();

        // 如果是 ' 那就找这个字符, 接受这个 \ 转义字符
        } else if (wch == L'\'') {
            while (peek() != L'\'') {
                if (peek() == L'\\') {
                    get1();
                }
                word += get1();
                TRACE(L"3.3.2%Ls\n", word);
            }
            word += get1();
        }
        TRACE(L"3.3%Ls\n", word);

    // 其他识别不出的情况全部丢弃, 直到下一个空白符, 如 ` @ 或者非 ASCII 标识符
    } else {
        while (not isspace(peek()) and pos < len) {
            // ((temp = L"3. <") += peek()) += L">\n";
            // TRACE(temp);
            get1();
            TRACE(L"3.4%Ls\n", word);
        }
    }
    // TRACE(word + L"\n");

    return std::pair { word, pos };
}


void analyse(CWnd *codebox1, CWnd *codebox2,
        CWnd *infobox, CWnd *tokenbox1, CWnd *tokenbox2) {

    CString countOutput { L"=== === === === === === === ===\r\n"
        L"下面是详细的计数结果\r\n" };
    mymap<std::wstring, int> wordMap1, wordMap2;

    // 对两个代码分别进行一次扫描
    for (auto box : { codebox1, codebox2 }) {
        CString words, word, gotText;
        size_t size = 0, len;
        auto &map = box == codebox1 ? wordMap1 : wordMap2;
        auto token = box == codebox1 ? tokenbox1 : tokenbox2;
        // std::unordered_map<std::wstring, int> wordMap;

        (words = L"代码 ") += (box == codebox1 ? L"1" : L"2");
        words += L" 分词:\r\n";
        box->GetWindowTextW(gotText);
        gotText += L"\r\n";
        len = gotText.GetLength();

        // 循环取得下一个单词
        while (true) {
            // static int times = 0;
            // TRACE("第 %d 次打印\n", ++times);
            std::tie(word, size) = getNextToken(gotText, size);
            // (tmp1 += word) += L"\r\n";
            if (size >= len) { break; }
            if (word != L"") {
                (words += word) += L"\r\n";
                ++map[std::wstring{word}];
            }
        }
        token->SetWindowTextW(words);

        // 分析这些关键词
        countOutput += L"=== === === === === === === ===\r\n";
        countOutput += box == codebox1 ? L"代码 1 " : L"代码 2 ";
        countOutput += L"的词频列表是: \r\n";
        // (output += L"的分词是: \r\n") += words;
        for (auto &pr : map) {
            if (not isalpha(pr.first[0])) { continue; }
            (countOutput += pr.first.c_str()) += L" 出现了 ";
            (countOutput += std::to_wstring(pr.second).c_str()) += L" 次\r\n";
        }
    }

    // 写入分析结果
    countOutput += L"=== === === === === === === ===\r\n分析完成\r\n";
    infobox->SetWindowTextW(countOutput);
}
