/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : ProcessPage.h                                                   *
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


// CProcessPage  dialog
#include "EDSDK.h"
#include "afxcmn.h"
#include "afxwin.h"

class CProcessPage : public CPropertyPage
{
	EdsImageRef	m_ImageRef;
	EdsInt32 m_nExposure;
	EdsInt32 m_WBShift[2];
	EdsPictureStyleDesc	m_PicStyDesc;
	EdsInt32 m_nPictureStyle;
	EdsInt32 m_nWB;
	EdsInt32 m_nColorSpace;
	EdsInt32 m_nColorTemp;
	DECLARE_DYNAMIC(CProcessPage)

// Construction
public:
	CProcessPage();
	virtual ~CProcessPage();
	void SetImageRef( EdsImageRef ref );
	BOOL IsClickWB()const{return (((CButton *)GetDlgItem(IDC_BUTTON6))->GetCheck());}
	void ClickWB();
// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPropertyChanged();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedCheckCashe();
	
	afx_msg void OnDigitalExposureChanged();
	afx_msg void OnWhiteBalanceChanged();
	afx_msg void OnWhiteBalanceShiftChanged();
	afx_msg void OnPictureStyleChanged();
	afx_msg void OnColorSpaceChanged();

	// DigitalExposureControl
	CSliderCtrl m_ExposureSlider;
	// WhiteBalance
	CComboBox m_WhiteBalanceCombo;
	CSliderCtrl m_WhiteBalanceShiftBASlider;
	CSliderCtrl m_WhiteBalanceShiftMGSlider;
	// ColorTemperature
	CEdit m_ColorTemperatureEdit;

	CComboBox m_PictureStyleCombo;
	CSliderCtrl m_ContrastSlider;
	CSliderCtrl m_SharpnessSlider;
	CSliderCtrl m_ColorToneSlider;
	CSliderCtrl m_SaturationSlider;
	CComboBox m_FilterEffectCombo;
	CComboBox m_ToningEffectCombo;
	CComboBox m_ColorSpaceCombo;
};


inline void CProcessPage::ClickWB()
{
	m_WhiteBalanceCombo.SetCurSel(-1);
	m_ColorTemperatureEdit.EnableWindow(false);
	m_WhiteBalanceCombo.SetWindowText("Click");
	
}
