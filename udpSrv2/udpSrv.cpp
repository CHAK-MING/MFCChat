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

	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = 6002;

	// 绑定到本机指定端口
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	// 接受请求，处理请求
	SOCKADDR_IN addrCli;
	int len = sizeof(SOCKADDR_IN);

	char sendBuf[] = "udp Server...";
	char recvBuf[100];

	while (true)
	{
		recvfrom(sockSrv, recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&addrCli, &len);
		std::cout << recvBuf << std::endl;

		sendto(sockSrv, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrCli, len);
	}

	closesocket(sockSrv);
	WSACleanup();
}