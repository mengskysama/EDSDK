/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : Av.cpp                                                          *
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
#include "Av.h"

#define WM_USER_PROPERTY_CHANGED		WM_APP+1
#define WM_USER_PROPERTYDESC_CHANGED	WM_APP+2
// CAv

IMPLEMENT_DYNAMIC(CAv, CPropertyComboBox)
CAv::CAv()
{
	// set up action command
	setActionCommand("set_Av");

	// Map of value and display name
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00,"00"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x08,"1"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x0B,"1.1"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x0C,"1.2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x0D,"1.2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x10,"1.4"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x13,"1.6"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x14,"1.8"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x15,"1.8"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x18,"2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x1B,"2.2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x1C,"2.5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x1D,"2.5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x20,"2.8"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x23,"3.2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x24,"3.5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x25,"3.5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x28,"4"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x2B,"4.5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x2C,"4.5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x2D,"5.0"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x30,"5.6"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x33,"6.3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x34,"6.7"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x35,"7.1"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x38,"8"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x3B,"9"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x3C,"9.5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x3D,"10"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x40,"11"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x43,"13"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x44,"13"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x45,"14"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x48,"16"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x4B,"18"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x4C,"19"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x4D,"20"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x50,"22"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x53,"25"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x54,"27"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x55,"29"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x58,"32"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x5B,"36"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x5C,"38"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x5D,"40"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x60,"45"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x63,"51"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x64,"54"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x65,"57"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x68,"64"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x6B,"72"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x6C,"76"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x6D,"80"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x70,"91"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xffffffff,"unknown"));
}

CAv::~CAv()
{
}


BEGIN_MESSAGE_MAP(CAv, CPropertyComboBox)
	ON_MESSAGE(WM_USER_PROPERTY_CHANGED, OnPropertyChanged)
	ON_MESSAGE(WM_USER_PROPERTYDESC_CHANGED, OnPropertyDescChanged)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelChange)
END_MESSAGE_MAP()



// CAv message handler
void CAv::OnSelChange() 
{
	DWORD_PTR data = GetItemData(GetCurSel());
	
	fireEvent(&data);
}

void CAv::update(Observable* from, CameraEvent *e)
{

	std::string event = e->getEvent();

	//Update property
	if(event == "PropertyChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_Av)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTY_CHANGED, NULL, NULL);
		}
	}

	//Update of list that can set property
	if(event == "PropertyDescChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_Av)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTYDESC_CHANGED, NULL, NULL);
		}	
	}
}

LRESULT CAv::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	updateProperty(getCameraModel()->getAv());
	return 0;
}

LRESULT CAv::OnPropertyDescChanged(WPARAM wParam, LPARAM lParam)
{
	updatePropertyDesc(&getCameraModel()->getAvDesc());
	return 0;
}


