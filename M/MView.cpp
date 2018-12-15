
// MView.cpp : CMView ���ʵ��
//

#include "stdafx.h"
#include "M.h"

#include "MDoc.h"
#include "MView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMView

IMPLEMENT_DYNCREATE(CMView, CView)

BEGIN_MESSAGE_MAP(CMView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMView ����/����

CMView::CMView()
{
	// TODO: �ڴ˴���ӹ������

}

CMView::~CMView()
{
}

BOOL CMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMView ����

void CMView::OnDraw(CDC* /*pDC*/)
{
	CMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMView ��ӡ


void CMView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMView ���

#ifdef _DEBUG
void CMView::AssertValid() const
{
	CView::AssertValid();
}

void CMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDoc* CMView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDoc)));
	return (CMDoc*)m_pDocument;
}
#endif //_DEBUG


// CMView ��Ϣ�������
