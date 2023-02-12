#include <WinSock2.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	// 初始化套接字库
	WORD wVersion = MAKEWORD(1, 1); // b | a << 8
	WSADATA wsadata;
	int err;

	err = WSAStartup(wVersion, &wsadata);
	if (err != 0)
	{
		return err;
	}
	if (LOBYTE(wsadata.wVersion) != 1 || HIBYTE(wsadata.wVersion) != 1)
	{
		// 清理套接字库
		WSACleanup();
		return -1;
	}

	SOCKET sockCli = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = 6002;

	SOCKADDR_IN addrCli;
	int len = sizeof(SOCKADDR);

	char sendBuf[] = "send from udp client";
	char recvBuf[100];

	sendto(sockCli, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrSrv, len);
	recvfrom(sockCli, recvBuf, 100, 0, (SOCKADDR*)&addrCli, &len);

	std::cout << recvBuf << std::endl;

	closesocket(sockCli);


	WSACleanup();
}

