/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : SavePage.cpp                                                    *
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
#include "stdafx.h"
#include "RAWDevelop.h"
#include "SavePage.h"
#include ".\savepage.h"

//////////////////////////////////////////////////////
// s_tblSaveType			
static STR_ID_TABLE s_tblSaveType[] = {			
	{ "Jpeg",		kEdsTargetImageType_Jpeg }, 
	{ "TIFF",		kEdsTargetImageType_TIFF }, 
	{ "TIFF16",		kEdsTargetImageType_TIFF16 }	
};			
// s_tblQuality			
static STR_ID_TABLE s_tblQuality[] = {			
	{ "1(low)",	1 }, 
	{ "2",		2 }, 
	{ "3",		3 },
	{ "4",		4 },
	{ "5",		5 },
	{ "6",		6 },
	{ "7",		7 },
	{ "8",		8 },
	{ "9",		9 },
	{ "10(high)", 10 },	
};			

// CSavePage 

IMPLEMENT_DYNAMIC(CSavePage, CPropertyPage)
CSavePage::CSavePage()
	: CPropertyPage(CSavePage::IDD)
{
	m_ImageRef = NULL;
}

CSavePage::~CSavePage()
{
}

//////////////////////////////////////////////////////
void CSavePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_SaveTypeCombo);
	DDX_Control(pDX, IDC_COMBO2, m_QualityCombo);
}


BEGIN_MESSAGE_MAP(CSavePage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedSave)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
END_MESSAGE_MAP()


// CSavePage 

//////////////////////////////////////////////////////
BOOL CSavePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	/// Initialization of the control used in this dialog.
	INIT_COMBO( m_SaveTypeCombo , s_tblSaveType );
	SET_COMBO ( m_SaveTypeCombo , kEdsTargetImageType_Jpeg );

	INIT_COMBO( m_QualityCombo , s_tblQuality );
	SET_COMBO ( m_QualityCombo , 8 );

	return TRUE;
}

//////////////////////////////////////////////////////
// The target EdsImageRef is registered into this page.
// EdsImageRef made applicable to picture adjustment to SavePage is registered.
void CSavePage::SetImageRef( EdsImageRef ref )
{
	m_ImageRef=ref;
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow( m_ImageRef != NULL );
	if( m_ImageRef == NULL )
		return;

	// kEdsPropID_Linear
	EdsBool value;
	EdsError err= EdsGetPropertyData( m_ImageRef, kEdsPropID_Linear, 0, sizeof(value),&value);

}

//////////////////////////////////////////////////////
/// A picture is developed and it outputs to a file.
/// The file path of the file pathname to save and an ICC profile is acquired,
/// and a picture preservation message is sent to a main dialog.
void CSavePage::OnBnClickedSave()
{
	static char BASED_CODE gbszJpegFilter[] = "Jpeg Files (*.JPG)|*.JPG||";
	static char BASED_CODE gbszTiffFilter[] = "Tiff Profile (*.TIF)|*.TIF||";
	char *ext;
	char *filter;

	long value;
	GET_COMBO( m_SaveTypeCombo , value );
	switch(value)
	{
	case kEdsTargetImageType_Jpeg:
		ext = "*.JPG";
		filter = gbszJpegFilter;
		break;
	case kEdsTargetImageType_TIFF:
	case kEdsTargetImageType_TIFF16:
		ext = "*.TIF";
		filter = gbszTiffFilter;
		break;
	default:
		return;
	}
	CString icc;
	GetDlgItem(IDC_EDIT5)->GetWindowText( icc );

	/// The file name to output is acquired.
	CFileDialog dlg(FALSE,ext,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);
	if( dlg.DoModal() == IDOK )
	{
		this->GetParent()->GetParent()->SendMessage(WM_IMAGE_UPDATE,(WPARAM)&dlg.GetPathName(),(LPARAM)&icc);
	}
}

//////////////////////////////////////////////////////
/// The setting value of ComboBox to EdsTargetImageType of this dialog is returned.
void CSavePage::Get( EdsTargetImageType &type )
{
	GET_COMBO( m_SaveTypeCombo , (long &)type );
}
//////////////////////////////////////////////////////
/// The setting value of ComboBox to EdsSaveImageSetting of this dialog is returned.
void CSavePage::Get( EdsSaveImageSetting &setting )
{
	GET_COMBO ( m_QualityCombo , setting.JPEGQuality );
	setting.iccProfileStream = 0;
	setting.reserved = 0;
}


//////////////////////////////////////////////////////
void CSavePage::OnCbnSelchangeCombo1()
{
	long value;
	GET_COMBO( m_SaveTypeCombo , value );
	m_QualityCombo.EnableWindow( kEdsTargetImageType_Jpeg==value);
	m_SaveTypeCombo.EnableWindow( kEdsTargetImageType_TIFF16==value);
}

