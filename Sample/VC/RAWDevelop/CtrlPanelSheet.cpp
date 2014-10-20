/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : CtrlPanelSheet.cpp                                              *
*                                                                             *
*   Description: This is the Sample code to show the usage of EDSDK.          *
*                                                                             *
*                                                                             *
*******************************************************************************
*                                                                             *
*   Written and developed by Camera Design Dept.53                            *
*   Copyright Canon Inc. 2006 All Rights Reserved                             *
*                                                                             *
*******************************************************************************
*   File Update Information:                                                  *
*     DATE      Identify    Comment                                           *
*   -----------------------------------------------------------------------   *
*   06-03-22    F-001        create first version.                            *
*                                                                             *
******************************************************************************/
#include "stdafx.h"
#include "RAWDevelop.h"
#include "CtrlPanelSheet.h"
#include ".\ctrlpanelsheet.h"


// CCtrlPanelSheet

IMPLEMENT_DYNAMIC(CCtrlPanelSheet, CPropertySheet)
CCtrlPanelSheet::CCtrlPanelSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CCtrlPanelSheet::CCtrlPanelSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_ProcessPage);
	AddPage(&m_SavePage);
}

CCtrlPanelSheet::~CCtrlPanelSheet()
{
}


BEGIN_MESSAGE_MAP(CCtrlPanelSheet, CPropertySheet)
END_MESSAGE_MAP()


// CCtrlPanelSheet 

