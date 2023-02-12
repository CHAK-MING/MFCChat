#include <WinSock2.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	// 初始化套接字库
	WORD wVersion = MAKEWORD(1,1); // b | a << 8
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

	// 创建套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	// 绑定到本机
	bind(sockSrv, (SOCKADDR*)(&addrSrv), sizeof(SOCKADDR));
	
	// 监听
	listen(sockSrv, 10);

	std::cout << "Server start at 6000" << std::endl;

	SOCKADDR_IN addrCli;
	int len = sizeof(SOCKADDR);

	char recvBuf[100];
	char sendBuf[100];
	while (true)
	{
		// 接受连接请求
		SOCKET sockCli = accept(sockSrv, (SOCKADDR*)&addrCli, &len);
		// 接受或发送数据
		sprintf(sendBuf, "hello");
		send(sockCli, sendBuf, strlen(sendBuf) + 1, 0);
		recv(sockCli, recvBuf, sizeof(recvBuf), 0);
		std::cout << recvBuf << std::endl;

		closesocket(sockCli);
	}

	// 关闭套接字
	closesocket(sockSrv);

	// 清理套接字库
	WSACleanup();
}