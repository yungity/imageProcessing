
// ImageProcessing_KYH_3View.cpp: CImageProcessingKYH3View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing_KYH_3.h"
#endif

#include "ImageProcessing_KYH_3Doc.h"
#include "ImageProcessing_KYH_3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingKYH3View

IMPLEMENT_DYNCREATE(CImageProcessingKYH3View, CView)

BEGIN_MESSAGE_MAP(CImageProcessingKYH3View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DOWN_SAMPLING, &CImageProcessingKYH3View::OnDownSampling)
	ON_COMMAND(ID_UP_SAMPLING, &CImageProcessingKYH3View::OnUpSampling)
	ON_COMMAND(ID_QUANTIZATION, &CImageProcessingKYH3View::OnQuantization)
	ON_COMMAND(ID_SUM_CONSTANT, &CImageProcessingKYH3View::OnSumConstant)
	ON_COMMAND(ID_SUB_CONSTANT, &CImageProcessingKYH3View::OnSubConstant)
	ON_COMMAND(ID_MUL_CONSTANT, &CImageProcessingKYH3View::OnMulConstant)
	ON_COMMAND(ID_DIV_CONSTANT, &CImageProcessingKYH3View::OnDivConstant)
	ON_COMMAND(ID_AND_OPERATE, &CImageProcessingKYH3View::OnAndOperate)
	ON_COMMAND(ID_OR_OPERATE, &CImageProcessingKYH3View::OnOrOperate)
	ON_COMMAND(ID_XOR_OPERATE, &CImageProcessingKYH3View::OnXorOperate)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CImageProcessingKYH3View::OnNegaTransform)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CImageProcessingKYH3View::OnGammaCorrection)
	ON_COMMAND(ID_BINARIZATION, &CImageProcessingKYH3View::OnBinarization)
	ON_COMMAND(ID_STRESS_TRANSFORM, &CImageProcessingKYH3View::OnStressTransform)
	ON_COMMAND(ID_HISTO_STRETCH, &CImageProcessingKYH3View::OnHistoStretch)
	ON_COMMAND(ID_END_IN_SEARCH, &CImageProcessingKYH3View::OnEndInSearch)
	ON_COMMAND(ID_HISTOGRAM, &CImageProcessingKYH3View::OnHistogram)
	ON_COMMAND(ID_HISTO_EQUAL, &CImageProcessingKYH3View::OnHistoEqual)
	ON_COMMAND(ID_HISTO_SPEC, &CImageProcessingKYH3View::OnHistoSpec)
	ON_COMMAND(ID_EMBOSSING, &CImageProcessingKYH3View::OnEmbossing)
	ON_COMMAND(ID_BLURR, &CImageProcessingKYH3View::OnBlurr)
	ON_COMMAND(ID_GAUSSIAN_FILTER, &CImageProcessingKYH3View::OnGaussianFilter)
	ON_COMMAND(ID_SHARPENING, &CImageProcessingKYH3View::OnSharpening)
	ON_COMMAND(ID_LPF_SHARP, &CImageProcessingKYH3View::OnLpfSharp)
	ON_COMMAND(ID_DIFF_OPERATOR_HOR, &CImageProcessingKYH3View::OnDiffOperatorHor)
	ON_COMMAND(ID_HOMOGEN_OPERATOR, &CImageProcessingKYH3View::OnHomogenOperator)
	ON_COMMAND(ID_LAPLACIAN, &CImageProcessingKYH3View::OnLaplacian)
	ON_COMMAND(ID_BILINEAR, &CImageProcessingKYH3View::OnBilinear)
	ON_COMMAND(ID_MEDIAN_SUB, &CImageProcessingKYH3View::OnMedianSub)
	ON_COMMAND(ID_MEAN_SUB, &CImageProcessingKYH3View::OnMeanSub)
	ON_COMMAND(ID_TRANSLATION, &CImageProcessingKYH3View::OnTranslation)
	ON_COMMAND(ID_MIRROR_HOR, &CImageProcessingKYH3View::OnMirrorHor)
	ON_COMMAND(ID_MIRROR_VER, &CImageProcessingKYH3View::OnMirrorVer)
	ON_COMMAND(ID_ROTATION, &CImageProcessingKYH3View::OnRotation)
	ON_COMMAND(ID_FRAME_SUM, &CImageProcessingKYH3View::OnFrameSum)
	ON_COMMAND(ID_FRAME_SUB, &CImageProcessingKYH3View::OnFrameSub)
	ON_COMMAND(ID_FRAME_MUL, &CImageProcessingKYH3View::OnFrameMul)
	ON_COMMAND(ID_FRAME_DIV, &CImageProcessingKYH3View::OnFrameDiv)
	ON_COMMAND(ID_FRAME_AND, &CImageProcessingKYH3View::OnFrameAnd)
	ON_COMMAND(ID_FRAME_OR, &CImageProcessingKYH3View::OnFrameOr)
	ON_COMMAND(ID_FRAME_COMB, &CImageProcessingKYH3View::OnFrameComb)
	ON_COMMAND(ID_BitPlane, &CImageProcessingKYH3View::OnBitplane)
