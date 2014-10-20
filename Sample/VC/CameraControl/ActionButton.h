/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : ActionButton.h      	                                          *
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

#include "ActionSource.h"
// CActionButton

class CActionButton : public CButton , public ActionSource
{

public:
	CActionButton();

public:
	virtual ~CActionButton();

protected:
	void OnClicked();
	DECLARE_MESSAGE_MAP()
};

