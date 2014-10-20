'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : CameraEventListener.vb                                          *
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

Option Strict Off
Option Explicit On 
Imports System.Runtime.InteropServices


Public Class CameraEventListener

    Public Shared Function handleObjectEvent( _
      ByVal inEvent As Integer, _
      ByVal inRef As IntPtr, _
      ByVal inContext As IntPtr) As Long

        Dim rtn As Long

        Select Case inEvent
            Case kEdsObjectEvent_DirItemRequestTransfer
                VBSample.controller.actionPerformed("download", inRef)

            Case Else
                '//Release unnecessary objects.
                If IsNothing(inRef) = False Then
                    EdsRelease(inRef)
                End If

        End Select

        rtn = CLng(EDS_ERR_OK)
        Return rtn

    End Function


    Public Shared Function handlePropertyEvent( _
         ByVal inEvent As Integer, _
         ByVal inPropertyID As Integer, _
         ByVal inParam As Integer, _
         ByVal inContext As IntPtr) As Long

        Dim rtn As Long

        Select Case inEvent
            Case kEdsPropertyEvent_PropertyChanged
                VBSample.controller.actionPerformed("get", inPropertyID)
            Case kEdsPropertyEvent_PropertyDescChanged
                VBSample.controller.actionPerformed("getlist", inPropertyID)
        End Select


        rtn = CLng(EDS_ERR_OK)
        Return rtn

    End Function


    Public Shared Function handleStateEvent( _
          ByVal inEvent As Integer, _
          ByVal inParam As Integer, _
          ByVal inContext As IntPtr) As Long

        Dim rtn As Long

        Select Case inEvent
            Case kEdsStateEvent_Shutdown
                VBSample.controller.actionPerformed("clse")

        End Select


        rtn = CLng(EDS_ERR_OK)
        Return rtn

    End Function


End Class
