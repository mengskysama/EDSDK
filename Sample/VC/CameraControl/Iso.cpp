/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : Iso.cpp                                                         *
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
#include "Iso.h"

#define WM_USER_PROPERTY_CHANGED		WM_APP+1
#define WM_USER_PROPERTYDESC_CHANGED	WM_APP+2
// CIso

IMPLEMENT_DYNAMIC(CIso, CPropertyComboBox)
CIso::CIso()
{
	// set up action command
	setActionCommand("set_ISOSpeed");

	// Map of value and display name
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00,"Auto"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x28,"6"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x30,"12"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x38,"25"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x40,"50"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x48,"100"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x4b,"125"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x4d,"160"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x50,"200"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x53,"250"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x55,"320"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x58,"400"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x5b,"500"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x5d,"640"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x60,"800"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x63,"1000"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x65,"1250"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x68,"1600"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x70,"3200"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x78,"6400"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x80,"12800"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x88,"25600"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x90,"51200"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x98,"102400"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xffffffff,"unknown"));
}

CIso::~CIso()
{
}


BEGIN_MESSAGE_MAP(CIso, CPropertyComboBox)
	ON_MESSAGE(WM_USER_PROPERTY_CHANGED, OnPropertyChanged)
	ON_MESSAGE(WM_USER_PROPERTYDESC_CHANGED, OnPropertyDescChanged)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelChange)
END_MESSAGE_MAP()



// CIso message handler
void CIso::OnSelChange() 
{
	DWORD_PTR data = GetItemData(GetCurSel());
	
	fireEvent(&data);
}

void CIso::update(Observable* from, CameraEvent *e)
{

	std::string event = e->getEvent();

	//Update property
	if(event == "PropertyChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_ISOSpeed)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTY_CHANGED, NULL, NULL);
		}
	}

	//Update of list that can set property
	if(event == "PropertyDescChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_ISOSpeed)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTYDESC_CHANGED, NULL, NULL);
		}	
	}
}

LRESULT CIso::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	updateProperty(getCameraModel()->getIso());
	return 0;
}

LRESULT CIso::OnPropertyDescChanged(WPARAM wParam, LPARAM lParam)
{
	updatePropertyDesc(&getCameraModel()->getIsoDesc());
	return 0;
}


