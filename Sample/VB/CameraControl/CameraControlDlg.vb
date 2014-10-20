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

Imports System.Runtime.InteropServices

Public Class VBSample
    Inherits System.Windows.Forms.Form
    Implements Observer

#Region "Created by Windows form designer."

    Public Sub New()
        MyBase.New()

        InitializeComponent()


    End Sub

    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    Private components As System.ComponentModel.IContainer

    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents TakeBtn As System.Windows.Forms.Button
    Friend WithEvents ISOSpeedCmb As System.Windows.Forms.ComboBox
    Friend WithEvents AvCmb As System.Windows.Forms.ComboBox
    Friend WithEvents TvCmb As System.Windows.Forms.ComboBox
    Private WithEvents AEModeCmb As System.Windows.Forms.ComboBox
    Friend WithEvents MeteringModeCmb As System.Windows.Forms.ComboBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents ExposureCompCmb As System.Windows.Forms.ComboBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents ExitBtn As System.Windows.Forms.Button
    Friend WithEvents InfoTextBox As System.Windows.Forms.TextBox
    Friend WithEvents ImageQualityCmb As System.Windows.Forms.ComboBox
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents progressBar As System.Windows.Forms.ProgressBar
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.TakeBtn = New System.Windows.Forms.Button
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label3 = New System.Windows.Forms.Label
        Me.Label5 = New System.Windows.Forms.Label
        Me.Label6 = New System.Windows.Forms.Label
        Me.AEModeCmb = New System.Windows.Forms.ComboBox
        Me.ISOSpeedCmb = New System.Windows.Forms.ComboBox
        Me.AvCmb = New System.Windows.Forms.ComboBox
        Me.TvCmb = New System.Windows.Forms.ComboBox
        Me.MeteringModeCmb = New System.Windows.Forms.ComboBox
        Me.Label1 = New System.Windows.Forms.Label
        Me.ExposureCompCmb = New System.Windows.Forms.ComboBox
        Me.Label4 = New System.Windows.Forms.Label
        Me.ExitBtn = New System.Windows.Forms.Button
        Me.InfoTextBox = New System.Windows.Forms.TextBox
        Me.progressBar = New System.Windows.Forms.ProgressBar
        Me.ImageQualityCmb = New System.Windows.Forms.ComboBox
        Me.Label7 = New System.Windows.Forms.Label
        Me.SuspendLayout()
        '
        'TakeBtn
        '
        Me.TakeBtn.Location = New System.Drawing.Point(297, 148)
        Me.TakeBtn.Name = "TakeBtn"
        Me.TakeBtn.Size = New System.Drawing.Size(96, 48)
        Me.TakeBtn.TabIndex = 0
        Me.TakeBtn.Text = "Take Picture"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label2.Location = New System.Drawing.Point(12, 19)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(53, 12)
        Me.Label2.TabIndex = 6
        Me.Label2.Text = "AE Mode:"
        Me.Label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label3.Location = New System.Drawing.Point(12, 115)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(25, 12)
        Me.Label3.TabIndex = 7
        Me.Label3.Text = "ISO:"
        Me.Label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label5.Location = New System.Drawing.Point(12, 83)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(21, 12)
        Me.Label5.TabIndex = 9
        Me.Label5.Text = "Av:"
        Me.Label5.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label6.Location = New System.Drawing.Point(12, 51)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(20, 12)
        Me.Label6.TabIndex = 10
        Me.Label6.Text = "Tv:"
        Me.Label6.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'AEModeCmb
        '
        Me.AEModeCmb.Location = New System.Drawing.Point(115, 16)
        Me.AEModeCmb.Name = "AEModeCmb"
        Me.AEModeCmb.Size = New System.Drawing.Size(166, 20)
        Me.AEModeCmb.TabIndex = 11
        '
        'ISOSpeedCmb
        '
        Me.ISOSpeedCmb.Location = New System.Drawing.Point(115, 112)
        Me.ISOSpeedCmb.Name = "ISOSpeedCmb"
        Me.ISOSpeedCmb.Size = New System.Drawing.Size(166, 20)
        Me.ISOSpeedCmb.TabIndex = 12
        '
        'AvCmb
        '
        Me.AvCmb.Location = New System.Drawing.Point(115, 80)
        Me.AvCmb.Name = "AvCmb"
        Me.AvCmb.Size = New System.Drawing.Size(166, 20)
        Me.AvCmb.TabIndex = 14
        '
        'TvCmb
        '
        Me.TvCmb.Location = New System.Drawing.Point(115, 48)
        Me.TvCmb.Name = "TvCmb"
        Me.TvCmb.Size = New System.Drawing.Size(166, 20)
        Me.TvCmb.TabIndex = 15
        '
        'MeteringModeCmb
        '
        Me.MeteringModeCmb.Location = New System.Drawing.Point(115, 143)
        Me.MeteringModeCmb.Name = "MeteringModeCmb"
        Me.MeteringModeCmb.Size = New System.Drawing.Size(166, 20)
        Me.MeteringModeCmb.TabIndex = 17
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.ForeColor = System.Drawing.Color.Black
        Me.Label1.Location = New System.Drawing.Point(12, 146)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(82, 12)
        Me.Label1.TabIndex = 16
        Me.Label1.Text = "Metering Mode:"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'ExposureCompCmb
        '
        Me.ExposureCompCmb.Location = New System.Drawing.Point(115, 176)
        Me.ExposureCompCmb.Name = "ExposureCompCmb"
        Me.ExposureCompCmb.Size = New System.Drawing.Size(166, 20)
        Me.ExposureCompCmb.TabIndex = 19
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label4.Location = New System.Drawing.Point(12, 179)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(87, 12)
        Me.Label4.TabIndex = 18
        Me.Label4.Text = "Exposure Comp:"
        Me.Label4.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'ExitBtn
        '
        Me.ExitBtn.Location = New System.Drawing.Point(313, 16)
        Me.ExitBtn.Name = "ExitBtn"
        Me.ExitBtn.Size = New System.Drawing.Size(80, 32)
        Me.ExitBtn.TabIndex = 4
        Me.ExitBtn.Text = "Quit"
        '
        'InfoTextBox
        '
        Me.InfoTextBox.BackColor = System.Drawing.SystemColors.InactiveBorder
        Me.InfoTextBox.Location = New System.Drawing.Point(12, 246)
        Me.InfoTextBox.Name = "InfoTextBox"
        Me.InfoTextBox.Size = New System.Drawing.Size(381, 19)
        Me.InfoTextBox.TabIndex = 20
        Me.InfoTextBox.Text = "Info"
        '
        'progressBar
        '
        Me.progressBar.Location = New System.Drawing.Point(297, 215)
        Me.progressBar.Name = "progressBar"
        Me.progressBar.Size = New System.Drawing.Size(96, 16)
        Me.progressBar.TabIndex = 21
        '
        'ImageQualityCmb
        '
        Me.ImageQualityCmb.Location = New System.Drawing.Point(115, 211)
        Me.ImageQualityCmb.Name = "ImageQualityCmb"
        Me.ImageQualityCmb.Size = New System.Drawing.Size(166, 20)
        Me.ImageQualityCmb.TabIndex = 22
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label7.Location = New System.Drawing.Point(12, 214)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(73, 12)
        Me.Label7.TabIndex = 23
        Me.Label7.Text = "ImageQuality:"
        Me.Label7.TextAlign = System.Drawing.ContentAlignment.MiddleRight
        '
        'VBSample
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 12)
        Me.ClientSize = New System.Drawing.Size(405, 276)
        Me.Controls.Add(Me.Label7)
        Me.Controls.Add(Me.ImageQualityCmb)
        Me.Controls.Add(Me.progressBar)
        Me.Controls.Add(Me.InfoTextBox)
        Me.Controls.Add(Me.ExposureCompCmb)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.MeteringModeCmb)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.TvCmb)
        Me.Controls.Add(Me.AvCmb)
        Me.Controls.Add(Me.ISOSpeedCmb)
        Me.Controls.Add(Me.AEModeCmb)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.ExitBtn)
        Me.Controls.Add(Me.TakeBtn)
        Me.ForeColor = System.Drawing.SystemColors.ControlText
        Me.MaximizeBox = False
        Me.Name = "VBSample"
        Me.Text = "VBSample"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

