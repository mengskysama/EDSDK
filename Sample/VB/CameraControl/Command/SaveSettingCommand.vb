'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : SaveSettingCommand.vb                                           *
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

Public Class SaveSettingCommand
    Inherits Command

    Private saveTo As EdsSaveTo

    Public Sub New(ByVal model As CameraModel, ByVal saveTo As EdsSaveTo)
        MyBase.new(model)
        saveTo = saveTo
    End Sub


    '// Execute a command.
    Public Overrides Function execute() As Boolean

        Dim err As Integer = EDS_ERR_OK
        Dim lock As Boolean = False

        '// You should do UILock when you send a command to camera models elder than EOS30D.
        If MyBase.model.isLegacy() Then

            err = EdsSendStatusCommand(MyBase.model.getCameraObject(), EdsCameraStatusCommand.kEdsCameraStatusCommand_UILock, 0)

            If err = EDS_ERR_OK Then

                lock = True

            End If
        End If

        '//Set destination of file save.
        If err = EDS_ERR_OK Then


            Dim ptr As IntPtr = Marshal.AllocHGlobal(Marshal.SizeOf(Me.saveTo))
            Marshal.StructureToPtr(Me.saveTo, ptr, False)

            err = EdsSetPropertyData(MyBase.model.getCameraObject(), _
                                    kEdsPropID_SaveTo, 0, Marshal.SizeOf(Me.saveTo), Me.saveTo)

            Marshal.FreeHGlobal(ptr)
        End If

        If lock = True Then

            err = EdsSendStatusCommand(MyBase.model.getCameraObject(), EdsCameraStatusCommand.kEdsCameraStatusCommand_UIUnLock, 0)

        End If

        '// Notify Error.
        If err <> EDS_ERR_OK Then

            '// Retry when the camera replys deviceBusy.
            If err = EDS_ERR_DEVICE_BUSY Then
                MyBase.model.notifyObservers(warn, err)
                Threading.Thread.Sleep(500)
                Return False

            End If

            MyBase.model.notifyObservers(errr, err)

        End If

        Return True

    End Function

End Class
