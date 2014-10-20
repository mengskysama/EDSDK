/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : Tv.cpp                                                          *
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
#include "Tv.h"

#define WM_USER_PROPERTY_CHANGED		WM_APP+1
#define WM_USER_PROPERTYDESC_CHANGED	WM_APP+2
// CTv

IMPLEMENT_DYNAMIC(CTv, CPropertyComboBox)
CTv::CTv()
{
	setActionCommand("set_Tv");

	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x0c,"Bulb"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x10,"30Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x13,"25Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x14,"20Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x15,"20Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x18,"15Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x1B,"13Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x1C,"10Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x1D,"10Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x20,"8Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x23,"6Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x24,"6Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x25,"5Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x28,"4Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x2B,"3Åh2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x2C,"3Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x2D,"2Åh5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x30,"2Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x33,"1Åh6"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x34,"1Åh5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x35,"1Åh3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x38,"1Åh"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x3B,"0Åh8"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x3C,"0Åh7"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x3D,"0Åh6"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x40,"0Åh5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x43,"0Åh4"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x44,"0Åh3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x45,"0Åh3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x48,"4"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x4B,"5"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x4C,"6"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x4D,"6"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x50,"8"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x53,"10"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x54,"10"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x55,"13"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x58,"15"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x5B,"20"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x5C,"20"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x5D,"25"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x60,"30"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x63,"40"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x64,"45"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x65,"50"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x68,"60"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x6B,"80"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x6C,"90"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x6D,"100"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x70,"125"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x73,"160"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x74,"180"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x75,"200"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x78,"250"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x7B,"320"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x7C,"350"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x7D,"400"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x80,"500"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x83,"640"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x84,"750"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x85,"800"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x88,"1000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x8B,"1250"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x8C,"1500"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x8D,"1600"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x90,"2000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x93,"2500"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x94,"3000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x95,"3200"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x98,"4000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x9B,"5000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x9C,"6000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x9D,"6400"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xA0,"8000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xffffffff,"unknown"));
}

CTv::~CTv()
{
}


BEGIN_MESSAGE_MAP(CTv, CPropertyComboBox)
	ON_MESSAGE(WM_USER_PROPERTY_CHANGED, OnPropertyChanged)
	ON_MESSAGE(WM_USER_PROPERTYDESC_CHANGED, OnPropertyDescChanged)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelChange)
END_MESSAGE_MAP()


// CTv message handler
void CTv::OnSelChange() 
{
	DWORD_PTR data = GetItemData(GetCurSel());
	
	fireEvent(&data);
}

void CTv::update(Observable* from, CameraEvent *e)
{

	std::string event = e->getEvent();

	//Update property
	if(event == "PropertyChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_Tv)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTY_CHANGED, NULL, NULL);
		}
	}

	//Update of list that can set property
	if(event == "PropertyDescChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_Tv)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTYDESC_CHANGED, NULL, NULL);
		}	
	}
}

LRESULT CTv::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	updateProperty(getCameraModel()->getTv());
	return 0;
}

LRESULT CTv::OnPropertyDescChanged(WPARAM wParam, LPARAM lParam)
{
	updatePropertyDesc(&getCameraModel()->getTvDesc());
	return 0;
}


