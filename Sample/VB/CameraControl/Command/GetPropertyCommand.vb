'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : GetPropertyCommand.vb                                           *
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


Public Class GetPropertyCommand
    Inherits Command

    Private propertyID As Integer


    Public Sub New(ByVal model As CameraModel, ByVal propertyID As Integer)
        MyBase.new(model)
        Me.propertyID = propertyID
    End Sub

    '// Execute a command.	
    Public Overrides Function execute() As Boolean

        Dim err As Integer = EDS_ERR_OK
        Dim locked As Boolean = False

        '// You should do UILock when you send a command to camera models elder than EOS30D.
        If MyBase.model.isLegacy() Then

            err = EdsSendStatusCommand(MyBase.model.getCameraObject(), EdsCameraStatusCommand.kEdsCameraStatusCommand_UILock, 0)

            If err = EDS_ERR_OK Then

                locked = True

            End If

        End If

        '//Get a property.
        If err = EDS_ERR_OK Then

            err = getProperty(Me.propertyID)

        End If

        If locked Then

            err = EdsSendStatusCommand(MyBase.model.getCameraObject(), EdsCameraStatusCommand.kEdsCameraStatusCommand_UIUnLock, 0)

        End If

        '// Notify Error.
        If err <> EDS_ERR_OK Then

            '// Retry when the camera replys deviceBusy.
            If (err & EDS_ERRORID_MASK) = EDS_ERR_DEVICE_BUSY Then

                MyBase.model.notifyObservers(warn, err)

                Return False

            End If

            MyBase.model.notifyObservers(errr, err)

        End If

        Return True

    End Function


    Private Function getProperty(ByVal id As Integer) As Integer
        Dim err As Integer = EDS_ERR_OK
        Dim dataType As EdsDataType = EdsDataType.kEdsDataType_Unknown
        Dim dataSize As Integer = 0


        If id = kEdsPropID_Unknown Then
            '// If the propertyID is invalidID,
            '// you should retry to get properties.
            '// InvalidID is able to be published for the models elder than EOS30D.

            If err = EDS_ERR_OK Then
                err = getProperty(kEdsPropID_AEMode)
            End If
            If err = EDS_ERR_OK Then
                err = getProperty(kEdsPropID_Tv)
            End If
            If err = EDS_ERR_OK Then
                err = getProperty(kEdsPropID_Av)
            End If
            If err = EDS_ERR_OK Then
                err = getProperty(kEdsPropID_ISOSpeed)
            End If
            If err = EDS_ERR_OK Then
                err = getProperty(kEdsPropID_ImageQuality)
            End If

            Return err
        End If

        '// Get propertysize.
        If err = EDS_ERR_OK Then

            err = EdsGetPropertySize( _
                    MyBase.model.getCameraObject(), _
                    id, _
                    0, _
                    dataType, _
                    dataSize)

        End If

        If err = EDS_ERR_OK Then

            Dim data As Integer
            If dataType = EdsDataType.kEdsDataType_UInt32 Then
                '// Get a property.
                Dim ptr As IntPtr = Marshal.AllocHGlobal(dataSize)

                err = EdsGetPropertyData(MyBase.model.getCameraObject(), _
                      id, _
                      0, _
                      dataSize, _
                      ptr)

                data = Marshal.PtrToStructure(ptr, GetType(Integer))
                Marshal.FreeHGlobal(ptr)

                If err = EDS_ERR_OK Then

                    MyBase.model.setPropertyUInt32(id, data)

                End If
            End If

            If dataType = EdsDataType.kEdsDataType_String Then

                Dim str As String 'char[EDS_MAX_NAME]
                Dim ptr As IntPtr = Marshal.AllocHGlobal(EDS_MAX_NAME)

                '// Get a property.
                err = EdsGetPropertyData(MyBase.model.getCameraObject(), _
                      id, _
                      0, _
                      dataSize, _
                      ptr)

                str = Marshal.PtrToStringAnsi(ptr)
                Marshal.FreeHGlobal(ptr)

                '// Stock the property .
                If err = EDS_ERR_OK Then

                    MyBase.model.setPropertyString(id, str)

                End If
            End If

        End If


        '// Notify updating.
        If err = EDS_ERR_OK Then

            MyBase.model.notifyObservers(updt, id)

        End If

        Return err

    End Function

End Class
