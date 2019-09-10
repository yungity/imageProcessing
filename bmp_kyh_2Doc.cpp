
// bmp_kyh_2Doc.cpp: Cbmpkyh2Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "bmp_kyh_2.h"
#endif

#include "bmp_kyh_2Doc.h"
# include <memory.h>
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cbmpkyh2Doc

IMPLEMENT_DYNCREATE(Cbmpkyh2Doc, CDocument)

BEGIN_MESSAGE_MAP(Cbmpkyh2Doc, CDocument)
END_MESSAGE_MAP()


// Cbmpkyh2Doc 생성/소멸

Cbmpkyh2Doc::Cbmpkyh2Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

Cbmpkyh2Doc::~Cbmpkyh2Doc()
{
}

BOOL Cbmpkyh2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// Cbmpkyh2Doc serialization

void Cbmpkyh2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void Cbmpkyh2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void Cbmpkyh2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cbmpkyh2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Cbmpkyh2Doc 진단

#ifdef _DEBUG
void Cbmpkyh2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cbmpkyh2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cbmpkyh2Doc 명령


BOOL Cbmpkyh2Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	//CFile에서 처리
	CFile hFile;        //파일을 읽어들이면 이 클래스 형식으로 저장.

	int height;        //이미지의 높이를 저장할 변수
	int width;        //이미지의 가로길이를 저장할 변수

	hFile.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);    //파일 열기
	hFile.Read(&dibHf, sizeof(BITMAPFILEHEADER));                          //dibHf에 파일헤더를 읽어들인다.

	//이 파일이 BMP파일인지 검사 
	if (dibHf.bfType != 0x4D42)
	{
		AfxMessageBox(L"Not BMP file!!");                                        //프로젝트 생성시 유니코드를 사용하게 할 경우
		return FALSE;                                                                      //L을 붙여준다
	}

	hFile.Read(&dibHi, sizeof(BITMAPINFOHEADER));                             //영상정보의 header를 읽기
	if (dibHi.biBitCount != 8 && dibHi.biBitCount != 24)                                //8,24비트가 아닐경우
	{
		AfxMessageBox(L"Gray/True Color Possible!!");
		return FALSE;
	}

	if (dibHi.biBitCount == 8)
		//8비트의 경우 팔레트를 생성해 주어야 한다. 총 256가지 색이므로 그 길이만큼 읽어들인다
		hFile.Read(palRGB, sizeof(RGBQUAD) * 256);

	//메모리 할당

	if (dibHi.biBitCount == 8)
	{
		ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - 256 * sizeof(RGBQUAD);
		//이미지의 크기는 파일 총 길이에서, 두 헤드와 팔레트의 사이즈를 제외한다.
	}
	else if (dibHi.biBitCount == 24) //컬러영상
	{
		ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
	}
	
	//이미지의 길이정보
	height = dibHi.biHeight;
	width = dibHi.biWidth;
	m_InImg = new unsigned char[ImgSize];
	m_OutImg = new unsigned char[ImgSize];

	//이미지를 저장, 출력할 배열생성.
	/*m_InImg = (unsigned char**) malloc(ImgSize);
	for (int i = 1; i < height; i++) {
		m_InImg[i] = m_InImg[i-1] + width;
	}
	memset(m_InImg[0], 0, ImgSize);
	
	m_OutImg = (unsigned char**) malloc(ImgSize);
	for (int i = 1; i < height; i++) {
		m_OutImg[i] = m_OutImg[i - 1] + width;
	}
	memset(m_OutImg[0], 0, ImgSize);*/

	hFile.Read(m_InImg, ImgSize);
	hFile.Close();

	

	return TRUE;
}


BOOL Cbmpkyh2Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// 전환
	unsigned char **temp;
	int height = dibHi.biHeight;
	int width = dibHi.biWidth;

	// BMP는 아래에서 위로 저장되는 형식이기 때문에 순서대로 저장하면 뒤집히므로 파일로 저장할 데이터를 뒤집기
	SPixel* rgbTemp = new SPixel[BUFSIZE]; // 파일저장할 데이터를 보관할 임시공간
	
	for (int i = 0; i < BUFSIZE; i++) {
		rgbTemp[i].r = g_rgb[BUFSIZE - 1 - i].r;
		rgbTemp[i].g = g_rgb[BUFSIZE - 1 - i].g;
		rgbTemp[i].b = g_rgb[BUFSIZE - 1 - i].b;
	}


	// bmp file 저장
	CFile file;
	file.Open(_T("bmp_re.bmp"), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	file.Write(&dibHf, sizeof(BITMAPFILEHEADER));
	file.Write(&dibHi, sizeof(BITMAPINFOHEADER));
	if (dibHi.biBitCount == 8)
		file.Write(palRGB, sizeof(RGBQUAD) * 256);
	file.Write(temp, height*width);
	file.Close();
	free(m_InImg);

	return TRUE;
}
