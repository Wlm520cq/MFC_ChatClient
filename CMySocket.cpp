#include "pch.h"
#include "CMySocket.h"
#include "MFC_ChatClientDlg.h"
#include "MFC_ChatClient.h"

CMySocket::CMySocket()//构造函数
{

}

CMySocket::~CMySocket()
{

}

// 回调 重写：要满足我们的自己设计的特殊用途：传参数
void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("#######OnConnect");

	//点击按键获取到窗口
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	//显示信息
#if 0
	CString str;
	//得到当前计算机的准确时间
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X");//
	str += _T("与服务器连接成功");//表示为  时间+与服务器连接成功  某某某时间与服务器连接成功
#endif
	CString strShow;
	CString strInfo = _T(" ");
	CString strMsg = _T("与服务器连接成功!");
	strShow = dlg->CatShowString(strInfo, strMsg);

	dlg->m_list.AddString(strShow);   //显示到窗口的 LIstBox 控件上

	CAsyncSocket::OnConnect(nErrorCode);//类名回调
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("#######OnReceive");
	//1. 接受数据到 szRecvBuf
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();

	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("#### Server szRecv=%d", szRecvBuf);

	//2.显示 szRecvBuf
	USES_CONVERSION;

	CString strRecvMsg = A2W(szRecvBuf);
#if 0
	CString strShow = _T("服务端: ");
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X ");
	strShow = strTime + strShow; //时间 + 我：内容
	strShow += strRecvMsg;
#endif
	//3.显示到列表框
	CString strShow;
	CString strInfo = _T("服务端: ");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);

	//选中单选框按钮
	if (((CButton*)dlg->GetDlgItem(IDC_AUTIOSEND_CHECK))->GetCheck())
	{
		//自动回复
		//1.读编辑框的内容
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSEND_EDIT, strAutoSendMsg);
		//封包 + 组格式     时间 + 昵称 + [自动回复] + 内容  发送个服务端的消息
		CString strName;
		dlg->GetDlgItemText(IDC_NAME_EDIT, strName);

		CString strMsg = strName + _T(" :[自动回复]: ") + strAutoSendMsg;

		char* szSendBuf = T2A(strMsg);
		dlg->m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

		//时间 + 昵称 + 内容
		strShow = dlg->CatShowString(_T(" "), strMsg);
		dlg->m_list.AddString(strShow);
		dlg->m_list.UpdateData(false);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}
