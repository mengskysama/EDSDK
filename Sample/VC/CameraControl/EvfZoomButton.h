/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : EvfZoomButton.h      	                                          *
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

#include "ActionButton.h"
#include "Observer.h"
// CEvfZoomButton

class CEvfZoomButton : public CActionButton , public Observer
{

public:
	CEvfZoomButton();
	virtual void update(Observable* from, CameraEvent *e);

public:
	virtual ~CEvfZoomButton();

protected:
	void OnClicked();
	DECLARE_MESSAGE_MAP()
};
