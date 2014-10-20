/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : EvfZoomButton.cpp                                                *
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
#include "CameraControl.h"
#include "EvfZoomButton.h"


/////////////////////////////////////////////////////////////////////////////
// CEvfZoomButton

CEvfZoomButton::CEvfZoomButton()
{
}

CEvfZoomButton::~CEvfZoomButton()
{
}
void CEvfZoomButton::update(Observable* from, CameraEvent *e)
{
	std::string event = e->getEvent();
	//PropertyChanged event
	if (event == "PropertyChanged")
	{
		EdsInt32 proeprtyID = *static_cast<EdsInt32 *>(e->getArg());
		if(proeprtyID==kEdsPropID_Evf_AFMode)
		{
			CameraModel* model = (CameraModel *)from;
			this->EnableWindow(model->getEvfAFMode()!=2);
		}
	}
}

BEGIN_MESSAGE_MAP(CEvfZoomButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
END_MESSAGE_MAP()

//EvfZoomButton  message handler
void CEvfZoomButton::OnClicked() 
{
	CActionButton::OnClicked();
}
