/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : AEMode.cpp                                                      *
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
#include "AEMode.h"

#include "CameraEvent.h"

#define WM_USER_PROPERTY_CHANGED		WM_APP+1
#define WM_USER_PROPERTYDESC_CHANGED	WM_APP+2

// CAEMode
IMPLEMENT_DYNAMIC(CAEMode, CPropertyComboBox)
CAEMode::CAEMode()
{
	// set up action command
	setActionCommand("set_AEMode");

	// Map of value and display name
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0,"P"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(1,"Tv"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(2,"Av"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(3,"M"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(4,"Bulb"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(5,"A-DEP"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(6,"DEP"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(7,"C"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(8,"Lock"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(9,"GreenMode"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(10,"Night Portrait"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(11,"Sports"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(13,"LandScape"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(14,"Close Up"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(15,"No Strobo"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(12,"Portrait"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(19,"Creative Auto"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xffffffff,"unknown"));

}

CAEMode::~CAEMode()
{
}


BEGIN_MESSAGE_MAP(CAEMode, CPropertyComboBox)
	ON_MESSAGE(WM_USER_PROPERTY_CHANGED, OnPropertyChanged)
	ON_MESSAGE(WM_USER_PROPERTYDESC_CHANGED, OnPropertyDescChanged)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelChange)
END_MESSAGE_MAP()

// CAEMode message handler
void CAEMode::OnSelChange() 
{
	DWORD_PTR data = GetItemData(GetCurSel());
	fireEvent(&data);
}

void CAEMode::update(Observable* from, CameraEvent *e)
{

	std::string event = e->getEvent();

	//Update property
	if(event == "PropertyChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_AEMode)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTY_CHANGED, NULL, NULL);
		}
	}

	//Update of list that can set property
	if(event == "PropertyDescChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_AEMode)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTYDESC_CHANGED, NULL, NULL);
		}	
	}
}

LRESULT CAEMode::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	updateProperty(getCameraModel()->getAEMode());
	return 0;
}

LRESULT CAEMode::OnPropertyDescChanged(WPARAM wParam, LPARAM lParam)
{
	updatePropertyDesc(&getCameraModel()->getAEModeDesc());
	return 0;
}





