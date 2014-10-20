/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : ProcessPage.cpp                                                 *
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
#include "ProcessPage.h"
#include ".\processpage.h"
////////////////////////////////////////////////////////
/// Combo Box registration data table.


// WhiteBalance
static STR_ID_TABLE s_tblWhiteBalance[] = {				
	{ "Auto",		kEdsWhiteBalance_Auto }, 
	{ "Daylight",	kEdsWhiteBalance_Daylight }, 	
	{ "Cloudy",		kEdsWhiteBalance_Cloudy }, 	
	{ "Tangsten",	kEdsWhiteBalance_Tangsten }, 	
	{ "Fluorescent",kEdsWhiteBalance_Fluorescent }, 		
	{ "Strobe",		kEdsWhiteBalance_Strobe }, 	
	{ "Shade",		kEdsWhiteBalance_Shade }, 
	{ "ColorTemp",	kEdsWhiteBalance_ColorTemp }, 	
};				
				
// PictureStyle				
static STR_ID_TABLE s_tblPictureStyle[] = {				
	{ "Standard",	kEdsPictureStyle_Standard }, 	
	{ "Portrait",	kEdsPictureStyle_Portrait }, 	
	{ "Landscape",	kEdsPictureStyle_Landscape }, 	
	{ "Neutral",	kEdsPictureStyle_Neutral }, 	
	{ "Faithful",	kEdsPictureStyle_Faithful }, 	
	{ "Monochrome",	kEdsPictureStyle_Monochrome }, 		
};			
			
// FilterEffect			
static STR_ID_TABLE s_tblFilterEffect[] = {			
	{ "None",		kEdsFilterEffect_None }, 
	{ "Yellow",		kEdsFilterEffect_Yellow }, 	
	{ "Orange",		kEdsFilterEffect_Orange }, 	
	{ "Red",		kEdsFilterEffect_Red }, 
	{ "Green",		kEdsFilterEffect_Green }
};			
			
// ToningEffect			
static STR_ID_TABLE s_tblToningEffect[] = {			
	{ "None",		kEdsTonigEffect_None }, 
	{ "Sepia",		kEdsTonigEffect_Sepia }, 
	{ "Blue",		kEdsTonigEffect_Blue }, 
	{ "Purple",		kEdsTonigEffect_Purple }, 	
	{ "Green",		kEdsTonigEffect_Green }
};			
			
// ColorSpace			
static STR_ID_TABLE s_tblColorSpace[] = {			
	{ "sRGB",		kEdsColorSpace_sRGB }, 
	{ "AdobeRGB",	kEdsColorSpace_AdobeRGB }	
};			
			
//////////////////////////////////////////////////////
// CProcessPage Dialog

IMPLEMENT_DYNAMIC(CProcessPage, CPropertyPage)
CProcessPage::CProcessPage()
	: CPropertyPage(CProcessPage::IDD)
{
	m_ImageRef=NULL;
	m_nExposure = 0;
	m_nPictureStyle=0;
	m_nWB=0;
	m_nColorSpace=0;
	memset(m_WBShift ,0,sizeof(m_WBShift));
	memset(&m_PicStyDesc ,0,sizeof(m_PicStyDesc));
}

//////////////////////////////////////////////////////
CProcessPage::~CProcessPage()
{
}

//////////////////////////////////////////////////////
void CProcessPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_EXPORSUR, m_ExposureSlider);
	DDX_Control(pDX, IDC_COMBO_WB, m_WhiteBalanceCombo);
	DDX_Control(pDX, IDC_SLIDER_BA, m_WhiteBalanceShiftBASlider);
	DDX_Control(pDX, IDC_SLIDER_MG, m_WhiteBalanceShiftMGSlider);
	DDX_Control(pDX, IDC_EDIT_CT, m_ColorTemperatureEdit);
	DDX_Control(pDX, IDC_COMBO_PS, m_PictureStyleCombo);
	DDX_Control(pDX, IDC_SLIDER_CON, m_ContrastSlider);
	DDX_Control(pDX, IDC_SLIDER_SHR, m_SharpnessSlider);
	DDX_Control(pDX, IDC_SLIDER_TONE, m_ColorToneSlider);
	DDX_Control(pDX, IDC_SLIDER_SATU, m_SaturationSlider);
	DDX_Control(pDX, IDC_COMBO_FE, m_FilterEffectCombo);
	DDX_Control(pDX, IDC_COMBO_TE, m_ToningEffectCombo);
	DDX_Control(pDX, IDC_COMBO_CS , m_ColorSpaceCombo );

}


