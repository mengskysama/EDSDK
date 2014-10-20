/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : AEMode.h    	                                                  *
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


#include "PropertyComboBox.h"
#include "Observer.h"
#include "ActionSource.h"
// CAEMode

class CAEMode : public CPropertyComboBox, public ActionSource , public Observer  
{
	DECLARE_DYNAMIC(CAEMode)

public:
	CAEMode();
	virtual ~CAEMode();

	//observer
	virtual void update(Observable* from, CameraEvent *e);

protected:
	void OnSelChange();
	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPropertyDescChanged(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};


