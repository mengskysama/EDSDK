#include "StdAfx.h"
#include "PropertyString.h"

////////////////////////////////////////////////////////
CPropertyItem::CPropertyItem(void)
{
	memset(m_title, 0, sizeof(m_title));
	m_value.clear();
}

CPropertyItem::~CPropertyItem(void)
{
	memset(m_title, 0, sizeof(m_title));
	m_value.clear();
}

CPropertyItem::CPropertyItem(EdsImageRef imageRef)
{
}

EdsError CPropertyItem::GetPropertyTitle(EdsUInt32	*ioSize, EdsChar *outTitle)
{
	if(ioSize==NULL)	return EDS_ERR_INVALID_PARAMETER;

	if(outTitle==NULL)
	{
		*ioSize = (EdsUInt32)strlen(m_title);
		return EDS_ERR_OK;
	}

	memset(outTitle, '\0', *ioSize);
	if(*ioSize>=strlen(m_title))	strncpy_s(outTitle, EDS_MAX_NAME, m_title, *ioSize);
	return EDS_ERR_OK;
}

EdsError CPropertyItem::GetPropertyValueCount(EdsUInt32	*outCount)
{
	if(outCount==NULL)	return EDS_ERR_INVALID_PARAMETER;
	*outCount = (EdsUInt32)m_value.size();
	return EDS_ERR_OK;
}

EdsError CPropertyItem::GetPropertyValue(EdsUInt32	index, EdsUInt32	*ioSize, EdsChar *outValue)
{
	if(ioSize==NULL||index>=m_value.size())	return EDS_ERR_INVALID_PARAMETER;

	if(outValue==NULL)
	{
		*ioSize = (EdsUInt32)strlen(m_value[index].c_str());
		return EDS_ERR_OK;
	}
	memset(outValue, '\0', *ioSize);
	if(*ioSize>=strlen(m_value[index].c_str()))	strncpy_s(outValue, MAX_PATH, m_value[index].c_str(), *ioSize);
	return EDS_ERR_OK;
}
const char * CPropertyItem::GetPropertyString(STR_ID_TABLE* inTable, int count, int propID)
{
	const char * retString = "Unknown";

	for(int i = 0; i < count; i++)
	{
		if(inTable[i].value == propID)
		{
			retString = inTable[i].string;
			break;
		}
	}
	return retString;
}

