
// MDoc.cpp : CMDoc 类的实现
//

#include "stdafx.h"
#include "M.h"

#include "MDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMDoc

IMPLEMENT_DYNCREATE(CMDoc, CDocument)

BEGIN_MESSAGE_MAP(CMDoc, CDocument)
END_MESSAGE_MAP()


// CMDoc 构造/析构

CMDoc::CMDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMDoc::~CMDoc()
{
}

BOOL CMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMDoc 序列化

void CMDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CMDoc 诊断

#ifdef _DEBUG
void CMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMDoc 命令
