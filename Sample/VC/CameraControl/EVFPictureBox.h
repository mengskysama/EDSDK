/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : EVFPictureBox.h	                                              *
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

#pragma once

#include "Observer.h"
#include "ActionSource.h"

// CEVFPictureBox

class CEVFPictureBox : public CStatic, public ActionSource , public Observer
{
	DECLARE_DYNAMIC(CEVFPictureBox)
	
private:
	BOOL active;
	EdsFocusInfo	m_focusInfo;
	EdsBool			m_bDrawZoomFrame;

	void OnDrawImage(CDC *pDC, unsigned char* pbyteImage, int size);
	void OnDrawFocusRect(CDC *pDC, CRect zoomRect, CSize sizeJpegLarge);
public:
	CEVFPictureBox();
	virtual ~CEVFPictureBox();

	//observer
	virtual void update(Observable* from, CameraEvent *e);

protected:
	afx_msg LRESULT OnEvfDataChanged(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};


