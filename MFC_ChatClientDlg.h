
// MFC_ChatClientDlg.h: 头文件
//

#pragma once
#include "CMySocket.h"

// CMFCChatClientDlg 对话框
class CMFCChatClientDlg : public CDialogEx
{
// 构造
public:
	CMFCChatClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CHATCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnectBnt();//标记  mark
	afx_msg void OnBnClickedDisconnectBtn();
	CMySocket* m_client;
	CListBox m_list;
	CEdit m_intput;
	afx_msg void OnBnClickedSendBtn();
	CString CatShowString(CString strInfo, CString strMsg);
	afx_msg void OnBnClickedSavenameBtn();
	//afx_msg void OnBnClickedAutiosendRadio();
	afx_msg void OnBnClickedClearmsgBtn();
	afx_msg void OnBnClickedAutiosendCheck();
	CComboBox m_WordColorCombo;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
