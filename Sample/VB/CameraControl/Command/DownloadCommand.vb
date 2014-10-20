'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : DownloadCommand.vb                                              *
'*                                                                             *
'*   Description: This is the Sample code to show the usage of EDSDK.          *
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
'*   06-03-22    F-001        create first version.                            *
'*                                                                             *
'******************************************************************************/

Option Explicit On
Imports System.Runtime.InteropServices



Public Class DownloadCommand
    Inherits Command

    Private directoryItem As IntPtr
    Public inProgressCallback As New _
                EdsProgressCallback(AddressOf ProgressFunc)


    Public Sub New(ByVal inModel As CameraModel, ByVal dirItem As IntPtr)
        MyBase.new(inModel)
        Me.directoryItem = dirItem
    End Sub

    Protected Overrides Sub Finalize()
        '// Release item.
        If IsNothing(Me.directoryItem) = False Then
            EdsRelease(Me.directoryItem)
            Me.directoryItem = Nothing

        End If
    End Sub


    '// Execute a command .
    Public Overrides Function execute() As Boolean

        Dim err As Integer = EDS_ERR_OK
        Dim stream As IntPtr = Nothing

        '// Get informations of the downloadling directory item.
        Dim dirItemInfo As EdsDirectoryItemInfo = Nothing
        err = EdsGetDirectoryItemInfo(Me.directoryItem, dirItemInfo)

        '// Notify starting transfer.
        If err = EDS_ERR_OK Then
            VBSample.model.notifyObservers(strt)
        End If

        '// Create a file stream for receiving image.
        If err = EDS_ERR_OK Then
            err = EdsCreateFileStream(dirItemInfo.szFileName, EdsFileCreateDisposition.kEdsFileCreateDisposition_CreateAlways, _
                                    EdsAccess.kEdsAccess_ReadWrite, stream)
        End If

        '// Set Progress Callback.
        If err = EDS_ERR_OK Then

            Dim gch As GCHandle = GCHandle.Alloc(Me)
            err = EdsSetProgressCallback(stream, inProgressCallback, _
                                            EdsProgressOption.kEdsProgressOption_Periodically, _
                                            GCHandle.op_Explicit(gch))
        End If

        '// Download image
        If err = EDS_ERR_OK Then

            err = EdsDownload(Me.directoryItem, dirItemInfo.size, stream)

        End If

        '// Complete downloading
        If err = EDS_ERR_OK Then

            err = EdsDownloadComplete(directoryItem)

        End If

        '// Release item
        If IsNothing(Me.directoryItem) = False Then

            err = EdsRelease(Me.directoryItem)
            directoryItem = Nothing

        End If

        '// Release the stream
        If IsNothing(stream) = False Then

            err = EdsRelease(stream)
            stream = Nothing

        End If

        '// Notify to complete downloading 
        If err = EDS_ERR_OK Then

            MyBase.model.notifyObservers(cplt)

        End If

        '// Notify Error
        If err <> EDS_ERR_OK Then
            MyBase.model.notifyObservers(errr, err)
        End If

        Return True

    End Function


    Public Shared Function ProgressFunc(ByVal inPercent As Integer, _
     ByVal inContext As IntPtr, ByRef outCancel As Boolean) As Long

        Dim rtn As Long = CLng(EDS_ERR_OK)

        VBSample.model.notifyObservers(prog, inPercent)

        Return rtn

    End Function



End Class
