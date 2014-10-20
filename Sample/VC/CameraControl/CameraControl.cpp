/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : CameraControl.cpp                                               *
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
#include "CameraControlDlg.h"
#include "EDSDK.h"
#include "EDSDKTypes.h"
#include "CameraModel.h"
#include "CameraModelLegacy.h"
#include "CameraController.h"
#include "CameraEventListener.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CameraModel* cameraModelFactory(EdsCameraRef camera, EdsDeviceInfo deviceInfo);

// CCameraControlApp

BEGIN_MESSAGE_MAP(CCameraControlApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCameraControlApp construction

CCameraControlApp::CCameraControlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCameraControlApp object

CCameraControlApp theApp;



// CCameraControlApp initialization
BOOL CCameraControlApp::InitInstance()
{
	InitCommonControls();
	CWinApp::InitInstance();


	EdsError	 err = EDS_ERR_OK;
	EdsCameraListRef cameraList = NULL;
	EdsCameraRef camera = NULL;
	EdsUInt32	 count = 0;	
	bool		 isSDKLoaded = false;

	// Initialization of SDK
	err = EdsInitializeSDK();

	if(err == EDS_ERR_OK)
	{
		isSDKLoaded = true;
	}

	//Acquisition of camera list
	if(err == EDS_ERR_OK)
	{
		err = EdsGetCameraList(&cameraList);
	}

	//Acquisition of number of Cameras
	if(err == EDS_ERR_OK)
	{
		err = EdsGetChildCount(cameraList, &count);
		if(count == 0)
		{
			err = EDS_ERR_DEVICE_NOT_FOUND;
		}
	}


	//Acquisition of camera at the head of the list
	if(err == EDS_ERR_OK)
	{	
		err = EdsGetChildAtIndex(cameraList , 0 , &camera);	
	}

	//Acquisition of camera information
	EdsDeviceInfo deviceInfo;
	if(err == EDS_ERR_OK)
	{	
		err = EdsGetDeviceInfo(camera , &deviceInfo);	
		if(err == EDS_ERR_OK && camera == NULL)
		{
			err = EDS_ERR_DEVICE_NOT_FOUND;
		}
	}


	//Release camera list
	if(cameraList != NULL)
	{
		EdsRelease(cameraList);
	}

	//Create Camera model
	if(err == EDS_ERR_OK )
	{
		_model = cameraModelFactory(camera, deviceInfo);
		if(_model == NULL)
		{
			err = EDS_ERR_DEVICE_NOT_FOUND;
		}
	}

	if(err != EDS_ERR_OK)
	{
		::MessageBox(NULL,"Cannot detect camera",NULL,MB_OK);
	}

	if(err == EDS_ERR_OK )
	{
		//Create CameraController
		_controller = new CameraController();
		//Create View Dialog
		CCameraControlDlg			view;
		
		_controller->setCameraModel(_model);
		_model->addObserver(&view);
		// Send Model Event to view	
		view.setCameraController(_controller);

		//Set Property Event Handler
		if(err == EDS_ERR_OK)
		{
			err = EdsSetPropertyEventHandler( camera, kEdsPropertyEvent_All, CameraEventListener::handlePropertyEvent , (EdsVoid *)_controller);
		}

		//Set Object Event Handler
		if(err == EDS_ERR_OK)
		{
			err = EdsSetObjectEventHandler( camera, kEdsObjectEvent_All, CameraEventListener::handleObjectEvent , (EdsVoid *)_controller);
		}

		//Set State Event Handler
		if(err == EDS_ERR_OK)
		{
			err = EdsSetCameraStateEventHandler( camera, kEdsStateEvent_All, CameraEventListener::handleStateEvent , (EdsVoid *)_controller);
		}

		m_pMainWnd = &view;
		INT_PTR nResponse = view.DoModal();

	}

	//Release Camera
	if( camera != NULL )
	{
		EdsRelease(camera);
		camera = NULL;
	}

	//Termination of SDK
	if(isSDKLoaded)
	{
		EdsTerminateSDK();
	}
	
	if(_model != NULL)
	{
		delete _model;
		_model = NULL;
	}


	if(_controller != NULL)
	{
		delete _controller;
		_controller = NULL;
	}
	 
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


CameraModel* cameraModelFactory(EdsCameraRef camera, EdsDeviceInfo deviceInfo)
{
	// if Legacy protocol.
	if(deviceInfo.deviceSubType == 0)
	{
		return new CameraModelLegacy(camera);
	}

	// PTP protocol.
	return new CameraModel(camera);
}