BEGIN_MESSAGE_MAP(CProcessPage, CPropertyPage)
ON_WM_HSCROLL()
ON_CBN_SELCHANGE(IDC_COMBO_PS, OnPictureStyleChanged)
ON_CBN_SELCHANGE(IDC_COMBO_WB, OnWhiteBalanceChanged)
ON_CBN_SELCHANGE(IDC_COMBO_FE, OnPictureStyleChanged)
ON_CBN_SELCHANGE(IDC_COMBO_TE, OnPictureStyleChanged)
ON_CBN_SELCHANGE(IDC_COMBO_CS, OnColorSpaceChanged)
ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
ON_BN_CLICKED(IDC_CHECK_CASHE, OnBnClickedCheckCashe)
ON_EN_KILLFOCUS(IDC_EDIT_CT, OnWhiteBalanceChanged)
END_MESSAGE_MAP()


//////////////////////////////////////////////////////

BOOL CProcessPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();


	/// Initialization of the control used in this dialog.
	InitSlider( m_ExposureSlider , -20 , 20 , 2 );
	INIT_COMBO( m_WhiteBalanceCombo , s_tblWhiteBalance );

	InitSlider( m_WhiteBalanceShiftBASlider , -9 , 9 );
	InitSlider( m_WhiteBalanceShiftMGSlider , -9 , 9 );

	INIT_COMBO( m_PictureStyleCombo , s_tblPictureStyle );
	InitSlider( m_ContrastSlider , -4 , 4 );
	InitSlider( m_SharpnessSlider , 0 , 7 );
	InitSlider( m_ColorToneSlider , -4 , 4 );
	InitSlider( m_SaturationSlider , -4 , 4 );
	INIT_COMBO( m_FilterEffectCombo , s_tblFilterEffect );
	INIT_COMBO( m_ToningEffectCombo , s_tblToningEffect );

	INIT_COMBO( m_ColorSpaceCombo , s_tblColorSpace );

	((CButton*) GetDlgItem(IDC_CHECK_CASHE))->SetCheck( true );
	
	LONG lStyle = GetWindowLong(((CButton *)GetDlgItem(IDC_BUTTON6))->m_hWnd, GWL_STYLE);
	lStyle |= (BS_AUTOCHECKBOX | BS_PUSHLIKE);
	SetWindowLong(((CButton *)GetDlgItem(IDC_BUTTON6))->m_hWnd , GWL_STYLE, lStyle);

	((CButton *)GetDlgItem(IDC_BUTTON6))->SetIcon(AfxGetApp( )->LoadIcon(IDI_ICON1));
	return TRUE;
}

