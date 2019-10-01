
// PenView.cpp: CPenView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Pen.h"
#endif

#include "PenDoc.h"
#include "PenView.h"
#include "CLine.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPenView

IMPLEMENT_DYNCREATE(CPenView, CView)

BEGIN_MESSAGE_MAP(CPenView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MENU_COLOR, &CPenView::OnMenuColor)
	ON_COMMAND_RANGE(ID_SIZE_1,ID_SIZE_32, OnSize)
END_MESSAGE_MAP()

// CPenView 생성/소멸

CPenView::CPenView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPenView::~CPenView()
{
}

BOOL CPenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPenView 그리기

void CPenView::OnDraw(CDC* pDC)
{
	CPenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int n = pDoc->m_oa.GetSize();
	CLine* p;


	for (int i = 0; i < n; i++) {
		p = (CLine*)pDoc->m_oa[i];
		p->Draw(pDC);
	}
}


// CPenView 인쇄

BOOL CPenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPenView 진단

#ifdef _DEBUG
void CPenView::AssertValid() const
{
	CView::AssertValid();
}

void CPenView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPenDoc* CPenView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPenDoc)));
	return (CPenDoc*)m_pDocument;
}
#endif //_DEBUG


// CPenView 메시지 처리기


void CPenView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	Size = 16;
	Col = RGB(0, 255, 0);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CPenView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags == MK_LBUTTON) {
		CLine* p = new CLine(Pnt, point, Size, Col);
		GetDocument()->m_oa.Add(p);
		Invalidate(false);
	}
	Pnt = point;
	CView::OnMouseMove(nFlags, point);
}


void CPenView::OnMenuColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		Col = dlg.GetColor();
	}
}




void CPenView::OnSize(UINT sel)
{
	// TODO: 여기에 구현 코드 추가.
	Size = sel - ID_SIZE_1+1;
	Size *= 8;
}
