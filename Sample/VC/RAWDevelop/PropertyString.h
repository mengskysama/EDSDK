#pragma once

#include "EDSDK.h"
#include "RAWDevelop.h"
#include <vector>
using namespace std;

class CPropertyItem
{
public:
	CPropertyItem(void);
	~CPropertyItem(void);
public:
	CPropertyItem(EdsImageRef	imageRef);
	virtual EdsError GetPropertyTitle(EdsUInt32	*ioSize, EdsChar *outTitle);
	virtual EdsError GetPropertyValueCount(EdsUInt32	*outCount);
	virtual EdsError GetPropertyValue(EdsUInt32	index, EdsUInt32	*ioSize, EdsChar *outValue);

protected:
	EdsChar		m_title[EDS_MAX_NAME];
	vector<string> m_value;

	virtual const char *  GetPropertyString(STR_ID_TABLE* inTable, int count, int propID);
};

class CPropertyItem_Thumbnail: public CPropertyItem
{
public:
	CPropertyItem_Thumbnail(void);
	~CPropertyItem_Thumbnail(void);
	CPropertyItem_Thumbnail(EdsImageRef	imageRef);
};

class CPropertyItem_FullView: public CPropertyItem
{
public:
	CPropertyItem_FullView(void);
	~CPropertyItem_FullView(void);
	CPropertyItem_FullView(EdsImageRef	imageRef);
};

class CPropertyItem_MakerName: public CPropertyItem
{
public:
	CPropertyItem_MakerName(void);
	~CPropertyItem_MakerName(void);
	CPropertyItem_MakerName(EdsImageRef	imageRef);
};

class CPropertyItem_ProductName: public CPropertyItem
{
public:
	CPropertyItem_ProductName(void);
	~CPropertyItem_ProductName(void);
	CPropertyItem_ProductName(EdsImageRef	imageRef);
};


class CPropertyItem_DateTime: public CPropertyItem
{
public:
	CPropertyItem_DateTime(void);
	~CPropertyItem_DateTime(void);
	CPropertyItem_DateTime(EdsImageRef	imageRef);
};

class CPropertyItem_Tv: public CPropertyItem
{
public:
	CPropertyItem_Tv(void);
	~CPropertyItem_Tv(void);
	CPropertyItem_Tv(EdsImageRef	imageRef);
};

class CPropertyItem_Av: public CPropertyItem
{
public:
	CPropertyItem_Av(void);
	~CPropertyItem_Av(void);
	CPropertyItem_Av(EdsImageRef	imageRef);
};

class CPropertyItem_ISOSpeed: public CPropertyItem
{
public:
	CPropertyItem_ISOSpeed(void);
	~CPropertyItem_ISOSpeed(void);
	CPropertyItem_ISOSpeed(EdsImageRef	imageRef);
};

class CPropertyItem_FocalLength: public CPropertyItem
{
public:
	CPropertyItem_FocalLength(void);
	~CPropertyItem_FocalLength(void);
	CPropertyItem_FocalLength(EdsImageRef	imageRef);
};

class CPropertyItem_LensName: public CPropertyItem
{
public:
	CPropertyItem_LensName(void);
	~CPropertyItem_LensName(void);
	CPropertyItem_LensName(EdsImageRef	imageRef);
};

class CPropertyItem_BodyID: public CPropertyItem
{
public:
	CPropertyItem_BodyID(void);
	~CPropertyItem_BodyID(void);
	CPropertyItem_BodyID(EdsImageRef	imageRef);
};

class CPropertyItem_OwnerName: public CPropertyItem
{
public:
	CPropertyItem_OwnerName(void);
	~CPropertyItem_OwnerName(void);
	CPropertyItem_OwnerName(EdsImageRef	imageRef);
};

class CPropertyItem_Copyright: public CPropertyItem
{
public:
	CPropertyItem_Copyright(void);
	~CPropertyItem_Copyright(void);
	CPropertyItem_Copyright(EdsImageRef	imageRef);
};

class CPropertyItem_Artist: public CPropertyItem
{
public:
	CPropertyItem_Artist(void);
	~CPropertyItem_Artist(void);
	CPropertyItem_Artist(EdsImageRef	imageRef);
};

class CPropertyItem_FirmwareVersion: public CPropertyItem
{
public:
	CPropertyItem_FirmwareVersion(void);
	~CPropertyItem_FirmwareVersion(void);
	CPropertyItem_FirmwareVersion(EdsImageRef	imageRef);
};

class CPropertyItem_Orientation: public CPropertyItem
{
public:
	CPropertyItem_Orientation(void);
	~CPropertyItem_Orientation(void);
	CPropertyItem_Orientation(EdsImageRef	imageRef);
};

