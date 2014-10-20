/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : PropertyComboBox.cpp                                            *
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
#include "PropertyComboBox.h"


// CPropertyComboBox

IMPLEMENT_DYNAMIC(CPropertyComboBox, CComboBox)
CPropertyComboBox::CPropertyComboBox()
{
}

CPropertyComboBox::~CPropertyComboBox()
{
}


BEGIN_MESSAGE_MAP(CPropertyComboBox, CComboBox)
END_MESSAGE_MAP()


// CPropertyComboBox message handler
void CPropertyComboBox::updateProperty(EdsUInt32 value)
{
	// The character string corresponding to data is acquired. 
	std::map<EdsUInt32, const char*>::iterator itr = _propertyTable.find(value);
	if (itr != _propertyTable.end())
	{		
		// Set String combo box
		SetWindowText(itr->second);
	}
}


void CPropertyComboBox::updatePropertyDesc(const EdsPropertyDesc* desc)
{
	// The content of the list is deleted.
	// Current settings values are not changed in some cases even if the list changes, so leave the selected text as it is
	CString ss;
	GetWindowText(ss);
	ResetContent();
	SetWindowText(ss);
	
	// It makes it to disable when there is no value list that can be set. 
	EnableWindow( desc->numElements != 0 );


	for(int i = 0; i < desc->numElements; i++)
	{
		// The character string corresponding to data is acquired.
		std::map<EdsUInt32, const char *>::iterator itr = _propertyTable.find((EdsUInt32)desc->propDesc[i]);

		// Create list of combo box
		if (itr != _propertyTable.end())
		{
			// Insert string
			int index = InsertString(-1, itr->second);
			// Set data
			SetItemData(index, itr->first);
		}
	}	
}