////////////////////////////////////////////////////////
CPropertyItem_Thumbnail::CPropertyItem_Thumbnail(EdsImageRef	imageRef)
{
	EdsImageInfo info;
	char value[EDS_MAX_NAME] = {0};
	if( EDS_ERR_OK == EdsGetImageInfo( imageRef , kEdsImageSrc_RAWThumbnail , &info ) )
	{
		sprintf_s( value , EDS_MAX_NAME, "%dx%d %dbit" , info.width , info.height , info.componentDepth );
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "Thumbnail");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_FullView::CPropertyItem_FullView(EdsImageRef	imageRef)
{
	EdsImageInfo info;
	char value[EDS_MAX_NAME] = {0};
	if( EDS_ERR_OK == EdsGetImageInfo( imageRef , kEdsImageSrc_RAWFullView , &info ) )
	{
		sprintf_s( value , EDS_MAX_NAME, "%dx%d %dbit" , info.width , info.height , info.componentDepth );
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "FullView");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_MakerName::CPropertyItem_MakerName(EdsImageRef	imageRef)
{
	char value[EDS_MAX_NAME] = {0};
	if(EDS_ERR_OK == EdsGetPropertyData(imageRef, kEdsPropID_MakerName , 0 , sizeof(value), value ))
	{
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "MakerName");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_ProductName::CPropertyItem_ProductName(EdsImageRef	imageRef)
{
	char value[EDS_MAX_NAME] = {0};
	if(EDS_ERR_OK == EdsGetPropertyData(imageRef, kEdsPropID_ProductName , 0 , sizeof(value), value ))
	{
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "ProductName");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_DateTime::CPropertyItem_DateTime(EdsImageRef	imageRef)
{
	EdsTime time;
	char value[EDS_MAX_NAME] = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_DateTime, 0, sizeof(time),&time))
	{
		sprintf_s( value , EDS_MAX_NAME , "%d/%d/%d %d:%d" , time.month,time.day,time.year,time.hour,time.minute );
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "FullView");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_Tv::CPropertyItem_Tv(EdsImageRef	imageRef)
{
	EdsRational rational;
	char value[EDS_MAX_NAME] = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_Tv, 0, sizeof(rational),&rational))
	{
		sprintf_s( value , EDS_MAX_NAME , "%d/%d" , rational.numerator , rational.denominator );
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "Tv");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_Av::CPropertyItem_Av(EdsImageRef	imageRef)
{
	EdsRational rational;
	char value[EDS_MAX_NAME] = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_Av, 0, sizeof(rational),&rational))
	{
		sprintf_s( value , EDS_MAX_NAME , "F%.1f"  , (double)rational.numerator/rational.denominator );
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "Av");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_ISOSpeed::CPropertyItem_ISOSpeed(EdsImageRef	imageRef)
{
	EdsUInt32 uValue;
	char value[EDS_MAX_NAME] = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_ISOSpeed, 0, sizeof(uValue),&uValue))
	{
		sprintf_s( value , EDS_MAX_NAME , "%d"  , uValue );
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "ISO");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_FocalLength::CPropertyItem_FocalLength(EdsImageRef	imageRef)
{
	EdsRational rational;
	char value[EDS_MAX_NAME] = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_FocalLength, 0, sizeof(rational),&rational))
	{
		sprintf_s( value , EDS_MAX_NAME , ":%.1fmm" , (double)rational.numerator/rational.denominator );
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "FocalLength");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_LensName ::CPropertyItem_LensName (EdsImageRef	imageRef)
{
	char value[EDS_MAX_NAME] = {0};
	if(EDS_ERR_OK == EdsGetPropertyData(imageRef, kEdsPropID_LensName , 0 , sizeof(value), value ))
	{
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "LensName ");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_BodyID::CPropertyItem_BodyID(EdsImageRef	imageRef)
{
	EdsUInt32 uValue;
	char value[EDS_MAX_NAME] = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_BodyID, 0, sizeof(uValue),&uValue))
	{
		sprintf_s( value , EDS_MAX_NAME , "%010d"  , uValue );
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "Body ID");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_OwnerName::CPropertyItem_OwnerName (EdsImageRef	imageRef)
{
	char value[EDS_MAX_NAME] = {0};
	if(EDS_ERR_OK == EdsGetPropertyData(imageRef, kEdsPropID_OwnerName , 0 , sizeof(value), value ))
	{
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "OwnerName");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_Artist::CPropertyItem_Artist (EdsImageRef	imageRef)
{
	char value[EDS_MAX_NAME] = {0};
	if(EDS_ERR_OK == EdsGetPropertyData(imageRef, kEdsPropID_Artist , 0 , sizeof(value), value ))
	{
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "Artist");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_Copyright::CPropertyItem_Copyright (EdsImageRef	imageRef)
{
	char value[EDS_MAX_NAME] = {0};
	if(EDS_ERR_OK == EdsGetPropertyData(imageRef, kEdsPropID_Copyright , 0 , sizeof(value), value ))
	{
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "Copyright");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_FirmwareVersion::CPropertyItem_FirmwareVersion (EdsImageRef	imageRef)
{
	char value[EDS_MAX_NAME] = {0};
	if(EDS_ERR_OK == EdsGetPropertyData(imageRef, kEdsPropID_FirmwareVersion , 0 , sizeof(value), value ))
	{
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "FirmwareVersion");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_JpegQuality::CPropertyItem_JpegQuality(EdsImageRef	imageRef)
{
	EdsUInt32 uValue;
	char value[EDS_MAX_NAME] = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_JpegQuality, 0, sizeof(uValue),&uValue))
	{
		sprintf_s( value , EDS_MAX_NAME , "%d"  , uValue );
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "JpegQuality");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_Orientation::CPropertyItem_Orientation(EdsImageRef	imageRef)
{
	EdsUInt32 uValue;
	char value[EDS_MAX_NAME] = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_Orientation, 0, sizeof(uValue),&uValue))
	{
		sprintf_s( value , EDS_MAX_NAME , "%d"  , uValue );
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "Orientation");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_AEMode::CPropertyItem_AEMode(EdsImageRef	imageRef)
{
	EdsUInt32 uValue;
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_AEMode, 0, sizeof(uValue),&uValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"Program AE",					0, 
			"Shutter-Speed Priority AE",	1, 
			"Aperture Priority AE",			2, 
			"Manual Exposure",				3, 
			"Bulb",							4, 
			"Auto Depth-of-Field AE AE",	5, 
			"Depth-of-Field  AE",			6, 
			"Auto",							9, 
			 "Night Scene Portrait",		10,
			 "Sports",						11,
			 "Portrait",					12,
			 "Landscape",					13,
			 "Close-Up",					14,
			 "Flash Off",					15,
		};
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)uValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "AE Mode");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_DriveMode::CPropertyItem_DriveMode(EdsImageRef	imageRef)
{
	EdsUInt32 uValue;
	char value[EDS_MAX_NAME] = {0};
	if(EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_DriveMode, 0, sizeof(uValue),&uValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"Single-Frame Shooting",			0x00,
			"Continuous Shooting",				0x01,
			"High-Speed Continuous Shooting",	0x04,
			"Low-Speed Continuous Shooting",	0x05,
			"Silent single shooting",			0x06,
			"Custom Self-Timer",				0x07,
			"10-Sec Self-Timer",				0x10,
			"2-Sec Self-Timer",					0x11,

		};
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)uValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "Drive Mode");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_MeteringMode::CPropertyItem_MeteringMode(EdsImageRef	imageRef)
{
	EdsUInt32 uValue;
	char value[EDS_MAX_NAME] = {0};
	if(EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_MeteringMode, 0, sizeof(uValue),&uValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"Spot metering",						1,
			"Evaluative metering",					3,
			"Partial metering",						4,
			"Center-weighted averaging metering",	5,
		};

		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)uValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "Metering Mode");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_AFMode::CPropertyItem_AFMode(EdsImageRef	imageRef)
{
	EdsUInt32 uValue;
	char value[EDS_MAX_NAME] = {0};
	if(EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_AFMode, 0, sizeof(uValue),&uValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"One-Shot AF",		0,
			"AI Servo AF",		1,
			"AI Focus AF",		2,
			"Manual Focus",		3,
		};

		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)uValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "AF Mode");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_ExposureCompensation::CPropertyItem_ExposureCompensation(EdsImageRef	imageRef)
{
	EdsRational rational;
	char value[EDS_MAX_NAME] = {0};
	if(EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_ExposureCompensation, 0, sizeof(rational),&rational))
	{
		if(rational.numerator==0)
			sprintf_s( value , EDS_MAX_NAME , "%d" , rational.numerator);
		else
		{
			sprintf_s( value , EDS_MAX_NAME , "%d/%d" , rational.numerator, rational.denominator );
		}
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "Exposure Compensation");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_DigitalExposure::CPropertyItem_DigitalExposure(EdsImageRef	imageRef)
{
	EdsRational rational;
	char value[EDS_MAX_NAME] = {0};
	if(EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_DigitalExposure|kEdsPropID_AtCapture_Flag, 0, sizeof(rational),&rational))
	{
		if(rational.numerator==0)
			sprintf_s( value , EDS_MAX_NAME , "%d" , rational.numerator);
		else
		{
			sprintf_s( value , EDS_MAX_NAME , "%d/%d" , rational.numerator, rational.denominator );
		}
		m_value.push_back(value);
		strcpy_s(m_title, EDS_MAX_NAME, "Digital Exposure ");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_FlashCompensation::CPropertyItem_FlashCompensation(EdsImageRef	imageRef)
{
	EdsUInt32 uValue;
	char value[EDS_MAX_NAME] = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_FlashCompensation, 0, sizeof(uValue),&uValue))
	{
		sprintf_s( value , EDS_MAX_NAME , "%d" , uValue);
	}
}

////////////////////////////////////////////////////////
CPropertyItem_Bracket::CPropertyItem_Bracket(EdsImageRef	imageRef)
{
	EdsUInt32 uValue;
	EdsRational rational;
	EdsDataType	type;
	EdsUInt32	size;	
	char value[EDS_MAX_NAME] = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_Bracket, 0, sizeof(uValue),&uValue))
	{
		char title[EDS_MAX_NAME] = {0};
		switch(uValue)
		{
		case 1:
			{
				EdsGetPropertyData( imageRef, kEdsPropID_AEBracket, 0, sizeof(rational),&rational);
				if(rational.numerator==0)
					sprintf_s( value , EDS_MAX_NAME , "%d" , rational.numerator);
				else
				{
					sprintf_s( value , EDS_MAX_NAME , "%d/%d" , rational.numerator, rational.denominator );
				}
				m_value.push_back(value);
				strcpy_s(m_title, EDS_MAX_NAME, "AE bracket");
				break;
			}
		case 2:
			{
				EdsGetPropertyData( imageRef, kEdsPropID_ISOBracket, 0, sizeof(rational),&rational);
				if(rational.numerator==0)
					sprintf_s( value , EDS_MAX_NAME , "%d" , rational.numerator);
				else
				{
					sprintf_s( value , EDS_MAX_NAME , "%d/%d" , rational.numerator, rational.denominator );
				}
				m_value.push_back(value);
				strcpy_s(m_title, EDS_MAX_NAME, "ISO bracket");
				break;
			}
		case 3:
			{
				EdsInt32 WbBrakcet[3];
				EdsGetPropertySize( imageRef, kEdsPropID_WhiteBalanceBracket, 0, &type,&size);
				EdsGetPropertyData( imageRef, kEdsPropID_WhiteBalanceBracket, 0, size, WbBrakcet);

				sprintf_s(value, EDS_MAX_NAME, "%d", WbBrakcet[0]);
				m_value.push_back(value);
				strcpy_s(m_title, EDS_MAX_NAME, "WB bracket mode");

				switch(WbBrakcet[0])
				{
				case 1:	sprintf_s(value, EDS_MAX_NAME, "AB:%d", WbBrakcet[1]);	break;
				case 2:	sprintf_s(value, EDS_MAX_NAME, "GM:%d", WbBrakcet[2]);	break;
				case 0:sprintf_s(value, EDS_MAX_NAME, "off");	break;
				default:sprintf_s(value , EDS_MAX_NAME , "Not Supported");	break;
				}
				m_value.push_back(value);
				break;
			}
		case 4:
			{
				EdsGetPropertyData( imageRef, kEdsPropID_FEBracket, 0, sizeof(rational),&rational);
				if(rational.numerator==0)
					sprintf_s( value , EDS_MAX_NAME , "%d" , rational.numerator);
				else
				{
					sprintf_s( value , EDS_MAX_NAME , "%d/%d" , rational.numerator, rational.denominator );
				}
				m_value.push_back(value);
				strcpy_s(m_title, EDS_MAX_NAME, "FE bracket");
				break;
			}
		default:
			{
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////
CPropertyItem_WhiteBalance::CPropertyItem_WhiteBalance(EdsImageRef	imageRef)
{
	EdsInt32	sValue;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_WhiteBalance|kEdsPropID_AtCapture_Flag, 0, sizeof(sValue),&sValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"Auto",							0,
			"Daylight",						1,
			"Cloudy",						2,
			"Tungsten",						3,
			"Fluorescent",					4,
			"Flash",						5,
			"Manual",						6,
			"Shade",						8,
			"Color temperature",			9,
			"Custom white balance: PC-1",	10,
			"Custom white balance: PC-2",	11,
			"Custom white balance: PC-3",	12,
			"Manual 2",						15,
			"Manual 3",						16,
			"Manual 4",						15,
			"Manual 5",						19,
			"Custom white balance: PC-4",	20,
			"Custom white balance: PC-5",	21,
		};

		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)sValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "White Balance");


		if(sValue == 9)
		{
			EdsUInt32	uValue;
			EdsGetPropertyData( imageRef, kEdsPropID_ColorTemperature|kEdsPropID_AtCapture_Flag, 0, sizeof(uValue),&uValue);
			sprintf_s(value, EDS_MAX_NAME, "%d K", uValue);
			m_value.push_back(value);
		}
	}
}

////////////////////////////////////////////////////////
CPropertyItem_WhiteBalanceShift::CPropertyItem_WhiteBalanceShift(EdsImageRef	imageRef)
{
	EdsInt32	wbShift[2];
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_WhiteBalanceShift|kEdsPropID_AtCapture_Flag, 0, sizeof(wbShift),&wbShift))
	{
		sprintf_s(value, EDS_MAX_NAME, "AB:%2d GM:%2d", wbShift[0], wbShift[1]);
		strcpy_s(m_title, EDS_MAX_NAME, "White Balance Shift");
		m_value.push_back(value);
	}
}

////////////////////////////////////////////////////////
CPropertyItem_Sharpness::CPropertyItem_Sharpness(EdsImageRef	imageRef)
{
	char value[EDS_MAX_NAME]  = {0};
	char productName[EDS_MAX_NAME]  = {0};
	if(EDS_ERR_OK != EdsGetPropertyData(imageRef, kEdsPropID_ProductName|kEdsPropID_AtCapture_Flag, 0 , sizeof(productName), productName ))	return;

	if(!strcmp("EOS-1D", productName) ||
		!strcmp("EOS-1Ds", productName))
	{
		EdsUInt32	sharpness[2];
		if(EDS_ERR_OK != EdsGetPropertyData( imageRef, kEdsPropID_Sharpness , 0, sizeof(sharpness),&sharpness))
		{
			STR_ID_TABLE propCaptions[] = {
				"Off",			0,
				"Rough",		1,
				"Mid. rough",	2,
				"Standard",		3,
				"Mid. fine",	4,
				"Fine",			5,
			};
			strcpy_s(m_title, EDS_MAX_NAME, "Sharpness");
			const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)sharpness[1]);
			if(tmpString != NULL)	sprintf_s(value, EDS_MAX_NAME, "level:%d target:%s", sharpness[0], tmpString);
			m_value.push_back(value);
		}
	}
	else
	{
		EdsUInt32 uValue;
		if( EDS_ERR_OK == EdsGetPropertyData( imageRef ,kEdsPropID_Sharpness , 0, sizeof(uValue),&uValue))
		{
			strcpy_s(m_title, EDS_MAX_NAME, "Sharpness");
			sprintf_s(value, EDS_MAX_NAME, "%d", uValue);
			m_value.push_back(value);
		}
	}
}

////////////////////////////////////////////////////////
CPropertyItem_ColorSaturation::CPropertyItem_ColorSaturation(EdsImageRef	imageRef)
{
	EdsInt32	sValue;
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_ColorSaturation|kEdsPropID_AtCapture_Flag, 0, sizeof(sValue),&sValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"Low",			-2,
			"Mid. low",		-1,
			"Standard",		0,
			"Mid. High",	1,
			"High",			2,
		};
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)sValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "Color Saturation");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_ColorMatrix::CPropertyItem_ColorMatrix(EdsImageRef	imageRef)
{
	EdsUInt32	uValue;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_ColorMatrix|kEdsPropID_AtCapture_Flag, 0, sizeof(uValue),&uValue))
	{
		sprintf_s(value, EDS_MAX_NAME, "%d", uValue);
		strcpy_s(m_title, EDS_MAX_NAME, "Color Matrix");
		m_value.push_back(value);
	}
}

////////////////////////////////////////////////////////
CPropertyItem_Contrast::CPropertyItem_Contrast(EdsImageRef	imageRef)
{
	EdsInt32	sValue;
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_Contrast|kEdsPropID_AtCapture_Flag, 0, sizeof(sValue),&sValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"Low",			-2,
			"Mid. low",		-1,
			"Standard",		0,
			"Mid. High",	1,
			"High",			2,
		};
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)sValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "Contrast");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_ColorTone::CPropertyItem_ColorTone(EdsImageRef	imageRef)
{
	EdsInt32	sValue;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_ColorTone|kEdsPropID_AtCapture_Flag, 0, sizeof(sValue),&sValue))
	{
		sprintf_s(value, EDS_MAX_NAME, "%d", sValue);
		strcpy_s(m_title, EDS_MAX_NAME, "Color Tone");
		m_value.push_back(value);
	}
}

////////////////////////////////////////////////////////
CPropertyItem_ColorSpace::CPropertyItem_ColorSpace(EdsImageRef	imageRef)
{
	EdsUInt32	uValue;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_ColorSpace|kEdsPropID_AtCapture_Flag, 0, sizeof(uValue),&uValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"sRGB",			1,
			"Adobe RGB",	2,
		};
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)uValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "Color Space");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_PhotoEffect::CPropertyItem_PhotoEffect(EdsImageRef	imageRef)
{
	EdsUInt32	uValue;
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_PhotoEffect|kEdsPropID_AtCapture_Flag, 0, sizeof(uValue),&uValue))
	{
		if(uValue==5)
		{
			strcpy_s(m_title, EDS_MAX_NAME, "Photo Effect");
			m_value.push_back("Black and White");
		}
	}
}

////////////////////////////////////////////////////////
CPropertyItem_FilterEffect::CPropertyItem_FilterEffect(EdsImageRef	imageRef)
{
	EdsUInt32	uValue;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_FilterEffect|kEdsPropID_AtCapture_Flag, 0, sizeof(uValue),&uValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"None",		0,
			"Yellow",	1,
			"Orange",	2,
			"Red",		3,
			"Green",		4,
		};
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)uValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "Filter Effect");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_ToningEffect::CPropertyItem_ToningEffect(EdsImageRef	imageRef)
{
	EdsUInt32	uValue;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_ToningEffect|kEdsPropID_AtCapture_Flag, 0, sizeof(uValue),&uValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"None",		0,
			"Sepia",	1,
			"Blue",		2,
			"Violet",	3,
			"Green",	4,
		};
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)uValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "Toning Effect");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_ToneCurve::CPropertyItem_ToneCurve(EdsImageRef	imageRef)
{
	EdsUInt32	uValue;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_ToneCurve, 0, sizeof(uValue),&uValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"Standard",			0x00,
			"User setting",		0x11,
			"Custom setting",	0x80,
			"TCD1",				0x01,
			"TCD2",				0x02,
			"TCD3",				0x03,
		};
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)uValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "Tone Curve");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_PictureStyle::CPropertyItem_PictureStyle(EdsImageRef	imageRef)
{
	EdsUInt32	uValue;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_PictureStyle|kEdsPropID_AtCapture_Flag, 0, sizeof(uValue),&uValue))
	{
		STR_ID_TABLE propCaptions[] = {
				"Standard",			0x81,
				"Portrait",			0x82,
				"Landscape",		0x83,
				"Neutral",			0x84,
				"Faithful",			0x85,
				"Monochrome",		0x86,
				"User Setting 1",	0x21,
				"User Setting 2",	0x22,
				"User Setting 3",	0x23,
			};
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)uValue);
		if(uValue&0x20)
		{
			// Picture Style Caption
			EdsChar name[64] ={0};
			EdsGetPropertyData( imageRef,kEdsPropID_PictureStyleCaption , 0, sizeof(name), name);
	
			sprintf_s(value, EDS_MAX_NAME, "%s(%s)", tmpString, name);
		}
		else
		{
			sprintf_s(value, EDS_MAX_NAME, "%s", tmpString);
		}
		strcpy_s(m_title, EDS_MAX_NAME, "Picture Style");
		m_value.push_back(value);

		// Picture Style Desc
		EdsPictureStyleDesc psDesc;
		if( EDS_ERR_OK == EdsGetPropertyData( imageRef,kEdsPropID_PictureStyleDesc|kEdsPropID_AtCapture_Flag , 0, sizeof(psDesc), &psDesc))
		{	
			sprintf_s(value , EDS_MAX_NAME , "Contrast:%d", psDesc.contrast);
			m_value.push_back(value);
			
			sprintf_s(value , EDS_MAX_NAME , "Sharpness:%d", psDesc.sharpness);
			m_value.push_back(value);
			
			if(uValue!=kEdsPictureStyle_Monochrome)
			{
				sprintf_s(value , EDS_MAX_NAME , "Saturation:%d", psDesc.saturation);
				m_value.push_back(value);
				
				sprintf_s(value , EDS_MAX_NAME , "ColorTone:%d", psDesc.colorTone);
				m_value.push_back(value);
			}
			else
			{
				STR_ID_TABLE propCaptions[] = {
					"None",		0,
					"Yellow",	1,
					"Orange",	2,
					"Red",		3,
					"Green",	4,
				};
				const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)psDesc.filterEffect);
				sprintf_s(value , EDS_MAX_NAME , "Filter Effect:%s", tmpString);
				m_value.push_back(value);
				
				STR_ID_TABLE propCaptions2[] = {
					"None",		0,
					"Sepia",	1,
					"Blue",		2,
					"Violet",	3,
					"Green",	4,
				};GetPropertyString(propCaptions2, sizeof(propCaptions2)/sizeof(STR_ID_TABLE), (int)psDesc.toningEffect);
				sprintf_s(value , EDS_MAX_NAME , "Toning Effect:%s", tmpString);
				m_value.push_back(value);

			}
		}
	}
}

////////////////////////////////////////////////////////
CPropertyItem_FlashOn::CPropertyItem_FlashOn(EdsImageRef	imageRef)
{
	EdsUInt32	uValue;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_FlashOn, 0, sizeof(uValue),&uValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"Off",	0,
			"On",	1,
		};
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)uValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "Flash On");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_FlashMode::CPropertyItem_FlashMode(EdsImageRef	imageRef)
{
	EdsUInt32	flashMode[2];
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_FlashMode, 0, sizeof(flashMode),&flashMode))
	{
		strcpy_s(m_title, EDS_MAX_NAME, "Flash Mode");
		STR_ID_TABLE propCaptions[] = {
			"None",				0,
			"Internal",			1,
			"external E-TTL",	2,
			"external A-TTL",	3,
		};		
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)flashMode[0]);
		m_value.push_back(tmpString);
		
		STR_ID_TABLE propCaptions2[] = {
			"1st Curtain Synchro",	0,
			"2nd Curtain Synchro",	1,
		};
		tmpString = GetPropertyString(propCaptions2, sizeof(propCaptions2)/sizeof(STR_ID_TABLE), (int)flashMode[1]);
		m_value.push_back(tmpString);
	}
}

////////////////////////////////////////////////////////
CPropertyItem_RedEye::CPropertyItem_RedEye(EdsImageRef	imageRef)
{
	EdsUInt32	uValue;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_RedEye, 0, sizeof(uValue),&uValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"Off",	0,
			"On",	1,
		};
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)uValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "Red-eye Reduction");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_NoiseReduction::CPropertyItem_NoiseReduction(EdsImageRef	imageRef)
{
	EdsUInt32	uValue;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_NoiseReduction, 0, sizeof(uValue),&uValue))
	{
		STR_ID_TABLE propCaptions[] = {
			"Off",		0,
			"On1",		1,
			"On2",		2,
			"On",		3,
			"Auto",		4,
		};
		const char * tmpString = GetPropertyString(propCaptions, sizeof(propCaptions)/sizeof(STR_ID_TABLE), (int)uValue);
		m_value.push_back(tmpString);
		strcpy_s(m_title, EDS_MAX_NAME, "Noise Reduction");
	}
}

////////////////////////////////////////////////////////
CPropertyItem_GPSVersionID::CPropertyItem_GPSVersionID(EdsImageRef	imageRef)
{
	EdsUInt8 gpsVersion[4];
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_GPSVersionID, 0, sizeof(gpsVersion),&gpsVersion))
	{
		strcpy_s(m_title, EDS_MAX_NAME, "GPS Version ID");
		sprintf_s(value, EDS_MAX_NAME, "%d.%d.%d.%d", gpsVersion[0], gpsVersion[1], gpsVersion[2], gpsVersion[3]);
		m_value.push_back(value);
	}
}

////////////////////////////////////////////////////////
CPropertyItem_GPSLatitude::CPropertyItem_GPSLatitude(EdsImageRef	imageRef)
{
	EdsChar latitudeRef;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_GPSLatitudeRef, 0, sizeof(latitudeRef),&latitudeRef))
	{
		EdsRational	latitude[3] = {0};
		EdsInt32 s;
		EdsInt32 m;
		EdsInt32 d;
		EdsGetPropertyData( imageRef,kEdsPropID_GPSLatitude , 0, sizeof(latitude), &latitude);	
		if( latitude[1].denominator == 1 )
		{
			if(latitude[2].numerator >= 60)
			{
				latitude[1].numerator += (latitude[2].numerator / 60);
				latitude[2].numerator %= 60;
			}
			if(latitude[1].numerator >= 60)
			{
				latitude[0].numerator += (latitude[1].numerator / 60);
				latitude[1].numerator %= 60;
			}
			if(latitude[0].numerator >= 90)
			{
				latitude[2].numerator = 0;
				latitude[1].numerator = 0;
				latitude[0].numerator = 90;
			}
			d = latitude[0].numerator;
			s = latitude[1].numerator;
			s = latitude[2].numerator;
		}
		else
		{
			if( latitude[1].denominator != 0 )
			{
				EdsDouble amari = (EdsDouble)(latitude[1].numerator - (latitude[1].numerator / latitude[1].denominator * latitude[1].denominator));
				s = (EdsInt32)(amari * 60 / latitude[1].denominator + 0.5);
				m = (EdsInt32)latitude[1].numerator / latitude[1].denominator;
				d = (EdsInt32)latitude[0].numerator / latitude[0].denominator;
				
				if(s >= 60)
				{
					m += (s / 60);
					s %= 60;
				}
				if(m >= 60)
				{
					d += (m / 60);
					m %= 60;
				}
				if(d >= 90)
				{
					s = 0;
					m = 0;
					d = 90;
				}
			}
		}
		strcpy_s(m_title, EDS_MAX_NAME, "GPS Latitude");
		sprintf_s(value, EDS_MAX_NAME, "%d %d %d %c:", d, m, s, latitudeRef);
		m_value.push_back(value);
	}
}

////////////////////////////////////////////////////////
CPropertyItem_GPSLongitude::CPropertyItem_GPSLongitude(EdsImageRef	imageRef)
{
	EdsChar longitudeRef;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_GPSLongitudeRef, 0, sizeof(longitudeRef),&longitudeRef))
	{
		EdsRational	longitude[3] = {0};
		EdsInt32 s;
		EdsInt32 m;
		EdsInt32 d;
		EdsGetPropertyData( imageRef,kEdsPropID_GPSLongitude , 0, sizeof(longitude), &longitude);	
		if( longitude[1].denominator == 1 )
		{
			if(longitude[2].numerator >= 60)
			{
				longitude[1].numerator += (longitude[2].numerator / 60);
				longitude[2].numerator %= 60;
			}
			if(longitude[1].numerator >= 60)
			{
				longitude[0].numerator += (longitude[1].numerator / 60);
				longitude[1].numerator %= 60;
			}
			if(longitude[0].numerator >= 180)
			{
				longitude[2].numerator = 0;
				longitude[1].numerator = 0;
				longitude[0].numerator = 180;
					}
			d = longitude[0].numerator;
			s = longitude[1].numerator;
			s = longitude[2].numerator;
		}
		else
		{
			if( longitude[1].denominator != 0 )
			{
				EdsDouble amari = (EdsDouble)(longitude[1].numerator - (longitude[1].numerator / longitude[1].denominator * longitude[1].denominator));
				s = (EdsInt32)(amari * 60 / longitude[1].denominator + 0.5);
				m = (EdsInt32)longitude[1].numerator / longitude[1].denominator;
				d = (EdsInt32)longitude[0].numerator / longitude[0].denominator;
				
				if(s >= 60)
				{
					m += (s / 60);
					s %= 60;
				}
				if(m >= 60)
				{
					d += (m / 60);
					m %= 60;
				}
				if(d >= 180)
				{
					s = 0;
					m = 0;
					d = 180;
				}
			}
		}
		strcpy_s(m_title, EDS_MAX_NAME, "GPS Longitude");
		sprintf_s(value, EDS_MAX_NAME, "%d %d %d %c:", d, m, s, longitudeRef);
		m_value.push_back(value);
	}
}

////////////////////////////////////////////////////////
CPropertyItem_GPSAltitude::CPropertyItem_GPSAltitude(EdsImageRef	imageRef)
{
	EdsUInt8	alitudeRef;
	EdsRational	rational;
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_GPSAltitudeRef, 0, sizeof(alitudeRef),&alitudeRef))
	{
		EdsGetPropertyData( imageRef,kEdsPropID_GPSAltitude , 0, sizeof(rational), &rational);	
		// negative value
		if( alitudeRef == 1)
		{	
			sprintf_s( value , EDS_MAX_NAME , "-%.2fm" , (EdsFloat)rational.numerator/rational.denominator );
		}
		// 
		else
		{
			sprintf_s( value , EDS_MAX_NAME , "%.2fm" ,(EdsFloat)rational.numerator/rational.denominator  );
		}
		strcpy_s(m_title, EDS_MAX_NAME, "GPS Altitude");
		m_value.push_back(value);
	}
}

////////////////////////////////////////////////////////
CPropertyItem_GPSDateStamp::CPropertyItem_GPSDateStamp(EdsImageRef	imageRef)
{
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_GPSDateStamp, 0, sizeof(value),&value))
	{
		strcpy_s(m_title, EDS_MAX_NAME, "GPS Date Stamp");
		m_value.push_back(value);
	}
}

////////////////////////////////////////////////////////
CPropertyItem_GPSTimeStamp::CPropertyItem_GPSTimeStamp(EdsImageRef	imageRef)
{
	EdsRational timeStamp[3];
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_GPSTimeStamp, 0, sizeof(timeStamp),&timeStamp))
	{
		if(timeStamp[0].denominator != 0 && timeStamp[1].denominator != 0 && timeStamp[2].denominator != 0)
			sprintf_s( value , EDS_MAX_NAME , "%02d:%02d:%02d" , timeStamp[0].numerator/ timeStamp[0].denominator , timeStamp[1].numerator/ timeStamp[1].denominator , timeStamp[2].numerator/ timeStamp[2].denominator );
		strcpy_s(m_title, EDS_MAX_NAME, "GPS Time Stamp");
		m_value.push_back(value);
	}
}

////////////////////////////////////////////////////////
CPropertyItem_GPSMapDatum::CPropertyItem_GPSMapDatum(EdsImageRef	imageRef)
{
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_GPSMapDatum, 0, sizeof(value),&value))
	{
		strcpy_s(m_title, EDS_MAX_NAME, "GPS Map Datum");
		m_value.push_back(value);
	}
}

////////////////////////////////////////////////////////
CPropertyItem_GPSSatellites::CPropertyItem_GPSSatellites(EdsImageRef	imageRef)
{
	char value[EDS_MAX_NAME]  = {0};
	if( EDS_ERR_OK == EdsGetPropertyData( imageRef, kEdsPropID_GPSSatellites, 0, sizeof(value),&value))
	{
		strcpy_s(m_title, EDS_MAX_NAME, "GPS Satellites");
		m_value.push_back(value);
	}
}



////////////////////////////////////////////////////////
CPropertyString::CPropertyString(void)
{
	m_ImgRef = NULL;
	m_propItem = NULL;
}

CPropertyString::~CPropertyString(void)
{
	if(m_ImgRef!=NULL)	EdsRelease(m_ImgRef);
	if(m_propItem!=NULL)	delete m_propItem;
	m_ImgRef = NULL;
	m_propItem = NULL;
}

CPropertyString::CPropertyString(EdsImageRef	imageRef)
{
	m_ImgRef = imageRef;
	EdsRetain(m_ImgRef);
	m_propItem = NULL;
}

EdsError CPropertyString::SetImageRef(EdsImageRef	imageRef)
{
	if(m_ImgRef!=NULL)	EdsRelease(m_ImgRef);
	if(m_propItem!=NULL)	delete m_propItem;
	m_ImgRef = imageRef;
	EdsRetain(m_ImgRef);
	return EDS_ERR_OK;
}

EdsError CPropertyString::SetPropertyID(EdsPropertyID	propID)
{
	EdsError err = EDS_ERR_OK;
	
	if(m_propItem!=NULL){delete m_propItem;	m_propItem=NULL;}

	switch(propID)
	{
	case kEdsPropID_MakerName:
		m_propItem = new CPropertyItem_MakerName(m_ImgRef);
		break;
	case kEdsPropID_ProductName:
		m_propItem = new CPropertyItem_ProductName(m_ImgRef);
		break;
	case kEdsPropID_DateTime:
		m_propItem = new CPropertyItem_DateTime(m_ImgRef);
		break;
	case kEdsPropID_Tv:
		m_propItem = new CPropertyItem_Tv(m_ImgRef);
		break;
	case kEdsPropID_Av:
		m_propItem = new CPropertyItem_Av(m_ImgRef);
		break;
	case kEdsPropID_ISOSpeed:
		m_propItem = new CPropertyItem_ISOSpeed(m_ImgRef);
		break;
	case kEdsPropID_FocalLength:
		m_propItem = new CPropertyItem_FocalLength(m_ImgRef);
		break;
	case kEdsPropID_LensName:
		m_propItem = new CPropertyItem_LensName(m_ImgRef);
		break;
	case kEdsPropID_BodyID:
		m_propItem = new CPropertyItem_BodyID(m_ImgRef);
		break;
	case kEdsPropID_OwnerName:
		m_propItem = new CPropertyItem_OwnerName(m_ImgRef);
		break;
	case kEdsPropID_Artist:
		m_propItem = new CPropertyItem_Artist(m_ImgRef);
		break;
	case kEdsPropID_Copyright:
		m_propItem = new CPropertyItem_Copyright(m_ImgRef);
		break;
	case kEdsPropID_FirmwareVersion:
		m_propItem = new CPropertyItem_FirmwareVersion(m_ImgRef);
		break;
	case kEdsPropID_JpegQuality:
		m_propItem = new CPropertyItem_JpegQuality(m_ImgRef);
		break;
	case kEdsPropID_Orientation:
		m_propItem = new CPropertyItem_Orientation(m_ImgRef);
		break;
	case kEdsPropID_AEMode:
		m_propItem = new CPropertyItem_AEMode(m_ImgRef);
		break;
	case kEdsPropID_DriveMode:
		m_propItem = new CPropertyItem_DriveMode(m_ImgRef);
		break;
	case kEdsPropID_MeteringMode:
		m_propItem = new CPropertyItem_MeteringMode(m_ImgRef);
		break;
	case kEdsPropID_AFMode:
		m_propItem = new CPropertyItem_AFMode(m_ImgRef);
		break;
	case kEdsPropID_ExposureCompensation:
		m_propItem = new CPropertyItem_ExposureCompensation(m_ImgRef);
		break;
	case kEdsPropID_DigitalExposure:
		m_propItem = new CPropertyItem_DigitalExposure(m_ImgRef);
		break;
	case kEdsPropID_FlashCompensation:
		m_propItem = new CPropertyItem_FlashCompensation(m_ImgRef);
		break;
	case kEdsPropID_Bracket:
		m_propItem = new CPropertyItem_Bracket(m_ImgRef);
		break;
	case kEdsPropID_WhiteBalance:
		m_propItem = new CPropertyItem_WhiteBalance(m_ImgRef);
		break;
	case kEdsPropID_WhiteBalanceShift:
		m_propItem = new CPropertyItem_WhiteBalanceShift(m_ImgRef);
		break;
	case kEdsPropID_Sharpness:
		m_propItem = new CPropertyItem_Sharpness(m_ImgRef);
		break;
	case kEdsPropID_ColorSaturation:
		m_propItem = new CPropertyItem_ColorSaturation(m_ImgRef);
		break;
	case kEdsPropID_ColorMatrix:
		m_propItem = new CPropertyItem_ColorMatrix(m_ImgRef);
		break;
	case kEdsPropID_Contrast:
		m_propItem = new CPropertyItem_Contrast(m_ImgRef);
		break;
	case kEdsPropID_ColorTone:
		m_propItem = new CPropertyItem_ColorTone(m_ImgRef);
		break;
	case kEdsPropID_ColorSpace:
		m_propItem = new CPropertyItem_ColorSpace(m_ImgRef);
		break;
	case kEdsPropID_PhotoEffect:
		m_propItem = new CPropertyItem_PhotoEffect(m_ImgRef);
		break;
	case kEdsPropID_FilterEffect:
		m_propItem = new CPropertyItem_FilterEffect(m_ImgRef);
		break;
	case kEdsPropID_ToningEffect:
		m_propItem = new CPropertyItem_ToningEffect(m_ImgRef);
		break;
	case kEdsPropID_ToneCurve:
		m_propItem = new CPropertyItem_ToneCurve(m_ImgRef);
		break;
	case kEdsPropID_PictureStyle:
		m_propItem = new CPropertyItem_PictureStyle(m_ImgRef);
		break;
	case kEdsPropID_FlashOn:
		m_propItem = new CPropertyItem_FlashOn(m_ImgRef);
		break;
	case kEdsPropID_FlashMode:
		m_propItem = new CPropertyItem_FlashMode(m_ImgRef);
		break;
	case kEdsPropID_RedEye:
		m_propItem = new CPropertyItem_RedEye(m_ImgRef);
		break;
	case kEdsPropID_NoiseReduction:
		m_propItem = new CPropertyItem_NoiseReduction(m_ImgRef);
		break;
	case kEdsPropID_GPSVersionID:
		m_propItem = new CPropertyItem_GPSVersionID(m_ImgRef);
		break;
	case kEdsPropID_GPSLatitude:
		m_propItem = new CPropertyItem_GPSLatitude(m_ImgRef);
		break;
	case kEdsPropID_GPSLongitude:
		m_propItem = new CPropertyItem_GPSLongitude(m_ImgRef);
		break;
	case kEdsPropID_GPSAltitude:
		m_propItem = new CPropertyItem_GPSAltitude(m_ImgRef);
		break;
	case kEdsPropID_GPSDateStamp:
		m_propItem = new CPropertyItem_GPSDateStamp(m_ImgRef);
		break;
	case kEdsPropID_GPSTimeStamp:
		m_propItem = new CPropertyItem_GPSTimeStamp(m_ImgRef);
		break;
	case kEdsPropID_GPSSatellites:
		m_propItem = new CPropertyItem_GPSSatellites(m_ImgRef);
		break;
	default:
		err = EDS_ERR_NOT_SUPPORTED;
		break;
	}
	return err;
}

EdsError CPropertyString::SetImageSource(EdsImageSource	imgSrc)
{
	EdsError err = EDS_ERR_OK;
	if(m_propItem!=NULL)
	{
		delete m_propItem;
		m_propItem=NULL;
	}
	switch(imgSrc)
	{
	case kEdsImageSrc_RAWThumbnail:
		m_propItem = new CPropertyItem_Thumbnail(m_ImgRef);
		break;
	case kEdsImageSrc_RAWFullView:
		m_propItem = new CPropertyItem_FullView(m_ImgRef);
		break;
	default:
		err = EDS_ERR_NOT_SUPPORTED;
		break;
	}
	return err;
}

EdsError CPropertyString::GetPropertyTitle(EdsUInt32	*ioSize, EdsChar *outTitle)
{
	EdsError err = EDS_ERR_INVALID_PARAMETER;
	if(m_propItem!=NULL) err = m_propItem->GetPropertyTitle(ioSize, outTitle);
	return err;
}

EdsError CPropertyString::GetPropertyValueCount(EdsUInt32	*outCount)
{
	EdsError err = EDS_ERR_INVALID_PARAMETER;
	if(m_propItem!=NULL) err = m_propItem->GetPropertyValueCount(outCount);
	return err;
}

EdsError CPropertyString::GetPropertyValue(EdsUInt32	index, EdsUInt32	*ioSize, EdsChar *outValue)
{
	EdsError err = EDS_ERR_INVALID_PARAMETER;
	if(m_propItem!=NULL) err = m_propItem->GetPropertyValue(index, ioSize, outValue);
	return err;
}
