/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : ExposureComp.cpp                                                *
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
#include "ExposureComp.h"

#define WM_USER_PROPERTY_CHANGED		WM_APP+1
#define WM_USER_PROPERTYDESC_CHANGED	WM_APP+2
// CExposureComp

IMPLEMENT_DYNAMIC(CExposureComp, CPropertyComboBox)
CExposureComp::CExposureComp()
{
	// set up action command
	setActionCommand("set_ExposureCompensation");

	// Map of value and display name
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x18,"+3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x15,"+2 2/3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x14,"+2 1/2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x13,"+2 1/3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x10,"+2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x0d,"+1 2/3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x0c,"+1 1/2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x0b,"+1 1/3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x08,"+1"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x05,"+2/3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x04,"+1/2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x03,"+1/3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00,"0"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xfd,"-1/3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xfc,"-1/2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xfb,"-2/3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xf8,"-1"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xf5,"-1 1/3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xf4,"-1 1/2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xf3,"-1 2/3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xf0,"-2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xed,"-2 1/3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xec,"-2 1/2"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xeb,"-2 2/3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xe8,"-3"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0xffffffff,"unknown"));
}

CExposureComp::~CExposureComp()
{
}


BEGIN_MESSAGE_MAP(CExposureComp, CPropertyComboBox)
	ON_MESSAGE(WM_USER_PROPERTY_CHANGED, OnPropertyChanged)
	ON_MESSAGE(WM_USER_PROPERTYDESC_CHANGED, OnPropertyDescChanged)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelChange)
END_MESSAGE_MAP()



// CExposureComp message handler
void CExposureComp::OnSelChange() 
{
	DWORD_PTR data = GetItemData(GetCurSel());
	
	fireEvent(&data);
}

void CExposureComp::update(Observable* from, CameraEvent *e)
{

	std::string event = e->getEvent();

	//Update property
	if(event == "PropertyChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_ExposureCompensation)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTY_CHANGED, NULL, NULL);
		}
	}

	//Update of list that can set property
	if(event == "PropertyDescChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_ExposureCompensation)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTYDESC_CHANGED, NULL, NULL);
		}	
	}
}

LRESULT CExposureComp::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	updateProperty(getCameraModel()->getExposureCompensation());
	return 0;
}

LRESULT CExposureComp::OnPropertyDescChanged(WPARAM wParam, LPARAM lParam)
{
	updatePropertyDesc(&getCameraModel()->getExposureCompensationDesc());
	return 0;
}


