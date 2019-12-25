#pragma once
#include <afxsock.h>

class CMySocket :
	public CAsyncSocket
{
public:
	CMySocket();//构造函数
	virtual ~CMySocket();//virtual重写函数   析构函数
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

