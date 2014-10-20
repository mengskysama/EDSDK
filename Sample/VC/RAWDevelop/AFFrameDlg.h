#pragma once

#include "EDSDK.h"
#include "DrawImage.h"

class CAFFrameDlg : public CDialog
{
	DECLARE_DYNAMIC(CAFFrameDlg)

public:
	CAFFrameDlg(CWnd* pParent = NULL);
	virtual ~CAFFrameDlg();

	virtual void SetImageRef(EdsImageRef inImageRef)
	{
		if(m_ImageRef!=NULL)EdsRelease(m_ImageRef);
		m_ImageRef = inImageRef;
		EdsRetain(m_ImageRef);
		this->PostMessage(WM_IMAGE_UPDATE,0,0);
	};
	enum { IDD = IDD_DIALOG3 };

protected:
	EdsImageRef m_ImageRef;
	CDrawImage *m_pDrawImage;
	EdsFocusInfo		m_focusInfo;
	virtual void DoDataExchange(CDataExchange* pDX);
	void LoadImage();

	afx_msg LRESULT OnImageUpdate(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
