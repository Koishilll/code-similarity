#pragma once
#include "pch.h"
#include "myvec.cpp"
#include "mylist.cpp"
#include "mymap.cpp"


/**
 * @brief 哈希函数的实现
 * 请看: https://github.com/abrandoned/murmur2/blob/master/MurmurHash2.c
 * @param key 要进行哈希的字符数组
 * @param len 数组长度
 * @param seed 哈希生成种子, 由用户指定, 需要保证程序运行过程中这个种子不可改变
 */
unsigned MurmurHash2(const void *key, size_t len, unsigned seed);


/**
 * @brief 打开文件到文本框里
 * @param editbox 文本框
 */
void openFileToEditbox(CWnd *editbox);


/**
 * @brief 扫描下一个令牌并返回
 * C++ 程序的文本由标记和空格组成。标记是 C++ 程序中对编译器有意义的最小元素。
 * C++ 解析器识别这些类型的标记：
 *  关键词; 标识符; 数字、布尔和指针字面量; 字符串和字符字面量;
 *  用户定义的字面量; 运算符; 标点符号;
 * 这个程序可以分出的词有:
 *  字母开头的 - 关键词 标识符
 *  数字开头的 - 数字
 *  符号开头的 - 符号 (可能连续 1-3 个) 注释 连续尖括号
 * @param code 代码字符串
 * @param pos 扫描开始的位置
 * @return std::pair<CString, size_t> 字符串和本次扫描的终止位置
 */
auto getNextToken(CString &code, size_t pos);


/**
 * @brief 计算两个向量的内积
 * @param vec1
 * @param vec2
 * @return double
 */
double getInnerProduct(const myvec<pair<std::wstring, int>> &vec1,
    const myvec<pair<std::wstring, int>> &vec2);


/**
 * @brief 计算 L1 范数
 * @param vec1
 * @param vec2
 * @return double
 */
double getL1Norm(const myvec<pair<std::wstring, int>> &vec1,
    const myvec<pair<std::wstring, int>> &vec2);


/**
 * @brief 计算 L2 范数
 * @param vec1
 * @param vec2
 * @return double
 */
double getL2Norm(const myvec<pair<std::wstring, int>> &vec1,
    const myvec<pair<std::wstring, int>> &vec2);


/**
 * @brief 计算余弦距离
 * @param vec1
 * @param vec2
 * @return double
 */
double getCosDistance(const myvec<pair<std::wstring, int>> &vec1,
    const myvec<pair<std::wstring, int>> &vec2);


/**
 * @brief 计算两个代码的差距
 * @param map1 代码 1 的词频
 * @param map2 代码 2 的词频
 * @return CString 分析结果
 */
CString calcDiff(const mymap<std::wstring, int> &map1,
    const mymap<std::wstring, int> &map2);


/**
 * @brief 将分析结果写入弹出的对话框
 * @param codebox1 代码 1
 * @param codebox2 代码 2
 * @param infobox 分析结果 (居中)
 * @param tokenbox1 代码 1 的令牌 (左边)
 * @param tokenbox2 代码 2 的令牌 (右边)
 */
void analyse(CWnd *codebox1, CWnd *codebox2, CWnd *infobox,
    CWnd *tokenbox1, CWnd *tokenbox2);