//////////////////////////////////////////////////////
// The target EdsImageRef is registered into this page.
// EdsImageRef made applicable to picture adjustment to ProsessPage is registered.
// Property information is read simultaneously with registration and an initial value is set to each control.
void CProcessPage::SetImageRef( EdsImageRef ref )
{
	m_ImageRef = ref;
	static int tblDisableCtrls[]=
	{
		IDC_SLIDER_EXPORSUR , IDC_SLIDER_BA , IDC_SLIDER_MG , 
		IDC_SLIDER_CON , IDC_SLIDER_SHR , IDC_SLIDER_TONE , IDC_SLIDER_SATU , 
		IDC_COMBO_WB , IDC_COMBO_PS , IDC_COMBO_FE , IDC_COMBO_TE , IDC_COMBO_CS ,
	};
	for(int i=0;i<sizeof(tblDisableCtrls)/sizeof(*tblDisableCtrls);i++)
		GetDlgItem(tblDisableCtrls[i])->EnableWindow(false);

	if( m_ImageRef==NULL )
	{
		return;
	}

	EdsRational rational;
	EdsError err;

	// DigitalExposure
	/// kEdsPropID_DigitalExposure of the target EdsImageRef is read and an initial value is set to Slider Control and Edit Control.
	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_DigitalExposure, 0, sizeof(rational),&rational);
	if( err == EDS_ERR_OK )
	{
		m_nExposure = rational.numerator;
		SET_SLIDER( m_ExposureSlider , m_nExposure , "%.1f" , IDC_EDIT1 );
	}


	// WhiteBalance
	/// kEdsPropID_WhiteBalance of the target EdsImageRef is read and an initial value is set to Combo Box.
	err= EdsGetPropertyData( m_ImageRef,kEdsPropID_WhiteBalance , 0, sizeof(m_nWB),&m_nWB);
	if( err == EDS_ERR_OK )
		SET_COMBO( m_WhiteBalanceCombo , m_nWB );
	// WhiteBalanceShift
	/// kEdsPropID_WhiteBalanceShift of the target EdsImageRef is read and an initial value is set to Slider Control and Edit Control.
	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_WhiteBalanceShift, 0, sizeof(m_WBShift),m_WBShift);
	if( err == EDS_ERR_OK )
	{
		SET_SLIDER( m_WhiteBalanceShiftBASlider , m_WBShift[0] , "%d" , IDC_EDIT2 );
		SET_SLIDER( m_WhiteBalanceShiftMGSlider , m_WBShift[1] , "%d" , IDC_EDIT3 );
	}
	// ColorTemperature
	/// kEdsPropID_ColorTemperature of the target EdsImageRef is read and an initial value is set to Edit Control.
	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_ColorTemperature, 0, sizeof(m_nColorTemp),&m_nColorTemp);
	if( err == EDS_ERR_OK )
	{
		CString str;
		str.Format("%d",m_nColorTemp);
		m_ColorTemperatureEdit.SetWindowText(str);
	}
	m_ColorTemperatureEdit.EnableWindow(m_nWB == kEdsWhiteBalance_ColorTemp);

	///////////////////////////////////////
	// Picture Style
	/// kEdsPropID_PictureStyle of the target EdsImageRef is read and an initial value is set to Combo Box.
	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_PictureStyle, 0, sizeof(m_nPictureStyle),&m_nPictureStyle);
	if( err == EDS_ERR_OK )
		SET_COMBO( m_PictureStyleCombo , m_nPictureStyle );
	///////////////////////////////////////
	// Picture Style Desc
	/// kEdsPropID_PictureStyleDesc of the target EdsImageRef is read and an initial value is set to each Slider Control and Edit Control, or Combo Box.
	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_PictureStyleDesc, 0, sizeof(m_PicStyDesc),&m_PicStyDesc);
	if( err == EDS_ERR_OK )
	{
		SET_SLIDER( m_ContrastSlider   , m_PicStyDesc.contrast  , "%d" , IDC_EDIT4 );	// Contrast
		SET_SLIDER( m_SharpnessSlider  , m_PicStyDesc.sharpness , "%d" , IDC_EDIT5 );	// Sharpness
		SET_SLIDER( m_ColorToneSlider  , m_PicStyDesc.colorTone , "%d" , IDC_EDIT6 );	// Color Tone
		SET_SLIDER( m_SaturationSlider , m_PicStyDesc.colorTone , "%d" , IDC_EDIT7 );	// Saturation

		SET_COMBO( m_FilterEffectCombo , m_PicStyDesc.filterEffect );	// FilterEffect
		SET_COMBO( m_ToningEffectCombo , m_PicStyDesc.toningEffect );	// ToningEffect
	}


	///////////////////////////////////////
	// Color Space
	/// kEdsPropID_ColorSpace of the target EdsImageRef is read and an initial value is set to Combo Box.
	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_ColorSpace, 0, sizeof(m_nColorSpace),&m_nColorSpace);
	if( err == EDS_ERR_OK )
		SET_COMBO( m_ColorSpaceCombo , m_nColorSpace );

	///////////////////////////////////////
	/// A default value (ON) is set to EdsCacheImage of the target EdsImageRef.
	EdsCacheImage( m_ImageRef,((CButton*) GetDlgItem(IDC_CHECK_CASHE))->GetCheck() );
}


