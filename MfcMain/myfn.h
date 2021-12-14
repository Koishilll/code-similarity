#pragma once
#include "pch.h"

void openFileToEditbox(CWnd *editbox);
auto getNextToken(CString &code, size_t pos);
void analyse(CWnd *infobox, CWnd *codebox1, CWnd *codebox2);
