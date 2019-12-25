
// MFC_ChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC_ChatClient.h"
#include "MFC_ChatClientDlg.h"
#include "afxdialogex.h"

#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_CHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_SENGMSG_EDIT, m_intput);
	DDX_Control(pDX, IDC_COLOR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BNT, &CMFCChatClientDlg::OnBnClickedConnectBnt)//标记 Mark
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CMFCChatClientDlg::OnBnClickedDisconnectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_SAVENAME_BTN, &CMFCChatClientDlg::OnBnClickedSavenameBtn)
	//ON_BN_CLICKED(IDC_AUTIOSEND_RADIO, &CMFCChatClientDlg::OnBnClickedAutiosendRadio)
	ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCChatClientDlg::OnBnClickedClearmsgBtn)
	ON_BN_CLICKED(IDC_AUTIOSEND_CHECK, &CMFCChatClientDlg::OnBnClickedAutiosendCheck)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//设置固定的端口号
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	//从配置文件里面获取昵称
	WCHAR wszName[MAX_PATH] = { 0 };
	WCHAR strPath[MAX_PATH] = { 0 };
	//获取当前路径
	GetCurrentDirectoryW(MAX_PATH, strPath);

	CString strFilePath;
	strFilePath.Format(L"%ls//Test.ini", strPath);

	DWORD dwNum = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL,
		wszName, MAX_PATH, strFilePath);
	if (dwNum > 0)
	{
		SetDlgItemText(IDC_NAME_EDIT, wszName);
		UpdateData(false);
	}
	else
	{
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), L"客户端", strFilePath);
		SetDlgItemText(IDC_NAME_EDIT, L"客户端");
		UpdateData(false);
	}

	//当没有连接到服务器的时候，断开连接、发送、自动回复消息都是不可点击的
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(false);       //发送按钮
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(false); //断开连接
	GetDlgItem(IDC_AUTIOSEND_CHECK)->EnableWindow(false);//自动回复消息
	GetDlgItem(IDC_CONNECT_BNT)->EnableWindow(true);     //连接服务器

	//添加颜色
	m_WordColorCombo.AddString(L"黑色");
	m_WordColorCombo.AddString(L"红色");
	m_WordColorCombo.AddString(L"蓝色");
	m_WordColorCombo.AddString(L"绿色");

	m_WordColorCombo.SetCurSel(0);

	SetDlgItemText(IDC_COLOR_COMBO, L"黑色");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//第一步  确定目的区域    第二步  加载资源图片并且转化为内存设备  第三步 绘图
		//1.定义DC
		CPaintDC dc(this); // 用于绘制的设备上下文
		//2.确定绘制的（目的）区域
		CRect rect;
		GetClientRect(&rect);

		//3.定义并创建一个内存设备环境 创建兼容性DC （搭桥梁）
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);

		//4.载入资源图片
		CBitmap bmpBackGround;
		bmpBackGround.LoadBitmapW(IDB_CLOUD_BITMAP);

		//5.将图片资源载入到位图里面 BitMap 位图
		BITMAP bBitMap;
		bmpBackGround.GetBitmap(&bBitMap);

		//6.将位图选入临时的内存设备环境
		CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackGround);

		//7.开始绘制
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp,
			0, 0, bBitMap.bmWidth, bBitMap.bmHeight, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//连接按钮的处理函数
void CMFCChatClientDlg::OnBnClickedConnectBnt()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(true);       //发送按钮
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(true); //断开连接
	GetDlgItem(IDC_AUTIOSEND_CHECK)->EnableWindow(true);//自动回复消息
	GetDlgItem(IDC_CONNECT_BNT)->EnableWindow(false);     //连接服务器

	//拿到 端口 和 IP
	TRACE("[ChatClient]Connect Btn");
	//端口  IP
	CString strPort, strIP;
	//重控件里面获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);

	//CString 转 char*
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	LPCSTR szIP = (LPCSTR)T2A(strIP);
	TRACE("szPort=%s,szIP=%s", szPort, szIP);

	//把字符串转换为数字
	int iPort = _ttoi(strPort);
	//1.创建一个 socket 对象
	m_client = new CMySocket;
	//创建套接字  容错率
	if (!m_client->Create())
	{
		TRACE("创建客服端失败！%d", GetLastError());
		return;
	}
	else
	{
		TRACE("创建成功！");
	}

	//连接 容错率
	//if (!m_client->Connect(strIP, iPort))
	//{
		//会报错   Connect 是 bool 值 不能直接是非零函数
		//但是也不会影响
	//}
	if (m_client->Connect(strIP, iPort) != SOCKET_ERROR)
	{
		TRACE("客服端连接失败！%d", GetLastError());
		return;
	}

}//标记 Mark