//////////////////////////////////////////////////////
void CProcessPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// OnPropertyChanged();
	if(pScrollBar == (CScrollBar*)&m_ExposureSlider)
		OnDigitalExposureChanged();
	if((pScrollBar == (CScrollBar*)&m_WhiteBalanceShiftBASlider) || 
		(pScrollBar == (CScrollBar*)&m_WhiteBalanceShiftMGSlider))
		OnWhiteBalanceShiftChanged();
	if((pScrollBar == (CScrollBar*)&m_ContrastSlider) || 
		(pScrollBar == (CScrollBar*)&m_SharpnessSlider) || 
		(pScrollBar == (CScrollBar*)&m_ColorToneSlider) || 
		(pScrollBar == (CScrollBar*)&m_SaturationSlider))
		OnPictureStyleChanged();

	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

//////////////////////////////////////////////////////
/// When this method is called when the change event of Control occurs, change of a property value is updated to EdsImageRef and there is change of a value, the drawing message of a picture is transmitted to a main dialog.
void CProcessPage::OnDigitalExposureChanged()
{
	bool bUpdate=false;
	EdsError err;
	CString str;

	EdsRational rational;

	///////////////////////////////////
	// DigitalExposure
	/// The present value is acquired from Slider Control.bUpdate is set to true when a value has change.
	bUpdate |= GET_SLIDER( m_ExposureSlider , m_nExposure , "%.1f" , IDC_EDIT1 );
	rational.numerator = m_nExposure;
	rational.denominator = 10;
	/// It is set as kEdsPropID_DigitalExposure of EdsImageRef for the value acquired from Control.
	err= EdsSetPropertyData( m_ImageRef, kEdsPropID_DigitalExposure , 0, sizeof(rational),&rational);
	/// When there is change of a property value, the message of renewal of picture drawing is sent.
	if( bUpdate )
		this->GetParent()->GetParent()->PostMessage(WM_IMAGE_UPDATE,0,0);
}


///////////////////////////////////////
// DigitalExposure
/// kEdsPropID_DigitalExposure is returned to the setting value at the time of photography.
void CProcessPage::OnBnClickedButton1()
{
	EdsRational rational;
	EdsError err;

	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_AtCapture_Flag|kEdsPropID_DigitalExposure, 0, sizeof(rational),&rational);
	if( err == EDS_ERR_OK )
		SET_SLIDER( m_ExposureSlider , rational.numerator , "%.1f" , IDC_EDIT1 );

	OnDigitalExposureChanged();
}
///////////////////////////////////////
// WhiteBalance
/// WhiteBalance information is returned to the setting value at the time of photography.
void CProcessPage::OnBnClickedButton2()
{
	EdsError err;
	EdsUInt32 value;
	EdsInt32 wbs[2];
	// WhiteBalance
	err= EdsGetPropertyData( m_ImageRef,kEdsPropID_AtCapture_Flag|kEdsPropID_WhiteBalance , 0, sizeof(value),&value);
	if( err == EDS_ERR_OK )
		SET_COMBO( m_WhiteBalanceCombo , value );
	// WhiteBalanceShift
	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_AtCapture_Flag|kEdsPropID_WhiteBalanceShift, 0, sizeof(wbs),wbs);
	if( err == EDS_ERR_OK )
	{
		SET_SLIDER( m_WhiteBalanceShiftBASlider , wbs[0] , "%d" , IDC_EDIT2 );
		SET_SLIDER( m_WhiteBalanceShiftMGSlider , wbs[1] , "%d" , IDC_EDIT3 );
	}
	// ColorTemperature
	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_AtCapture_Flag|kEdsPropID_ColorTemperature, 0, sizeof(value),&value);
	if( err == EDS_ERR_OK )
	{
		CString str;
		str.Format("%d",value);
		GetDlgItem(IDC_EDIT_CT)->SetWindowText(str);
	}
	OnWhiteBalanceChanged();
}

