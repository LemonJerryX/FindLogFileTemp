
// MDoc.h : CMDoc ��Ľӿ�
//


#pragma once


class CMDoc : public CDocument
{
protected: // �������л�����
	CMDoc();
	DECLARE_DYNCREATE(CMDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


