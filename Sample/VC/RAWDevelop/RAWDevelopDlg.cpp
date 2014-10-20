/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : RAWDevelopDlg.cpp                                               *
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
#include "RAWDevelopDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRAWDevelopDlg dialog



CRAWDevelopDlg::CRAWDevelopDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRAWDevelopDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pDrawImage = NULL;
	m_ImageRef = NULL;
	m_bLoadDisable = false;
	m_width=0;
}

void CRAWDevelopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRAWDevelopDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OPENFILE, OnBnClickedOpenFile)
	ON_BN_CLICKED(IDC_RADIO_THM, OnBnClickedRadioThm)
	ON_BN_CLICKED(IDC_RADIO_FULL, OnBnClickedRadioFull)
	ON_EN_CHANGE(IDC_EDIT_Y, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_X, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_W, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_H, OnEnChangeEdit)
	ON_MESSAGE(WM_IMAGE_UPDATE, OnImageUpdate)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_AFFRAME, OnBnClickedAfframe)
	ON_EN_KILLFOCUS(IDC_EDIT_X, &CRAWDevelopDlg::OnEnKillfocusEdit)
	ON_EN_KILLFOCUS(IDC_EDIT_Y, &CRAWDevelopDlg::OnEnKillfocusEdit)
	ON_EN_KILLFOCUS(IDC_EDIT_W, &CRAWDevelopDlg::OnEnKillfocusEdit)
	ON_EN_KILLFOCUS(IDC_EDIT_H, &CRAWDevelopDlg::OnEnKillfocusEdit)
END_MESSAGE_MAP()


// CRAWDevelopDlg message handlers

