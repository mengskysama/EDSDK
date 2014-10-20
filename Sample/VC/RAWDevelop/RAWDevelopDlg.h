/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : RAWDevelopDlg.h                                                 *
*                                                                             *
*   Description: This is the Sample code to show the usage of EDSDK.          *
*                                                                             *
*                                                                             *
*******************************************************************************
*                                                                             *
*   Written and developed by Camera Design Dept.53                            *
*   Copyright Canon Inc. 2006 All Rights Reserved                             *
*                                                                             *
*******************************************************************************
*   File Update Information:                                                  *
*     DATE      Identify    Comment                                           *
*   -----------------------------------------------------------------------   *
*   06-03-22    F-001        create first version.                            *
*                                                                             *
******************************************************************************/
#pragma once

#include "DrawImage.h"
#include "EDSDK.h"
#include "CtrlPanelSheet.h"
#include "AFFrameDlg.h"
#include "PropertyString.h"

// CRAWDevelopDlg dialog
class CRAWDevelopDlg : public CDialog
{
	EdsImageRef	m_ImageRef;
	float m_ratio;
	float m_ratioOfThmToFull;
	CCtrlPanelSheet *m_pCtrlPanel;
	bool m_bLoadDisable;
	int m_width;
	CDrawImage *m_pDrawImage;

	CAFFrameDlg	*m_afFrameDlg;
// Construction
public:
	CRAWDevelopDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RAWDEVELOP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedOpenFile();
	afx_msg void OnBnClickedRadioThm();
	afx_msg void OnBnClickedRadioFull();
	afx_msg void OnEnChangeEdit();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnBnClickedAfframe();
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnImageUpdate(WPARAM wParam, LPARAM lParam);
	void LoadImage();
	void SaveImage( CString &path , CString &icc );
	void LoadPropertyList();
	BOOL IsThumbnail() const { return ((CButton*) GetDlgItem(IDC_RADIO_THM))->GetCheck();}

public:

	static EdsError EDSCALLBACK ProgressFunc ( EdsUInt32 inPercent , EdsVoid *inContext , EdsBool *outCancel );

	void PositionEmbeddedPropertySheet(CWnd* pParent,CPropertySheet* pPSheet,CRect rcNewPosition);
	void AddPropertyList( const char *label , const char *data );
	void AddPropertyList( CPropertyString *propStr);

public:
public:
	afx_msg void OnEnKillfocusEdit();
};


//////////////////////////////////////////////////////
inline void CRAWDevelopDlg::PositionEmbeddedPropertySheet(CWnd* pParent,CPropertySheet* pPSheet,CRect rcNewPosition)
{
	ASSERT_VALID(pParent);
	ASSERT_VALID(pPSheet);

	CTabCtrl* pTabCtrl=pPSheet->GetTabControl();
	ASSERT(pTabCtrl !=NULL);

	CRect rcTabCtrl;
	pTabCtrl->GetWindowRect(&rcTabCtrl);
	pParent->ScreenToClient(&rcTabCtrl);

	CRect rcPSheet;
	pPSheet->GetWindowRect(&rcPSheet);
	pParent->ScreenToClient(&rcPSheet);

	int dcx=rcPSheet.Width() - rcTabCtrl.Width();
	int dcy=rcPSheet.Height() - rcTabCtrl.Height();

	pPSheet->MoveWindow(rcNewPosition.left,
		rcNewPosition.top,
		rcNewPosition.Width(),
		rcNewPosition.Height());

	pTabCtrl->SetWindowPos(NULL,0,0,
		rcNewPosition.Width() - dcx,
		rcNewPosition.Height() - dcy,
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);


	int nCurrentPage=pPSheet->GetActiveIndex();
	for(int i=0 ;i<pPSheet->GetPageCount();++i)
	{
		pPSheet->SetActivePage(i);
	}
	pPSheet->SetActivePage(nCurrentPage);

}

//////////////////////////////////////////////////////
inline void CRAWDevelopDlg::AddPropertyList( const char *label , const char *data )
{
	CListCtrl *pList=(CListCtrl *)GetDlgItem(IDC_LIST1);
	int index=pList->GetItemCount();
	pList->InsertItem(index,label);
	pList->SetItemText(index,1,data);
}

