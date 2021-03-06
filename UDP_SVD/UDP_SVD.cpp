#include "stdafx.h"
#include "hoxy_Header.h"

SOCKET g_serverSock;
UCHAR g_protocal[10] = { 0xff, 0xee, 0xdd, 0xaa, 0x00, 0x99, 0x77, 0x55, 0x33, 0x11 };

int main()
{
	// 초기화
	CCmdStart myCmdStart;
	CCmdStart::CmdDebugText(L"Start", true);
	CSockUtill::WSAStart();

	// 1. UDP 소켓 생성
	g_serverSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (g_serverSock == INVALID_SOCKET)
	{
		CCmdStart::CmdDebugText(L"socket()", false);
	}

	// 2. 브로드캐스팅 활성화(소켓옵션 : 책참고, 옵션인자 : MSDN 참고)
	CSockUtill::SetBroadCast(g_serverSock, true);

	// 포트범위 - 19001 ~ 19099
	for (int i = 19001; i <= 19099; i++)
	{
		// 3. 브로드캐스팅 시 IP 는 INADDR_BROADCAST / 255.255.255.255
		SOCKADDR_IN serverAddr;
		serverAddr.sin_family = AF_INET;
		InetPton(AF_INET, L"255.255.255.255", &serverAddr.sin_addr.s_addr);
		serverAddr.sin_port = htons(i);

		// 4. 프로토콜로 데이터 UDP 쏘기
		int ret_sendto = sendto(g_serverSock, (const char*)g_protocal, 10, 0, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR));
		if (ret_sendto < 0)
		{
			CCmdStart::CmdDebugText(L"sendto", false);
		}

		// 5. 200밀리세컨드 동안 데이터 수신 확인
		FD_SET rset;
		FD_ZERO(&rset);
		FD_SET(g_serverSock, &rset);

		timeval myTime;
		myTime.tv_sec = 0;
		myTime.tv_usec = 200 * 1000;

		int ret_select = select(0, &rset, 0, 0, &myTime);
		if (ret_select > 0)
		{
			char buf[100];
			ZeroMemory(buf, 100);
			SOCKADDR_IN recvedAddr;
			ZeroMemory(&recvedAddr, sizeof(SOCKADDR_IN));
			int addrSize = sizeof(SOCKADDR);

			int ret_recv = recvfrom(g_serverSock, buf, 100, 0, (SOCKADDR*)&recvedAddr, &addrSize);
			if (ret_recv < 0)
			{
				CCmdStart::CmdDebugText(L"sendto", false);
			}

			// 6. 데이터 오면 해당 송신자 확인, 데이터 확인 후 IP, Port, 방이름 출력
			wcout << L"recved : " << ret_recv << endl;

			WCHAR ipText[20] = {};
			InetNtop(AF_INET, &recvedAddr.sin_addr.s_addr, ipText, 20);
			wcout << L"ip : " << ipText << endl;
			wcout << L"port : " << i << endl;

			//wprintf(L"%ws\n", (WCHAR*)buf);
			wcout << (WCHAR*)buf << endl;
			wcout << L"---------------------------------------------------" << endl;
		}
		else
		{
			//wcout << L"not found : " << i << endl;
		}
	}

	return 0;
}