BOOL CRAWDevelopDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	/// EDSDK is initialized.
	EdsInitializeSDK();

	/// The instance of a picture drawing class is created.
	CWnd *pFrame=GetDlgItem(IDC_IMAGEFRAME);
	CRect rect;
	pFrame->GetWindowRect(rect);
	m_pDrawImage = new CDrawImage(rect.Size());

	/// Property information display area is initialized.
	CListCtrl *pList=(CListCtrl *)GetDlgItem(IDC_LIST1);
	pList->SetBkColor(RGB(0,0,0));
	pList->SetTextBkColor(RGB(0,0,0));
	pList->SetTextColor(RGB(255,255,255));

	/// Instance creation of an operation panel
	m_pCtrlPanel = new CCtrlPanelSheet("Panel");
	if(!m_pCtrlPanel->Create(this,WS_CHILD|WS_VISIBLE , 0))
	{
		TRACE0("create failed\n");
		return FALSE;
	}
	m_pCtrlPanel->ModifyStyle(0,WS_TABSTOP);
	m_pCtrlPanel->ModifyStyleEx(0,WS_EX_CONTROLPARENT);

	CRect rcNewPosition;
	CWnd* pWndNewArea=GetDlgItem(IDC_CTRLPANEL_FRAME);
	if(pWndNewArea==NULL)
	{
		ASSERT(FALSE);
		return false;
	}
	pWndNewArea->GetWindowRect(&rcNewPosition);
	this->ScreenToClient(&rcNewPosition);
	PositionEmbeddedPropertySheet(this,m_pCtrlPanel,rcNewPosition);
	m_pCtrlPanel->SetImageRef(m_ImageRef);


	/// ProgressCtrl is initialized.
	CProgressCtrl *pProgress=(CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	pProgress->SetPos(0);
	pProgress->SetRange(0,100);

	// initialize "AF Frame" &"Tone Curve" check boxes
	CButton *pAFFrame=(CButton*)GetDlgItem(IDC_AFFRAME);
	pAFFrame->EnableWindow(TRUE);
	pAFFrame->SetCheck(BST_UNCHECKED);

	m_afFrameDlg = NULL;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRAWDevelopDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRAWDevelopDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
		/// A picture is drawn.
		CWnd *pFrame=GetDlgItem(IDC_IMAGEFRAME);
		CPaintDC dc(pFrame);
		m_pDrawImage->Draw(dc.m_hDC);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRAWDevelopDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//////////////////////////////////////////////////////
/// A picture file is chosen and EdsImageRef is created.
void CRAWDevelopDlg::OnBnClickedOpenFile()
{
	if( m_pDrawImage == NULL )
		return;
	static char BASED_CODE gbszFilter[] = "CR2 Files (*.CR2)|*.CR2|CRW Files (*.CRW)|*.CRW|TIF Files (*.TIF)|*.TIF|AllFiles (*.*)|*.*||";
	CFileDialog dlg(TRUE,"*.CR2",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,gbszFilter);
	if( dlg.DoModal() == IDOK )
	{
		m_width=0;
		EdsStreamRef     StreamRef;
		EdsError err;

		/// EdsStreamRef of the selected file is created.
		err = EdsCreateFileStream(dlg.GetPathName(),kEdsFileCreateDisposition_OpenExisting,kEdsAccess_ReadWrite,&StreamRef);
		if( err == EDS_ERR_OK )
		{
			if(m_ImageRef)
			{
				/// When EdsImageRef is already created, EdsImageRef no longer using is released.
				EdsRelease(m_ImageRef);
				m_ImageRef=NULL;
				m_pCtrlPanel->SetImageRef(m_ImageRef);
			}
			/// EdsImageRef is created.
			err = EdsCreateImageRef(StreamRef,&m_ImageRef);
			if( err == EDS_ERR_OK )
			{
				CheckRadioButton(IDC_RADIO_THM, IDC_RADIO_FULL, IDC_RADIO_THM);
				GetDlgItem(IDC_EDIT1)->SetWindowText( dlg.GetPathName() );

				/// A property is acquired from EdsImageRef and a property display list is created.
				LoadPropertyList();
				
				OnBnClickedRadioThm();
				/// To the page of a control panel   EdsImageRef is registered.
				m_pCtrlPanel->SetImageRef(m_ImageRef);

				/// AF Frame Dialog   EdsImageRef is registered.
				EdsDataType type;
				EdsUInt32 size;
				err= EdsGetPropertySize( m_ImageRef, kEdsPropID_FocusInfo , 0 , &type, &size);
				if(err==EDS_ERR_OK)
				{
					GetDlgItem(IDC_AFFRAME)->EnableWindow(TRUE);
					if(m_afFrameDlg!=NULL)
					{
						m_afFrameDlg->SetImageRef(m_ImageRef);
						if(	((CButton *)GetDlgItem(IDC_AFFRAME))->GetCheck()==BST_CHECKED) m_afFrameDlg->ShowWindow(SW_SHOW);
					}
				}
				else
				{
					GetDlgItem(IDC_AFFRAME)->EnableWindow(FALSE);
					if(m_afFrameDlg!=NULL)m_afFrameDlg->ShowWindow(SW_HIDE);
				}
				LoadImage();
			}
			EdsRelease(StreamRef);
		}
	}

}
//////////////////////////////////////////////////////
/// A property is acquired from the target EdsImageRef to the list of property
/// information display area, and display information is registered.
void CRAWDevelopDlg::LoadPropertyList()
{
	CListCtrl *pList=(CListCtrl *)GetDlgItem(IDC_LIST1);
	pList->DeleteAllItems();
	int nColumnCount = pList->GetHeaderCtrl()->GetItemCount();
	// Delete all of the columns.
	for (int i=0;i < nColumnCount;i++)
	{
		pList->DeleteColumn(0);
	}
	pList->InsertColumn(0,"Caption",LVCFMT_LEFT,110);
	pList->InsertColumn(1,"Data",LVCFMT_LEFT,200);

	EdsError err;

	CPropertyString	* propString = new CPropertyString(m_ImageRef);
	EdsImageSource	srcList[] ={
			kEdsImageSrc_RAWThumbnail,
			kEdsImageSrc_RAWFullView,
	};
	EdsPropertyID	propList[] = {
			kEdsPropID_MakerName,
			kEdsPropID_ProductName,
			kEdsPropID_DateTime,
			kEdsPropID_Tv,
			kEdsPropID_Av,
			kEdsPropID_ISOSpeed,
			kEdsPropID_FocalLength,
			kEdsPropID_LensName,
			kEdsPropID_BodyID,
			kEdsPropID_Artist,

			kEdsPropID_Copyright,
			kEdsPropID_OwnerName,
			kEdsPropID_FirmwareVersion,
			kEdsPropID_JpegQuality,
			kEdsPropID_Orientation,
			kEdsPropID_AEMode,

			kEdsPropID_DriveMode,
			kEdsPropID_MeteringMode,
			kEdsPropID_AFMode,
			kEdsPropID_ExposureCompensation,
			kEdsPropID_DigitalExposure,
			kEdsPropID_FlashCompensation,
			kEdsPropID_Bracket,
			kEdsPropID_WhiteBalance,
			kEdsPropID_WhiteBalanceShift,
			kEdsPropID_Sharpness,
			kEdsPropID_ColorSaturation,
			kEdsPropID_ColorMatrix,
			kEdsPropID_Contrast,
			kEdsPropID_ColorTone,
			kEdsPropID_ColorSpace,
			kEdsPropID_PhotoEffect,
			kEdsPropID_FilterEffect,
			kEdsPropID_ToningEffect,
			kEdsPropID_ToneCurve,
			kEdsPropID_PictureStyle,
			kEdsPropID_FlashOn,
			kEdsPropID_FlashMode,
			kEdsPropID_RedEye,
			kEdsPropID_NoiseReduction,
			kEdsPropID_GPSVersionID,
			kEdsPropID_GPSLatitude,
			kEdsPropID_GPSLongitude,
			kEdsPropID_GPSAltitude,
			kEdsPropID_GPSDateStamp,
			kEdsPropID_GPSTimeStamp,
			kEdsPropID_GPSSatellites,

			kEdsPropID_GPSStatus,
	};

	for(int i = 0; i < sizeof(srcList)/sizeof(EdsImageSource); i++)
	{
		err = propString->SetImageSource(srcList[i]);
		if(err == EDS_ERR_OK)	AddPropertyList(propString);
	}
	for(int i = 0; i < sizeof(propList)/sizeof(EdsPropertyID); i++)
	{
		err = propString->SetPropertyID(propList[i]);
		if(err == EDS_ERR_OK)	AddPropertyList(propString);
	}

	if(propString) delete propString;
}

void CRAWDevelopDlg::AddPropertyList( CPropertyString *propStr)
{
	EdsChar		*title = NULL;
	EdsUInt32	titleLen = 0;
	EdsChar		*value = NULL;
	EdsUInt32	valueLen = 0;
	EdsUInt32	valueCount = 0;
	EdsError	err;

	// value
	err = propStr->GetPropertyValueCount(&valueCount);
	if(valueCount > 0)
	{
		// title
		err = propStr->GetPropertyTitle(&titleLen, NULL);
		if(err == EDS_ERR_OK && titleLen > 0)	title = (EdsChar*)calloc(EDS_MAX_NAME + 1, 1);
		if(title != NULL)		err = propStr->GetPropertyTitle(&titleLen, title);

		err = propStr->GetPropertyValue(0, &valueLen, NULL);
		if(err == EDS_ERR_OK && valueLen > 0)	value = (EdsChar*)calloc(EDS_MAX_NAME + 1, 1);
		if(value != NULL)		err = propStr->GetPropertyValue(0, &valueLen, value);

		if( err == EDS_ERR_OK && title != NULL && value != NULL)
		{
			AddPropertyList( title , CString(":")+value );
		}
		if(title!=NULL)	free(title);
		if(value!=NULL)	free(value);
		
		for(EdsUInt32 j = 1; j < valueCount; j++)
		{
			// value
			err = propStr->GetPropertyValue(j, &valueLen, NULL);
			if(err == EDS_ERR_OK && valueLen > 0)	value = (EdsChar*)calloc(EDS_MAX_NAME + 1, 1);
			if(value != NULL)		err = propStr->GetPropertyValue(j, &valueLen, value);
			if(err == EDS_ERR_OK && value != NULL)
			{
				AddPropertyList( "" , CString(":")+value );
			}
			if(value!=NULL)	free(value);
		}
	}
}

//////////////////////////////////////////////////////
/// The callback function for a progress display.
EdsError EDSCALLBACK CRAWDevelopDlg::ProgressFunc (
						EdsUInt32	inPercent,
						EdsVoid *	inContext,
						EdsBool	*	outCancel
						)
{
	CRAWDevelopDlg *pobj = (CRAWDevelopDlg *)inContext;
	CProgressCtrl *pProgress=(CProgressCtrl*)pobj->GetDlgItem(IDC_PROGRESS1);
	pProgress->SetPos(inPercent);

	if(inPercent==100)
	{
		pobj->Invalidate();
	}
	return EDS_ERR_OK;
}


//////////////////////////////////////////////////////
/// A picture is acquired from the target EdsImageRef and an acquisition picture is registered into a drawing instance.
void CRAWDevelopDlg::LoadImage()
{
	/// The picture of a drawing instance is cleared.
	m_pDrawImage->Clear(0);
	if( m_ImageRef == NULL )
		return;

	/// The sauce of the picture to acquire is determined with reference to a radio button.
	EdsImageSource source=kEdsImageSrc_Thumbnail;
	if( ((CButton*) GetDlgItem(IDC_RADIO_THM))->GetCheck() )
	{
		source = kEdsImageSrc_RAWThumbnail;
	}
	if( ((CButton*) GetDlgItem(IDC_RADIO_FULL))->GetCheck() )
	{
		source = kEdsImageSrc_RAWFullView;
	}	
	EdsImageInfo	thmInfo, fullInfo;
	EdsGetImageInfo( m_ImageRef , kEdsImageSrc_RAWThumbnail , &thmInfo );
	EdsGetImageInfo( m_ImageRef , kEdsImageSrc_RAWFullView , &fullInfo );
	m_ratioOfThmToFull = (float)fullInfo.width/thmInfo.width;

	/// The picture area to request is acquired from an editing box.
	EdsRect rect;
	CString str;
	GetDlgItem(IDC_EDIT_X)->GetWindowText(str);
	rect.point.x	= atoi( str );
	GetDlgItem(IDC_EDIT_Y)->GetWindowText(str);
	rect.point.y	= atoi( str );
	GetDlgItem(IDC_EDIT_W)->GetWindowText(str);
	rect.size.width	= atoi( str );
	GetDlgItem(IDC_EDIT_H)->GetWindowText(str);
	rect.size.height= atoi( str );

	/// Demand size is adjusted so that an aspect ratio may not change.
	EdsSize viewSize;
	viewSize.width = m_pDrawImage->GetWidth();
	viewSize.height = m_pDrawImage->GetHeight();
	if(rect.size.width>rect.size.height)
	{
		m_ratio = (float)rect.size.width / viewSize.width;
		if((EdsInt32)(rect.size.height/m_ratio) > viewSize.height)
			m_ratio = (float)rect.size.height / viewSize.height;
	}
	else
	{
		m_ratio = (float)rect.size.height / viewSize.height;
		if((EdsInt32)(rect.size.width/m_ratio) > viewSize.width)
			m_ratio = (float)rect.size.width / viewSize.width;	
	}
	EdsSize size;
	size.width = (EdsInt32)(rect.size.width/m_ratio);
	size.height = (EdsInt32)(rect.size.height/m_ratio);

	/// Creation of an output stream.
	EdsStreamRef DstStreamRef;
	EdsError err = EdsCreateMemoryStream( 0 , &DstStreamRef );

	/// A progress callback function is set as the output stream.
	if(err == EDS_ERR_OK)
	{
		err = EdsSetProgressCallback(DstStreamRef, ProgressFunc, kEdsProgressOption_Periodically, this);
	}
	/// A picture is acquired from EdsImageRef.
	err = EdsGetImage( m_ImageRef , source , kEdsTargetImageType_RGB , rect , size , DstStreamRef );
	if( err == EDS_ERR_OK )
	{
		/// The start address of the acquired picture is acquired.
		EdsVoid* pBuff;
		EdsGetPointer( DstStreamRef , &pBuff );
		/// A picture is updated to a drawing instance.
		m_pDrawImage->SetImage( size.width , size.height , pBuff );
		GetDlgItem(IDC_IMAGEFRAME)->Invalidate();
	}
	else
	{
		AfxMessageBox("The error occurred with the EdsGetImage function.");
	}
	/// The output stream is released.
	EdsRelease(DstStreamRef);

	/// Progress is reset.
	CProgressCtrl *pProgress=(CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	pProgress->SetPos(0);
}



//////////////////////////////////////////////////////
void CRAWDevelopDlg::SaveImage( CString &path , CString &icc )
{
	EdsTargetImageType	inImageType;
	EdsSaveImageSetting	inSaveSetting;
	m_pCtrlPanel->Get(inImageType);
	m_pCtrlPanel->Get(inSaveSetting);

	EdsStreamRef ICCRef=NULL;

	EdsStreamRef DstStreamRef;
	EdsError err = EdsCreateFileStream( path , kEdsFileCreateDisposition_CreateAlways , kEdsAccess_Write , &DstStreamRef );
	if( err == EDS_ERR_OK )
	{
		/// A progress callback function is set as the output stream.
		if(err == EDS_ERR_OK)
		{
			err = EdsSetProgressCallback( DstStreamRef , ProgressFunc , kEdsProgressOption_Periodically, this);
		}
		if( !icc.IsEmpty() )
		{
			/// ICC is set when adding ICC.
			err = EdsCreateFileStream( icc , kEdsFileCreateDisposition_OpenExisting , kEdsAccess_Read , &ICCRef );
			if( err == EDS_ERR_OK )
			{
				inSaveSetting.iccProfileStream = ICCRef;
			}
		}
		/// Picture preservation is performed.
		err = EdsSaveImage( m_ImageRef , inImageType , inSaveSetting , DstStreamRef );
	}
	if(ICCRef)
		EdsRelease(ICCRef);

	/// The output stream is released.
	EdsRelease(DstStreamRef);

	/// Progress is reset.
	CProgressCtrl *pProgress=(CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	pProgress->SetPos(0);
}



//////////////////////////////////////////////////////
/// The picture redraw demand message from a control panel is processed.
LRESULT CRAWDevelopDlg::OnImageUpdate(WPARAM wParam, LPARAM lParam)
{
	if( wParam == 0 )
	{
		/// Development is performed and carried out and a view is updated.
		LoadImage();
	}
	else
	{
		/// A picture preservation demand is performed.
		CString *pPath = (CString*)wParam;
		CString *pIcc = (CString*)lParam;
		SaveImage( *pPath , *pIcc );
	}
	if(m_afFrameDlg!=NULL)m_afFrameDlg->PostMessage(WM_IMAGE_UPDATE,0,0);
	return 0;
}


//////////////////////////////////////////////////////
/// Click white balance click preparation processing.
/// Cursor form will be changed into a syringe if it goes into picture drawing area.
void CRAWDevelopDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if( m_pCtrlPanel->IsClickWB() )
	{
		CWnd *pFrame=GetDlgItem(IDC_IMAGEFRAME);
		CRect rect;
		pFrame->GetWindowRect(rect);
		this->ScreenToClient(&rect);
		if( rect.PtInRect(point) )
		{
			HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);
			::SetCursor( hCursor );
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

//////////////////////////////////////////////////////
/// Click white balance click processing.
/// Click coordinates are computed by full view conversion, and it sets to EdsImageRef.
void CRAWDevelopDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if( m_pCtrlPanel->IsClickWB() )
	{
		m_pCtrlPanel->ClickWB();
		CWnd *pFrame=GetDlgItem(IDC_IMAGEFRAME);
		CRect rect;
		pFrame->GetWindowRect(rect);
		this->ScreenToClient(&rect);
		if( rect.PtInRect(point) )
		{
			HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);
			::SetCursor( hCursor );
			EdsPoint click,p;

			p.x = point.x-rect.left;
			p.y = point.y-rect.top;
			click.x = (int)(p.x*m_ratio);
			click.y = (int)(p.y*m_ratio);

			CString str;
			GetDlgItem(IDC_EDIT_X)->GetWindowText(str);
			click.x	+= atoi( str );
			GetDlgItem(IDC_EDIT_Y)->GetWindowText(str);
			click.y	+= atoi( str );

			if( IsThumbnail() )
			{
				click.x = (int)(click.x*m_ratioOfThmToFull);
				click.y = (int)(click.y*m_ratioOfThmToFull);
			}

			EdsError err;
			err= EdsSetPropertyData( m_ImageRef, kEdsPropID_ClickWBPoint , 0, sizeof(click),&click);
			if( err == EDS_ERR_OK )
			{
				EdsUInt32 uValue=kEdsWhiteBalance_Click;
				err = EdsSetPropertyData( m_ImageRef,kEdsPropID_WhiteBalance , 0, sizeof(uValue),&uValue);
				if( err == EDS_ERR_OK )
					LoadImage();
			}
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}

//////////////////////////////////////////////////////
/// End processing of this dialog.
void CRAWDevelopDlg::OnClose()
{
	m_pCtrlPanel->DestroyWindow();
	delete m_pDrawImage;
	delete m_pCtrlPanel;

	if(m_afFrameDlg!=NULL)	delete m_afFrameDlg;
	/// It will release, if the instance of EdsImageRef is generated.
	if(m_ImageRef)
	{
		EdsRelease(m_ImageRef);
		m_ImageRef=NULL;
	}

	// The end of EDSDK.
	EdsTerminateSDK();

	CDialog::OnClose();
}