END_MESSAGE_MAP()

// CImageProcessingKYH3View 생성/소멸

CImageProcessingKYH3View::CImageProcessingKYH3View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProcessingKYH3View::~CImageProcessingKYH3View()
{
}

BOOL CImageProcessingKYH3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingKYH3View 그리기

void CImageProcessingKYH3View::OnDraw(CDC* pDC)
{
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int i, j; unsigned char R, G, B;
	//입력 영상 출력
	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = pDoc->m_InputImage[i*pDoc->m_width + j];
			G = B = R; //grayscale 이라 RGB값이 다 같음.
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}

	// 축소된 영상 출력
	for (i = 0; i < pDoc->m_Re_height; i++) { 
		for (j = 0; j < pDoc->m_Re_width; j++) { 
			R = pDoc->m_OutputImage[i*pDoc->m_Re_width + j]; 
			G = B = R; 
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B)); 
		} 
	}
}


// CImageProcessingKYH3View 인쇄

BOOL CImageProcessingKYH3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProcessingKYH3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProcessingKYH3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageProcessingKYH3View 진단

#ifdef _DEBUG
void CImageProcessingKYH3View::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingKYH3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingKYH3Doc* CImageProcessingKYH3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingKYH3Doc)));
	return (CImageProcessingKYH3Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingKYH3View 메시지 처리기


void CImageProcessingKYH3View::OnDownSampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); // Doc 클래스 참조 
	ASSERT_VALID(pDoc);

	pDoc->OnDownSampling(); // Doc 클래스에 OnDownSampling 함수 호출

	Invalidate(TRUE); // 화면 갱신

}


void CImageProcessingKYH3View::OnUpSampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); // Doc 클래스 참조 
	ASSERT_VALID(pDoc);

	pDoc->OnUpSampling(); // Doc 클래스에 OnUpSampling 함수 호출
	Invalidate(TRUE); // 화면 갱신
}


void CImageProcessingKYH3View::OnQuantization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnQuantization();//Doc 클래스의 onQuantization 호출

	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingKYH3View::OnSumConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);//인스턴스 주소를 가져옴

	pDoc->OnSumConstant();

	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnSubConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); // 도큐먼트 클라스 참조
	ASSERT_VALID(pDoc);// 인스턴스 주소를 가져옴

	pDoc->OnSubConstant();

	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnMulConstant()
{
	CImageProcessingKYH3Doc* pDoc = GetDocument(); //도큐먼트 값 참조
	ASSERT_VALID(pDoc); //인스턴스 주소를 가져옴

	pDoc->OnMulConstant(); //OnMulConstant 함수 호출해서 계산 하게 하고

	Invalidate(TRUE); //화면 다시 수정
}


void CImageProcessingKYH3View::OnDivConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	// 도큐먼트 클래스 참조 
	ASSERT_VALID(pDoc); // 인스턴스 주소를 가져옴

	pDoc->OnDivConstant();

	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnAndOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);

	pDoc->OnAndOperate();

	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnOrOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOrOperate();

	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnXorOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnXorOperate();

	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnNegaTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNegaTransform();

	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnGammaCorrection()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGammaCorrection();

	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinarization();

	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnStressTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnStressTransform();

	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnHistoStretch()
{
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnHistoStretch();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnEndInSearch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEndInSearch();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistogram();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnHistoSpec()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistoSpec();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnEmbossing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEmbossing();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnBlurr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnBlurr();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnGaussianFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnGaussianFilter();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnSharpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnSharpening();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnHpfSharp()
{
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHpfSharp();
	Invalidate(TRUE);

	
}


void CImageProcessingKYH3View::OnLpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLpfSharp();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnDiffOperatorHor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnDiffOperatorHor();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnHomogenOperator()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnHomogenOperator();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnLaplacian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnLaplacian();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnNearest()
{
	// TODO: 여기에 구현 코드 추가.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnNearest();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnBilinear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnBilinear();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnMedianSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnMedianSub();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnMeanSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnMeanSub();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnTranslation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnTranslation();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnMirrorHor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnMirrorHor();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnMirrorVer()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnMirrorVer();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnRotation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnRotation();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnFrameSum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnFrameSum();
	Invalidate(TRUE);

}


void CImageProcessingKYH3View::OnFrameSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc);
	pDoc->OnFrameComb();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnFrameMul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameComb();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnFrameDiv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameComb();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnFrameAnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameComb();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnFrameOr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameComb();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnFrameComb()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameComb();
	Invalidate(TRUE);
}


void CImageProcessingKYH3View::OnBitplane()
{
	CImageProcessingKYH3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBitplane();
	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
