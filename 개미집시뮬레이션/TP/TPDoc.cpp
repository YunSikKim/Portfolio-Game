// TPDoc.cpp : CTPDoc 클래스의 구현
//

#include "stdafx.h"
#include "TP.h"

#include "TPDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTPDoc

IMPLEMENT_DYNCREATE(CTPDoc, CDocument)

BEGIN_MESSAGE_MAP(CTPDoc, CDocument)
END_MESSAGE_MAP()


// CTPDoc 생성/소멸

CTPDoc::CTPDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CTPDoc::~CTPDoc()
{
}

BOOL CTPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CTPDoc serialization

void CTPDoc::Serialize(CArchive& ar)
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


// CTPDoc 진단

#ifdef _DEBUG
void CTPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTPDoc 명령