class CPropertyItem_JpegQuality: public CPropertyItem
{
public:
	CPropertyItem_JpegQuality(void);
	~CPropertyItem_JpegQuality(void);
	CPropertyItem_JpegQuality(EdsImageRef	imageRef);
};

class CPropertyItem_AEMode: public CPropertyItem
{
public:
	CPropertyItem_AEMode(void);
	~CPropertyItem_AEMode(void);
	CPropertyItem_AEMode(EdsImageRef	imageRef);
};

class CPropertyItem_DriveMode: public CPropertyItem
{
public:
	CPropertyItem_DriveMode(void);
	~CPropertyItem_DriveMode(void);
	CPropertyItem_DriveMode(EdsImageRef	imageRef);
};

class CPropertyItem_MeteringMode: public CPropertyItem
{
public:
	CPropertyItem_MeteringMode(void);
	~CPropertyItem_MeteringMode(void);
	CPropertyItem_MeteringMode(EdsImageRef	imageRef);
};

class CPropertyItem_AFMode: public CPropertyItem
{
public:
	CPropertyItem_AFMode(void);
	~CPropertyItem_AFMode(void);
	CPropertyItem_AFMode(EdsImageRef	imageRef);
};

class CPropertyItem_ExposureCompensation: public CPropertyItem
{
public:
	CPropertyItem_ExposureCompensation(void);
	~CPropertyItem_ExposureCompensation(void);
	CPropertyItem_ExposureCompensation(EdsImageRef	imageRef);
};

class CPropertyItem_DigitalExposure: public CPropertyItem
{
public:
	CPropertyItem_DigitalExposure(void);
	~CPropertyItem_DigitalExposure(void);
	CPropertyItem_DigitalExposure(EdsImageRef	imageRef);
};

class CPropertyItem_FlashCompensation: public CPropertyItem
{
public:
	CPropertyItem_FlashCompensation(void);
	~CPropertyItem_FlashCompensation(void);
	CPropertyItem_FlashCompensation(EdsImageRef	imageRef);
};

class CPropertyItem_Bracket: public CPropertyItem
{
public:
	CPropertyItem_Bracket(void);
	~CPropertyItem_Bracket(void);
	CPropertyItem_Bracket(EdsImageRef	imageRef);
};

class CPropertyItem_WhiteBalance: public CPropertyItem
{
public:
	CPropertyItem_WhiteBalance(void);
	~CPropertyItem_WhiteBalance(void);
	CPropertyItem_WhiteBalance(EdsImageRef	imageRef);
};

class CPropertyItem_WhiteBalanceShift: public CPropertyItem
{
public:
	CPropertyItem_WhiteBalanceShift(void);
	~CPropertyItem_WhiteBalanceShift(void);
	CPropertyItem_WhiteBalanceShift(EdsImageRef	imageRef);
};

class CPropertyItem_Sharpness: public CPropertyItem
{
public:
	CPropertyItem_Sharpness(void);
	~CPropertyItem_Sharpness(void);
	CPropertyItem_Sharpness(EdsImageRef	imageRef);
};

class CPropertyItem_ColorSaturation: public CPropertyItem
{
public:
	CPropertyItem_ColorSaturation(void);
	~CPropertyItem_ColorSaturation(void);
	CPropertyItem_ColorSaturation(EdsImageRef	imageRef);
};

class CPropertyItem_ColorMatrix: public CPropertyItem
{
public:
	CPropertyItem_ColorMatrix(void);
	~CPropertyItem_ColorMatrix(void);
	CPropertyItem_ColorMatrix(EdsImageRef	imageRef);
};

class CPropertyItem_Contrast: public CPropertyItem
{
public:
	CPropertyItem_Contrast(void);
	~CPropertyItem_Contrast(void);
	CPropertyItem_Contrast(EdsImageRef	imageRef);
};

class CPropertyItem_ColorTone: public CPropertyItem
{
public:
	CPropertyItem_ColorTone(void);
	~CPropertyItem_ColorTone(void);
	CPropertyItem_ColorTone(EdsImageRef	imageRef);
};

class CPropertyItem_ColorSpace: public CPropertyItem
{
public:
	CPropertyItem_ColorSpace(void);
	~CPropertyItem_ColorSpace(void);
	CPropertyItem_ColorSpace(EdsImageRef	imageRef);
};

class CPropertyItem_PhotoEffect: public CPropertyItem
{
public:
	CPropertyItem_PhotoEffect(void);
	~CPropertyItem_PhotoEffect(void);
	CPropertyItem_PhotoEffect(EdsImageRef	imageRef);
};

class CPropertyItem_FilterEffect: public CPropertyItem
{
public:
	CPropertyItem_FilterEffect(void);
	~CPropertyItem_FilterEffect(void);
	CPropertyItem_FilterEffect(EdsImageRef	imageRef);
};