///////////////////////////////////////
// Picture Style
/// Picture Style information is returned to the setting value at the time of photography.
void CProcessPage::OnBnClickedButton3()
{
	EdsError err;
	EdsUInt32 value;
	EdsPictureStyleDesc	desc;
	///////////////////////////////////////
	// Picture Style
	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_AtCapture_Flag|kEdsPropID_PictureStyle, 0, sizeof(value),&value);
	if( err == EDS_ERR_OK )
		SET_COMBO( m_PictureStyleCombo , value );
	///////////////////////////////////////
	// Picture Style Desc
	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_AtCapture_Flag|kEdsPropID_PictureStyleDesc, 0, sizeof(desc),&desc);
	if( err == EDS_ERR_OK )
	{
		SET_SLIDER( m_ContrastSlider   , desc.contrast  , "%d" , IDC_EDIT4 );	// Contrast
		SET_SLIDER( m_SharpnessSlider  , desc.sharpness , "%d" , IDC_EDIT5 );	// Sharpness
		SET_SLIDER( m_ColorToneSlider  , desc.colorTone , "%d" , IDC_EDIT6 );	// Color Tone
		SET_SLIDER( m_SaturationSlider , desc.colorTone , "%d" , IDC_EDIT7 );	// Saturation
		SET_COMBO( m_FilterEffectCombo , desc.filterEffect );
		SET_COMBO( m_ToningEffectCombo , desc.toningEffect );
	}
	OnPictureStyleChanged();
}


///////////////////////////////////////
// Color Space
/// kEdsPropID_ColorSpace is returned to the setting value at the time of photography.
void CProcessPage::OnBnClickedButton4()
{
	EdsError err;
	EdsUInt32 value;
	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_AtCapture_Flag|kEdsPropID_ColorSpace, 0, sizeof(value),&value);
	if( err == EDS_ERR_OK )
		SET_COMBO( m_ColorSpaceCombo , value );
	OnColorSpaceChanged();
}

//////////////////////////////////////////////////////
// CacheImage
/// A setup of EdsCacheImage is changed into the value acquired from the check box.
void CProcessPage::OnBnClickedCheckCashe()
{
	EdsCacheImage( m_ImageRef,((CButton*) GetDlgItem(IDC_CHECK_CASHE))->GetCheck() );

}

void CProcessPage::OnWhiteBalanceChanged()
{
	bool bUpdate=false;
	EdsError err;

	CString str;
	EdsUInt32 value;
	///////////////////////////////////
	// WhiteBalance
	/// The present value is acquired from Combo Box.
	bUpdate |= GET_COMBO( m_WhiteBalanceCombo , m_nWB );
	/// It is set as kEdsPropID_WhiteBalance of EdsImageRef for the value acquired from Control.
	err= EdsSetPropertyData( m_ImageRef, kEdsPropID_WhiteBalance , 0, sizeof(m_nWB),&m_nWB);
	///////////////////////////////////
	// WhiteBalanceShift BA/MG
	/// The present value is acquired from Slider Control.
	bUpdate |= GET_SLIDER( m_WhiteBalanceShiftBASlider , m_WBShift[0] , "%d" , IDC_EDIT2 );
	bUpdate |= GET_SLIDER( m_WhiteBalanceShiftMGSlider , m_WBShift[1] , "%d" , IDC_EDIT3 );
	/// It is set as kEdsPropID_WhiteBalanceShift of EdsImageRef for the value acquired from Control.
	err= EdsSetPropertyData( m_ImageRef, kEdsPropID_WhiteBalanceShift, 0, sizeof(m_WBShift),&m_WBShift);
	
	///////////////////////////////////
	// ColorTemperature
	m_ColorTemperatureEdit.EnableWindow(m_nWB == kEdsWhiteBalance_ColorTemp);
	GetDlgItem(IDC_EDIT_CT)->GetWindowText(str);
	value = atoi(str);
	/// The setting value of ColorTemperature is evaluated.It changes into the value which can be set up.
	if( 2800 > value )	value = 2800;
	if( 10000 < value )	value = 10000;
	bUpdate |= ( value != m_nColorTemp);
	m_nColorTemp = value-value%100;
	if( atoi(str) != m_nColorTemp)
	{
		/// If a value is changed, it will update to Edit Control.
		str.Format("%d",m_nColorTemp);
		GetDlgItem(IDC_EDIT_CT)->SetWindowText(str);
	}
	/// It is set as kEdsPropID_ColorTemperature of EdsImageRef for the value acquired from Control.
	err= EdsSetPropertyData( m_ImageRef, kEdsPropID_ColorTemperature, 0, sizeof(m_nColorTemp),&m_nColorTemp);

	/// When there is change of a property value, the message of renewal of picture drawing is sent.
	if( bUpdate )
		this->GetParent()->GetParent()->PostMessage(WM_IMAGE_UPDATE,0,0);
}

