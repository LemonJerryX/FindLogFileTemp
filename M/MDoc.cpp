
// MDoc.cpp : CMDoc ���ʵ��
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


// CMDoc ����/����

CMDoc::CMDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMDoc::~CMDoc()
{
}

BOOL CMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMDoc ���л�

void CMDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CMDoc ���

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


// CMDoc ����
