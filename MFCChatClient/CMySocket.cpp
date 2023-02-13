#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

// 连接会进到该回调函数
void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("##Client OnConnect");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	CString strShow;
	strShow = dlg->CatShowString(_T(""), _T("与服务器连接成功"));
	dlg->m_list.AddString(strShow);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("##Client OnReceive");

	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("##Client szRecvBuf = %s", szRecvBuf);

	// 显示Buffer
	USES_CONVERSION;
	CString strShow;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strInfo = _T("服务端: ");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);
	dlg->m_list.AddString(strShow);
	
	// 选中单选框按钮
	if (((CButton*)(dlg->GetDlgItem(IDC_AUTOSENDMSG_CHECK)))->GetCheck())
	{
		// 自动回复
		// 1.读编辑框的内容
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, strAutoSendMsg);
		// 2.封包+组格式
		CString strInfo;
		dlg->GetDlgItemTextW(IDC_NAME_EDIT, strInfo);
		strInfo += ": [自动回复]";
		CString strMsg = dlg->CatShowString(strInfo, strAutoSendMsg);
		char* szSendBuf = T2A(strInfo + strAutoSendMsg);
		dlg->m_client->Send(szSendBuf,SEND_MAX_BUF,0);
		dlg->m_list.AddString(strMsg);
		dlg->UpdateData(FALSE);
	}
	
	CAsyncSocket::OnReceive(nErrorCode);
}