void CProcessPage::OnWhiteBalanceShiftChanged()
{
	bool bUpdate=false;
	EdsError err;

	///////////////////////////////////
	// WhiteBalanceShift BA/MG
	/// The present value is acquired from Slider Control.
	bUpdate |= GET_SLIDER( m_WhiteBalanceShiftBASlider , m_WBShift[0] , "%d" , IDC_EDIT2 );
	bUpdate |= GET_SLIDER( m_WhiteBalanceShiftMGSlider , m_WBShift[1] , "%d" , IDC_EDIT3 );
	/// It is set as kEdsPropID_WhiteBalanceShift of EdsImageRef for the value acquired from Control.
	err= EdsSetPropertyData( m_ImageRef, kEdsPropID_WhiteBalanceShift, 0, sizeof(m_WBShift),&m_WBShift);
	

	/// When there is change of a property value, the message of renewal of picture drawing is sent.
	if( bUpdate )
		this->GetParent()->GetParent()->PostMessage(WM_IMAGE_UPDATE,0,0);
}

void CProcessPage::OnPictureStyleChanged()
{
	bool bUpdate=false;
	EdsError err;
	///////////////////////////////////
	// Picture Style
	/// The present value is acquired from Combo Box.
	bUpdate |= GET_COMBO( m_PictureStyleCombo , m_nPictureStyle );
	/// It is set as kEdsPropID_PictureStyle of EdsImageRef for the value acquired from Control.
	err= EdsSetPropertyData( m_ImageRef, kEdsPropID_PictureStyle, 0, sizeof(m_nPictureStyle),&m_nPictureStyle);
	///////////////////////////////////
	// Picture Style Desc
	/// A Picture Style setting item value is acquired from each control.
	bUpdate |= GET_SLIDER( m_ContrastSlider   , m_PicStyDesc.contrast   , "%d" , IDC_EDIT4 );	// Contrast
	bUpdate |= GET_SLIDER( m_SharpnessSlider  , m_PicStyDesc.sharpness  , "%d" , IDC_EDIT5 );	// Sharpness
	bUpdate |= GET_SLIDER( m_ColorToneSlider  , m_PicStyDesc.colorTone  , "%d" , IDC_EDIT6 );	// ColorTone
	bUpdate |= GET_SLIDER( m_SaturationSlider , m_PicStyDesc.saturation , "%d" , IDC_EDIT7 );	// Saturation
	bUpdate |= GET_COMBO( m_FilterEffectCombo , m_PicStyDesc.filterEffect );	// FilterEffect
	bUpdate |= GET_COMBO( m_ToningEffectCombo , m_PicStyDesc.toningEffect );	// ToningEffect

	/// It is set as kEdsPropID_PictureStyleDesc of EdsImageRef for the value acquired from Control.
	err= EdsSetPropertyData( m_ImageRef, kEdsPropID_PictureStyleDesc, 0, sizeof(m_PicStyDesc),&m_PicStyDesc);
	
	/// When there is change of a property value, the message of renewal of picture drawing is sent.
	if( bUpdate )
		this->GetParent()->GetParent()->PostMessage(WM_IMAGE_UPDATE,0,0);
}

void CProcessPage::OnColorSpaceChanged()
{
	bool bUpdate=false;
	EdsError err;
	///////////////////////////////////
	// ColorSpace
	/// The present value is acquired from Combo Box.
	bUpdate |= GET_COMBO( m_ColorSpaceCombo , m_nColorSpace );
	/// It is set as kEdsPropID_ColorSpace of EdsImageRef for the value acquired from Control.
	err= EdsSetPropertyData( m_ImageRef, kEdsPropID_ColorSpace, 0, sizeof(m_nColorSpace),&m_nColorSpace);
	
	/// When there is change of a property value, the message of renewal of picture drawing is sent.
	if( bUpdate )
		this->GetParent()->GetParent()->PostMessage(WM_IMAGE_UPDATE,0,0);
}