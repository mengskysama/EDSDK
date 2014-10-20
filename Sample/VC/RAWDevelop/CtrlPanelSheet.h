/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : CtrlPanelSheet.h                                                *
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
#pragma once



// CCtrlPanelSheet
#include "ProcessPage.h"
#include "SavePage.h"

class CCtrlPanelSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CCtrlPanelSheet)
	CProcessPage m_ProcessPage;
	CSavePage m_SavePage;
public:
	CCtrlPanelSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCtrlPanelSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CCtrlPanelSheet();
	void SetImageRef( EdsImageRef ref )
	{
		m_ProcessPage.SetImageRef( ref );
		m_SavePage.SetImageRef( ref );
	}
	void Get( EdsTargetImageType &type )
	{
		m_SavePage.Get( type );
	}
	void Get( EdsSaveImageSetting &inSaveSetting )
	{
		m_SavePage.Get( inSaveSetting );
	}
	BOOL IsClickWB()const{return m_ProcessPage.IsClickWB();}
	void ClickWB(){ m_ProcessPage.ClickWB();}

protected:
	DECLARE_MESSAGE_MAP()
public:
};


