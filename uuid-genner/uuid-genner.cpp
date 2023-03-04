// uuid-genner.cpp : 此文件包含 "wmain" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS

//简洁起见，我不会在这个项目里附加my-gists作为submodle，不过你可以在 https://github.com/steve02081504/my-gists 找到它。
#include "my-gists/windows/MD5maker.hpp"
#include "my-gists/codepage.hpp"
#include "my-gists/base64.h"
#include <iostream>

int wmain(int argc, wchar_t* argv[]) {
	if(argc < 2) {
		std::wcout << L"Usage: uuid-genner.exe <string>" << std::endl;
		return 0;
	}
	std::wstring str = argv[1];
	using namespace CODEPAGE_n;
	std::string utf8str	 = UnicodeToMultiByte(str, CP_UTF8);
	auto		md5		 = MD5maker.get_str_md5(utf8str);
	auto		md5_view = std::string{(char*)md5.digest, 16};
	std::cout << EncodeBase64(md5_view) << std::endl;
	return 0;
}
