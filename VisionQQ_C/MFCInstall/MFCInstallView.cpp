
// MFCInstallView.cpp: CMFCInstallView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCInstall.h"
#endif

#include "MFCInstallDoc.h"
#include "MFCInstallView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCInstallView

IMPLEMENT_DYNCREATE(CMFCInstallView, CView)

BEGIN_MESSAGE_MAP(CMFCInstallView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCInstallView 构造/析构

CMFCInstallView::CMFCInstallView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCInstallView::~CMFCInstallView()
{
}

BOOL CMFCInstallView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCInstallView 绘图

void CMFCInstallView::OnDraw(CDC* /*pDC*/)
{
	CMFCInstallDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCInstallView 打印

BOOL CMFCInstallView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCInstallView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCInstallView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCInstallView 诊断

#ifdef _DEBUG
void CMFCInstallView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCInstallView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCInstallDoc* CMFCInstallView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCInstallDoc)));
	return (CMFCInstallDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCInstallView 消息处理程序