//////////////////////////////////////////////////////
inline void CRAWDevelopDlg::OnEnChangeEdit()
{
/*	static int bkx=-1;
	static int bky=-1;
	static int bkh=-1;
	if( m_bLoadDisable )
		m_width=0;
	else
	{
		int x,y,w,h;

		CString str;
		GetDlgItem(IDC_EDIT_X)->GetWindowText(str);
		x=atoi(	str );
		GetDlgItem(IDC_EDIT_Y)->GetWindowText(str);
		y=atoi(	str );
		GetDlgItem(IDC_EDIT_W)->GetWindowText(str);
		w=atoi(	str );
		GetDlgItem(IDC_EDIT_H)->GetWindowText(str);
		h=atoi(	str );

		if((x!=bkx)||(y!=bky)||(w!=m_width)||(h!=bkh))
			LoadImage();
		bkx=x;
		bky=y;
		m_width=w;
		bkh=h;
	}
	*/
}
inline void CRAWDevelopDlg::OnEnKillfocusEdit()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	static int bkx=-1;
	static int bky=-1;
	static int bkh=-1;
	if( m_bLoadDisable )
		m_width=0;
	else
	{
		int x,y,w,h;

		CString str;
		GetDlgItem(IDC_EDIT_X)->GetWindowText(str);
		x=atoi(	str );
		GetDlgItem(IDC_EDIT_Y)->GetWindowText(str);
		y=atoi(	str );
		GetDlgItem(IDC_EDIT_W)->GetWindowText(str);
		w=atoi(	str );
		GetDlgItem(IDC_EDIT_H)->GetWindowText(str);
		h=atoi(	str );

		if((x!=bkx)||(y!=bky)||(w!=m_width)||(h!=bkh))
			this->PostMessage(WM_IMAGE_UPDATE,0,0);
		bkx=x;
		bky=y;
		m_width=w;
		bkh=h;
	}
}

//////////////////////////////////////////////////////
// Processing of a thumbnail radio button.FIT size is computed and set to an editing box.
inline void CRAWDevelopDlg::OnBnClickedRadioThm()
{
	CheckRadioButton(IDC_RADIO_FIT, IDC_RADIO_100, IDC_RADIO_FIT);
	m_bLoadDisable =true;
	GetDlgItem(IDC_EDIT_X)->SetWindowText( "0" );
	GetDlgItem(IDC_EDIT_Y)->SetWindowText( "0" );
	CString str;
	EdsImageInfo imgInfo = {0};
	EdsGetImageInfo( m_ImageRef , kEdsImageSrc_RAWThumbnail , &imgInfo );
	str.Format("%d",imgInfo.effectiveRect.size.width);
	GetDlgItem(IDC_EDIT_W)->SetWindowText( str );
	str.Format("%d",imgInfo.effectiveRect.size.height);
	m_bLoadDisable =false;
	GetDlgItem(IDC_EDIT_H)->SetWindowText( str );
}

//////////////////////////////////////////////////////
// Processing of a full view radio button.FIT size is computed and set to an editing box.
inline void CRAWDevelopDlg::OnBnClickedRadioFull()
{
	CheckRadioButton(IDC_RADIO_FIT, IDC_RADIO_100, IDC_RADIO_FIT);
	m_bLoadDisable =true;
	GetDlgItem(IDC_EDIT_X)->SetWindowText( "0" );
	GetDlgItem(IDC_EDIT_Y)->SetWindowText( "0" );
	CString str;
	EdsImageInfo imgInfo = {0};
	EdsGetImageInfo( m_ImageRef , kEdsImageSrc_RAWFullView , &imgInfo );
	str.Format("%d",imgInfo.effectiveRect.size.width);
	GetDlgItem(IDC_EDIT_W)->SetWindowText( str );
	str.Format("%d",imgInfo.effectiveRect.size.height);
	m_bLoadDisable =false;
	GetDlgItem(IDC_EDIT_H)->SetWindowText( str );
}

inline void CRAWDevelopDlg::OnBnClickedAfframe()
{
	CButton *pAFFrame=(CButton*)GetDlgItem(IDC_AFFRAME);
	int check = pAFFrame->GetCheck();
	if(BST_UNCHECKED==check)
	{
		if(m_afFrameDlg!=NULL)
		{
			m_afFrameDlg->ShowWindow(SW_HIDE);
			m_afFrameDlg->DestroyWindow();
			delete m_afFrameDlg;
			m_afFrameDlg = NULL;
		}
	}
	else
	{
		// AF Frame Dlg
		if(m_afFrameDlg==NULL)
		{
			m_afFrameDlg = new CAFFrameDlg();
			m_afFrameDlg->Create(IDD_DIALOG3);
			m_afFrameDlg->SetImageRef(m_ImageRef);
			if(m_afFrameDlg!=NULL)m_afFrameDlg->ShowWindow(SW_SHOW);
		}
	}
}
