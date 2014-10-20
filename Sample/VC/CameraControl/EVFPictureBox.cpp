/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : EVFPictureBox.cpp                                                *
*                                                                             *
*   Description: This is the Sample code to show the usage of EDSDK.          *
*                                                                             *
*                                                                             *
*******************************************************************************
*                                                                             *
*   Written and developed by Camera Design Dept.53                            *
*   Copyright Canon Inc. 2006-2008 All Rights Reserved                        *
*                                                                             *
*******************************************************************************/

#include "stdafx.h"
#include <atlimage.h>

#include "CameraControl.h"
#include "EVFPictureBox.h"

#define WM_USER_EVF_DATA_CHANGED		WM_APP+1
// CEVFPictureBox

IMPLEMENT_DYNAMIC(CEVFPictureBox, CStatic)
CEVFPictureBox::CEVFPictureBox()
{
	active = FALSE;
	memset(&m_focusInfo, 0, sizeof(EdsFocusInfo));
}

CEVFPictureBox::~CEVFPictureBox()
{
}


BEGIN_MESSAGE_MAP(CEVFPictureBox, CStatic)
	ON_MESSAGE(WM_USER_EVF_DATA_CHANGED, OnEvfDataChanged)
END_MESSAGE_MAP()



// CEVFPictureBox messge handler

void CEVFPictureBox::update(Observable* from, CameraEvent *e)
{

	std::string event = e->getEvent();

	if(event == "EvfDataChanged")
	{
		EVF_DATASET data = *static_cast<EVF_DATASET *>(e->getArg());
	
		//The update processing can be executed from another thread. 
		::SendMessage(this->m_hWnd, WM_USER_EVF_DATA_CHANGED, (WPARAM) &data, NULL);

		EdsInt32 propertyID = kEdsPropID_FocusInfo;
		fireEvent("get_Property", &propertyID);

		// Download image data.
		fireEvent("downloadEVF");
	}
	
	if (event == "PropertyChanged")
	{
		EdsInt32 proeprtyID = *static_cast<EdsInt32 *>(e->getArg());
		if(proeprtyID == kEdsPropID_Evf_OutputDevice)
		{
			CameraModel* model = (CameraModel *)from;
			EdsUInt32 device = model->getEvfOutputDevice();

			// PC live view has started.
			if (!active && (device & kEdsEvfOutputDevice_PC) != 0)
			{
				active = TRUE;
				// Start download of image data.
				fireEvent("downloadEVF");
			}

			// PC live view has ended.
			if(active && (device & kEdsEvfOutputDevice_PC) == 0)
			{
				active = FALSE;
			}
		}
		if(proeprtyID == kEdsPropID_FocusInfo)
		{
			CameraModel* model = (CameraModel *)from;
			float xRatio = 1;
			float yRatio = 1;
			CRect rect;
			GetWindowRect(&rect);

			EdsFocusInfo focusInfo = {0};
			focusInfo = model->getFocusInfo();
			m_focusInfo = focusInfo;
			xRatio = (float)(rect.Width())/(float)(focusInfo.imageRect.size.width);
			yRatio = (float)(rect.Height())/(float)(focusInfo.imageRect.size.height);
			for(EdsUInt32 i = 0; i < focusInfo.pointNumber; i++)
			{
				m_focusInfo.focusPoint[i].rect.point.x = (EdsUInt32)(m_focusInfo.focusPoint[i].rect.point.x * xRatio);
				m_focusInfo.focusPoint[i].rect.point.y = (EdsUInt32)(m_focusInfo.focusPoint[i].rect.point.y * yRatio);
				m_focusInfo.focusPoint[i].rect.size.width = (EdsUInt32)(m_focusInfo.focusPoint[i].rect.size.width * xRatio);
				m_focusInfo.focusPoint[i].rect.size.height = (EdsUInt32)(m_focusInfo.focusPoint[i].rect.size.height * yRatio);
			}
		}
		if(proeprtyID==kEdsPropID_Evf_AFMode)
		{
			CameraModel* model = (CameraModel *)from;
			m_bDrawZoomFrame = model->getEvfAFMode()!=2;
		}
	}	
}

LRESULT CEVFPictureBox::OnEvfDataChanged(WPARAM wParam, LPARAM lParam)
{
	EVF_DATASET data = *(EVF_DATASET *)wParam;
	EdsUInt32 size;

	unsigned char* pbyteImage = NULL; 

	// Get image (JPEG) pointer.
	EdsGetPointer(data.stream, (EdsVoid**)&pbyteImage );
	
	if(pbyteImage != NULL)
	{
		EdsGetLength(data.stream, &size);

		CDC *pDC = GetDC();
	
		// Display image data.
		OnDrawImage(pDC, pbyteImage, size);

		// Display the focus border if displaying the entire image.
		if(data.zoom == 1 && (data.sizeJpegLarge.width != 0 && data.sizeJpegLarge.height != 0))
		{
			OnDrawFocusRect(pDC, CRect(data.zoomRect.point.x, data.zoomRect.point.y, data.zoomRect.point.x + data.zoomRect.size.width, data.zoomRect.point.y + data.zoomRect.size.height), CSize(data.sizeJpegLarge.width, data.sizeJpegLarge.height));
		}

		ReleaseDC(pDC);
	}


	return 0;
}