//断开连接的处理函数
void CMFCChatClientDlg::OnBnClickedDisconnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//1.控制控件
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(false);       //发送按钮
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(false); //断开连接
	GetDlgItem(IDC_AUTIOSEND_CHECK)->EnableWindow(false);//自动回复消息
	GetDlgItem(IDC_CONNECT_BNT)->EnableWindow(true);     //连接服务器

	//2.回收资源
	m_client->Close();
	if (m_client != NULL)
	{
		delete m_client;
		m_client = NULL;
	}
	//3.显示到列表框
	CString strShow;
	strShow = CatShowString(L" ", L"已经断开与服务器的连接！");
	m_list.AddString(strShow);
	UpdateData(false);
}

//发送消息的函数（包装）
CString CMFCChatClientDlg::CatShowString(CString strInfo, CString strMsg)
{
	//时间 + 信息（昵称） + 消息
	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X ");
	CString strShow;
	strShow = strTime + strShow;
	strShow += strInfo;
	strShow += strMsg;
	return strShow;
}

//发送消息的处理函数
void CMFCChatClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//1.获取编辑框内容
	CString strTmpMsg;
	GetDlgItem(IDC_SENGMSG_EDIT)->GetWindowText(strTmpMsg);
	CString strName;
	GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(strName);

	strTmpMsg = strName + L": " + strTmpMsg;

	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);

	//2.发送消息给服务端
	m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

	//3.显示到列表框中
	CString strShow;
	//CString strInfo = strName + L": ";
	strShow = CatShowString(L" ", strTmpMsg);
	m_list.AddString(strShow);
	UpdateData(false);

#if 0
	CString strShow;
	CString strInfo = _T("我: ");
	CString strTime;
	m_tm = CTime::GetCurrentTime();
	strTime = m_tm.Format("%X ");
	strShow = strTime + strShow; //时间 + 我：内容
	strShow += strTmpMsg;
#endif

	//清空编辑框
	GetDlgItem(IDC_SENGMSG_EDIT)->SetWindowText(_T(" "));
}

//保存昵称的处理函数
void CMFCChatClientDlg::OnBnClickedSavenameBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName);
	if (strName.GetLength() <= 0)
	{
		MessageBox(L"昵称不能为空！");
		return;
	}

	if (IDOK == AfxMessageBox(_T("真的要修改昵称吗？"), MB_OKCANCEL))
	{
		WCHAR strPath[MAX_PATH] = { 0 };
		//获取当前路径
		GetCurrentDirectoryW(MAX_PATH, strPath);
		TRACE("#### strPath=%ls", strPath);
		CString strFilePath;
		strFilePath.Format(L"%ls//Test.ini", strPath);

		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
	}
}


//void CMFCChatClientDlg::OnBnClickedAutiosendRadio()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	if (((CButton*)GetDlgItem(IDC_AUTIOSEND_RADIO))->GetCheck())
//	{
//		((CButton*)GetDlgItem(IDC_AUTIOSEND_RADIO))->SetCheck(false);
//	}
//	else
//	{
//		((CButton*)GetDlgItem(IDC_AUTIOSEND_RADIO))->SetCheck(true);
//	}
//
//}

//清除屏幕的处理函数
void CMFCChatClientDlg::OnBnClickedClearmsgBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}

//点击 自动回复的 处理函数
void CMFCChatClientDlg::OnBnClickedAutiosendCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AUTIOSEND_CHECK))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_AUTIOSEND_CHECK))->SetCheck(false);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_AUTIOSEND_CHECK))->SetCheck(true);
	}
}

//更改颜色的处理函数
HBRUSH CMFCChatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	CString strColor;
	m_WordColorCombo.GetWindowTextW(strColor);

	if (IDC_LIST1 == pWnd->GetDlgCtrlID() || IDC_SENGMSG_EDIT == pWnd->GetDlgCtrlID()) {
		if (strColor == L"黑色")
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		if (strColor == L"红色")
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		if (strColor == L"蓝色")
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		if (strColor == L"绿色")
		{
			pDC->SetTextColor(RGB(0, 255, 0));
		}
	}

	return hbr;
}

//防止点击 回车键 退出程序的处理函数
BOOL CMFCChatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	//规避回车键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return true;
	}

	//规避空格键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE)
	{
		return true;
	}

	//添加快捷键
	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetKeyState(VK_CONTROL) < 0)//Ctrl 是否按下
		{
			if (pMsg->wParam == 'X')
			{
				CDialogEx::OnOK();
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