class CPropertyItem_ToningEffect: public CPropertyItem
{
public:
	CPropertyItem_ToningEffect(void);
	~CPropertyItem_ToningEffect(void);
	CPropertyItem_ToningEffect(EdsImageRef	imageRef);
};

class CPropertyItem_ToneCurve: public CPropertyItem
{
public:
	CPropertyItem_ToneCurve(void);
	~CPropertyItem_ToneCurve(void);
	CPropertyItem_ToneCurve(EdsImageRef	imageRef);
};

class CPropertyItem_PictureStyle: public CPropertyItem
{
public:
	CPropertyItem_PictureStyle(void);
	~CPropertyItem_PictureStyle(void);
	CPropertyItem_PictureStyle(EdsImageRef	imageRef);
};

class CPropertyItem_FlashOn: public CPropertyItem
{
public:
	CPropertyItem_FlashOn(void);
	~CPropertyItem_FlashOn(void);
	CPropertyItem_FlashOn(EdsImageRef	imageRef);
};

class CPropertyItem_FlashMode: public CPropertyItem
{
public:
	CPropertyItem_FlashMode(void);
	~CPropertyItem_FlashMode(void);
	CPropertyItem_FlashMode(EdsImageRef	imageRef);
};

class CPropertyItem_RedEye: public CPropertyItem
{
public:
	CPropertyItem_RedEye(void);
	~CPropertyItem_RedEye(void);
	CPropertyItem_RedEye(EdsImageRef	imageRef);
};

class CPropertyItem_NoiseReduction: public CPropertyItem
{
public:
	CPropertyItem_NoiseReduction(void);
	~CPropertyItem_NoiseReduction(void);
	CPropertyItem_NoiseReduction(EdsImageRef	imageRef);
};

class CPropertyItem_GPSVersionID: public CPropertyItem
{
public:
	CPropertyItem_GPSVersionID(void);
	~CPropertyItem_GPSVersionID(void);
	CPropertyItem_GPSVersionID(EdsImageRef	imageRef);
};

class CPropertyItem_GPSLatitude: public CPropertyItem
{
public:
	CPropertyItem_GPSLatitude(void);
	~CPropertyItem_GPSLatitude(void);
	CPropertyItem_GPSLatitude(EdsImageRef	imageRef);
};

class CPropertyItem_GPSLongitude: public CPropertyItem
{
public:
	CPropertyItem_GPSLongitude(void);
	~CPropertyItem_GPSLongitude(void);
	CPropertyItem_GPSLongitude(EdsImageRef	imageRef);
};

class CPropertyItem_GPSAltitude: public CPropertyItem
{
public:
	CPropertyItem_GPSAltitude(void);
	~CPropertyItem_GPSAltitude(void);
	CPropertyItem_GPSAltitude(EdsImageRef	imageRef);
};

class CPropertyItem_GPSDateStamp: public CPropertyItem
{
public:
	CPropertyItem_GPSDateStamp(void);
	~CPropertyItem_GPSDateStamp(void);
	CPropertyItem_GPSDateStamp(EdsImageRef	imageRef);
};

class CPropertyItem_GPSTimeStamp: public CPropertyItem
{
public:
	CPropertyItem_GPSTimeStamp(void);
	~CPropertyItem_GPSTimeStamp(void);
	CPropertyItem_GPSTimeStamp(EdsImageRef	imageRef);
};

class CPropertyItem_GPSMapDatum: public CPropertyItem
{
public:
	CPropertyItem_GPSMapDatum(void);
	~CPropertyItem_GPSMapDatum(void);
	CPropertyItem_GPSMapDatum(EdsImageRef	imageRef);
};

class CPropertyItem_GPSSatellites: public CPropertyItem
{
public:
	CPropertyItem_GPSSatellites(void);
	~CPropertyItem_GPSSatellites(void);
	CPropertyItem_GPSSatellites(EdsImageRef	imageRef);
};


class CPropertyString
{
public:
	CPropertyString(void);
	~CPropertyString(void);
public:
	CPropertyString(EdsImageRef	imageRef);
	EdsError SetImageRef(EdsImageRef	imageRef);
	EdsError SetPropertyID(EdsPropertyID	propID);
	EdsError SetImageSource(EdsImageSource	imgSrc);

	EdsError GetPropertyTitle(EdsUInt32	*ioSize, EdsChar *outTitle);
	EdsError GetPropertyValueCount(EdsUInt32	*outCount);
	EdsError GetPropertyValue(EdsUInt32	index, EdsUInt32	*ioSize, EdsChar *outValue);
protected:
	EdsImageRef		m_ImgRef;
	CPropertyItem	*m_propItem;
};

