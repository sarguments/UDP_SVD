#include "stdafx.h"
#include "hoxy_Header.h"
#include "hoxy_CmdStart.h"

CCmdStart::CCmdStart()
{
	// ���� �õ�
	srand((unsigned int)time(NULL));

	//HANDLE  hConsole;
	//CONSOLE_CURSOR_INFO stConsoleCursor;

	////-------------------------------------------------------------
	//// ȭ���� Ŀ���� �Ⱥ��̰Բ� �����Ѵ�.
	////-------------------------------------------------------------
	//stConsoleCursor.bVisible = FALSE;
	//stConsoleCursor.dwSize = 1;			// Ŀ�� ũ��.
	//// �̻��ϰԵ� 0 �̸� ���´�. 1���ϸ� �ȳ��´�.

	////-------------------------------------------------------------
	//// �ܼ�ȭ�� (���ٴٵ� �ƿ�ǲ) �ڵ��� ���Ѵ�.
	////-------------------------------------------------------------
	//hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleCursorInfo(hConsole, &stConsoleCursor);

	//// �ܼ� â ����
	//AllocConsole();
	//FILE *acStreamOut;
	//freopen_s(&acStreamOut, "CONOUT$", "wt", stdout);

	//_wsetlocale(LC_ALL, L"");
	// ó�� �ѹ���
	//std::locale::global(std::locale(""));
	//CCmdStart::CmdDebugText(L"Locale Init", true);
}

CCmdStart::~CCmdStart()
{
}

void CCmdStart::CmdDebugText(WCHAR* text, bool bParam)
{
	if (bParam)
	{
		wcout << std::setw(20) << text << std::setw(50) << L"|OK|" << endl;
	}
	else
	{
		wcout << std::setw(20) << text << std::setw(40) << L"|ERROR| : " << std::setw(10) << GetLastError() << endl;
	}
}