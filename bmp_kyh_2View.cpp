
// bmp_kyh_2View.cpp: Cbmpkyh2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "bmp_kyh_2.h"
#endif

#include "bmp_kyh_2Doc.h"
#include "bmp_kyh_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cbmpkyh2View

IMPLEMENT_DYNCREATE(Cbmpkyh2View, CScrollView)

BEGIN_MESSAGE_MAP(Cbmpkyh2View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cbmpkyh2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cbmpkyh2View 생성/소멸

Cbmpkyh2View::Cbmpkyh2View()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));

	for (int i = 0; i < 256; i++)
	{
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbReserved = 0;
	}
}

Cbmpkyh2View::~Cbmpkyh2View()
{
	if (BmInfo) delete BmInfo;
}

BOOL Cbmpkyh2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// Cbmpkyh2View 그리기

void Cbmpkyh2View::OnDraw(CDC* pDC)
{
#define WIDTHBYTES(bits)	(((bits)+31)/32*4);        //이미지 가로 바이트 길이는 4바이트의 배수

	//BmInfo;

	int height;

	int width;

	int rwsize;



	CBmpReadingDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (!pDoc)

		return;



	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	if (pDoc->m_InImg == NULL)

		return;



	//24비트 비트맵 파일의 영상출력

	if (pDoc->dibHi.biBitCount == 24) {

		height = pDoc->dibHi.biHeight;
		width = pDoc->dibHi.biWidth;
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth);

		BmInfo->bmiHeader = pDoc->dibHi;
		SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height, 0, 0, 0, height, pDoc->m_InImg, BmInfo, DIB_RGB_COLORS);

	}

	else	//8비트 컬러일 경우

	{
		int index;
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth);

		//팔레트를 읽어들이며 반복출력
		for (int i = 0; i < pDoc->dibHi.biHeight; i++)
			for (int j = 0; j < pDoc->dibHi.biWidth; j++) 
			{
				index = pDoc->m_InImg[i*rwsize + j];
				BYTE R = pDoc->palRGB[index].rgbRed;
				BYTE G = pDoc->palRGB[index].rgbGreen;

				BYTE B = pDoc->palRGB[index].rgbBlue;



				//pDC->SetPixel(j,i,RGB(R,G,B));
				//영상 반전출력

				pDC->SetPixel(j, pDoc->dibHi.biHeight - i - 1, RGB(R, G, B));



			}

	}

}

void Cbmpkyh2View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// Cbmpkyh2View 인쇄


void Cbmpkyh2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cbmpkyh2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Cbmpkyh2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Cbmpkyh2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void Cbmpkyh2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cbmpkyh2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cbmpkyh2View 진단

#ifdef _DEBUG
void Cbmpkyh2View::AssertValid() const
{
	CScrollView::AssertValid();
}

void Cbmpkyh2View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

Cbmpkyh2Doc* Cbmpkyh2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cbmpkyh2Doc)));
	return (Cbmpkyh2Doc*)m_pDocument;
}
#endif //_DEBUG


// Cbmpkyh2View 메시지 처리기
