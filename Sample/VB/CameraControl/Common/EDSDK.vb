'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : EDSDK.h                                                         *
'*                                                                             *
'*   Description: PROTO TYPE DEFINITION OF EDSDK API                           *
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
'*   06-03-08    F-001        create first version.                            *
'*                                                                             *
'******************************************************************************/
'Option Strict Off
Option Explicit On 

Imports System.Runtime.InteropServices

Public Module EDSDK

    '===================================================
    '
    ' EDSDK.h
    '
    '===================================================

    '/******************************************************************************
    '*******************************************************************************
    '//
    '//  initialize / terminate
    '//
    '*******************************************************************************
    '******************************************************************************/

    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsInitializeSDK
    '//
    '//  Description:
    '//      Initializes the libraries. 
    '//      When using the EDSDK libraries, you must call this API once  
    '//          before using EDSDK APIs.
    '//
    '//  Parameters:
    '//       In:    None
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsInitializeSDK Lib "EDSDK" () As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsTerminateSDK
    '//
    '//  Description:
    '//      Terminates use of the libraries. 
    '//      This function muse be called when ending the SDK.
    '//      Calling this function releases all resources allocated by the libraries.
    '//
    '//  Parameters:
    '//       In:    None
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsTerminateSDK Lib "EDSDK" () As Integer


    '/******************************************************************************
    '*******************************************************************************
    '//
    '//  reference counter
    '//
    '*******************************************************************************
    '******************************************************************************/

    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsRetain
    '//
    '//  Description:
    '//     Increment the reference counter of the item.
    '//
    '//  Parameters:
    '//       In:   inRef - The reference for the item.
    '//      Out:   None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsRetain Lib "EDSDK" (ByVal inRef As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsRelease
    '//
    '//  Description:
    '//     Decrement the reference counter of the item.
    '//     The item is not deleted until a reference counter is set to 0.
    '//
    '//  Parameters:
    '//       In:   inRef - The reference of the item.
    '//      Out:   None
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsRelease Lib "EDSDK" (ByVal inRef As IntPtr) As Integer


    '/******************************************************************************
    '*******************************************************************************
    '//
    '//  item tree 
    '//
    '*******************************************************************************
    '******************************************************************************/


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetChildCount
    '//
    '//  Description:
    '//      Gets the number of child objects of the designated object.
    '//      Example: Number of files in a directory
    '//
    '//  Parameters:
    '//       In:    inRef - The reference of the list.
    '//      Out:    outCount - Number of elements in this list.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetChildCount Lib "EDSDK" ( _
        ByVal inCameraListRef As IntPtr, _
        ByRef outCount As Integer) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetChildAtIndex
    '//
    '//  Description:
    '//       Gets an indexed child object of the designated object. 
    '//
    '//  Parameters:
    '//       In:    inRef - The reference of the item.
    '//              inIndex -  The index that is passed in, is zero based.
    '//      Out:    outRef - The pointer which receives reference of the 
    '//                           specified index .
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetChildAtIndex Lib "EDSDK" ( _
        ByVal inRef As IntPtr, _
        ByVal inIndex As Integer, _
        ByRef outRef As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetParent
    '//
    '//  Description:
    '//      Gets the parent object of the designated object.
    '//
    '//  Parameters:
    '//       In:    inRef        - The reference of the item.
    '//      Out:    outParentRef - The pointer which receives reference.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetParent Lib "EDSDK" ( _
        ByVal inRef As IntPtr, _
        ByRef outParentRef As IntPtr) As Integer


    '/******************************************************************************
    '*******************************************************************************
    '//
    '//  property 
    '//
    '*******************************************************************************
    '******************************************************************************/


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetPropertySize
    '//
    '//  Description:
    '//      Gets the byte size and data type of a designated property 
    '//          from a camera object or image object.
    '//
    '//  Parameters:
    '//       In:    inRef - The reference of the item.
    '//              inPropertyID - The ProprtyID
    '//              inParam - Additional information of property.
    '//                   We use this parameter in order to specify an index
    '//                   in case there are two or more values over the same ID.
    '//      Out:    outDataType - Pointer to the buffer that is to receive the property
    '//                        type data.
    '//              outSize - Pointer to the buffer that is to receive the property
    '//                        size.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetPropertySize Lib "EDSDK" ( _
        ByVal inRef As IntPtr, _
        ByVal inPropertyID As Integer, _
        ByVal inParam As Integer, _
        ByRef outDataType As EdsDataType, _
        ByRef outSize As Integer) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetPropertyData
    '//
    '//  Description:
    '//     Get the property data value.
    '//
    '//  Parameters:
    '//       In:   inRef - The reference of the item.
    '//             inPropertyID - The ProprtyID
    '//             inParam - Additional information of property.
    '//                  We use this parameter in order to specify an index
    '//                  in case there are two or more values over the same ID.
    '//             inPropertySize - The number of bytes of the prepared buffer
    '//                 for receive property-value.
    '//      Out:   outPropertyValue - The buffer pointer to receive property-value.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetPropertyData Lib "EDSDK" ( _
        ByVal inRef As IntPtr, _
        ByVal inPropertyID As Integer, _
        ByVal inParam As Integer, _
        ByVal inPropertySize As Integer, _
        ByVal outPropertyData As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsSetPropertyData
    '//
    '//  Description:
    '//      Sets property data for the object designated in inRef. 
    '//
    '//  Parameters:
    '//       In:    inRef - The reference of the item.
    '//              inPropertyID - The ProprtyID
    '//              inParam - Additional information of property.
    '//              inPropertySize - The number of bytes of the prepared buffer
    '//                  for set property-value.
    '//              inPropertyData - The buffer pointer to set property-value.
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsSetPropertyData Lib "EDSDK" ( _
        ByVal inRef As IntPtr, _
        ByVal inPropertyID As Integer, _
        ByVal inParam As Integer, _
        ByVal inPropertySize As Integer, _
        <MarshalAs(UnmanagedType.AsAny)> ByVal inPropertyData As Object) As Integer


    '/*-----------------------------------------------------------------------------
    '//  
    '//  Function:   EdsGetPropertyDesc
    '//
    '//  Description:
    '//      Gets a list of property data that can be set for the object 
    '//          designated in inRef, as well as maximum and minimum values. 
    '//      This API is intended for only some shooting-related properties.
    '//
    '//  Parameters:
    '//       In:    inRef - The reference of the camera.
    '//              inPropertyID - The Property ID.
    '//       Out:   outPropertyDesc - Array of the value which can be set up.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetPropertyDesc Lib "EDSDK" ( _
        ByVal inRef As IntPtr, _
        ByVal inPropertyID As Integer, _
        ByRef outPropertyDesc As EdsPropertyDesc) As Integer


    '/******************************************************************************
    '*******************************************************************************
    '//
    '// device-list and device operation 
    '//
    '*******************************************************************************
    '******************************************************************************/

    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetCameraList
    '//
    '//  Description:
    '//      Gets camera list objects.
    '//
    '//  Parameters:
    '//       In:    None
    '//      Out:    outCameraListRef - Pointer to the camera-list.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetCameraList Lib "EDSDK" ( _
        ByRef outCameraListRef As IntPtr) As Integer


    '/******************************************************************************
    '*******************************************************************************
    '//
    '// camera operation 
    '//
    '*******************************************************************************
    '******************************************************************************/

    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetDeviceInfo
    '//
    '//  Description:
    '//      Gets device information, such as the device name.  
    '//      Because device information of remote cameras is stored 
    '//          on the host computer, you can use this API 
    '//          before the camera object initiates communication
    '//          (that is, before a session is opened). 
    '//
    '//  Parameters:
    '//       In:    inCameraRef - The reference of the camera.
    '//      Out:    outDeviceInfo - Information as device of camera.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetDeviceInfo Lib "EDSDK" ( _
        ByVal inCameraRef As IntPtr, _
        ByRef outDeviceInfo As EdsDeviceInfo) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsOpenSession
    '//
    '//  Description:
    '//      Establishes a logical connection with a remote camera. 
    '//      Use this API after getting the camera's EdsCamera object.
    '//
    '//  Parameters:
    '//       In:    inCameraRef - The reference of the camera 
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsOpenSession Lib "EDSDK" (ByVal inCameraRef As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsCloseSession
    '//
    '//  Description:
    '//       Closes a logical connection with a remote camera.
    '//
    '//  Parameters:
    '//       In:    inCameraRef - The reference of the camera 
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsCloseSession Lib "EDSDK" (ByVal inCameraRef As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsSendCommand
    '//
    '//  Description:
    '//       Sends a command such as "Shoot" to a remote camera. 
    '//
    '//  Parameters:
    '//       In:    inCameraRef - The reference of the camera which will receive the 
    '//                      command.
    '//              inCommand - Specifies the command to be sent.
    '//              inParam -     Specifies additional command-specific information.
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsSendCommand Lib "EDSDK" ( _
        ByVal inCameraRef As IntPtr, _
        ByVal inCommandID As Integer, _
        ByVal inParam As Integer) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsSendStatusCommand
    '//
    '//  Description:
    '//       Sets the remote camera state or mode.
    '//
    '//  Parameters:
    '//       In:    inCameraRef - The reference of the camera which will receive the 
    '//                      command.
    '//              inStatusCommand - Specifies the command to be sent.
    '//              inParam -     Specifies additional command-specific information.
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsSendStatusCommand Lib "EDSDK" ( _
        ByVal inCameraRef As IntPtr, _
        ByVal inStatusCommand As Integer, _
        ByVal inParam As Integer) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsSetCapacity
    '//
    '//  Description:
    '//      Sets the remaining HDD capacity on the host computer
    '//          (excluding the portion from image transfer),
    '//          as calculated by subtracting the portion from the previous time. 
    '//      Set a reset flag initially and designate the cluster length 
    '//          and number of free clusters.
    '//      Some type 2 protocol standard cameras can display the number of shots 
    '//          left on the camera based on the available disk capacity 
    '//          of the host computer. 
    '//      For these cameras, after the storage destination is set to the computer, 
    '//          use this API to notify the camera of the available disk capacity 
    '//          of the host computer.
    '//
    '//  Parameters:
    '//       In:    inCameraRef - The reference of the camera which will receive the 
    '//                      command.
    '//              inCapacity -  The remaining capacity of a transmission place.
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsSetCapacity Lib "EDSDK" ( _
                ByVal inCameraRef As IntPtr, _
                ByVal inCapacity As EdsCapacity) As Integer

    '/******************************************************************************
    '*******************************************************************************
    '//
    '// volume operation
    '//
    '*******************************************************************************
    '******************************************************************************/

    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetVolumeInfo
    '//
    '//  Description:
    '//      Gets volume information for a memory card in the camera.
    '//
    '//  Parameters:
    '//       In:    inVolumeRef - The reference of the volume.
    '//      Out:    outVolumeInfo - information of  the volume.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Auto Function EdsGetVolumeInfo Lib "EDSDK" ( _
        ByVal inVolumeRef As IntPtr, _
        ByRef outVolumeInfo As EdsVolumeInfo) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsFormatVolume
    '//
    '//  Description:
    '//       .
    '//
    '//  Parameters:
    '//       In:    inVolumeRef - The reference of volume .
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsFormatVolume Lib "EDSDK" (ByVal inVolumeRef As IntPtr) As Integer


    '/******************************************************************************
    '*******************************************************************************
    '//
    '// directory item operation
    '//
    '*******************************************************************************
    '******************************************************************************/

    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetDirectoryItemInfo
    '//
    '//  Description:
    '//      Gets information about the directory or file objects 
    '//          on the memory card (volume) in a remote camera.
    '//
    '//  Parameters:
    '//       In:    inDirItemRef - The reference of the directory item.
    '//      Out:    outDirItemInfo - information of the directory item.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetDirectoryItemInfo Lib "EDSDK" ( _
        ByVal inDirItemRefs As IntPtr, _
        ByRef outDirItemInfo As EdsDirectoryItemInfo) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsDeleteDirectoryItem
    '//
    '//  Description:
    '//      Deletes a camera folder or file.
    '//      If folders with subdirectories are designated, all files are deleted 
    '//          except protected files. 
    '//      EdsDirectoryItem objects deleted by means of this API are implicitly 
    '//          released by the EDSDK. Thus, there is no need to release them 
    '//          by means of EdsRelease.
    '//
    '//  Parameters:
    '//       In:    inDirItemRef - The reference of the directory item.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsDeleteDirectoryItem Lib "EDSDK" ( _
        ByVal inDirItemRef As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsDownload
    '//
    '//  Description:
    '//       Downloads a file on a remote camera 
    '//          (in the camera memory or on a memory card) to the host computer. 
    '//      The downloaded file is sent directly to a file stream created in advance. 
    '//      When dividing the file being retrieved, call this API repeatedly. 
    '//      Also in this case, make the data block size a multiple of 512 (bytes), 
    '//          excluding the final block.
    '//
    '//  Parameters:
    '//       In:    inDirItemRef - The reference of the directory item.
    '//              inReadSize   - 
    '//
    '//      Out:    outStream    - The reference of the stream.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsDownload Lib "EDSDK" ( _
        ByVal inDirItemRef As IntPtr, _
        ByVal inReadSize As Integer, _
        ByVal outStream As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsDownloadCancel
    '//
    '//  Description:
    '//       Must be executed when downloading of a directory item is canceled. 
    '//      Calling this API makes the camera cancel file transmission.
    '//      It also releases resources. 
    '//      This operation need not be executed when using EdsDownloadThumbnail. 
    '//
    '//  Parameters:
    '//       In:    inDirItemRef - The reference of the directory item.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsDownloadCancel Lib "EDSDK" (ByVal inDirItemRef As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsDownloadComplete
    '//
    '//  Description:
    '//       Must be called when downloading of directory items is complete. 
    '//          Executing this API makes the camera 
    '//              recognize that file transmission is complete. 
    '//          This operation need not be executed when using EdsDownloadThumbnail.
    '//
    '//  Parameters:
    '//       In:    inDirItemRef - The reference of the directory item.
    '//
    '//      Out:    outStream    - None.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsDownloadComplete Lib "EDSDK" (ByVal inDirItemRef As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsDownloadThumbnail
    '//
    '//  Description:
    '//      Extracts and downloads thumbnail information from image files in a camera. 
    '//      Thumbnail information in the camera's image files is downloaded 
    '//          to the host computer. 
    '//      Downloaded thumbnails are sent directly to a file stream created in advance.
    '//
    '//  Parameters:
    '//       In:    inDirItemRef - The reference of the directory item.
    '//
    '//      Out:    outStream - The reference of the stream.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsDownloadThumbnail Lib "EDSDK" ( _
        ByVal inDirItemRef As IntPtr, _
        ByVal outStream As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetAttribute
    '//
    '//  Description:
    '//      Gets attributes of files on a camera.
    '//  
    '//  Parameters:
    '//       In:    inDirItemRef - The reference of the directory item.
    '//      Out:    outFileAttribute  - Indicates the file attributes. 
    '//                  As for the file attributes, OR values of the value defined
    '//                  by enum EdsFileAttributes can be retrieved. Thus, when 
    '//                  determining the file attributes, you must check 
    '//                  if an attribute flag is set for target attributes. 
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetAttribute Lib "EDSDK" ( _
        ByVal inDirItemRef As IntPtr, _
        ByRef outFileAttribute As EdsFileAttributes) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsSetAttribute
    '//
    '//  Description:
    '//      Changes attributes of files on a camera.
    '//  
    '//  Parameters:
    '//       In:    inDirItemRef - The reference of the directory item.
    '//              inFileAttribute  - Indicates the file attributes. 
    '//                      As for the file attributes, OR values of the value 
    '//                      defined by enum EdsFileAttributes can be retrieved. 
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsSetAttribute Lib "EDSDK" ( _
        ByVal inDirItemRef As IntPtr, _
        ByVal inFileAttribute As EdsFileAttributes) As Integer


    '/******************************************************************************
    '*******************************************************************************
    '//
    '// stream operation
    '//
    '*******************************************************************************
    '******************************************************************************/

    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsCreateFileStream
    '//
    '//  Description:
    '//      Creates a new file on a host computer (or opens an existing file) 
    '//          and creates a file stream for access to the file. 
    '//      If a new file is designated before executing this API, 
    '//          the file is actually created following the timing of writing 
    '//          by means of EdsWrite or the like with respect to an open stream.
    '//
    '//  Parameters:
    '//       In:    inFileName - Pointer to a null-terminated string that specifies
    '//                           the file name.
    '//              inCreateDisposition - Action to take on files that exist, 
    '//                                and which action to take when files do not exist.  
    '//              inDesiredAccess - Access to the stream (reading, writing, or both).
    '//      Out:    outStream - The reference of the stream.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsCreateFileStream Lib "EDSDK" ( _
        ByVal inFileName As String, _
        ByVal inCreateDisposition As Integer, _
        ByVal inDesiredAccess As Integer, _
        ByRef outStream As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsCreateMemoryStream
    '//
    '//  Description:
    '//      Creates a stream in the memory of a host computer. 
    '//      In the case of writing in excess of the allocated buffer size, 
    '//          the memory is automatically extended.
    '//
    '//  Parameters:
    '//       In:    inBufferSize - The number of bytes of the memory to allocate.
    '//      Out:    outStream - The reference of the stream.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsCreateMemoryStream Lib "EDSDK" ( _
            ByVal inBufferSize As Integer, _
            ByRef outStream As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsCreateStreamEx
    '//
    '//  Description:
    '//      An extended version of EdsCreateStreamFromFile. 
    '//      Use this function when working with Unicode file names.
    '//
    '//  Parameters:
    '//       In:    inURL (for Macintosh) - Designate CFURLRef. 
    '//              inFileName (for Windows) - Designate the file name. 
    '//              inCreateDisposition - Action to take on files that exist, 
    '//                                and which action to take when files do not exist.  
    '//              inDesiredAccess - Access to the stream (reading, writing, or both).
    '//
    '//      Out:    outStream - The reference of the stream.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsCreateFileStreamEx Lib "EDSDK" ( _
        ByRef inFileName As String, _
        ByVal inCreateDisposition As EdsFileCreateDisposition, _
        ByVal inDesiredAccess As EdsAccess, _
        ByRef outStream As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsCreateMemoryStreamFromPointer        
    '//
    '//  Description:
    '//      Creates a stream from the memory buffer you prepare. 
    '//      Unlike the buffer size of streams created by means of EdsCreateMemoryStream, 
    '//      the buffer size you prepare for streams created this way does not expand.
    '//
    '//  Parameters:
    '//       In:    inBufferSize - The number of bytes of the memory to allocate.
    '//      Out:    outStream - The reference of the stream.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsCreateMemoryStreamFromPointer Lib "EDSDK" ( _
       ByVal inUserBuffer As IntPtr, _
       ByVal inBufferSize As Integer, _
       ByRef outStream As IntPtr) As Integer

    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetPointer                   
    '//
    '//  Description:
    '//      Gets the pointer to the start address of memory managed by the memory stream. 
    '//      As the EDSDK automatically resizes the buffer, the memory stream provides 
    '//          you with the same access methods as for the file stream. 
    '//      If access is attempted that is excessive with regard to the buffer size
    '//          for the stream, data before the required buffer size is allocated 
    '//          is copied internally, and new writing occurs. 
    '//      Thus, the buffer pointer might be switched on an unknown timing. 
    '//      Caution in use is therefore advised. 
    '//
    '//  Parameters:
    '//       In:    inStream - Designate the memory stream for the pointer to retrieve. 
    '//      Out:    outPointer - If successful, returns the pointer to the buffer 
    '//                  written in the memory stream.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetPointer Lib "EDSDK" ( _
            ByVal inStream As IntPtr, _
            ByRef outPointer As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsRead
    '//
    '//  Description:
    '//      Reads data the size of inReadSize into the outBuffer buffer, 
    '//          starting at the current read or write position of the stream. 
    '//      The size of data actually read can be designated in outReadSize.
    '//
    '//  Parameters:
    '//       In:    inStreamRef - The reference of the stream or image.
    '//              inReadSize -  The number of bytes to read.
    '//      Out:    outBuffer - Pointer to the user-supplied buffer that is to receive
    '//                          the data read from the stream. 
    '//              outReadSize - The actually read number of bytes.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsRead Lib "EDSDK" ( _
            ByVal inStreamRef As IntPtr, _
            ByVal inReadSize As Integer, _
            ByVal outBuffer As IntPtr, _
            ByRef outReadSize As Integer) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsWrite
    '//
    '//  Description:
    '//      Writes data of a designated buffer 
    '//          to the current read or write position of the stream. 
    '//
    '//  Parameters:
    '//       In:    inStreamRef  - The reference of the stream or image.
    '//              inWriteSize - The number of bytes to write.
    '//              inBuffer - A pointer to the user-supplied buffer that contains 
    '//                         the data to be written to the stream.
    '//      Out:    outWrittenSize - The actually written-in number of bytes.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsWrite Lib "EDSDK" ( _
            ByVal inStreamRef As IntPtr, _
            ByVal inWriteSize As Integer, _
            ByVal inBuffer As IntPtr, _
            ByRef outWrittenSize As Integer) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsSeek
    '//
    '//  Description:
    '//      Moves the read or write position of the stream
    '            (that is, the file position indicator).
    '//
    '//  Parameters:
    '//       In:    inStreamRef  - The reference of the stream or image. 
    '//              inSeekOffset - Number of bytes to move the pointer. 
    '//              inSeekOrigin - Pointer movement mode. Must be one of the following 
    '//                             values.
    '//                  kEdsSeek_Cur     Move the stream pointer inSeekOffset bytes 
    '//                                   from the current position in the stream. 
    '//                  kEdsSeek_Begin   Move the stream pointer inSeekOffset bytes
    '//                                   forward from the beginning of the stream. 
    '//                  kEdsSeek_End     Move the stream pointer inSeekOffset bytes
    '//                                   from the end of the stream. 
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsSeek Lib "EDSDK" ( _
            ByVal inStreamRef As IntPtr, _
            ByVal inSeekOffset As Integer, _
            ByVal inSeekOrigin As EdsSeekOrigin) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetPosition
    '//
    '//  Description:
    '//       Gets the current read or write position of the stream
    '//          (that is, the file position indicator).
    '//
    '//  Parameters:
    '//       In:    inStreamRef - The reference of the stream or image.
    '//      Out:    outPosition - The current stream pointer.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetPosition Lib "EDSDK" ( _
            ByVal inStreamRef As IntPtr, _
            ByRef outPosition As Integer) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetLength
    '//
    '//  Description:
    '//      Gets the stream size.
    '//
    '//  Parameters:
    '//       In:    inStreamRef - The reference of the stream or image.
    '//      Out:    outLength - The length of the stream.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetLength Lib "EDSDK" ( _
            ByVal inStreamRef As IntPtr, _
            ByRef outLength As Integer) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsCopyData
    '//
    '//  Description:
    '//      Copies data from the copy source stream to the copy destination stream. 
    '//      The read or write position of the data to copy is determined from 
    '//          the current file read or write position of the respective stream. 
    '//      After this API is executed, the read or write positions of the copy source 
    '//          and copy destination streams are moved an amount corresponding to 
    '//          inWriteSize in the positive direction. 
    '//
    '//  Parameters:
    '//       In:    inStreamRef - The reference of the stream or image.
    '//              inWriteSize - The number of bytes to copy.
    '//      Out:    outStreamRef - The reference of the stream or image.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsCopyData Lib "EDSDK" ( _
            ByVal inStreamRef As IntPtr, _
            ByVal inWriteSize As Integer, _
            ByVal OutStreamRef As IntPtr) As Integer



    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsSetProgressCallback
    '//
    '//  Description:
    '//      Register a progress callback function. 
    '//      An event is received as notification of progress during processing that 
    '//          takes a relatively long time, such as downloading files from a
    '//          remote camera. 
    '//      If you register the callback function, the EDSDK calls the callback
    '//          function during execution or on completion of the following APIs. 
    '//      This timing can be used in updating on-screen progress bars, for example.
    '//
    '//  Parameters:
    '//       In:    inRef - The reference of the stream or image.
    '//              inProgressCallback - Pointer to a progress callback function.
    '//              inProgressOption - The option about progress is specified.
    '//                              Must be one of the following values.
    '//                         kEdsProgressOption_Done 
    '//                             When processing is completed,a callback function
    '//                             is called only at once.
    '//                         kEdsProgressOption_Periodically
    '//                             A callback function is performed periodically.
    '//              inContext - Application information, passed in the argument 
    '//                      when the callback function is called. Any information 
    '//                      required for your program may be added. 
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsSetProgressCallback Lib "EDSDK" ( _
        ByVal inRef As IntPtr, _
        ByVal inProgressCallback As EdsProgressCallback, _
        ByVal inProgressOption As EdsProgressOption, _
        ByVal inContext As IntPtr) As Integer



    '/******************************************************************************
    '*******************************************************************************
    '//
    '// image operation
    '//
    '*******************************************************************************
    '******************************************************************************/


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsCreateImageRef
    '//
    '//  Description:
    '//      Creates an image object from an image file. 
    '//      Without modification, stream objects cannot be worked with as images. 
    '//      Thus, when extracting images from image files, 
    '//          you must use this API to create image objects. 
    '//      The image object created this way can be used to get image information 
    '//          (such as the height and width, number of color components, and
    '//           resolution), thumbnail image data, and the image data itself.
    '//
    '//  Parameters:
    '//       In:    inStreamRef - The reference of the stream.
    '//
    '//       Out:    outImageRef - The reference of the image.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsCreateImageRef Lib "EDSDK" ( _
        ByVal inStreamRef As IntPtr, _
        ByRef outImageRef As IntPtr) As Integer




    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetImageInfo
    '//
    '//  Description:
    '//      Gets image information from a designated image object. 
    '//      Here, image information means the image width and height, 
    '//          number of color components, resolution, and effective image area.
    '//
    '//  Parameters:
    '//       In:    inStreamRef - Designate the object for which to get image information. 
    '//              inImageSource - Of the various image data items in the image file,
    '//                  designate the type of image data representing the 
    '//                  information you want to get. Designate the image as
    '//                  defined in Enum EdsImageSource. 
    '//
    '//                      kEdsImageSrc_FullView
    '//                                  The image itself (a full-sized image) 
    '//                      kEdsImageSrc_Thumbnail
    '//                                  A thumbnail image 
    '//                      kEdsImageSrc_Preview
    '//                                  A preview image
    '//                      kEdsImageSrc_RAWThumbnail
    '//                                  A RAW thumbnail image 
    '//                      kEdsImageSrc_RAWFullView
    '//                                  A RAW full-sized image 
    '//       Out:    outImageInfo - Stores the image data information designated 
    '//                      in inImageSource. 
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetImageInfo Lib "EDSDK" ( _
            ByVal inImageRef As IntPtr, _
            ByVal inImageSource As EdsImageSource, _
            ByRef outImageInfo As EdsImageInfo) As Integer

    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsGetImage                         
    '//
    '//  Description:
    '//      Gets designated image data from an image file, in the form of a
    '//          designated rectangle. 
    '//      Returns uncompressed results for JPEGs and processed results 
    '//          in the designated pixel order (RGB, Top-down BGR, and so on) for
    '//           RAW images. 
    '//      Additionally, by designating the input/output rectangle, 
    '//          it is possible to get reduced, enlarged, or partial images. 
    '//      However, because images corresponding to the designated output rectangle 
    '//          are always returned by the SDK, the SDK does not take the aspect 
    '//          ratio into account. 
    '//      To maintain the aspect ratio, you must keep the aspect ratio in mind 
    '//          when designating the rectangle. 
    '//
    '//  Parameters:
    '//      In:     
    '//              inImageRef - Designate the image object for which to get 
    '//                      the image data.
    '//              inImageSource - Designate the type of image data to get from
    '//                      the image file (thumbnail, preview, and so on). 
    '//                      Designate values as defined in Enum EdsImageSource. 
    '//              inImageType - Designate the output image type. Because
    '//                      the output format of EdGetImage may only be RGB, only
    '//                      kEdsTargetImageType_RGB or kEdsTargetImageType_RGB16
    '//                      can be designated. 
    '//                      However, image types exceeding the resolution of 
    '//                      inImageSource cannot be designated. 
    '//              inSrcRect - Designate the coordinates and size of the rectangle
    '//                      to be retrieved (processed) from the source image. 
    '//              inDstSize - Designate the rectangle size for output. 
    '//
    '//      Out:    
    '//              outStreamRef - Designate the memory or file stream for output of
    '//                      the image.
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsGetImage Lib "EDSDK" ( _
        ByVal inImageRef As IntPtr, _
        ByVal inImageSource As EdsImageSource, _
        ByVal inImageType As EdsTargetImageType, _
        ByVal inSrcRect As EdsRect, _
        ByVal inDstSize As EdsSize, _
        ByVal outStreamRef As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsSaveImage            
    '//
    '//  Description:
    '//      Saves as a designated image type after RAW processing. 
    '//      When saving with JPEG compression, 
    '//          the JPEG quality setting applies with respect to EdsOptionRef.
    '//
    '//  Parameters:
    '//      In:    
    '//          inImageRef - Designate the image object for which to produce the file. 
    '//          inImageType - Designate the image type to produce. Designate the 
    '//                  following image types.
    '//
    '//                  kEdsTargetImageType - Jpeg  JPEG
    '//                  kEdsTargetImageType - TIFF  8-bit TIFF
    '//                  kEdsTargetImageType - TIFF16    16-bit TIFF
    '//          inSaveSetting - Designate saving options, such as JPEG image quality.
    '//      Out:    
    '//          outStreamRef - Specifies the output file stream. The memory stream 
    '//                  cannot be specified here.
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsSaveImage Lib "EDSDK" ( _
        ByVal inImageRef As IntPtr, _
        ByVal inImageType As EdsTargetImageType, _
        ByVal inSaveSetting As EdsSaveImageSetting, _
        ByVal outStreamRef As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsCacheImage                       
    '//
    '//  Description:
    '//      Switches a setting on and off for creation of an image cache in the SDK 
    '//          for a designated image object during extraction (processing) of
    '//          the image data. 
    '//          Creating the cache increases the processing speed, starting from
    '//          the second time.
    '//
    '//  Parameters:
    '//      In:     inImageRef - The reference of the image.
    '//              inUseCache - If cache image data or not
    '//                          If set to FALSE, the cached image data will released.
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsCacheImage Lib "EDSDK" ( _
         ByVal inImageRef As IntPtr, _
         ByVal inUseCache As Boolean) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsReflectImageProperty         
    '//  Description:
    '//      Incorporates image object property changes 
    '//          (effected by means of EdsSetPropertyData) in the stream. 
    '//
    '//  Parameters:
    '//      In:     inImageRef - The reference of the image.
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsReflectImageProperty Lib "EDSDK" (ByVal inImageRef As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsCreateEvfImageRef         
    '//  Description:
    '//       Creates an object used to get the live view image data set. 
    '//
    '/  Parameters:
    '//      In:     inStreamRef - The stream reference which opened to get EVF JPEG image.
    '//      Out:    outEvfImageRef - The EVFData reference.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsCreateEvfImageRef Lib "EDSDK" ( _
            ByVal inStreamRef As IntPtr, _
            ByRef outEvfImageRef As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsDownloadEvfImage         
    '//  Description:
    '//		Downloads the live view image data set for a camera currently in live view mode.
    '//		Live view can be started by using the property ID:kEdsPropertyID_Evf_OutputDevice and
    '//		data:EdsOutputDevice_PC to call EdsSetPropertyData.
    '//		In addition to image data, information such as zoom, focus position, and histogram data
    '//		is included in the image data set. Image data is saved in a stream maintained by EdsEvfImageRef.
    '//		EdsGetPropertyData can be used to get information such as the zoom, focus position, etc.
    '//		Although the information of the zoom and focus position can be obtained from EdsEvfImageRef,
    '//		settings are applied to EdsCameraRef.
    '//
    '//  Parameters:
    '//      In:     inCameraRef - The Camera reference.
    '//      In:     inEvfImageRef - The EVFData reference.
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsDownloadEvfImage Lib "EDSDK" ( _
                ByVal inCameraRef As IntPtr, _
                ByVal inEvfImageRef As IntPtr) As Integer

    '/******************************************************************************
    '*******************************************************************************
    '//
    '// event handler
    '//
    '*******************************************************************************
    '******************************************************************************/


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsSetCameraAddedHandler
    '//
    '//  Description:
    '//      Registers a callback function for when a camera is detected.
    '//
    '//  Parameters:
    '//       In:    inCameraAddedHandler - Pointer to a callback function
    '//                          called when a camera is connected physically
    '//              inContext - Specifies an application-defined value to be sent to
    '//                          the callback function pointed to by CallBack parameter.
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsSetCameraAddedHandler Lib "EDSDK" ( _
            ByVal inCameraAddedHandler As EdsCameraAddedHandler, _
            ByVal inContext As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsSetPropertyEventHandler
    '//              
    '//  Description:
    '//       Registers a callback function for receiving status 
    '//          change notification events for property states on a camera.
    '//
    '//  Parameters:
    '//       In:    inCameraRef - Designate the camera object. 
    '//              inEvent - Designate one or all events to be supplemented.
    '//              inPropertyEventHandler - Designate the pointer to the callback
    '//                      function for receiving property-related camera events.
    '//              inContext - Designate application information to be passed by 
    '//                      means of the callback function. Any data needed for
    '//                      your application can be passed. 
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsSetPropertyEventHandler Lib "EDSDK" ( _
        ByVal inCameraRef As IntPtr, _
        ByVal inEvnet As Integer, _
        ByVal inPropertyEventHandler As EdsPropertyEventHandler, _
        ByVal inContext As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:   EdsSetObjectEventHandler
    '//              
    '//  Description:
    '//       Registers a callback function for receiving status 
    '//          change notification events for objects on a remote camera. 
    '//      Here, object means volumes representing memory cards, files and directories, 
    '//          and shot images stored in memory, in particular. 
    '//
    '//  Parameters:
    '//       In:    inCameraRef - Designate the camera object. 
    '//              inEvent - Designate one or all events to be supplemented.
    '//                  To designate all events, use kEdsObjectEvent_All. 
    '//              inObjectEventHandler - Designate the pointer to the callback function
    '//                  for receiving object-related camera events.
    '//              inContext - Passes inContext without modification,
    '//                  as designated as an EdsSetObjectEventHandler argument. 
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsSetObjectEventHandler Lib "EDSDK" ( _
        ByVal inCameraRef As IntPtr, _
        ByVal inEvnet As Integer, _
        ByVal inObjectEventHandler As EdsObjectEventHandler, _
        ByVal inContext As IntPtr) As Integer


    '/*-----------------------------------------------------------------------------
    '//
    '//  Function:  EdsSetCameraStateEventHandler
    '//              
    '//  Description:
    '//      Registers a callback function for receiving status 
    '//          change notification events for property states on a camera.
    '//
    '//  Parameters:
    '//       In:    inCameraRef - Designate the camera object. 
    '//              inEvent - Designate one or all events to be supplemented.
    '//                  To designate all events, use kEdsStateEvent_All. 
    '//              inStateEventHandler - Designate the pointer to the callback function
    '//                  for receiving events related to camera object states.
    '//              inContext - Designate application information to be passed
    '//                  by means of the callback function. Any data needed for
    '//                  your application can be passed. 
    '//      Out:    None
    '//
    '//  Returns:    Any of the sdk errors.
    '-----------------------------------------------------------------------------*/
    Public Declare Function EdsSetCameraStateEventHandler Lib "EDSDK" ( _
        ByVal inCameraRef As IntPtr, _
        ByVal inEvnet As Integer, _
        ByVal inStateEventHandler As EdsStateEventHandler, _
        ByVal inContext As IntPtr) As Integer

End Module
