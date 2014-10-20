'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : Command.vb                                                      *
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

Public Module commandName
    ' Command IDs
    Public Const errr As Integer = 1 'errr
    Public Const prog As Integer = 2 'prog
    Public Const strt As Integer = 3 'strt
    Public Const cplt As Integer = 4 'cplt
    Public Const warn As Integer = 5 'warn
    Public Const updt As Integer = 6 'updt
    Public Const upls As Integer = 7 'upls
    Public Const clse As Integer = 1 'close
End Module



' Abstract command class. 
' All command classes extends this one.
Public Class Command

    Protected model As CameraModel

    Public Sub New(ByVal model As CameraModel)
        Me.model = model
    End Sub


    '// Execute a command.
    Public Overridable Function execute() As Boolean
    End Function

End Class
