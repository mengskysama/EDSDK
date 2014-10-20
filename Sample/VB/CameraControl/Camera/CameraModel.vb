'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : CameraModel.vb                                                  *
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

Public Class CameraModel
    Inherits Observable


    Protected camera As IntPtr

    '// UIlock counter
    Protected lockCount As Integer

    '// Model name
    Protected modelName As String

    '// Parameters
    Protected AEMode As Integer
    Protected Av As Integer
    Protected Tv As Integer
    Protected Iso As Integer
    Protected MeteringMode As Integer
    Protected ExposureCompensation As Integer
    Protected ImageQuality As Integer
    Protected availableShot As Integer

    '// Available parameter lists
    Protected AEModeDesc As EdsPropertyDesc
    Protected AvDesc As EdsPropertyDesc
    Protected TvDesc As EdsPropertyDesc
    Protected IsoDesc As EdsPropertyDesc
    Protected MeteringModeDesc As EdsPropertyDesc
    Protected ExposureCompensationDesc As EdsPropertyDesc
    Protected ImageQualityDesc As EdsPropertyDesc


    '// Constructor
    Public Sub New(ByVal camera As IntPtr)
        Me.lockCount = 0
        Me.camera = camera
    End Sub

    '// Get a camera object
    Public Function getCameraObject() As IntPtr
        Return Me.camera
    End Function


    '// -----------------------------------------------------------------
    '// Stock parameters ---------------------------------------------

    Private Sub setAEMode(ByVal value As Integer)
        AEMode = value
    End Sub

    Private Sub setTv(ByVal value As Integer)
        Tv = value
    End Sub

    Private Sub setAv(ByVal value As Integer)
        Av = value
    End Sub

    Private Sub setIso(ByVal value As Integer)
        Iso = value
    End Sub

    Private Sub setMeteringMode(ByVal value As Integer)
        MeteringMode = value
    End Sub

    Private Sub setExposureCompensation(ByVal value As Integer)
        ExposureCompensation = value
    End Sub

    Private Sub setImageQuality(ByVal value As Integer)
        ImageQuality = value
    End Sub

    Private Sub setModelName(ByVal modelName As String)
        modelName = modelName
    End Sub

    '// -----------------------------------------------------------------
    '// Give parameters ---------------------------------------------

    Private Function getAEMode() As Integer
        Return AEMode
    End Function

    Private Function getTv() As Integer
        Return Tv
    End Function

    Private Function getAv() As Integer
        Return Av
    End Function

    Private Function getIso() As Integer
        Return Iso
    End Function

    Private Function getMeteringMode() As Integer
        Return MeteringMode
    End Function

    Private Function getExposureCompensation() As Integer
        Return ExposureCompensation
    End Function

    Private Function getImageQuality() As Integer
        Return ImageQuality
    End Function

    '// -----------------------------------------------------------------
    '// Give available parameter lists ----------------------------------

    Private Function getAEModeDesc() As EdsPropertyDesc
        Return AEModeDesc
    End Function

    Private Function getAvDesc() As EdsPropertyDesc
        Return AvDesc
    End Function

    Private Function getTvDesc() As EdsPropertyDesc
        Return TvDesc
    End Function

    Private Function getIsoDesc() As EdsPropertyDesc
        Return IsoDesc
    End Function

    Private Function getMeteringModeDesc() As EdsPropertyDesc
        Return MeteringModeDesc
    End Function

    Private Function getExposureCompensationDesc() As EdsPropertyDesc
        Return ExposureCompensationDesc
    End Function

    Private Function getImageQualityDesc() As EdsPropertyDesc
        Return ImageQualityDesc
    End Function


    '// -----------------------------------------------------------------
    '// Stock available parameter lists ---------------------------------

    Private Sub setAEModeDesc(ByVal desc As EdsPropertyDesc)
        AEModeDesc = desc
    End Sub

    Private Sub setAvDesc(ByVal desc As EdsPropertyDesc)
        AvDesc = desc
    End Sub

    Private Sub setTvDesc(ByVal desc As EdsPropertyDesc)
        TvDesc = desc
    End Sub

    Private Sub setIsoDesc(ByVal desc As EdsPropertyDesc)
        IsoDesc = desc
    End Sub

    Private Sub setMeteringModeDesc(ByVal desc As EdsPropertyDesc)
        MeteringModeDesc = desc
    End Sub

    Private Sub setExposureCompensationDesc(ByVal desc As EdsPropertyDesc)
        ExposureCompensationDesc = desc
    End Sub

    Private Sub setImageQualityDesc(ByVal desc As EdsPropertyDesc)
        ImageQualityDesc = desc
    End Sub


    '// Set a property <UInt32>
    Public Sub setPropertyUInt32(ByVal propertyID As Integer, ByVal value As Integer)
        Select Case propertyID
            Case kEdsPropID_AEMode
                setAEMode(value)
            Case kEdsPropID_Tv
                setTv(value)
            Case kEdsPropID_Av
                setAv(value)
            Case kEdsPropID_ISOSpeed
                setIso(value)
            Case kEdsPropID_MeteringMode
                setMeteringMode(value)
            Case kEdsPropID_ExposureCompensation
                setExposureCompensation(value)
            Case kEdsPropID_ImageQuality
                setImageQuality(value)
        End Select
    End Sub


    '// Get a property <UInt32>
    Public Function getPropertyUInt32(ByVal propertyID As Integer) As Integer
        Dim value As Integer = &HFFFFFFFF
        Select Case propertyID
            Case kEdsPropID_AEMode
                value = getAEMode()
            Case kEdsPropID_Tv
                value = getTv()
            Case kEdsPropID_Av
                value = getAv()
            Case kEdsPropID_ISOSpeed
                value = getIso()
            Case kEdsPropID_MeteringMode
                value = getMeteringMode()
            Case kEdsPropID_ExposureCompensation
                value = getExposureCompensation()
            Case kEdsPropID_ImageQuality
                value = getImageQuality()
        End Select
        Return value

    End Function


    '// Get a property <String>
    Public Sub getPropertyString(ByVal propertyID As Integer, ByRef str As String)
        Select Case propertyID
            Case kEdsPropID_ProductName
                str = modelName
        End Select
    End Sub


    '// Set a property <String>
    Public Sub setPropertyString(ByVal propertyID As Integer, ByVal str As String)
        Select Case propertyID
            Case kEdsPropID_ProductName
                modelName = str
        End Select
    End Sub


    '// Set an available parameter list.
    Public Sub setPropertyDesc(ByVal propertyID As Integer, ByVal desc As EdsPropertyDesc)
        Select Case propertyID
            Case kEdsPropID_AEMode
                setAEModeDesc(desc)
            Case kEdsPropID_Tv
                setTvDesc(desc)
            Case kEdsPropID_Av
                setAvDesc(desc)
            Case kEdsPropID_ISOSpeed
                setIsoDesc(desc)
            Case kEdsPropID_MeteringMode
                setMeteringModeDesc(desc)
            Case kEdsPropID_ExposureCompensation
                setExposureCompensationDesc(desc)
            Case kEdsPropID_ImageQuality
                setImageQualityDesc(desc)
        End Select
    End Sub

    '// Get an available parameter list.
    Public Function getPropertyDesc(ByVal propertyID As Integer) As EdsPropertyDesc
        Dim desc As EdsPropertyDesc = Nothing
        Select Case propertyID
            Case kEdsPropID_AEMode
                desc = getAEModeDesc()
            Case kEdsPropID_Tv
                desc = getTvDesc()
            Case kEdsPropID_Av
                desc = getAvDesc()
            Case kEdsPropID_ISOSpeed
                desc = getIsoDesc()
            Case kEdsPropID_MeteringMode
                desc = getMeteringModeDesc()
            Case kEdsPropID_ExposureCompensation
                desc = getExposureCompensationDesc()
            Case kEdsPropID_ImageQuality
                desc = getImageQualityDesc()
        End Select
        Return desc
    End Function

    '// Check camera accessing flag.
    '// Connected camera is not a legacy one, this method will be called.
    Public Overridable Function isLegacy() As Boolean
        Return False
    End Function

End Class
