#include "pch.h"
#include "CMySocket.h"
#include "MFC_ChatClientDlg.h"
#include "MFC_ChatClient.h"

CMySocket::CMySocket()//���캯��
{

}

CMySocket::~CMySocket()
{

}

// �ص� ��д��Ҫ�������ǵ��Լ���Ƶ�������;��������
void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("#######OnConnect");

	//���������ȡ������
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	//��ʾ��Ϣ
#if 0
	CString str;
	//�õ���ǰ�������׼ȷʱ��
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X");//
	str += _T("����������ӳɹ�");//��ʾΪ  ʱ��+����������ӳɹ�  ĳĳĳʱ������������ӳɹ�
#endif
	CString strShow;
	CString strInfo = _T(" ");
	CString strMsg = _T("����������ӳɹ�!");
	strShow = dlg->CatShowString(strInfo, strMsg);

	dlg->m_list.AddString(strShow);   //��ʾ�����ڵ� LIstBox �ؼ���

	CAsyncSocket::OnConnect(nErrorCode);//�����ص�
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("#######OnReceive");
	//1. �������ݵ� szRecvBuf
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();

	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("#### Server szRecv=%d", szRecvBuf);

	//2.��ʾ szRecvBuf
	USES_CONVERSION;

	CString strRecvMsg = A2W(szRecvBuf);
#if 0
	CString strShow = _T("�����: ");
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X ");
	strShow = strTime + strShow; //ʱ�� + �ң�����
	strShow += strRecvMsg;
#endif
	//3.��ʾ���б��
	CString strShow;
	CString strInfo = _T("�����: ");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);

	//ѡ�е�ѡ��ť
	if (((CButton*)dlg->GetDlgItem(IDC_AUTIOSEND_CHECK))->GetCheck())
	{
		//�Զ��ظ�
		//1.���༭�������
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSEND_EDIT, strAutoSendMsg);
		//��� + ���ʽ     ʱ�� + �ǳ� + [�Զ��ظ�] + ����  ���͸�����˵���Ϣ
		CString strName;
		dlg->GetDlgItemText(IDC_NAME_EDIT, strName);

		CString strMsg = strName + _T(" :[�Զ��ظ�]: ") + strAutoSendMsg;

		char* szSendBuf = T2A(strMsg);
		dlg->m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

		//ʱ�� + �ǳ� + ����
		strShow = dlg->CatShowString(_T(" "), strMsg);
		dlg->m_list.AddString(strShow);
		dlg->m_list.UpdateData(false);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}
