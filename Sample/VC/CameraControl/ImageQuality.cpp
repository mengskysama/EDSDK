/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : ImageQuality.cpp                                                *
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
#include "ImageQuality.h"

#define WM_USER_PROPERTY_CHANGED		WM_APP+1
#define WM_USER_PROPERTYDESC_CHANGED	WM_APP+2
// CImageQuality

IMPLEMENT_DYNAMIC(CImageQuality, CPropertyComboBox)
CImageQuality::CImageQuality()
{
	// set up action command
	setActionCommand("set_ImageQuality");

	// PTP Camera
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00640f0f, "RAW"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00640013, "RAW + Large Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00640113, "RAW + Middle Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00640213, "RAW + Small Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00640012, "RAW + Large Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00640112, "RAW + Middle Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00640212, "RAW + Small Normal Jpeg"));
	
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00640010, "RAW + Large Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00640510, "RAW + Middle1 Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00640610, "RAW + Middle2 Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00640210, "RAW + Small Jpeg"));

	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01640f0f, "Middle Raw(Small RAW1)"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01640013, "Middle Raw(Small RAW1) + Large Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01640113, "Middle Raw(Small RAW1) + Middle Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01640213, "Middle Raw(Small RAW1) + Small Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01640012, "Middle Raw(Small RAW1) + Large Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01640112, "Middle Raw(Small RAW1) + Middle Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01640212, "Middle Raw(Small RAW1) + Small Normal Jpeg"));

	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01640010, "Middle Raw + Large Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01640510, "Middle Raw + Middle1 Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01640610, "Middle Raw + Middle2 Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01640210, "Middle Raw + Small Jpeg"));

	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02640f0f, "Small RAW(Small RAW2)"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02640013, "Small RAW(Small RAW2) + Large Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02640113, "Small RAW(Small RAW2) + Middle Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02640213, "Small RAW(Small RAW2) + Small Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02640012, "Small RAW(Small RAW2) + Large Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02640112, "Small RAW(Small RAW2) + Middle Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02640212, "Small RAW(Small RAW2) + Small Normal Jpeg"));

	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02640010, "Small RAW + Large Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02640510, "Small RAW + Middle1 Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02640610, "Small RAW + Middle2 Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02640210, "Small RAW + Small Jpeg"));

	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00130f0f, "Large Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00120f0f, "Large Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01130f0f, "Middle Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01120f0f, "Middle Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02130f0f, "Small Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02120f0f, "Small Normal Jpeg"));

	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00100f0f, "Large Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x05100f0f, "Middle1 Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x06100f0f, "Middle2 Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02100f0f, "Small Jpeg"));

	// Legacy Camera
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00240000, "RAW"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00240013, "RAW + Large Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00240113, "RAW + Middle Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00240213, "RAW + Small Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00240012, "RAW + Large Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00240112, "RAW + Middle Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00240212, "RAW + Small Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00130000, "Large Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01130000, "Middle Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02130000, "Small Fine Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x00120000, "Large Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x01120000, "Middle Normal Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x02120000, "Small Normal Jpeg"));

	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x002f000f, "RAW"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x002f001f, "RAW + Large Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x002f051f, "RAW + Middle1 Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x002f061f, "RAW + Middle2 Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x002f021f, "RAW + Small Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x001f000f, "Large Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x051f000f, "Middle1 Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x061f000f, "Middle2 Jpeg"));
	_propertyTable.insert( std::pair<EdsUInt32, const char *>(0x021f000f, "Small Jpeg"));

}

CImageQuality::~CImageQuality()
{
}


BEGIN_MESSAGE_MAP(CImageQuality, CPropertyComboBox)
	ON_MESSAGE(WM_USER_PROPERTY_CHANGED, OnPropertyChanged)
	ON_MESSAGE(WM_USER_PROPERTYDESC_CHANGED, OnPropertyDescChanged)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelChange)
END_MESSAGE_MAP()


// CImageQuality message handler
void CImageQuality::OnSelChange() 
{
	DWORD_PTR data = GetItemData(GetCurSel());
	
	fireEvent(&data);
}

void CImageQuality::update(Observable* from, CameraEvent *e)
{

	std::string event = e->getEvent();

	//Update property
	if(event == "PropertyChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_ImageQuality)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTY_CHANGED, NULL, NULL);
		}
	}

	//Update of list that can set property
	if(event == "PropertyDescChanged")
	{
		EdsInt32 propertyID = *static_cast<EdsInt32 *>(e->getArg());
		
		if(propertyID == kEdsPropID_ImageQuality)
		{
			//The update processing can be executed from another thread. 
			::PostMessage(this->m_hWnd, WM_USER_PROPERTYDESC_CHANGED, NULL, NULL);
		}	
	}
}

LRESULT CImageQuality::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	updateProperty(getCameraModel()->getImageQuality());
	return 0;
}

LRESULT CImageQuality::OnPropertyDescChanged(WPARAM wParam, LPARAM lParam)
{
	updatePropertyDesc(&getCameraModel()->getImageQualityDesc());
	return 0;
}


