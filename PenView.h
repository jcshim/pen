
// PenView.h: CPenView 클래스의 인터페이스
//

#pragma once


class CPenView : public CView
{
protected: // serialization에서만 만들어집니다.
	CPenView() noexcept;
	DECLARE_DYNCREATE(CPenView)

// 특성입니다.
public:
	CPenDoc* GetDocument() const;

// 작업입니다.
public:
	CPoint Pnt;
	COLORREF Col;
	int Size;
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CPenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMenuColor();
	void OnSize(UINT size);
};

#ifndef _DEBUG  // PenView.cpp의 디버그 버전
inline CPenDoc* CPenView::GetDocument() const
   { return reinterpret_cast<CPenDoc*>(m_pDocument); }
#endif

