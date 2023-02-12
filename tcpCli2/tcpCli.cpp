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

	SOCKET sockCli = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrCli;
	addrCli.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrCli.sin_family = AF_INET;
	addrCli.sin_port = htons(6000);

	connect(sockCli, (SOCKADDR*)&addrCli, sizeof(SOCKADDR));

	char sendBuf[] = { "hello" };
	char recvBuf[100] = {0};

	// 发送数据到服务器
	send(sockCli, sendBuf, strlen(sendBuf) + 1, 0);

	// 接收服务器发送的数据
	recv(sockCli, recvBuf, sizeof(recvBuf), 0);

	std::cout << recvBuf << std::endl;

	// 关闭套接字
	closesocket(sockCli);

	// 清理套接字库
	WSACleanup();
}