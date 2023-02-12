#include <WinSock2.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")


int main()
{
	// ��ʼ���׽��ֿ�
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
		// �����׽��ֿ�
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

	// �������ݵ�������
	send(sockCli, sendBuf, strlen(sendBuf) + 1, 0);

	// ���շ��������͵�����
	recv(sockCli, recvBuf, sizeof(recvBuf), 0);

	std::cout << recvBuf << std::endl;

	// �ر��׽���
	closesocket(sockCli);

	// �����׽��ֿ�
	WSACleanup();
}