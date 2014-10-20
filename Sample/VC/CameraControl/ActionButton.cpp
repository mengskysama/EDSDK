/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : ActionButton.cpp                                                *
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
#include "ActionButton.h"


/////////////////////////////////////////////////////////////////////////////
// ActionButton

CActionButton::CActionButton()
{
}

CActionButton::~CActionButton()
{
}


BEGIN_MESSAGE_MAP(CActionButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
END_MESSAGE_MAP()

//ActionButton  message handler
void CActionButton::OnClicked() 
{
	fireEvent();
}
