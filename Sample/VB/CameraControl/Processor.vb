'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : Processor.vb                                                    *
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

Imports System.Object
Imports System.Threading


Public Class Processor

    Protected thread As Thread


    '// Flag for this thread running or not
    Protected running As Boolean

    '// queue  
    Protected queue As New Queue

    '// End application command
    Protected closeCommand As Command

    '// Sync object
    Protected ReadOnly syncObject As New Object


    Public Sub New()
        Me.running = False
        Me.closeCommand = Nothing
        Me.thread = New Thread(AddressOf run)
    End Sub


    Protected Overrides Sub Finalize()
        clear()
    End Sub



    '// Set end application command
    Public Sub setCloseCommand(ByVal closeCommand As Command)
        Me.closeCommand = closeCommand
    End Sub


    Public Sub enqueue(ByVal command As Command)

        If IsNothing(command) = True Then
            End
        End If

        Try
            Monitor.Enter(syncObject)

            Me.queue.Enqueue(command)

            Monitor.PulseAll(syncObject)

        Finally
            Monitor.Exit(syncObject)
        End Try

    End Sub



    Public Sub stopTh()

        Try
            Monitor.Enter(syncObject)

            Me.running = False

            Monitor.PulseAll(syncObject)

        Finally

            Monitor.Exit(syncObject)

        End Try

    End Sub


    Public Sub join()
        thread.Join()
        thread = Nothing

    End Sub


    Public Sub clear()

        Monitor.Enter(syncObject)

        Try

            Me.queue.Clear()

        Finally

            Monitor.Exit(syncObject)

        End Try
    End Sub


    Public Sub start()

        Me.thread.Start()

    End Sub



    Public Sub run()

        Me.running = True

        While Me.running

            System.Threading.Thread.Sleep(1)

            Dim command As Command = take()

            If IsNothing(command) = False Then

                Dim complete As Boolean = command.execute()

                If complete = False Then
                    ' >Retry 
                    ' When a command execution failed with DeviceBusy or some errors,
                    ' and you want to set some retrying sequence, you should sleep _
                    ' about 500 micro seconds because it makes camera unstable.
                    thread.Sleep(500)

                    enqueue(command)
                Else
                    command = Nothing
                End If

            End If

        End While

        '// Clear the queue.
        clear()

        '// End application
        If IsNothing(closeCommand) = False Then
            Me.closeCommand.execute()
            Me.closeCommand = Nothing
        End If

    End Sub


    '//take a command from the queue
    Protected Function take() As Command

        Dim command As Command = Nothing


        Try
            Monitor.Enter(syncObject)

            '// Wait when the queue is empty.
            While queue.Count = 0 And running = True
                Monitor.Wait(syncObject)
            End While


            If running = True Then
                command = queue.Dequeue()
            End If

            Monitor.PulseAll(syncObject)

        Finally
            Monitor.Exit(syncObject)
        End Try


        Return command

    End Function


End Class
