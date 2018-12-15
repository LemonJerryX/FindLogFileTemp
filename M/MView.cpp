
// MView.cpp : CMView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMView 构造/析构

CMView::CMView()
{
	// TODO: 在此处添加构造代码

}

CMView::~CMView()
{
}

BOOL CMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMView 绘制

void CMView::OnDraw(CDC* /*pDC*/)
{
	CMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMView 打印


void CMView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CMView 诊断

#ifdef _DEBUG
void CMView::AssertValid() const
{
	CView::AssertValid();
}

void CMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDoc* CMView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDoc)));
	return (CMDoc*)m_pDocument;
}
#endif //_DEBUG


// CMView 消息处理程序
