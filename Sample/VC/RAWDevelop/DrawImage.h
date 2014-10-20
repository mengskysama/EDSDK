/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : DrawImage.h                                                     *
*                                                                             *
*   Description: This is the Sample code to show the usage of EDSDK.          *
*                                                                             *
*                                                                             *
*******************************************************************************
*                                                                             *
*   Written and developed by Camera Design Dept.53                            *
*   Copyright Canon Inc. 2006 All Rights Reserved                             *
*                                                                             *
*******************************************************************************
*   File Update Information:                                                  *
*     DATE      Identify    Comment                                           *
*   -----------------------------------------------------------------------   *
*   06-03-22    F-001        create first version.                            *
*                                                                             *
******************************************************************************/

#ifndef _DrawImage_H
#define _DrawImage_H

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class CDrawImage  
{
#define DIBPIXSIZE 3
protected:
	HDC				m_hdcMem;
	HBITMAP			m_hBMP;
	LPBITMAPINFO	m_lpDIB;
    LPBYTE			m_lpBMP;
    
    int m_nWidth;
    int m_nHeight;
	int m_nBitCount;
	int	m_nPadding;

public:
	HBITMAP  GetHBMP( ){return m_hBMP;};

	//------------------------------------------------------------------------------
	// CDrawImage
	//------------------------------------------------------------------------------
	CDrawImage( CSize size ):m_lpDIB(NULL),m_hdcMem(NULL),m_hBMP(NULL),m_nWidth(size.cx),m_nHeight(size.cy)
	{
		m_lpDIB=(LPBITMAPINFO)GlobalAlloc(GPTR,
					sizeof(BITMAPINFOHEADER)
					+ sizeof(DWORD)*2); 
		if( m_lpDIB == NULL )
			return ;

		m_nBitCount= DIBPIXSIZE*8;

		m_lpDIB->bmiHeader.biSize			= sizeof( BITMAPINFOHEADER );
		m_lpDIB->bmiHeader.biWidth			= m_nWidth;
		m_lpDIB->bmiHeader.biHeight			= m_nHeight*(-1);
		m_lpDIB->bmiHeader.biPlanes			= 1;
		m_lpDIB->bmiHeader.biBitCount		= m_nBitCount;
		m_lpDIB->bmiHeader.biCompression	= BI_RGB;
		m_lpDIB->bmiHeader.biSizeImage		= 0;
		m_lpDIB->bmiHeader.biXPelsPerMeter	= 0;
		m_lpDIB->bmiHeader.biYPelsPerMeter	= 0;
		m_lpDIB->bmiHeader.biClrUsed		= 0;
		m_lpDIB->bmiHeader.biClrImportant	= 0;

		m_hBMP   = CreateDIBSection( NULL,m_lpDIB, DIB_RGB_COLORS, (VOID **)&m_lpBMP, NULL, 0 );
		if( m_hBMP == NULL )
		{
			GlobalFree( HGLOBAL(m_lpDIB) );
			m_lpDIB=NULL;
			return ;
		}

		m_hdcMem = CreateCompatibleDC( NULL );
		if( m_hdcMem == NULL )
		{
			GlobalFree( HGLOBAL(m_lpDIB) );
			DeleteObject( m_hBMP );
			m_lpDIB=NULL;
			m_hBMP=NULL;
			return ;
		}

		SelectObject( m_hdcMem, m_hBMP );
		m_nPadding = (sizeof(long)-(((m_nWidth)*DIBPIXSIZE)%sizeof(long)))%sizeof(long);
		
		Clear();
	}

	//------------------------------------------------------------------------------
	//~CDrawImage()
	//------------------------------------------------------------------------------
	~CDrawImage()
	{
		if( m_lpDIB )
		{
			GlobalFree( m_lpDIB );
			DeleteObject( m_hBMP );
	 		DeleteDC( m_hdcMem ); 
		}
	}

	//------------------------------------------------------------------------------
	// void Clear( BYTE n=0x80 )
	//------------------------------------------------------------------------------
	void Clear( BYTE n=0x80 )
	{
		if( m_lpDIB )
			memset( m_lpBMP, n, (DIBPIXSIZE*m_nWidth+m_nPadding)*m_nHeight );
	}

	//------------------------------------------------------------------------------
	// bool SetImage( int width , int height , const void *pRGB )
	//------------------------------------------------------------------------------
	bool SetImage( int width , int height , const void *pRGB )
	{
		const unsigned char *p=(const unsigned char *)pRGB;
		for(int y=0;y<height;y++)
		{
			unsigned char *pdst=m_lpBMP+(DIBPIXSIZE*m_nWidth+m_nPadding)*y;
			for(int x=0;x<width;x++)
			{
				*(pdst+2) = *(p++);	// B <- R
				*(pdst+1) = *(p++);	// G <- G
				*(pdst+0) = *(p++);	// R <- B
				pdst += 3;
			}
		}
		return true;
	}

	//------------------------------------------------------------------------------
	// int GetWidth( ) const
	//------------------------------------------------------------------------------
	int GetWidth( ) const
	{
		return m_nWidth; 
	}

	//------------------------------------------------------------------------------
	// int GetHeight( ) const
	//------------------------------------------------------------------------------
	int GetHeight( ) const
	{
		return m_nHeight; 
	}

	//------------------------------------------------------------------------------
	// void Draw( HDC hDC )
	//------------------------------------------------------------------------------
	void Draw( HDC hDC )
	{
		BitBlt( hDC, 0, 0, m_nWidth, m_nHeight , m_hdcMem, 0, 0, SRCCOPY );
	}
};

#endif	// _DrawImage_H
