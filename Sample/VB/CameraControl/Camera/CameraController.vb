'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : CameraController.vb                                             *
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



Public Class CameraController

    '// Camera model
    Protected model As CameraModel

    '// Command processing
    Protected processor As New Processor


    '// Constractor
    Public Sub New()
        model = Nothing
    End Sub

    '// Destructor
    Protected Overrides Sub Finalize()
    End Sub


    Public Sub setCameraModel(ByVal model As CameraModel)
        Me.model = model
    End Sub


    '// Start processor thread   
    Public Sub run()

        processor.start()

        'The communication with the camera begins
        StoreAsync(New OpenSessionCommand(model))

    End Sub


    Public Sub actionPerformed(ByVal strEvent As String, ByVal inObject As IntPtr)
        If strEvent = "download" Then
            StoreAsync(New DownloadCommand(model, inObject)) ' 
        End If
    End Sub


    Public Sub actionPerformed(ByVal strEvent As String)

        If strEvent = "opensession" Then

            '// Start communication with remote camera.
            StoreAsync(New OpenSessionCommand(model))

        ElseIf strEvent = "takepicture" Then
            StoreAsync(New TakePictureCommand(model))

        ElseIf strEvent = "close" Then
            model.notifyObservers(clse)
            processor.setCloseCommand(New CloseSessionCommand(model))
            processor.stopTh()
            processor.join()
        End If

    End Sub


    Public Sub actionPerformed(ByVal strEvent As String, ByVal id As Integer, Optional ByVal data As Integer = 0)
        If strEvent = "get" Then
            StoreAsync(New GetPropertyCommand(model, id))

        ElseIf strEvent = "set" Then
            StoreAsync(New SetPropertyCommand(model, id, data))

        ElseIf strEvent = "getlist" Then
            StoreAsync(New GetPropertyDescCommand(model, id))

        End If

    End Sub


    '// Receive a command
    Protected Sub StoreAsync(ByVal command As Command)
        If IsNothing(command) = False Then
            processor.enqueue(command)

        End If

    End Sub


End Class
