#include <WinSock2.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	// ��ʼ���׽��ֿ�
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
		// �����׽��ֿ�
		WSACleanup();
		return -1;
	}

	// �����׽���
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	// �󶨵�����
	bind(sockSrv, (SOCKADDR*)(&addrSrv), sizeof(SOCKADDR));
	
	// ����
	listen(sockSrv, 10);

	std::cout << "Server start at 6000" << std::endl;

	SOCKADDR_IN addrCli;
	int len = sizeof(SOCKADDR);

	char recvBuf[100];
	char sendBuf[100];
	while (true)
	{
		// ������������
		SOCKET sockCli = accept(sockSrv, (SOCKADDR*)&addrCli, &len);
		// ���ܻ�������
		sprintf(sendBuf, "hello");
		send(sockCli, sendBuf, strlen(sendBuf) + 1, 0);
		recv(sockCli, recvBuf, sizeof(recvBuf), 0);
		std::cout << recvBuf << std::endl;

		closesocket(sockCli);
	}

	// �ر��׽���
	closesocket(sockSrv);

	// �����׽��ֿ�
	WSACleanup();
}