#End Region


#Region "User defined attributes"

    ' Save as class variable, new delegates of event handlers.
    Public inPropertyEventHandler As New _
                EdsPropertyEventHandler(AddressOf CameraEventListener.handlePropertyEvent)
    Public inObjectEventHandler As New _
                EdsObjectEventHandler(AddressOf CameraEventListener.handleObjectEvent)
    Public inStateEventHandler As New _
                EdsStateEventHandler(AddressOf CameraEventListener.handleStateEvent)
    '
    Public Shared controller As CameraController
    Public Shared model As CameraModel
    Public Shared m_cmbTbl As Hashtable = New Hashtable



#End Region


    Delegate Sub UpdateDelegate( _
        ByVal from As Observable, _
        ByVal msg As Integer, _
        ByVal data As Integer)

    Sub UpdateWindow(ByVal from As Observable, ByVal msg As Integer, ByVal data As Integer) _
        Implements Observer.update

        'Get the name of this thread.
        Dim threadName As String = _
        System.Threading.Thread.CurrentThread.Name()

        '// Make this form be able to be updated by other thread.
        If InvokeRequired Then
            'Create UpdateDelegate
            Dim dlg As New UpdateDelegate(AddressOf UpdateWindow)
            Try
                BeginInvoke(dlg, New Object() {from, msg, data})
            Catch e As Exception
                Return
            Finally
            End Try
            Return
        End If



        Select Case msg
            Case prog '//Progress of image downloading .
                progressBar.Value = data

            Case strt '// Start downloading.
                '//_progress.SetPos(0);

            Case cplt '// Complete downloading.
                progressBar.Value = 0

            Case updt '// Update properties.
                Dim propertyID As Integer = data
                Dim propData As Integer = model.getPropertyUInt32(propertyID)
                UpdateProperty(propertyID, propData)

            Case upls '// Update an available property list.
                Dim propertyID As Integer = data
                Dim desc As EdsPropertyDesc = model.getPropertyDesc(propertyID)
                UpdatePropertyDesc(propertyID, desc)

            Case warn '// Warning
                InfoTextBox.Text = "Device Busy"

            Case errr '// Error
                '// Nothing to do because the first getting property from model 30D is sure to fail. 
                Dim ss As String
                ss = String.Format("%x", data)
                InfoTextBox.Text = ss

            Case clse '// Close
                TakeBtn.Enabled = False
                progressBar.Enabled = False
                InfoTextBox.Enabled = False
                AEModeCmb.Enabled = False
                TvCmb.Enabled = False
                AvCmb.Enabled = False
                ISOSpeedCmb.Enabled = False

        End Select

        If msg <> errr And msg <> warn Then
            InfoTextBox.Text = ""
        End If


    End Sub



    Sub UpdateProperty(ByVal propertyID As Integer, ByVal data As Integer)
        Dim propList As Hashtable = CameraProperty.g_PropList.Item(propertyID)
        Select Case propertyID
            Case kEdsPropID_AEMode
                AEModeCmb.Text = propList.Item(data)
            Case kEdsPropID_ISOSpeed
                ISOSpeedCmb.Text = propList.Item(data)
            Case kEdsPropID_MeteringMode
                MeteringModeCmb.Text = propList.Item(data)
            Case kEdsPropID_Av
                AvCmb.Text = propList.Item(data)
            Case kEdsPropID_Tv
                TvCmb.Text = propList.Item(data)
            Case kEdsPropID_ExposureCompensation
                ExposureCompCmb.Text = propList.Item(data)
            Case kEdsPropID_ImageQuality
                ImageQualityCmb.Text = propList.Item(data)
        End Select

    End Sub



    Sub UpdatePropertyDesc(ByVal propertyID As Integer, ByVal desc As EdsPropertyDesc)
        Dim err As Integer
        Dim iCnt As Integer
        Dim cmb As ComboBox = m_cmbTbl.Item(propertyID)
        Dim propList As Hashtable = CameraProperty.g_PropList.Item(propertyID)
        Dim propStr As String
        Dim propValueList As ArrayList = New ArrayList

        If cmb Is Nothing Then
            Return
        End If

        cmb.BeginUpdate()
        cmb.Items.Clear()
        For iCnt = 0 To desc.numElements - 1
            propStr = propList(desc.propDesc(iCnt))
            If propStr <> Nothing Then
                err = cmb.Items.Add(propStr)
                propValueList.Add(desc.propDesc(iCnt))
            End If
        Next

        cmb.Tag = propValueList ' Set the property value list

        cmb.EndUpdate()
        If cmb.Items.Count = 0 Then
            cmb.Enabled = False '// No available item.
        Else
            cmb.Enabled = True
        End If

    End Sub



    Public Function cameraModelFactory(ByVal camera As IntPtr, ByVal deviceInfo As EdsDeviceInfo) As CameraModel

        ' if Legacy protocol.
        If deviceInfo.DeviceSubType = 0 Then
            Return New CameraModelLegacy(camera)
        End If

        ' PTP protocol.
        Return New CameraModel(camera)

    End Function



