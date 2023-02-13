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

// ���ӻ�����ûص�����
void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("##Client OnConnect");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	CString strShow;
	strShow = dlg->CatShowString(_T(""), _T("����������ӳɹ�"));
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

	// ��ʾBuffer
	USES_CONVERSION;
	CString strShow;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strInfo = _T("�����: ");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);
	dlg->m_list.AddString(strShow);
	
	// ѡ�е�ѡ��ť
	if (((CButton*)(dlg->GetDlgItem(IDC_AUTOSENDMSG_CHECK)))->GetCheck())
	{
		// �Զ��ظ�
		// 1.���༭�������
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, strAutoSendMsg);
		// 2.���+���ʽ
		CString strInfo;
		dlg->GetDlgItemTextW(IDC_NAME_EDIT, strInfo);
		strInfo += ": [�Զ��ظ�]";
		CString strMsg = dlg->CatShowString(strInfo, strAutoSendMsg);
		char* szSendBuf = T2A(strInfo + strAutoSendMsg);
		dlg->m_client->Send(szSendBuf,SEND_MAX_BUF,0);
		dlg->m_list.AddString(strMsg);
		dlg->UpdateData(FALSE);
	}
	
	CAsyncSocket::OnReceive(nErrorCode);
}