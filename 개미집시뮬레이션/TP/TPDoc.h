// TPDoc.h : CTPDoc Ŭ������ �������̽�
//


#pragma once


class CTPDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CTPDoc();
	DECLARE_DYNCREATE(CTPDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CTPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


