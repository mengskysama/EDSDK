/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : PropertyComboBox.h	                                          *
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

#include <map>
// CPropertyComboBox

class CPropertyComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CPropertyComboBox)

public:
	CPropertyComboBox();
	virtual ~CPropertyComboBox();

protected:
	void OnSelChange();

	DECLARE_MESSAGE_MAP()

	std::map<EdsUInt32, const char *> _propertyTable;

	void updateProperty(EdsUInt32 value);
	void updatePropertyDesc(const EdsPropertyDesc* desc);
};


