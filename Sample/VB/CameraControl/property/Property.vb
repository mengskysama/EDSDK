'/******************************************************************************
'*                                                                             *
'*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
'*      NAME : Property.vb                                                     *
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

Imports System
Imports System.Collections
Imports System.Runtime.InteropServices

Public Structure TPropStrVal
    Dim val As Integer
    <MarshalAs(UnmanagedType.ByValTStr, SizeConst:=256)> Dim str As String
End Structure



Public Class CameraProperty
    ' Uniting camera properties and express strings table

    Public Shared g_AEMode As Hashtable = New Hashtable
    Public Shared g_ISOSpeed As Hashtable = New Hashtable
    Public Shared g_Av As Hashtable = New Hashtable
    Public Shared g_Tv As Hashtable = New Hashtable
    Public Shared g_MeteringMode As Hashtable = New Hashtable
    Public Shared g_ExposureComp As Hashtable = New Hashtable
    Public Shared g_ImageQuality As Hashtable = New Hashtable

    Public Shared g_PropList As Hashtable = New Hashtable


    Public Sub New()
        tableInit()
    End Sub



    Private Sub tableInit()

        g_MeteringMode.Add(1, "Spot Metering")
        g_MeteringMode.Add(3, "Evaluative Metering")
        g_MeteringMode.Add(4, "Partial Metering")
        g_MeteringMode.Add(5, "Center-Weighted Average Metering")
        g_MeteringMode.Add(&HFFFFFFFF, "unkown")


        g_ExposureComp.Add(&H18, "+3")
        g_ExposureComp.Add(&H15, "+2 2/3")
        g_ExposureComp.Add(&H14, "+2 1/2")
        g_ExposureComp.Add(&H13, "+2 1/3")
        g_ExposureComp.Add(&H10, "+2")
        g_ExposureComp.Add(&HD, "+1 2/3")
        g_ExposureComp.Add(&HC, "+1 1/2")
        g_ExposureComp.Add(&HB, "+1 1/3")
        g_ExposureComp.Add(&H8, "+1")
        g_ExposureComp.Add(&H5, "+2/3")
        g_ExposureComp.Add(&H4, "+1/2")
        g_ExposureComp.Add(&H3, "+1/3")
        g_ExposureComp.Add(&H0, "0")
        g_ExposureComp.Add(&HFD, "-1/3")
        g_ExposureComp.Add(&HFC, "-1/2")
        g_ExposureComp.Add(&HFB, "-2/3")
        g_ExposureComp.Add(&HF8, "-1")
        g_ExposureComp.Add(&HF5, "-1 1/3")
        g_ExposureComp.Add(&HF4, "-1 1/2")
        g_ExposureComp.Add(&HF3, "-1 2/3")
        g_ExposureComp.Add(&HF0, "-2")
        g_ExposureComp.Add(&HED, "-2 1/3")
        g_ExposureComp.Add(&HEC, "-2 1/2")
        g_ExposureComp.Add(&HEB, "-2 2/3")
        g_ExposureComp.Add(&HE8, "-3")
        g_ExposureComp.Add(&HFFFFFFFF, "unkown")


        g_AEMode.Add(0, "P")
        g_AEMode.Add(1, "Tv")
        g_AEMode.Add(2, "Av")
        g_AEMode.Add(3, "M")
        g_AEMode.Add(4, "Bulb")
        g_AEMode.Add(5, "A-DEP")
        g_AEMode.Add(6, "Depth-of-Field AE")
        g_AEMode.Add(7, "Manual")
        g_AEMode.Add(8, "Lock")
        g_AEMode.Add(9, "GreenMode")
        g_AEMode.Add(10, "Night Scene Portrait")
        g_AEMode.Add(11, "Sports")
        g_AEMode.Add(12, "Portrait")
        g_AEMode.Add(13, "Landscape")
        g_AEMode.Add(14, "Close Up")
        g_AEMode.Add(15, "Flash Off")
        g_AEMode.Add(&HFFFFFFFF, "unknown")


        g_ISOSpeed.add(&H0, "Auto")
        g_ISOSpeed.add(&H28, "6")
        g_ISOSpeed.add(&H30, "12")
        g_ISOSpeed.add(&H38, "25")
        g_ISOSpeed.add(&H40, "50")
        g_ISOSpeed.add(&H48, "100")
        g_ISOSpeed.add(&H4B, "125")
        g_ISOSpeed.add(&H4D, "160")
        g_ISOSpeed.add(&H50, "200")
        g_ISOSpeed.add(&H53, "250")
        g_ISOSpeed.add(&H55, "320")
        g_ISOSpeed.add(&H58, "400")
        g_ISOSpeed.Add(&H5B, "500")
        g_ISOSpeed.Add(&H5D, "640")
        g_ISOSpeed.Add(&H60, "800")
        g_ISOSpeed.Add(&H63, "1000")
        g_ISOSpeed.Add(&H65, "1250")
        g_ISOSpeed.Add(&H68, "1600")
        g_ISOSpeed.Add(&H70, "3200")
        g_ISOSpeed.Add(&H78, "6400")
        g_ISOSpeed.Add(&H80, "12800")
        g_ISOSpeed.Add(&H88, "25600")
        g_ISOSpeed.Add(&H90, "51200")
        g_ISOSpeed.Add(&H98, "102400")
        g_ISOSpeed.Add(&HFFFFFFFF, "unknown")


        g_Av.Add(&H8, "1")
        g_Av.Add(&HB, "1.1")
        g_Av.Add(&HC, "1.2")
        g_Av.Add(&HD, "1.2")
        g_Av.Add(&H10, "1.4")
        g_Av.Add(&H13, "1.6")
        g_Av.Add(&H14, "1.8")
        g_Av.Add(&H15, "1.8")
        g_Av.Add(&H18, "2")
        g_Av.Add(&H1B, "2.2")
        g_Av.Add(&H1C, "2.5")
        g_Av.Add(&H1D, "2.5")
        g_Av.Add(&H20, "2.8")
        g_Av.Add(&H23, "3.2")
        g_Av.Add(&H24, "3.5")
        g_Av.Add(&H25, "3.5")
        g_Av.Add(&H28, "4")
        g_Av.Add(&H2B, "4")
        g_Av.Add(&H2C, "4.5")
        g_Av.Add(&H2D, "5.6")
        g_Av.Add(&H30, "5.6")
        g_Av.Add(&H33, "6.3")
        g_Av.Add(&H34, "6.7")
        g_Av.Add(&H35, "7.1")
        g_Av.Add(&H38, "8")
        g_Av.Add(&H3B, "9")
        g_Av.Add(&H3C, "9.5")
        g_Av.Add(&H3D, "10")
        g_Av.Add(&H40, "11")
        g_Av.Add(&H43, "13")
        g_Av.Add(&H44, "13")
        g_Av.Add(&H45, "14")
        g_Av.Add(&H48, "16")
        g_Av.Add(&H4B, "18")
        g_Av.Add(&H4C, "19")
        g_Av.Add(&H4D, "20")
        g_Av.Add(&H50, "22")
        g_Av.Add(&H53, "25")
        g_Av.Add(&H54, "27")
        g_Av.Add(&H55, "29")
        g_Av.Add(&H58, "32")
        g_Av.Add(&H5B, "36")
        g_Av.Add(&H5C, "38")
        g_Av.Add(&H5D, "40")
        g_Av.Add(&H60, "45")
        g_Av.Add(&H63, "51")
        g_Av.Add(&H64, "54")
        g_Av.Add(&H65, "57")
        g_Av.Add(&H68, "64")
        g_Av.Add(&H6B, "72")
        g_Av.Add(&H6C, "76")
        g_Av.Add(&H6D, "80")
        g_Av.Add(&H70, "91")
        g_Av.Add(&HFFFFFFFF, "unknown")


        g_Tv.Add(&H10, "30""")
        g_Tv.Add(&H13, "25""")
        g_Tv.Add(&H14, "20""")
        g_Tv.Add(&H15, "20""")
        g_Tv.Add(&H18, "15""")
        g_Tv.Add(&H1B, "13""")
        g_Tv.Add(&H1C, "10""")
        g_Tv.Add(&H1D, "10""")
        g_Tv.Add(&H20, "8""")
        g_Tv.Add(&H23, "6""")
        g_Tv.Add(&H24, "6""")
        g_Tv.Add(&H25, "5""")
        g_Tv.Add(&H28, "4""")
        g_Tv.Add(&H2B, "3""" + "2")
        g_Tv.Add(&H2C, "3""")
        g_Tv.Add(&H2D, "2""" + "5")
        g_Tv.Add(&H30, "2""")
        g_Tv.Add(&H33, "1""" + "6")
        g_Tv.Add(&H34, "1""" + "5")
        g_Tv.Add(&H35, "1""" + "3")
        g_Tv.Add(&H38, "1""")
        g_Tv.Add(&H3B, "0""" + "8")
        g_Tv.Add(&H3C, "0""" + "7")
        g_Tv.Add(&H3D, "0""" + "6")
        g_Tv.Add(&H40, "0""" + "5")
        g_Tv.Add(&H43, "0""" + "4")
        g_Tv.Add(&H44, "0""" + "3")
        g_Tv.Add(&H45, "0""" + "3")
        g_Tv.Add(&H48, "4")
        g_Tv.Add(&H4B, "5")
        g_Tv.Add(&H4C, "6")
        g_Tv.Add(&H4D, "6")
        g_Tv.Add(&H50, "8")
        g_Tv.Add(&H53, "10")
        g_Tv.Add(&H54, "10")
        g_Tv.Add(&H55, "13")
        g_Tv.Add(&H58, "15")
        g_Tv.Add(&H5B, "20")
        g_Tv.Add(&H5C, "20")
        g_Tv.Add(&H5D, "25")
        g_Tv.Add(&H60, "30")
        g_Tv.Add(&H63, "40")
        g_Tv.Add(&H64, "45")
        g_Tv.Add(&H65, "50")
        g_Tv.Add(&H68, "60")
        g_Tv.Add(&H6B, "80")
        g_Tv.Add(&H6C, "90")
        g_Tv.Add(&H6D, "100")
        g_Tv.Add(&H70, "125")
        g_Tv.Add(&H73, "160")
        g_Tv.Add(&H74, "180")
        g_Tv.Add(&H75, "200")
        g_Tv.Add(&H78, "250")
        g_Tv.Add(&H7B, "320")
        g_Tv.Add(&H7C, "350")
        g_Tv.Add(&H7D, "400")
        g_Tv.Add(&H80, "500")
        g_Tv.Add(&H83, "640")
        g_Tv.Add(&H84, "750")
        g_Tv.Add(&H85, "800")
        g_Tv.Add(&H88, "1000")
        g_Tv.Add(&H8B, "1250")
        g_Tv.Add(&H8C, "1500")
        g_Tv.Add(&H8D, "1600")
        g_Tv.Add(&H90, "2000")
        g_Tv.Add(&H93, "2500")
        g_Tv.Add(&H94, "3000")
        g_Tv.Add(&H95, "3200")
        g_Tv.Add(&H98, "4000")
        g_Tv.Add(&H9B, "5000")
        g_Tv.Add(&H9C, "6000")
        g_Tv.Add(&H9D, "6400")
        g_Tv.Add(&HA0, "8000")
        g_Tv.Add(&HFFFFFFFF, "unknown")


        ' PTP Camera
        g_ImageQuality.Add(&H640F0F, "RAW")
        g_ImageQuality.Add(&H2640F0F, "Small RAW")
        g_ImageQuality.Add(&H640013, "RAW + Large Fine Jpeg")
        g_ImageQuality.Add(&H640113, "RAW + Middle Fine Jpeg")
        g_ImageQuality.Add(&H640213, "RAW + Small Fine Jpeg")
        g_ImageQuality.Add(&H640012, "RAW + Large Normal Jpeg")
        g_ImageQuality.Add(&H640112, "RAW + Middle Normal Jpeg")
        g_ImageQuality.Add(&H640212, "RAW + Small Normal Jpeg")
        g_ImageQuality.Add(&H130F0F, "Large Fine Jpeg")
        g_ImageQuality.Add(&H1130F0F, "Middle Fine Jpeg")
        g_ImageQuality.Add(&H2130F0F, "Small Fine Jpeg")
        g_ImageQuality.Add(&H120F0F, "Large Normal Jpeg")
        g_ImageQuality.Add(&H1120F0F, "Middle Normal Jpeg")
        g_ImageQuality.Add(&H2120F0F, "Small Normal Jpeg")

        g_ImageQuality.Add(&H640010, "RAW + Large Jpeg")
        g_ImageQuality.Add(&H640510, "RAW + Middle1 Jpeg")
        g_ImageQuality.Add(&H640610, "RAW + Middle2 Jpeg")
        g_ImageQuality.Add(&H640210, "RAW + Small Jpeg")
        g_ImageQuality.Add(&H100F0F, "Large Jpeg")
        g_ImageQuality.Add(&H5100F0F, "Middle1 Jpeg")
        g_ImageQuality.Add(&H6100F0F, "Middle2 Jpeg")
        g_ImageQuality.Add(&H2100F0F, "Small Jpeg")
        g_ImageQuality.Add(&H2640010, "Small RAW + Large Jpegg")
        g_ImageQuality.Add(&H2640510, "Small RAW + Middle1 Jpeg")
        g_ImageQuality.Add(&H2640610, "Small RAW + Middle2 Jpeg")
        g_ImageQuality.Add(&H2640210, "Small RAW + Small Jpeg")

        g_ImageQuality.Add(&H2640013, "Small RAW + Large Fine Jpeg")
        g_ImageQuality.Add(&H2640113, "Small RAW + Middle Fine Jpeg")
        g_ImageQuality.Add(&H2640213, "Small RAW + Small Fine Jpeg")
        g_ImageQuality.Add(&H2640012, "Small RAW + Large Normal Jpeg")
        g_ImageQuality.Add(&H2640112, "Small RAW + Middle Normal Jpeg")
        g_ImageQuality.Add(&H2640212, "Small RAW + Small Normal Jpeg")

        g_ImageQuality.Add(&H1640F0F, "Small RAW1")
        g_ImageQuality.Add(&H1640013, "Small RAW1 + Large Fine Jpeg")
        g_ImageQuality.Add(&H1640113, "Small RAW1 + Middle Fine Jpeg")
        g_ImageQuality.Add(&H1640213, "Small RAW1 + Small Fine Jpeg")
        g_ImageQuality.Add(&H1640012, "Small RAW1 + Large Normal Jpeg")
        g_ImageQuality.Add(&H1640112, "Small RAW1 + Middle Normal Jpeg")
        g_ImageQuality.Add(&H1640212, "Small RAW1 + Small Normal Jpeg")

        ' Legacy Camera
        g_ImageQuality.Add(&H240000, "RAW")
        g_ImageQuality.Add(&H240013, "RAW + Large Fine Jpeg")
        g_ImageQuality.Add(&H240113, "RAW + Middle Fine Jpeg")
        g_ImageQuality.Add(&H240213, "RAW + Small Fine Jpeg")
        g_ImageQuality.Add(&H240012, "RAW + Large Normal Jpeg")
        g_ImageQuality.Add(&H240112, "RAW + Middle Normal Jpeg")
        g_ImageQuality.Add(&H240212, "RAW + Small Normal Jpeg")
        g_ImageQuality.Add(&H130000, "Large Fine Jpeg")
        g_ImageQuality.Add(&H1130000, "Middle Fine Jpeg")
        g_ImageQuality.Add(&H2130000, "Small Fine Jpeg")
        g_ImageQuality.Add(&H120000, "Large Normal Jpeg")
        g_ImageQuality.Add(&H1120000, "Middle Normal Jpeg")
        g_ImageQuality.Add(&H2120000, "Small Normal Jpeg")

        g_ImageQuality.Add(&H2F000F, "RAW")
        g_ImageQuality.Add(&H2F001F, "RAW + Large Jpeg")
        g_ImageQuality.Add(&H2F051F, "RAW + Middle1 Jpeg")
        g_ImageQuality.Add(&H2F061F, "RAW + Middle2 Jpeg")
        g_ImageQuality.Add(&H2F021F, "RAW + Small Jpeg")
        g_ImageQuality.Add(&H1F000F, "Large Jpeg")
        g_ImageQuality.Add(&H51F000F, "Middle1 Jpeg")
        g_ImageQuality.Add(&H61F000F, "Middle2 Jpeg")
        g_ImageQuality.Add(&H21F000F, "Small Jpeg")

        g_PropList.Add(kEdsPropID_AEMode, g_AEMode)
        g_PropList.Add(kEdsPropID_ISOSpeed, g_ISOSpeed)
        g_PropList.Add(kEdsPropID_Av, g_Av)
        g_PropList.Add(kEdsPropID_Tv, g_Tv)
        g_PropList.Add(kEdsPropID_MeteringMode, g_MeteringMode)
        g_PropList.Add(kEdsPropID_ExposureCompensation, g_ExposureComp)
        g_PropList.Add(kEdsPropID_ImageQuality, g_ImageQuality)

    End Sub


End Class
