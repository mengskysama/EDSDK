/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : SavePage.h                                                      *
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


// CSavePage dialog
#include "EDSDK.h"

class CSavePage : public CPropertyPage
{
	EdsImageRef	m_ImageRef;
	DECLARE_DYNAMIC(CSavePage)

// Construction
public:
	CSavePage();
	virtual ~CSavePage();

	void SetImageRef( EdsImageRef ref );
	void Get( EdsTargetImageType &type );
	void Get( EdsSaveImageSetting &inSaveSetting );

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSave();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton2();

	CComboBox m_SaveTypeCombo;
	CComboBox m_QualityCombo;
};



inline void CSavePage::OnBnClickedButton2()
{
	static char BASED_CODE gbszFilter[] = "Color Profile (*.ICC)|*.ICC||";
	CFileDialog dlg(TRUE,"*.ICC",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,gbszFilter);
	if( dlg.DoModal() == IDOK )
		GetDlgItem(IDC_EDIT5)->SetWindowText( dlg.GetPathName() );
}
