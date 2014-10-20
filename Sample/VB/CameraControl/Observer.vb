'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : Observer.vb                                                     *
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
Imports System
Imports System.Runtime.InteropServices



Public Interface Observer
    Sub update(ByVal from As Observable, ByVal msg As Integer, ByVal data As Integer)
End Interface



Public Class Observable
    Private m_numof_ob As Integer

    Private m_observers() As Observer


    Public Sub New()
        m_numof_ob = -1 ' ArraySize = 0
    End Sub

    Protected Overrides Sub Finalize()
        deleteObservers()
    End Sub

    '// Add an observer.
    Public Sub addObserver(ByVal ob As Object)

        m_numof_ob = m_numof_ob + 1
        ReDim Preserve m_observers(m_numof_ob)
        m_observers(m_numof_ob) = ob

    End Sub

    '// Delete an observer .
    Public Sub deleteObserver(ByVal ob As Observer)

        Dim iCnt As Integer

        If m_numof_ob <= 0 Then

            ReDim m_observers(-1)
            m_numof_ob = -1

        Else
            For iCnt = 0 To m_numof_ob
                If m_observers(iCnt) Is ob Then
                    Do
                        m_observers(iCnt) = m_observers(iCnt + 1)
                        iCnt = iCnt + 1
                    Loop Until iCnt = m_numof_ob
                End If
            Next

            m_observers(m_numof_ob) = Nothing
            m_numof_ob = m_numof_ob - 1
            ReDim Preserve m_observers(m_numof_ob)

        End If

    End Sub


    '// Notify to observers.
    Public Sub notifyObservers(ByVal msg As Integer, Optional ByVal data As Integer = 0)

        Dim iCnt As Integer

        For iCnt = m_numof_ob To 0 Step -1

            m_observers(iCnt).update(Me, msg, data)
            iCnt = iCnt - 1

        Next

    End Sub


    Public Sub deleteObservers()
        Dim icnt As Integer

        For icnt = 0 To m_numof_ob
            m_observers(icnt) = Nothing
        Next

        ' Set the number of observer as 0.
        m_numof_ob = 0

    End Sub


    Public Function countObservers() As Integer
        Return m_numof_ob

    End Function

End Class
