/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : CameraControl.h	                                              *
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

#ifndef __AFXWIN_H__
	#error Please include 'Stdafx.h' before including this file in PCH. 
#endif

#include "resource.h"

#include "CameraController.h"
#include "CameraModel.h"

// CCameraControlApp:
// CCameraControlApp dialog used for App About

class CCameraControlApp : public CWinApp
{
public:
	CCameraControlApp();

// Overrides
	public:
	virtual BOOL InitInstance();


	CameraModel*		_model;
	CameraController*	_controller;

	friend CameraController* getController();
	friend CameraModel* getModel();

// Implementation

	DECLARE_MESSAGE_MAP()
};

inline CameraController* getCameraController() {return static_cast<CCameraControlApp*>(AfxGetApp())->_controller;}
inline CameraModel* getCameraModel() {return static_cast<CCameraControlApp*>(AfxGetApp())->_model;}

extern CCameraControlApp theApp;
