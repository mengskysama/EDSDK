'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : EdsTypes.h                                                      *
'*                                                                             *
'*   Description: COMMON DEFINITION FOR EDSDK                                  *
'*                                                                             *
'*                                                                             *
'*******************************************************************************
'*                                                                             *
'*   Written and developed by Camera Design Dept.53                            *
'*   Copyright Canon Inc. 2006 All Rights Reserved                             *
'*                                                                             *
'*******************************************************************************
'*   File Update Information:                                                  *
'*     DATE      Identify    Comment                                           *
'*   -----------------------------------------------------------------------   *
'*   06-03-08    F-001       create first version.                             *
'*                                                                             *
'******************************************************************************/
'Option Strict Off
Option Explicit On 

Imports System.Runtime.InteropServices

Public Module EDSDKTypes

    '/******************************************************************************
    ' Definition of Data Types
    '******************************************************************************/

    '/*-----------------------------------------------------------------------------
    ' Data Type
    '-----------------------------------------------------------------------------*/
    Public Enum EdsDataType
        kEdsDataType_Unknown = 0
        kEdsDataType_Bool = 1
        kEdsDataType_String = 2
        kEdsDataType_Int8 = 3
        kEdsDataType_UInt8 = 6
        kEdsDataType_Int16 = 4
        kEdsDataType_UInt16 = 7
        kEdsDataType_Int32 = 8
        kEdsDataType_UInt32 = 9
        kEdsDataType_Int64 = 10
        kEdsDataType_UInt64 = 11
        kEdsDataType_Float = 12
        kEdsDataType_Double = 13
        kEdsDataType_ByteBlock = 14
        kEdsDataType_Rational = 20
        kEdsDataType_Point = 21
        kEdsDataType_Rect = 22
        kEdsDataType_Time

        kEdsDataType_Bool_Array = 30
        kEdsDataType_Int8_Array = 31
        kEdsDataType_Int16_Array = 32
        kEdsDataType_Int32_Array = 33
        kEdsDataType_UInt8_Array = 34
        kEdsDataType_UInt16_Array = 35
        kEdsDataType_UInt32_Array = 36
        kEdsDataType_Rational_Array = 37

        kEdsDataType_FocusInfo = 101
        kEdsDataType_PictureStyleDesc
    End Enum