#Region "Window Events"
    Private Sub TakeBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TakeBtn.Click
        '
        ' Release button
        '
        controller.actionPerformed("takepicture")

    End Sub



    Private Sub ExitBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ExitBtn.Click
        ' Quit button
        Me.Close()

        End
    End Sub

#End Region


    Private Sub VBSample_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

        Dim err As Integer = EDS_ERR_OK
        Dim cameraList As IntPtr = Nothing
        Dim camera As IntPtr = Nothing
        Dim count As Integer = 0
        Dim isSDKLoaded As Boolean = False
        Dim propObj As New CameraProperty

        ' connect property id to combobox. 
        m_cmbTbl.Add(kEdsPropID_AEMode, Me.AEModeCmb)
        m_cmbTbl.Add(kEdsPropID_ISOSpeed, Me.ISOSpeedCmb)
        m_cmbTbl.Add(kEdsPropID_Av, Me.AvCmb)
        m_cmbTbl.Add(kEdsPropID_Tv, Me.TvCmb)
        m_cmbTbl.Add(kEdsPropID_MeteringMode, Me.MeteringModeCmb)
        m_cmbTbl.Add(kEdsPropID_ExposureCompensation, Me.ExposureCompCmb)
        m_cmbTbl.Add(kEdsPropID_ImageQuality, Me.ImageQualityCmb)


        err = EdsInitializeSDK()


        If err = EDS_ERR_OK Then

            isSDKLoaded = True

        End If

        If err = EDS_ERR_OK Then

            err = EdsGetCameraList(cameraList)

        End If


        If err = EDS_ERR_OK Then

            err = EdsGetChildCount(cameraList, count)
            If count = 0 Then
                err = EDS_ERR_DEVICE_NOT_FOUND
            End If

        End If

        '// Get the first camera.
        If err = EDS_ERR_OK Then

            err = EdsGetChildAtIndex(cameraList, 0, camera)

        End If


        Dim deviceInfo As EdsDeviceInfo = Nothing

        If err = EDS_ERR_OK Then

            err = EdsGetDeviceInfo(camera, deviceInfo)

            If err = EDS_ERR_OK And IsNothing(camera) = True Then
                err = EDS_ERR_DEVICE_NOT_FOUND
            End If

        End If


        If IsNothing(cameraList) = False Then

            EdsRelease(cameraList)

        End If


        '// Create the camera model 
        If err = EDS_ERR_OK Then

            model = cameraModelFactory(camera, deviceInfo)

            If IsNothing(model) = True Then
                err = EDS_ERR_DEVICE_NOT_FOUND

            End If
        End If


        If err <> EDS_ERR_OK Then

            MessageBox.Show("Cannot detect camera")

        End If



        If err = EDS_ERR_OK Then

            '// Create a controller
            controller = New CameraController

            '// Set the model to this controller.
            controller.setCameraModel(model)

            '// Make notify the model updating to the view.
            model.addObserver(Me)

            ' ------------------------------------------------------------------------
            ' ------------------------------------------------------------------------
            ' You should create class instance of delegates of event handlers 
            ' with 'new' expressly if its attribute is Shared, 
            ' because System sometimes do garbage-collect these delegates.
            '
            '
            ' This error occurs.
            '
            ' CallbackOnCollectedDelegate is detected.
            ' Message: Callback was called with
            ' garbage-collected delegate of  
            ' Type() 'VBSample3!VBSample3.EDSDKTypes+EdsPropertyEventHandler::Invoke' 
            ' 
            ' It will be able to make data loss or application clash.
            ' You should stock delegates when you want to send delegate to unmanaged code.
            '
            ' ------------------------------------------------------------------------
            If err = EDS_ERR_OK Then

                err = EdsSetPropertyEventHandler(camera, kEdsPropertyEvent_All, _
                        inPropertyEventHandler, IntPtr.Zero)
            End If

            '// Set ObjectEventHandler
            If err = EDS_ERR_OK Then
                err = EdsSetObjectEventHandler(camera, kEdsObjectEvent_All, _
                    inObjectEventHandler, IntPtr.Zero)

            End If

            '// Set StateEventHandler
            If err = EDS_ERR_OK Then
                err = EdsSetCameraStateEventHandler(camera, kEdsStateEvent_All, _
                    inStateEventHandler, IntPtr.Zero)
            End If

        End If



        If err <> EDS_ERR_OK Then

            If IsNothing(camera) = False Then
                EdsRelease(camera)
                camera = Nothing
            End If

            If (isSDKLoaded) Then
                EdsTerminateSDK()
            End If

            If IsNothing(model) = False Then
                model = Nothing
            End If


            If IsNothing(controller) = False Then
                controller = Nothing
            End If


            End

        End If



        '//Execute the controller.
        controller.run()

    End Sub

    Private Sub VBSample_FormClosing(ByVal sender As System.Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles MyBase.FormClosing

        controller.actionPerformed("close")

        If IsNothing(model) Then
            If IsNothing(model.getCameraObject()) = False Then
                EdsRelease(model.getCameraObject())
            End If
        End If

        EdsTerminateSDK()

    End Sub

    Private Sub AEModeCmb_SelectionChangeCommitted(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles AEModeCmb.SelectionChangeCommitted
        Dim cmb As ComboBox = CType(sender, ComboBox) ' "sender" is the combobox
        Dim propValueList As ArrayList = CType(cmb.Tag, ArrayList)
        Dim data As Integer = propValueList.Item(cmb.SelectedIndex)

        controller.actionPerformed("set", kEdsPropID_AEMode, data)

    End Sub

    Private Sub TvCmb_SelectionChangeCommitted(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TvCmb.SelectionChangeCommitted
        Dim cmb As ComboBox = CType(sender, ComboBox) ' "sender" is the combobox
        Dim propValueList As ArrayList = CType(cmb.Tag, ArrayList)
        Dim data As Integer = propValueList.Item(cmb.SelectedIndex)
        Dim id As Integer

        'If cmb.Equals(Me.AEModeCmb) Then
        '    id = kEdsPropID_AEMode
        'ElseIf cmb.Equals(Me.TvCmb) Then
        '    id = kEdsPropID_Tv
        'ElseIf cmb.Equals(Me.AvCmb) Then
        '    id = kEdsPropID_Av
        'ElseIf cmb.Equals(Me.ISOSpeedCmb) Then
        '    id = kEdsPropID_ISOSpeed
        'ElseIf cmb.Equals(Me.MeteringModeCmb) Then
        '    id = kEdsPropID_MeteringMode
        'ElseIf cmb.Equals(Me.ExposureCompCmb) Then
        '    id = kEdsPropID_ExposureCompensation
        'Else
        '    Console.WriteLine("What's this?")
        'End If

        id = kEdsPropID_Tv
        controller.actionPerformed("set", id, data)

    End Sub

    Private Sub AvCmb_SelectionChangeCommitted(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles AvCmb.SelectionChangeCommitted
        Dim cmb As ComboBox = CType(sender, ComboBox) ' "sender" is the combobox
        Dim propValueList As ArrayList = CType(cmb.Tag, ArrayList)
        Dim data As Integer = propValueList.Item(cmb.SelectedIndex)

        controller.actionPerformed("set", kEdsPropID_Av, data)

    End Sub

    Private Sub ISOSpeedCmb_SelectionChangeCommitted(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ISOSpeedCmb.SelectionChangeCommitted
        Dim cmb As ComboBox = CType(sender, ComboBox) ' "sender" is the combobox
        Dim propValueList As ArrayList = CType(cmb.Tag, ArrayList)
        Dim data As Integer = propValueList.Item(cmb.SelectedIndex)

        controller.actionPerformed("set", kEdsPropID_ISOSpeed, data)

    End Sub

    Private Sub MeteringModeCmb_SelectionChangeCommitted(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MeteringModeCmb.SelectionChangeCommitted

        Dim cmb As ComboBox = CType(sender, ComboBox) ' "sender" is the combobox
        Dim propValueList As ArrayList = CType(cmb.Tag, ArrayList)
        Dim data As Integer = propValueList.Item(cmb.SelectedIndex)

        controller.actionPerformed("set", kEdsPropID_MeteringMode, data)

    End Sub

    Private Sub ExposureCompCmb_SelectionChangeCommitted(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ExposureCompCmb.SelectionChangeCommitted
        Dim cmb As ComboBox = CType(sender, ComboBox) ' "sender" is the combobox
        Dim propValueList As ArrayList = CType(cmb.Tag, ArrayList)
        Dim data As Integer = propValueList.Item(cmb.SelectedIndex)

        controller.actionPerformed("set", kEdsPropID_ExposureCompensation, data)

    End Sub


    Private Sub ImageQualityCmb_SelectionChangeCommitted(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ImageQualityCmb.SelectionChangeCommitted

        Dim cmb As ComboBox = CType(sender, ComboBox) ' "sender" is the combobox
        Dim propValueList As ArrayList = CType(cmb.Tag, ArrayList)
        Dim data As Integer = propValueList.Item(cmb.SelectedIndex)

        controller.actionPerformed("set", kEdsPropID_ImageQuality, data)

    End Sub

End Class

