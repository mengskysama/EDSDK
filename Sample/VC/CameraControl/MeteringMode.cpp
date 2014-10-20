/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : MeteringMode.cpp                                                *
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
#include "MeteringMode.h"

#define WM_USER_PROPERTY_CHANGED		WM_APP+1
#define WM_USER_PROPERTYDESC_CHANGED	WM_APP+2
// CMeteringMode

IMPLEMENT_DYNAMIC(CMeteringMode, CPropertyComboBox)
CMeteringMode::CMeteringMode()
{
	// set up action command
	setActionCommand("set_MeteringMode");

	// Map of value and display name
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(1,"Spot"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(3,"Evaluative"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(4,"Partial"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(5,"Center-Weighted Average"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xffffffff,"unknown"));
}

CMeteringMode::~CMeteringMode()
{
}


BEGIN_MESSAGE_MAP(CMeteringMode, CPropertyComboBox)
	ON_MESSAGE(WM_USER_PROPERTY_CHANGED, OnPropertyChanged)
	ON_MESSAGE(WM_USER_PROPERTYDESC_CHANGED, OnPropertyDescChanged)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelChange)
END_MESSAGE_MAP()


// CMeteringMode message handler
void CMeteringMode::OnSelChange() 
{
	DWORD_PTR data = GetItemData(GetCurSel());
	
	fireEvent(&data);
}

void CMeteringMode::update(Observable* from, CameraEvent *e)
{

	std::string event = e->getEvent();

	//Update property
	if(event == "PropertyChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_MeteringMode)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTY_CHANGED, NULL, NULL);
		}
	}

	//Update of list that can set property
	if(event == "PropertyDescChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_MeteringMode)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTYDESC_CHANGED, NULL, NULL);
		}	
	}
}

LRESULT CMeteringMode::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	updateProperty(getCameraModel()->getMeteringMode());
	return 0;
}

LRESULT CMeteringMode::OnPropertyDescChanged(WPARAM wParam, LPARAM lParam)
{
	updatePropertyDesc(&getCameraModel()->getMeteringModeDesc());
	return 0;
}