#Region "Property IDs"
    '/*-----------------------------------------------------------------------------
    '    Property IDs()
    '-----------------------------------------------------------------------------*/

    '////////////////////////////////////////////
    '// Camera Setting Properties
    '////////////////////////////////////////////   
    Public Const kEdsPropID_Unknown As Integer = &HFFFF        '// 

    Public Const kEdsPropID_ProductName As Integer = &H2       '// Product name
    Public Const kEdsPropID_BodyID As Integer = &H3            '// Body ID
    Public Const kEdsPropID_OwnerName As Integer = &H4         '// Owner
    Public Const kEdsPropID_MakerName As Integer = &H5         '// Manufacturer
    Public Const kEdsPropID_DateTime As Integer = &H6          '// For cameras, the system time; for images, the shooting time
    Public Const kEdsPropID_FirmwareVersion As Integer = &H7   '// Firmware Version 
    Public Const kEdsPropID_BatteryLevel As Integer = &H8      '// Battery state: 0-100% or "AC"

    '// CFn=&h00000002 PFn
    Public Const kEdsPropID_CFn As Integer = &H9               '// Custom Function settings
    Public Const kEdsPropID_PFn As Integer = &HA               '// Personal Function settings

    Public Const kEdsPropID_SaveTo As Integer = &HB            '// Destination where image was saved                         

    Public Const kEdsPropID_UserWhiteBalanceData As Integer = &H201 '// Set user-defined data in Set1, 2, or 3, or read it out 
    Public Const kEdsPropID_UserToneCurveData As Integer = &H202    '// // Set user-defined data in Set1, 2, or 3, or read it out 
    Public Const kEdsPropID_UserPictureStyleData As Integer = &H203 '// User picture style data

    Public Const kEdsPropID_UserManualWhiteBalanceData As Integer = &H204

    Public Const kEdsPropID_BatteryQuality As Integer = &H10
    Public Const kEdsPropID_BatteryShutterCount As Integer = &H11
    Public Const kEdsPropID_BatteryCalibration As Integer = &H12
    Public Const kEdsPropID_BatteryName As Integer = &H13

    Public Const kEdsPropID_HDDirectoryStructure As Integer = &H20
    Public Const kEdsPropID_WFTStatus As Integer = &H21

    Public Const kEdsPropID_QuickReviewTime As Integer = &HF
    Public Const kEdsPropID_ShutterCounter As Integer = &H22
    Public Const kEdsPropID_PhotoStudioMode As Integer = &H30
    Public Const kEdsPropID_SpecialOption As Integer = &H31


    Public Const kEdsPropID_DataInputTransmission As Integer = &H50
    Public Const kEdsPropID_Wft_ProfileLockConfig As Integer = &H52
    Public Const kEdsPropID_Wft_TransmissionConfig As Integer = &H53
    Public Const kEdsPropID_Wft_TCPIPConfig As Integer = &H54
    Public Const kEdsPropID_Wft_FTPConfig As Integer = &H55
    Public Const kEdsPropID_Wft_WirelessConfig As Integer = &H56
    Public Const kEdsPropID_Wft_WiredConfig As Integer = &H57
    Public Const kEdsPropID_Wft_SettingsName As Integer = &H58
    Public Const kEdsPropID_Wft_Info As Integer = &H59


    '////////////////////////////////////////////
    '// Image Properties
    '////////////////////////////////////////////

    Public Const kEdsPropID_ImageQuality As Integer = &H100    '// Image quality
    Public Const kEdsPropID_JpegQuality As Integer = &H101     '// Value representing compression when saved as a JPEG; 1 to 10 (cap)
    Public Const kEdsPropID_Orientation As Integer = &H102     '// The image orientation
    Public Const kEdsPropID_ICCProfile As Integer = &H103      '// ICC Profile data
    Public Const kEdsPropID_FocusInfo As Integer = &H104       '// focus Info

    Public Const kEdsPropID_DigitalExposure As Integer = &H105   '// Digital exposure compensation
    Public Const kEdsPropID_WhiteBalance As Integer = &H106      '// White balance (light source)
    Public Const kEdsPropID_ColorTemperature As Integer = &H107  '// Color temperature setting value
    Public Const kEdsPropID_WhiteBalanceShift As Integer = &H108 '// White balance shift compensation

    Public Const kEdsPropID_Contrast As Integer = &H109         '// Contrast setting
    Public Const kEdsPropID_ColorSaturation As Integer = &H10A  '// Saturation setting
    Public Const kEdsPropID_ColorTone As Integer = &H10B        '// Color tone setting
    Public Const kEdsPropID_Sharpness As Integer = &H10C        '// Sharpness setting value
    Public Const kEdsPropID_ColorSpace As Integer = &H10D       '// Color space setting
    Public Const kEdsPropID_ToneCurve As Integer = &H10E        '// Tone curve (standard or custom)

    Public Const kEdsPropID_PhotoEffect As Integer = &H10F      '// Color effect setting
    Public Const kEdsPropID_FilterEffect As Integer = &H110     '// Filter effect setting
    Public Const kEdsPropID_ToningEffect As Integer = &H111     '// Gradation effect setting

    Public Const kEdsPropID_ParameterSet As Integer = &H112     '// Processing parameter setting
    Public Const kEdsPropID_ColorMatrix As Integer = &H113      '// Color matrix setting

    Public Const kEdsPropID_PictureStyle As Integer = &H114     '// Picture style
    Public Const kEdsPropID_PictureStyleDesc As Integer = &H115 '// Picture style setting details

    Public Const kEdsPropID_PictureStyleCaption As Integer = &H200 '// Computer settings caption for the picture style at the time of shooting
    Public Const kEdsPropID_CustomWBCaption As Integer = &H204

    '////////////////////////////////////////////
    '// Develop Properties
    '////////////////////////////////////////////
    Public Const kEdsPropID_Linear As Integer = &H300       '// Linear processing ON/OFF
    Public Const kEdsPropID_ClickWBPoint As Integer = &H301 '// Click WB coordinates
    Public Const kEdsPropID_WBCoeffs As Integer = &H302     '// WB control value

    '////////////////////////////////////////////
    '// Property Masks
    '////////////////////////////////////////////
    Public Const kEdsPropID_AtCapture_Flag As Integer = &H80000000
    '// A supporting property for getting the properties at the time of shooting. 
    '// This property ID cannot be used by itself. 

    '////////////////////////////////////////////
    '// Capture Properties
    '////////////////////////////////////////////
    Public Const kEdsPropID_AEMode As Integer = &H400           '// Shooting mode
    Public Const kEdsPropID_DriveMode As Integer = &H401        '// Drive mode (cap)
    Public Const kEdsPropID_ISOSpeed As Integer = &H402         '// ISO sensitivity setting value
    Public Const kEdsPropID_MeteringMode As Integer = &H403     '// Metering mode
    Public Const kEdsPropID_AFMode As Integer = &H404           '// AF mode (cap)
    Public Const kEdsPropID_Av As Integer = &H405               '// Aperture value (cap) at the time of shooting
    Public Const kEdsPropID_Tv As Integer = &H406               '// Shutter speed setting value (cap)
    Public Const kEdsPropID_ExposureCompensation As Integer = &H407  '// Exposure compensation (cap)
    Public Const kEdsPropID_FlashCompensation As Integer = &H408  '// Flash compensation setting
    Public Const kEdsPropID_FocalLength As Integer = &H409      '// Lens focal length information at the time of shooting

    Public Const kEdsPropID_AvailableShots As Integer = &H40A   '// Number of available shots

    Public Const kEdsPropID_Bracket As Integer = &H40B          '// ISO, auto exposure or flash exposure bracket
    Public Const kEdsPropID_WhiteBalanceBracket As Integer = &H40C  '// White balance bracket

    Public Const kEdsPropID_LensName As Integer = &H40D         '// String representing the lens name
    Public Const kEdsPropID_AEBracket As Integer = &H40E        '// Auto exposure bracket value
    Public Const kEdsPropID_FEBracket As Integer = &H40F        '// Flash exposure bracket value
    Public Const kEdsPropID_ISOBracket As Integer = &H410       '// ISO bracket value

    Public Const kEdsPropID_NoiseReduction As Integer = &H411   '// Noise reduction

    Public Const kEdsPropID_FlashOn As Integer = &H412          '// Use of the flash (activated or not)
    Public Const kEdsPropID_RedEye As Integer = &H413           '// Red-eye reduction
    Public Const kEdsPropID_FlashMode As Integer = &H414        '// Flash type

    Public Const kEdsPropID_TempStatus As Integer = &H415
    Public Const kEdsPropID_LensStatus As Integer = &H416


    '////////////////////////////////////////////
    '// EVF Properties
    '////////////////////////////////////////////
    Public Const kEdsPropID_Evf_OutputDevice As Integer = &H500
    Public Const kEdsPropID_Evf_Mode As Integer = &H501
    Public Const kEdsPropID_Evf_WhiteBalance As Integer = &H502
    Public Const kEdsPropID_Evf_ColorTemperature As Integer = &H503
    Public Const kEdsPropID_Evf_DepthOfFieldPreview As Integer = &H504
    Public Const kEdsPropID_Evf_Sharpness As Integer = &H505
    Public Const kEdsPropID_Evf_ClickWBCoeffs As Integer = &H506

    '// EVF IMAGE DATA Properties
    Public Const kEdsPropID_Evf_Zoom As Integer = &H507
    Public Const kEdsPropID_Evf_ZoomPosition As Integer = &H508
    Public Const kEdsPropID_Evf_FocusAid As Integer = &H509
    Public Const kEdsPropID_Evf_Histogram As Integer = &H50A
    Public Const kEdsPropID_Evf_ImagePosition As Integer = &H50B
    Public Const kEdsPropID_Evf_HistogramStatus As Integer = &H50C

#End Region

    '/*-----------------------------------------------------------------------------
    ' Send Commands
    '-----------------------------------------------------------------------------*/
    Public Enum EdsCameraCommand
        kEdsCameraCommand_TakePicture           'The camera is requested to take a picture.
        kEdsCameraCommand_ExtendShutDownTimer   ' KeepDeviceOn  
        kEdsCameraCommand_BulbStart
        kEdsCameraCommand_BulbEnd
        kEdsCameraCommand_DoAfEvf = &H102
        kEdsCameraCommand_DriveLensEvf = &H103
        kEdsCameraCommand_DoClickWBEvf = &H104
        kEdsCameraCommand_ReflectWftProfile = &H201
        kEdsCameraCommand_PassThrough = &H1000  ' Sends specific commands to a camera.
    End Enum

    '/*-----------------------------------------------------------------------------
    ' Camera State
    '-----------------------------------------------------------------------------*/
    Public Enum EdsCameraStatusCommand
        kEdsCameraStatusCommand_UILock              '// 
        kEdsCameraStatusCommand_UIUnLock            '// 
        kEdsCameraStatusCommand_EnterDirectTransfer '// The camera is changed to direct transmission mode.
        kEdsCameraStatusCommand_ExitDirectTransfer  '// The camera is exited from direct transmission mode.
    End Enum


#Region "CAMERE EVENTS"
    '/*-----------------------------------------------------------------------------
    ' Camera Events
    '-----------------------------------------------------------------------------*/

    '////////////////////////////////////////////
    '// Property Event
    '////////////////////////////////////////////
    Public Const kEdsPropertyEvent_All As Integer = &H100

    Public Const kEdsPropertyEvent_PropertyChanged As Integer = &H101
    ' The value of the property specified 
    '// by the parameter has changed. 
    '// If it is necessary, it should be
    '// re-acquired.
    '// When property is not specified,
    '// it is necessary to acquire all parameters. 

    Public Const kEdsPropertyEvent_PropertyDescChanged As Integer = &H102
    '// The value of the property specified 
    '// by the parameter has changed. 
    '// If it is necessary, it should be
    '// re-acquired.
    '// When property is not specified,
    '// it is necessary to acquire all parameters.  


    '////////////////////////////////////////////
    '// Object Event
    '////////////////////////////////////////////
    Public Const kEdsObjectEvent_All As Integer = &H200                 '// Indicates that the VolumeInfo dataset

    Public Const kEdsObjectEvent_VolumeInfoChanged As Integer = &H201
    '// Indicates that the VolumeInfo dataset
    '// for a particular object has changed, 
    '// and that it should be re-requested.

    Public Const kEdsObjectEvent_VolumeUpdateItems As Integer = &H202
    '//
    Public Const kEdsObjectEvent_FolderUpdateItems As Integer = &H203


    Public Const kEdsObjectEvent_DirItemCreated As Integer = &H204
    '// The file or the folder was created. 


    Public Const kEdsObjectEvent_DirItemRemoved As Integer = &H205
    '// The file or the folder was removed. 


    Public Const kEdsObjectEvent_DirItemInfoChanged As Integer = &H206
    '// Indicates that the DirectoryItemInfo dataset
    '// for a particular object has changed, 
    '// and that it should be re-requested.

    Public Const kEdsObjectEvent_DirItemContentChanged As Integer = &H207
    '// DS_Event_ObjectContentChanged


    Public Const kEdsObjectEvent_DirItemRequestTransfer As Integer = &H208
    '// Indicates that there is an object that
    '// should be transferred.
    '// Please download the object specified 
    '// by the parameter when you receive 
    '// this event. 


    Public Const kEdsObjectEvent_DirItemRequestTransferDT As Integer = &H209
    '// Indicates that the direct forwarding 
    '// button of the camera was pushed.
    '// Please download the object specified 
    '// by the parameter when you receive 
    '// this event. 

    Public Const kEdsObjectEvent_DirItemCancelTransferDT As Integer = &H20A
    '// Indicates that the cancellation button
    '// of the camera was pushed while transfering
    '// Please discontinue transfering the object
    '// specified by the parameter. 
    '//         
    Public Const kEdsObjectEvent_VolumeAdded As Integer = &H20C
    Public Const kEdsObjectEvent_VolumeRemoved As Integer = &H20D

    '////////////////////////////////////////////
    '// State Event
    '////////////////////////////////////////////
    Public Const kEdsStateEvent_All As Integer = &H300

    Public Const kEdsStateEvent_Shutdown As Integer = &H301  '// The camera shut down.  


    Public Const kEdsStateEvent_JobStatusChanged As Integer = &H302
    '// the state of the presence of the object
    '// that should be transferred has changed.


    Public Const kEdsStateEvent_WillSoonShutDown As Integer = &H303
    '// After the time passage of the time-out, 
    '// the connection with the camera is cut. 
    '// It depends on the setting of the camera 
    '// about the time-out time. 



    Public Const kEdsStateEvent_ShutDownTimerUpdate As Integer = &H304
    '// After the WillSoonShutDown event, 
    '// the shutdown timer has updated.                                  


    Public Const kEdsStateEvent_CaptureError As Integer = &H305
    '// It failed in capture because 
    '// hardware error occurred by the camera.


    Public Const kEdsStateEvent_InternalError As Integer = &H306               '// The error occurred in SDK. 


    Public Const kEdsStateEvent_AfResult As Integer = &H309


    Public Const kEdsStateEvent_BulbExposureTime As Integer = &H310

#End Region



    '/*-----------------------------------------------------------------------------
    '  Drive Lens
    '-----------------------------------------------------------------------------*/
    Public Enum EdsEvfDriveLens
        kEdsEvfDriveLens_Near1 = 1
        kEdsEvfDriveLens_Near2 = 2
        kEdsEvfDriveLens_Near3 = 3
        kEdsEvfDriveLens_Far1 = &H8001
        kEdsEvfDriveLens_Far2 = &H8002
        kEdsEvfDriveLens_Far3 = &H8003
    End Enum

    '/*-----------------------------------------------------------------------------
    '  Drive Lens
    '-----------------------------------------------------------------------------*/
    Public Enum EdsEvfDepthOfFieldPreview
        kEdsEvfDepthOfFieldPreview_OFF = 0
        kEdsEvfDepthOfFieldPreview_ON = 1
    End Enum


    '/*-----------------------------------------------------------------------------
    ' Stream Seek Origins
    '-----------------------------------------------------------------------------*/
    Public Enum EdsSeekOrigin
        kEdsSeek_Cur = 0 '// Seek from Current Point
        kEdsSeek_Begin  '// Seek from Start Point
        kEdsSeek_End  '// Seek from End Point
    End Enum


    '/*-----------------------------------------------------------------------------
    ' File and Propaties Access
    '-----------------------------------------------------------------------------*/
    Public Enum EdsAccess
        kEdsAccess_Read = 0  '   // Enables subsequent open operations on the object to
        '// request read access. 
        kEdsAccess_Write  ',     // Enables subsequent open operations on the object to
        ' // request write access.
        kEdsAccess_ReadWrite ',  // Enables subsequent open operations on the object to 
        '// request read and write access.
        kEdsAccess_Error = &HFFFFFFFF
    End Enum


    '/*-----------------------------------------------------------------------------
    ' File Create Disposition
    '-----------------------------------------------------------------------------*/
    Public Enum EdsFileCreateDisposition
        kEdsFileCreateDisposition_CreateNew = 0
        '// Creates a new file. The function fails  
        '// if the specified file already exists.
        kEdsFileCreateDisposition_CreateAlways
        '// Creates a new file. If the file exists, 
        '// the function overwrites the file and clears
        '// the existing attributes.
        kEdsFileCreateDisposition_OpenExisting
        '// Opens the file. The function fails 
        '// if the file does not exist. 
        kEdsFileCreateDisposition_OpenAlways
        '// Opens the file, if it exists. 
        '// If the file does not exist, 
        '// the function creates the file.
        kEdsFileCreateDisposition_TruncateExsisting
        '// Opens the file. Once opened, the file is 
        '// truncated so that its size is zero bytes.
        '// The function fails if the file does not exist.
    End Enum



    '/*-----------------------------------------------------------------------------
    ' Image Type 
    '-----------------------------------------------------------------------------*/
    Public Enum EdsImageType
        kEdsImageType_Unknown = &H0
        kEdsImageType_Jpeg = &H1
        kEdsImageType_CRW = &H2
        kEdsImageType_RAW = &H4
        kEdsImageType_CR2 = &H6
    End Enum


    Public Enum EdsTargetImageType
        kEdsTargetImageType_Unknown = &H0
        kEdsTargetImageType_Jpeg = &H1
        kEdsTargetImageType_TIFF = &H7          '//  8bitTIFF
        kEdsTargetImageType_TIFF16 = &H8        '//  16bitTIFF  
        kEdsTargetImageType_RGB = &H9           '//  8bitRGB
        kEdsTargetImageType_RGB16 = &HA         '//  16bitRGB
    End Enum


    Public Enum EdsImageSize
        kEdsImageSize_Large = 0
        kEdsImageSize_Middle = 1
        kEdsImageSize_Small = 2
        kEdsImageSize_Middle1 = 5
        kEdsImageSize_Middle2 = 6
        kEdsImageSize_Unknown = &HFFFFFFFF
    End Enum


    Public Enum EdsImageQuality
        kEdsImageQuality_Normal = 2
        kEdsImageQuality_Fine = 3
        kEdsImageQuality_Lossless = 4
        kEdsImageQuality_SuperFine = 5
        kEdsImageQuality_Unknown = &HFFFFFFFF
    End Enum


    Public Enum EdsImageSource
        kEdsImageSrc_FullView
        kEdsImageSrc_Thumbnail
        kEdsImageSrc_Preview
        kEdsImageSrc_RAWThumbnail
        kEdsImageSrc_RAWFullView
    End Enum

    '/*-----------------------------------------------------------------------------
    ' Progress Option
    '-----------------------------------------------------------------------------*/
    Public Enum EdsProgressOption
        kEdsProgressOption_NoReport = 0   '// no callback.
        kEdsProgressOption_Done           '// performs callback only at once 
        '// at the time of an end.
        kEdsProgressOption_Periodically   '// performs callback periodically.
    End Enum


    '/*-----------------------------------------------------------------------------
    ' file attribute 
    '-----------------------------------------------------------------------------*/
    Public Enum EdsFileAttributes
        kEdsFileAttribute_Normal = &H0
        kEdsFileAttribute_ReadOnly = &H1
        kEdsFileAttribute_Hidden = &H2
        kEdsFileAttribute_System = &H4
        kEdsFileAttribute_Archive = &H20
    End Enum



    '/*-----------------------------------------------------------------------------
    ' Battery level
    '-----------------------------------------------------------------------------*/
    Public Enum EdsBatteryLevel
        kEdsBatteryLevel_Empty = 1
        kEdsBatteryLevel_Low = 30
        kEdsBatteryLevel_Half = 50
        kEdsBatteryLevel_Normal = 80
        kEdsBatteryLevel_AC = &HFFFFFFFF
    End Enum


    '/*-----------------------------------------------------------------------------
    ' Save To
    '-----------------------------------------------------------------------------*/
    Public Enum EdsSaveTo
        kEdsSaveTo_Camera = 1
        kEdsSaveTo_Host = 2
        kEdsSaveTo_Both = kEdsSaveTo_Camera + kEdsSaveTo_Host
    End Enum


    '/*-----------------------------------------------------------------------------
    ' StorageType
    '-----------------------------------------------------------------------------*/
    Public Enum EdsStorageType
        kEdsStorageType_Non = 0
        kEdsStorageType_CF = 1
        kEdsStorageType_SD = 2
    End Enum




    '/*-----------------------------------------------------------------------------
    ' White Balance
    '-----------------------------------------------------------------------------*/
    Public Enum EdsWhiteBalance
        kEdsWhiteBalance_Auto = 0
        kEdsWhiteBalance_Daylight = 1
        kEdsWhiteBalance_Cloudy = 2
        kEdsWhiteBalance_Tangsten = 3
        kEdsWhiteBalance_Fluorescent = 4
        kEdsWhiteBalance_Strobe = 5
        kEdsWhiteBalance_WhitePaper = 6
        kEdsWhiteBalance_Shade = 8
        kEdsWhiteBalance_ColorTemp = 9
        kEdsWhiteBalance_PCSet1 = 10
        kEdsWhiteBalance_PCSet2 = 11
        kEdsWhiteBalance_PCSet3 = 12

        kEdsWhiteBalance_Click = -1
        kEdsWhiteBalance_Pasted = -2
    End Enum

    '/*-----------------------------------------------------------------------------
    ' Photo Effect
    '-----------------------------------------------------------------------------*/
    Public Enum EdsPhotoEffect
        kEdsPhotoEffect_Off = 0
        kEdsPhotoEffect_Monochrome = 5
    End Enum


    '/*-----------------------------------------------------------------------------
    ' Color Matrix  
    '-----------------------------------------------------------------------------*/
    Public Enum EdsColorMatrix
        kEdsColorMatrix_Custom = 0
        kEdsColorMatrix_1 = 1
        kEdsColorMatrix_2 = 2
        kEdsColorMatrix_3 = 3
        kEdsColorMatrix_4 = 4
        kEdsColorMatrix_5 = 5
        kEdsColorMatrix_6 = 6
        kEdsColorMatrix_7 = 7
    End Enum


    '/*-----------------------------------------------------------------------------
    ' Filter Effect
    '-----------------------------------------------------------------------------*/
    Public Enum EdsFilterEffect
        kEdsFilterEffect_None = 0
        kEdsFilterEffect_Yellow = 1
        kEdsFilterEffect_Orange = 2
        kEdsFilterEffect_Red = 3
        kEdsFilterEffect_Green = 4
    End Enum

    '/*-----------------------------------------------------------------------------
    ' Toning Effect 
    '-----------------------------------------------------------------------------*/
    Public Enum EdsTonigEffect
        kEdsTonigEffect_None = 0
        kEdsTonigEffect_Sepia = 1
        kEdsTonigEffect_Blue = 2
        kEdsTonigEffect_Purple = 3
        kEdsTonigEffect_Green = 4
    End Enum


    '/*-----------------------------------------------------------------------------
    ' Color Space
    '-----------------------------------------------------------------------------*/
    Public Enum EdsColorSpace
        kEdsColorSpace_sRGB = 1
        kEdsColorSpace_AdobeRGB = 2
        kEdsColorSpace_Unknown = &HFFFFFFFF
    End Enum



    '/*-----------------------------------------------------------------------------
    ' PictureStyle
    '-----------------------------------------------------------------------------*/
    Public Enum EdsPictureStyle
        kEdsPictureStyle_Standard = &H81
        kEdsPictureStyle_Portrait = &H82
        kEdsPictureStyle_Landscape = &H83
        kEdsPictureStyle_Neutral = &H84
        kEdsPictureStyle_Faithful = &H85
        kEdsPictureStyle_Monochrome = &H86
        kEdsPictureStyle_User1 = &H21
        kEdsPictureStyle_User2 = &H22
        kEdsPictureStyle_User3 = &H23
        kEdsPictureStyle_PC1 = &H41
        kEdsPictureStyle_PC2 = &H42
        kEdsPictureStyle_PC3 = &H43
    End Enum


    '/*-----------------------------------------------------------------------------
    ' Transfer Option
    '-----------------------------------------------------------------------------*/
    Enum EdsTransferOption
        kEdsTransferOption_ByDirectTransfer = 1
        kEdsTransferOption_ByRelease = 2
        kEdsTransferOption_ToDesktop = &H100
    End Enum



    Public Enum EdsAEMode
        kEdsAEMode_Program = 0
        kEdsAEMode_Tv = 1
        kEdsAEMode_Av = 2
        kEdsAEMode_Manual = 3
        kEdsAEMode_Bulb = 4
        kEdsAEMode_A_DEP = 5
        kEdsAEMode_DEP = 6
        kEdsAEMode_Custom = 7
        kEdsAEMode_Lock = 8
        kEdsAEMode_Green = 9
        kEdsAEMode_NightPortrait = 10
        kEdsAEMode_Sports = 11
        kEdsAEMode_Portrait = 12
        kEdsAEMode_Landscape = 13
        kEdsAEMode_Closeup = 14
        kEdsAEMode_FlashOff = 15
        kEdsAEMode_Unknown = &HFFFFFFFF
    End Enum



    '/*-----------------------------------------------------------------------------
    ' Bracket
    '-----------------------------------------------------------------------------*/
    Public Enum EdsBracket
        kEdsBracket_AEB = &H1
        kEdsBracket_ISOB = &H2
        kEdsBracket_WBB = &H4
        kEdsBracket_FEB = &H8
        kEdsBracket_Unknown = &HFFFFFFFF
    End Enum

    '/*-----------------------------------------------------------------------------
    ' Temp status
    '-----------------------------------------------------------------------------*/
    Public Enum EdsTempStatus
        kEdsTempStatus_Normal = 0
        kEdsTempStatus_Warning = 1
        kEdsTempStatus_Disable_LV = 2
        kEdsTempStatus_Disable_Capture = 3
    End Enum

    '/*-----------------------------------------------------------------------------
    ' EVF Output Device [Flag]
    '-----------------------------------------------------------------------------*/
    Public Enum EdsEvfOutputDevice
        kEdsEvfOutputDevice_TFT = 1
        kEdsEvfOutputDevice_PC = 2
    End Enum

    '/*-----------------------------------------------------------------------------
    ' EVF Zoom
    '-----------------------------------------------------------------------------*/
    Public Enum EdsEvfZoom
        kEdsEvfZoom_Fit = 1
        kEdsEvfZoom_x5 = 5
        kEdsEvfZoom_x10 = 10
    End Enum

    '/******************************************************************************
    ' Definition of Structures
    '******************************************************************************/
    '/*-----------------------------------------------------------------------------
    ' Point
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsPoint
        Public x As Integer
        Public y As Integer
    End Structure

    <StructLayout(LayoutKind.Sequential)> Public Structure EdsSize
        Public width As Integer
        Public height As Integer
    End Structure


    '/*-----------------------------------------------------------------------------
    ' Rectangle
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsRect  '
        Public point As EdsPoint
        Public size As EdsSize
    End Structure

    '/*-----------------------------------------------------------------------------
    ' Rational
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsRational
        Public numerator As Integer
        Public denominator As Integer
    End Structure


    '/*-----------------------------------------------------------------------------
    ' Time
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsTime
        Public year As Integer                         '// year
        Public month As Integer                        '// month 1=January, 2=February, ...
        Public day As Integer                          '// day
        Public hour As Integer                         '// hour
        Public minute As Integer                       '// minute
        Public second As Integer                       '// second
        Public milliseconds As Integer                 '// reserved
    End Structure


    '/******************************************************************************
    ' Definition of Constants
    '******************************************************************************/
    Public Const EDS_MAX_NAME As Short = 256
    Public Const EDS_TRANSFER_BLOCK_SIZE As Integer = 512
    '// When the DirectoryItem is downloaded
    '// or uploaded separately for the plural
    '// block, The size of the block
    '// other than the terminal block should be
    '// assumed to be a multiple in 512 bytes.


    '/******************************************************************************
    ' Camera Detect Evnet Handler
    '******************************************************************************/
    Public Delegate Function EdsCameraAddedHandler( _
         ByVal inContext As IntPtr) As Long


    '/******************************************************************************
    ' Callback Functions
    '******************************************************************************/
    Public Delegate Function EdsProgressCallback( _
        ByVal inPercent As Integer, _
        ByVal inContext As IntPtr, _
        ByRef outCancel As Boolean) As Long


    '/******************************************************************************
    ' Evnet Handler
    '******************************************************************************/
    Public Delegate Function EdsPropertyEventHandler( _
        ByVal inEvent As Integer, _
        ByVal inPropertyID As Integer, _
        ByVal inParam As Integer, _
        ByVal inContext As IntPtr) As Long


    Public Delegate Function EdsObjectEventHandler( _
        ByVal inEvent As Integer, _
        ByVal inRef As IntPtr, _
        ByVal inContext As IntPtr) As Long


    Public Delegate Function EdsStateEventHandler( _
        ByVal inEvent As Integer, _
        ByVal inEventData As Integer, _
        ByVal inContext As IntPtr) As Long



    '/******************************************************************************
    ' Definition of Structures
    '******************************************************************************/

    '/*-----------------------------------------------------------------------------
    ' Device Info
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsDeviceInfo
        <MarshalAs(UnmanagedType.ByValTStr, SizeConst:=EDS_MAX_NAME)> Public szPortName As String
        <MarshalAs(UnmanagedType.ByValTStr, SizeConst:=EDS_MAX_NAME)> Public szDeviceDescription As String
        Public DeviceSubType As Integer
    End Structure


    '/*-----------------------------------------------------------------------------
    ' Volume Info
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsVolumeInfo
        Public storageType As Integer
        Public access As Integer
        Public maxCapacity As Int64
        Public freeSpaceInBytes As Int64
        <MarshalAs(UnmanagedType.ByValTStr, SizeConst:=EDS_MAX_NAME)> Public szVolumeLabel As String
    End Structure


    '/*-----------------------------------------------------------------------------
    ' DirectoryItem Info
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsDirectoryItemInfo
        Public size As Integer
        Public isFolder As Boolean
        Public groupID As Integer
        Public opt As Integer
        <MarshalAs(UnmanagedType.ByValTStr, SizeConst:=EDS_MAX_NAME)> Public szFileName As String
    End Structure


    '/*-----------------------------------------------------------------------------
    ' Image Info
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsImageInfo
        Public width As Integer     '// image width 
        Public height As Integer     '// image height

        Public numOfComponents As Integer  '// number of color components in image.
        Public componentDepth As Integer   '// bits per sample.  8 or 16.

        Public effectiveRect As EdsRect
        '// Effective rectangles except 
        '// a black line of the image. 
        '// A black line might be in the top and bottom
        '// of the thumbnail image. 

        Public reserved1 As Integer
        Public reserved2 As Integer

    End Structure


    '/*-----------------------------------------------------------------------------
    ' SaveImageSetting                      
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsSaveImageSetting
        Public JPEGQuality As Integer
        Public iccProfileStream As IntPtr
        Public reserved As Integer
    End Structure


    '/*-----------------------------------------------------------------------------
    '    Property Desc
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsPropertyDesc
        Public form As Integer
        Public access As Integer
        Public numElements As Integer
        <MarshalAs(UnmanagedType.ByValArray, SizeConst:=128)> Public propDesc() As Integer
    End Structure


    '////////////////////////////////////////////////////////////////////////////////
    '/*-----------------------------------------------------------------------------
    ' Picture Style Desc
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsPictureStyleDesc
        Public contrast As Integer
        Public sharpness As Integer
        Public saturation As Integer
        Public colorTone As Integer
        Public filterEffect As Integer
        Public toningEffect As Integer
    End Structure


    '/*-----------------------------------------------------------------------------
    ' Focus Info
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsFocusPoint
        Public valid As Integer      '// if the frame is valid.
        Public justFocus As Integer  '// if the frame is just focus.
        Public rect As EdsRect       '// rectangle of focus point.
        Public reserved As Integer   '// reserved
    End Structure


    <StructLayout(LayoutKind.Sequential)> Public Structure EdsFocusInfo
        Public imageRect As EdsRect            '// rectangle of the image.
        Public pointNumber As Integer         '// number of point.
        <MarshalAs(UnmanagedType.ByValArray, SizeConst:=128)> Public focusPoint() As EdsFocusPoint '// each frame's description.
    End Structure


    '/*-----------------------------------------------------------------------------
    ' User WhiteBalance (PC set1,2,3)/ User ToneCurve / User PictureStyle dataset 
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsUsersetData
        Public valid As Integer
        Public dataSize As Integer
        <MarshalAs(UnmanagedType.ByValTStr, SizeConst:=32)> Public szCaption As String
        <MarshalAs(UnmanagedType.ByValArray, SizeConst:=1)> Public data() As Byte
    End Structure


    '/*-----------------------------------------------------------------------------
    ' Capacity
    '-----------------------------------------------------------------------------*/
    <StructLayout(LayoutKind.Sequential)> Public Structure EdsCapacity
        Public numberOfFreeClusters As Integer  '// free clusters
        Public bytesPerSector As Integer        '// sectors per cluster
        Public reset As Boolean
    End Structure



End Module
