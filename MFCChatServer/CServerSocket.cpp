#include "pch.h"
#include "CServerSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"

CServerSocket::CServerSocket()
{

}
CServerSocket::~CServerSocket()
{

}

// ����Listen
void CServerSocket::OnAccept(int nErrorCode)
{
	TRACE("##Server OnAccept");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();

	// ����
	dlg->m_chat = new CChatSocket;
	Accept(*(dlg->m_chat));

	CString strShow;
	strShow = dlg->CatShowString(_T(""), _T("�ͻ������ӳɹ�"));
	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(false);

	CAsyncSocket::OnAccept(nErrorCode);
}
