/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : RAWDevelop.h                                                    *
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
// RAWDevelop.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CRAWDevelopApp:
// See RAWDevelop.cpp for the implementation of this class
//

class CRAWDevelopApp : public CWinApp
{
public:
	CRAWDevelopApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRAWDevelopApp theApp;


#define WM_IMAGE_UPDATE WM_USER + 1

typedef struct
{
	const char *string;
	int			value;
}STR_ID_TABLE;


//////////////////////////////////////////////
// User Interface control
#define INIT_COMBO(ctrl,table)\
	InitComboBox( ctrl , table , sizeof(table)/sizeof(*table))

#define SET_COMBO( ctrl,value)\
		SetComboBox( ctrl , value )
#define GET_COMBO( ctrl,value)\
		GetComboBox( ctrl , value )

#define GET_SLIDER( slider , value , form , editid )\
		GetSlider(  slider , value , form , *GetDlgItem(editid) )
#define SET_SLIDER( slider , value , form , editid )\
		SetSlider(  slider , value , form , *GetDlgItem(editid) )

inline void InitComboBox( CComboBox &combo , const STR_ID_TABLE *table , int size )
{
	for(int i=0;i<size;i++)
	{
		int index = combo.InsertString( -1 , table[i].string );
		combo.SetItemData(index, table[i].value);
	}
}

inline bool GetComboBox( CComboBox &combo , long &value )
{
	int index = combo.GetCurSel();
	if( index == CB_ERR )
		return false;
	long item = (long)combo.GetItemData(index);
	bool bUpdate = (value != item);
	value = item;
	return bUpdate;
}
inline bool GetComboBox( CComboBox &combo , unsigned long &value )
{
	return GetComboBox( combo , (long &)value );
}
inline bool SetComboBox( CComboBox &combo , int value )
{
	for(int i=0;i<combo.GetCount();i++)
	{
		if( value == (long)combo.GetItemData(i) )
		{
			combo.SetCurSel(i);
			combo.EnableWindow(true);
			return true;
		}
	}
	combo.SetCurSel(0xffffffff);
	return false;
}

inline void InitSlider( CSliderCtrl &slider , int min , int max , int tic=1 , int value=0 )
{
	slider.SetRange(min,max,true);
	slider.SetTicFreq(tic);
	slider.SetPos(value);
}

inline void SetSlider( CSliderCtrl &slider , int value , const char *form , CWnd &edit )
{
	slider.SetPos(value);
	CString str;
	if( strcmp(form,"%.1f") == 0 )
		str.Format( form , (float)value/10 );
	else
		str.Format( form , value );
	edit.SetWindowText(str);
	slider.EnableWindow(true);
}

inline bool GetSlider( CSliderCtrl &slider , long &value , const char *form , CWnd &edit )
{
	bool bUpdate = (value != slider.GetPos());
	value = slider.GetPos();
	CString str;
	if( strcmp(form,"%.1f") == 0 )
		str.Format( form , (float)value/10 );
	else
		str.Format( form , value );
	edit.SetWindowText(str);
	return bUpdate;
}
inline bool GetSlider( CSliderCtrl &slider , unsigned long &value , const char *form , CWnd &edit )
{
	return GetSlider( slider , (long &)value , form , edit );
}