void CEVFPictureBox::OnDrawImage(CDC *pDC, unsigned char* pbyteImage, int size)
{
	CImage image;

	CComPtr<IStream> stream;
	stream = NULL;

	HGLOBAL hMem = ::GlobalAlloc(GHND, size); 
	LPVOID pBuff = ::GlobalLock(hMem);

	memcpy(pBuff, pbyteImage, size);

	::GlobalUnlock(hMem);
	CreateStreamOnHGlobal(hMem, TRUE, &stream);

	image.Load(stream);

	
	CRect rect;
	GetWindowRect(&rect);

	// Drawing
	SetStretchBltMode(pDC->GetSafeHdc() , COLORONCOLOR);
	image.StretchBlt(pDC->GetSafeHdc(),  0,0,rect.Width(),rect.Height(),0,0,image.GetWidth(), image.GetHeight(),SRCCOPY);
	//image.BitBlt(hDC, 0, 0);
	image.Destroy();

	::GlobalFree(hMem);
}


void CEVFPictureBox::OnDrawFocusRect(CDC *pDC, CRect zoomRect, CSize sizeJpegLarge)
{
	// Get window size.
	CRect rect;
	GetWindowRect(&rect);

	// Draw Zoom Frame
	if(m_bDrawZoomFrame)
	{
		int cx = rect.Width();
		int cy = rect.Height();

		// The zoomPosition is given by the coordinates of the upper left of the focus border using Jpeg Large size as a reference.
		
		// The size of the focus border is one fifth the size of Jpeg Large.
		// Because the image fills the entire window, the height and width to be drawn is one fifth of the window size.

		int iw = sizeJpegLarge.cx;
		int ih = sizeJpegLarge.cy;

		// Upper left coordinate to be drawn.
		CPoint topLeft(zoomRect.left * cx / iw, zoomRect.top * cy / ih);

		// Upper right coordinate to be drawn.
		CPoint topRight(zoomRect.right * cx / iw, zoomRect.top * cy / ih);

		// Lower right coordinate to be drawn.
		CPoint bottomRight(zoomRect.right * cx / iw, zoomRect.bottom * cy / ih);

		// Lower left coordinate to be drawn.
		CPoint bottomLeft(zoomRect.left * cx / iw, zoomRect.bottom * cy / ih);

		// Draw.
		CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
		CPen *oldPen = pDC->SelectObject(&pen);
	 	
		pDC->MoveTo(topLeft);
		pDC->LineTo(topRight);
		pDC->LineTo(bottomRight);
		pDC->LineTo(bottomLeft);
		pDC->LineTo(topLeft);
		pDC->SelectObject(oldPen);
		pen.DeleteObject();
	}

	// Draw AF Frames
	HPEN defaultPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HPEN justPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN disablePen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
	HPEN oldPenH;
	LOGBRUSH  logBrush = {0};
	logBrush.lbStyle = BS_NULL;
	HBRUSH newBrush = CreateBrushIndirect(&logBrush);
	HBRUSH oldBrush = (HBRUSH)SelectObject(pDC->m_hDC, newBrush);

	for(EdsUInt32 i = 0; i < m_focusInfo.pointNumber; i++)
	{
		if(m_focusInfo.focusPoint[i].valid==1) {
			// Selecte Just Focus Pen
			if(m_focusInfo.focusPoint[i].justFocus&1) {
				oldPenH = (HPEN)SelectObject(pDC->m_hDC, justPen);
			} else {
				oldPenH = (HPEN)SelectObject(pDC->m_hDC, defaultPen);
			}
			if(m_focusInfo.focusPoint[i].selected!=1)
				oldPenH = (HPEN)SelectObject(pDC->m_hDC, disablePen);


			// Set Frame Rect
			RECT frame;
			frame.left = (int)(m_focusInfo.focusPoint[i].rect.point.x);
			frame.top = (int)(m_focusInfo.focusPoint[i].rect.point.y);
			frame.right = frame.left + (int)(m_focusInfo.focusPoint[i].rect.size.width);
			frame.bottom = frame.top + (int)(m_focusInfo.focusPoint[i].rect.size.height);
			Rectangle(pDC->m_hDC, frame.left, frame.top, frame.right, frame.bottom);
			SelectObject(pDC->m_hDC, oldPenH);
		}
	}
	SelectObject(pDC->m_hDC, oldBrush);
	DeleteObject(newBrush);
	DeleteObject(disablePen);
	DeleteObject(justPen);
	DeleteObject(defaultPen);
}
