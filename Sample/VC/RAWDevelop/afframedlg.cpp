// AFFrameDlg.cpp
//

#include "stdafx.h"
#include "RAWDevelop.h"
#include "AFFrameDlg.h"


// CAFFrameDlg
IMPLEMENT_DYNAMIC(CAFFrameDlg, CDialog)

CAFFrameDlg::CAFFrameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAFFrameDlg::IDD, pParent)
{
	m_ImageRef = NULL;
	m_pDrawImage = NULL;
}

CAFFrameDlg::~CAFFrameDlg()
{
	if(m_ImageRef!=NULL){
		EdsRelease(m_ImageRef);
	}
	if(m_pDrawImage!=NULL)delete m_pDrawImage;
	m_ImageRef = NULL;
	m_pDrawImage = NULL;
}

void CAFFrameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CAFFrameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	RECT wRect;
	this->GetWindowRect(&wRect);
	
	/// The instance of a picture drawing class is created.
	CWnd *pFrame=GetDlgItem(IDC_AFFRAME_VIEW);
	CRect rect;
	pFrame->GetClientRect(rect);
	m_pDrawImage = new CDrawImage(rect.Size());

	memset(&m_focusInfo, 0, sizeof(m_focusInfo));
	return TRUE;  // return TRUE  unless you set the focus to a control
}


BEGIN_MESSAGE_MAP(CAFFrameDlg, CDialog)
	ON_MESSAGE(WM_IMAGE_UPDATE, OnImageUpdate)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAFFrameDlg
LRESULT CAFFrameDlg::OnImageUpdate(WPARAM wParam, LPARAM lParam)
{
	if( wParam == 0 )
	{
		/// Development is performed and carried out and a view is updated.
		LoadImage();
	}
	return 0;
}

//////////////////////////////////////////////////////
/// A picture is acquired from the target EdsImageRef and an acquisition picture is registered into a drawing instance.
void CAFFrameDlg::LoadImage()
{
	/// The picture of a drawing instance is cleared.
	m_pDrawImage->Clear(0);
	if( m_ImageRef == NULL )
		return;

	EdsImageSource source = kEdsImageSrc_RAWThumbnail;
	EdsImageInfo imageInfo;
	EdsGetImageInfo( m_ImageRef , source, &imageInfo); 

	/// Demand size is adjusted so that an aspect ratio may not change.
	EdsSize viewSize;
	float ratio;
	viewSize.width = m_pDrawImage->GetWidth();
	viewSize.height = m_pDrawImage->GetHeight();
	if(imageInfo.effectiveRect.size.width>imageInfo.effectiveRect.size.height)
	{
		ratio = (float)imageInfo.effectiveRect.size.width / viewSize.width;
		if((EdsInt32)(imageInfo.effectiveRect.size.height/ratio) > viewSize.height)
			ratio = (float)imageInfo.effectiveRect.size.height / viewSize.height;
	}
	else
	{
		ratio = (float)imageInfo.effectiveRect.size.height / viewSize.height;
		if((EdsInt32)(imageInfo.effectiveRect.size.width/ratio) > viewSize.width)
			ratio = (float)imageInfo.effectiveRect.size.width / viewSize.width;	
	}
	EdsSize size;
	size.width = (EdsInt32)(imageInfo.effectiveRect.size.width/ratio);
	size.height = (EdsInt32)(imageInfo.effectiveRect.size.height/ratio);

	/// Creation of an output stream.
	EdsStreamRef DstStreamRef;
	EdsError err = EdsCreateMemoryStream( 0 , &DstStreamRef );

	/// A picture is acquired from EdsImageRef.
	err = EdsGetImage( m_ImageRef , source , kEdsTargetImageType_RGB , imageInfo.effectiveRect , size , DstStreamRef );
	if( err == EDS_ERR_OK )
	{
		/// The start address of the acquired picture is acquired.
		EdsVoid* pBuff;
		EdsGetPointer( DstStreamRef , &pBuff );
		/// A picture is updated to a drawing instance.
		m_pDrawImage->SetImage( size.width , size.height , pBuff );
	}
	else
	{
		AfxMessageBox("The error occurred with the EdsGetImage function.");
	}
	/// The output stream is released.
	EdsRelease(DstStreamRef);

	// FocusInfo
	EdsFocusInfo	focusInfo = {0};
	err= EdsGetPropertyData( m_ImageRef, kEdsPropID_FocusInfo , 0 , sizeof(focusInfo), &focusInfo );
	m_focusInfo = focusInfo;
	if(err == EDS_ERR_OK)
	{
		float xRatio = 1;
		float yRatio = 1;

		xRatio = (float)size.width/focusInfo.imageRect.size.width;
		yRatio = (float)size.height/focusInfo.imageRect.size.height;
		for(EdsUInt32 i = 0; i < focusInfo.pointNumber; i++)
		{
			m_focusInfo.focusPoint[i].rect.point.x = (EdsUInt32)(m_focusInfo.focusPoint[i].rect.point.x * xRatio);
			m_focusInfo.focusPoint[i].rect.point.y = (EdsUInt32)(m_focusInfo.focusPoint[i].rect.point.y * yRatio);
			m_focusInfo.focusPoint[i].rect.size.width = (EdsUInt32)(m_focusInfo.focusPoint[i].rect.size.width * xRatio);
			m_focusInfo.focusPoint[i].rect.size.height = (EdsUInt32)(m_focusInfo.focusPoint[i].rect.size.height * yRatio);
		}
		RedrawWindow();
	}
}

void CAFFrameDlg::OnPaint()
{
	CDialog::OnPaint();
	/// A picture is drawn.
	CWnd *pFrame=GetDlgItem(IDC_AFFRAME_VIEW);
	CPaintDC dc(pFrame);
	if(m_pDrawImage!=NULL)
	{
		m_pDrawImage->Draw(dc.m_hDC);

		HPEN defaultPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		HPEN justPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		HPEN oldPen;
		LOGBRUSH  logBrush = {0};
		logBrush.lbStyle = BS_NULL;
		HBRUSH newBrush = CreateBrushIndirect(&logBrush);
		HBRUSH oldBrush = (HBRUSH)SelectObject(dc.m_hDC, newBrush);

		for(EdsUInt32 i = 0; i < m_focusInfo.pointNumber; i++)
		{
			if(m_focusInfo.focusPoint[i].valid==1) {
				if(m_focusInfo.focusPoint[i].justFocus==1) {
					oldPen = (HPEN)SelectObject(dc.m_hDC, justPen);
				} else {
					oldPen = (HPEN)SelectObject(dc.m_hDC, defaultPen);
				}
				RECT frame;
				frame.left = (int)(m_focusInfo.focusPoint[i].rect.point.x);
				frame.top = (int)(m_focusInfo.focusPoint[i].rect.point.y);
				frame.right = frame.left + (int)(m_focusInfo.focusPoint[i].rect.size.width);
				frame.bottom = frame.top + (int)(m_focusInfo.focusPoint[i].rect.size.height);

				Rectangle(dc.m_hDC, frame.left, frame.top, frame.right, frame.bottom);
				SelectObject(dc.m_hDC, oldPen);
			}
		}
		SelectObject(dc.m_hDC, oldBrush);
		DeleteObject(newBrush);
		DeleteObject(justPen);
		DeleteObject(defaultPen);
	}
}
