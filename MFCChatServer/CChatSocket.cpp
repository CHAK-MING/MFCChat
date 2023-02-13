#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServerDlg.h"
#include "MFCChatServer.h"


CChatSocket::CChatSocket()
{

}

CChatSocket::~CChatSocket()
{

}

void CChatSocket::OnReceive(int nErrorCode)
{
	// 1. �������ݵ�buffer
	TRACE("##Server OnReceive");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[MAX_SERVER_BUF] = { 0 };
	Receive(szRecvBuf, MAX_SERVER_BUF, 0);
	TRACE("##Server szRecvBuf = %s", szRecvBuf);

	// ��ʾBuffer
	USES_CONVERSION;
	CString strShow;
	CString strRecvMsg = A2W(szRecvBuf);
	strShow = dlg->CatShowString(_T(""), strRecvMsg);
	dlg->m_list.AddString(strShow);


	CAsyncSocket::OnReceive(nErrorCode);
}
