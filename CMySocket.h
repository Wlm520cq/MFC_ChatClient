#pragma once
#include <afxsock.h>

class CMySocket :
	public CAsyncSocket
{
public:
	CMySocket();//���캯��
	virtual ~CMySocket();//virtual��д����   ��������
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

