// TPDoc.cpp : CTPDoc Ŭ������ ����
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


// CTPDoc ����/�Ҹ�

CTPDoc::CTPDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CTPDoc::~CTPDoc()
{
}

BOOL CTPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CTPDoc serialization

void CTPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CTPDoc ����

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


// CTPDoc ���
