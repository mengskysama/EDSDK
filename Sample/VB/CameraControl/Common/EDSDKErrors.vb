'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : EDSDKErros.h                                                    *
'*                                                                             *
'*   Description: ERROR DEFINITION FOR EDSDK                                   *
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

Public Module EDSDKErrors

    Public Const EDS_ERRORID_MASK As Integer = &HFFFFL

    Public Const EDS_ERR_OK As Integer = 0
    '/* Miscellaneous errors */
    Public Const EDS_ERR_UNIMPLEMENTED As Integer = &H1L
    Public Const EDS_ERR_INTERNAL_ERROR As Integer = &H2L
    Public Const EDS_ERR_MEM_ALLOC_FAILED As Integer = &H3L
    Public Const EDS_ERR_MEM_FREE_FAILED As Integer = &H4L
    Public Const EDS_ERR_OPERATION_CANCELLED As Integer = &H5L
    Public Const EDS_ERR_INCOMPATIBLE_VERSION As Integer = &H6L
    Public Const EDS_ERR_NOT_SUPPORTED As Integer = &H7L
    Public Const EDS_ERR_UNEXPECTED_EXCEPTION As Integer = &H8L
    Public Const EDS_ERR_PROTECTION_VIOLATION As Integer = &H9L
    Public Const EDS_ERR_MISSING_SUBCOMPONENT As Integer = &HAL
    Public Const EDS_ERR_SELECTION_UNAVAILABLE As Integer = &HBL

    '/* File errors */
    Public Const EDS_ERR_FILE_IO_ERROR As Integer = &H20L
    Public Const EDS_ERR_FILE_TOO_MANY_OPEN As Integer = &H21L
    Public Const EDS_ERR_FILE_NOT_FOUND As Integer = &H22L
    Public Const EDS_ERR_FILE_OPEN_ERROR As Integer = &H23L
    Public Const EDS_ERR_FILE_CLOSE_ERROR As Integer = &H24L
    Public Const EDS_ERR_FILE_SEEK_ERROR As Integer = &H25L
    Public Const EDS_ERR_FILE_TELL_ERROR As Integer = &H26L
    Public Const EDS_ERR_FILE_READ_ERROR As Integer = &H27L
    Public Const EDS_ERR_FILE_WRITE_ERROR As Integer = &H28L
    Public Const EDS_ERR_FILE_PERMISSION_ERROR As Integer = &H29L
    Public Const EDS_ERR_FILE_DISK_FULL_ERROR As Integer = &H2AL
    Public Const EDS_ERR_FILE_ALREADY_EXISTS As Integer = &H2BL
    Public Const EDS_ERR_FILE_FORMAT_UNRECOGNIZED As Integer = &H2CL
    Public Const EDS_ERR_FILE_DATA_CORRUPT As Integer = &H2DL
    Public Const EDS_ERR_FILE_NAMING_NA As Integer = &H2EL

    '/* Directory errors */          
    Public Const EDS_ERR_DIR_NOT_FOUND As Integer = &H40L
    Public Const EDS_ERR_DIR_IO_ERROR As Integer = &H41L
    Public Const EDS_ERR_DIR_ENTRY_NOT_FOUND As Integer = &H42L
    Public Const EDS_ERR_DIR_ENTRY_EXISTS As Integer = &H43L
    Public Const EDS_ERR_DIR_NOT_EMPTY As Integer = &H44L

    '/* Property errors */
    Public Const EDS_ERR_PROPERTIES_UNAVAILABLE As Integer = &H50L
    Public Const EDS_ERR_PROPERTIES_MISMATCH As Integer = &H51L
    Public Const EDS_ERR_PROPERTIES_NOT_LOADED As Integer = &H53L

    '/* Function Parameter errors */     
    Public Const EDS_ERR_INVALID_PARAMETER As Integer = &H60L
    Public Const EDS_ERR_INVALID_HANDLE As Integer = &H61L
    Public Const EDS_ERR_INVALID_POINTER As Integer = &H62L
    Public Const EDS_ERR_INVALID_INDEX As Integer = &H63L
    Public Const EDS_ERR_INVALID_LENGTH As Integer = &H64L
    Public Const EDS_ERR_INVALID_FN_POINTER As Integer = &H65L
    Public Const EDS_ERR_INVALID_SORT_FN As Integer = &H66L

    '/* Device errors */
    Public Const EDS_ERR_DEVICE_NOT_FOUND As Integer = &H80L
    Public Const EDS_ERR_DEVICE_BUSY As Integer = &H81L
    Public Const EDS_ERR_DEVICE_INVALID As Integer = &H82L
    Public Const EDS_ERR_DEVICE_EMERGENCY As Integer = &H83L
    Public Const EDS_ERR_DEVICE_MEMORY_FULL As Integer = &H84L
    Public Const EDS_ERR_DEVICE_INTERNAL_ERROR As Integer = &H85L
    Public Const EDS_ERR_DEVICE_INVALID_PARAMETER As Integer = &H86L
    Public Const EDS_ERR_DEVICE_NO_DISK As Integer = &H87L
    Public Const EDS_ERR_DEVICE_DISK_ERROR As Integer = &H88L
    Public Const EDS_ERR_DEVICE_CF_GATE_CHANGED As Integer = &H89L
    Public Const EDS_ERR_DEVICE_DIAL_CHANGED As Integer = &H8AL
    Public Const EDS_ERR_DEVICE_NOT_INSTALLED As Integer = &H8BL
    Public Const EDS_ERR_DEVICE_STAY_AWAKE As Integer = &H8CL
    Public Const EDS_ERR_DEVICE_NOT_RELEASED As Integer = &H8DL

    '/* Stream errors */
    Public Const EDS_ERR_STREAM_IO_ERROR As Integer = &HA0L
    Public Const EDS_ERR_STREAM_NOT_OPEN As Integer = &HA1L
    Public Const EDS_ERR_STREAM_ALREADY_OPEN As Integer = &HA2L
    Public Const EDS_ERR_STREAM_OPEN_ERROR As Integer = &HA3L
    Public Const EDS_ERR_STREAM_CLOSE_ERROR As Integer = &HA4L
    Public Const EDS_ERR_STREAM_SEEK_ERROR As Integer = &HA5L
    Public Const EDS_ERR_STREAM_TELL_ERROR As Integer = &HA6L
    Public Const EDS_ERR_STREAM_READ_ERROR As Integer = &HA7L
    Public Const EDS_ERR_STREAM_WRITE_ERROR As Integer = &HA8L
    Public Const EDS_ERR_STREAM_PERMISSION_ERROR As Integer = &HA9L
    Public Const EDS_ERR_STREAM_COULDNT_BEGIN_THREAD As Integer = &HAAL
    Public Const EDS_ERR_STREAM_BAD_OPTIONS As Integer = &HABL
    Public Const EDS_ERR_STREAM_END_OF_STREAM As Integer = &HACL

    '/* Communications errors */
    Public Const EDS_ERR_COMM_PORT_IS_IN_USE As Integer = &HC0L
    Public Const EDS_ERR_COMM_DISCONNECTED As Integer = &HC1L
    Public Const EDS_ERR_COMM_DEVICE_INCOMPATIBLE As Integer = &HC2L
    Public Const EDS_ERR_COMM_BUFFER_FULL As Integer = &HC3L
    Public Const EDS_ERR_COMM_USB_BUS_ERR As Integer = &HC4L

    '/* Lock/Unlock */
    Public Const EDS_ERR_USB_DEVICE_LOCK_ERROR As Integer = &HD0L
    Public Const EDS_ERR_USB_DEVICE_UNLOCK_ERROR As Integer = &HD1L

    '/* STI/WIA */
    Public Const EDS_ERR_STI_UNKNOWN_ERROR As Integer = &HE0L
    Public Const EDS_ERR_STI_INTERNAL_ERROR As Integer = &HE1L
    Public Const EDS_ERR_STI_DEVICE_CREATE_ERROR As Integer = &HE2L
    Public Const EDS_ERR_STI_DEVICE_RELEASE_ERROR As Integer = &HE3L
    Public Const EDS_ERR_DEVICE_NOT_LAUNCHED As Integer = &HE4L

    Public Const EDS_ERR_ENUM_NA As Integer = &HF0L
    Public Const EDS_ERR_INVALID_FN_CALL As Integer = &HF1L
    Public Const EDS_ERR_HANDLE_NOT_FOUND As Integer = &HF2L
    Public Const EDS_ERR_INVALID_ID As Integer = &HF3L
    Public Const EDS_ERR_WAIT_TIMEOUT_ERROR As Integer = &HF4L

    '/* PTP */
    Public Const EDS_ERR_SESSION_NOT_OPEN As Integer = &H2003
    Public Const EDS_ERR_INVALID_TRANSACTIONID As Integer = &H2004
    Public Const EDS_ERR_INCOMPLETE_TRANSFER As Integer = &H2007
    Public Const EDS_ERR_INVALID_STRAGEID As Integer = &H2008
    Public Const EDS_ERR_DEVICEPROP_NOT_SUPPORTED As Integer = &H200A
    Public Const EDS_ERR_INVALID_OBJECTFORMATCODE As Integer = &H200B
    Public Const EDS_ERR_SELF_TEST_FAILED As Integer = &H2011
    Public Const EDS_ERR_PARTIAL_DELETION As Integer = &H2012
    Public Const EDS_ERR_SPECIFICATION_BY_FORMAT_UNSUPPORTED As Integer = &H2014
    Public Const EDS_ERR_NO_VALID_OBJECTINFO As Integer = &H2015
    Public Const EDS_ERR_INVALID_CODE_FORMAT As Integer = &H2016
    Public Const EDS_ERR_UNKNOWN_VENDER_CODE As Integer = &H2017
    Public Const EDS_ERR_CAPTURE_ALREADY_TERMINATED As Integer = &H2018
    Public Const EDS_ERR_INVALID_PARENTOBJECT As Integer = &H201A
    Public Const EDS_ERR_INVALID_DEVICEPROP_FORMAT As Integer = &H201B
    Public Const EDS_ERR_INVALID_DEVICEPROP_VALUE As Integer = &H201C
    Public Const EDS_ERR_SESSION_ALREADY_OPEN As Integer = &H201E
    Public Const EDS_ERR_TRANSACTION_CANCELLED As Integer = &H201F
    Public Const EDS_ERR_SPECIFICATION_OF_DESTINATION_UNSUPPORTED As Integer = &H2020
    Public Const EDS_ERR_UNKNOWN_COMMAND As Integer = &HA001
    Public Const EDS_ERR_OPERATION_REFUSED As Integer = &HA005
    Public Const EDS_ERR_LENS_COVER_CLOSE As Integer = &HA006
    Public Const EDS_ERR_LOW_BATTERY As Integer = &HA101
    Public Const EDS_ERR_OBJECT_NOTREADY As Integer = &HA102

    Public Const EDS_ERR_LAST_GENERIC_ERROR_PLUS_ONE As Integer = &HF5L
End Module
