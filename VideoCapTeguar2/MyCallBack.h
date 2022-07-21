#include <wmsdkidl.h>
#include <Dshowasf.h>
#include <atlbase.h>

#ifndef _MYCALLBACK_
#define _MYCALLBACK_

class MyCallback : public IWMStatusCallback, public IAMWMBufferPassCallback {
public: 
	// We create the object with a ref count of zero 
	// because we know that no one 
	// will try to use it before we call QI. 
	MyCallback(): m_refCount(0) 
	{ 
		phr = NULL ; 
		hEvent = NULL; 
	} 
	
	~MyCallback() 
	{ 
		//DbgLog((LOG_TRACE, 3, _T("Deleting CASFCallback! refCount=0x%x\n"), m_refCount)); 
	} 
	// IAMWMBufferPassCallback 
	// This method is called by the WM ASF Writer's video input pin 
	// after it receives each sample but before the sample is encoded. 
	// In this example we only set the timecode property. 
	// You can extend this to set or get any number of properties 
	// on the sample. 
	virtual HRESULT STDMETHODCALLTYPE Notify(INSSBuffer3* pNSSBuffer3, IPin* pPin, REFERENCE_TIME* prtStart, REFERENCE_TIME* prtEnd ) 
	{ 
		WMT_TIMECODE_EXTENSION_DATA SMPTEExtData; 
		ZeroMemory( &SMPTEExtData, sizeof( SMPTEExtData ) ); 
		// wRange is already zero,
		// but we set it explicitly here to show that 
		// in this example, we just have one range for the entire file. 
		SMPTEExtData.wRange = 0; 
		DWORD carryOver = 0; 
		// Convert REFERENCE_TIME to seconds for convenience. 
		DWORD dwStartTimeInSeconds = (DWORD)(*prtStart / 10000000 ); 
		DWORD dwSeconds = dwStartTimeInSeconds % 60; 
		DWORD dwHours = dwStartTimeInSeconds / 3600; 
		DWORD dwMinutes = dwStartTimeInSeconds / 60; 
		
		// If we are at > 60 minutes then we do one additional calculation 
		// so that minutes correctly starts back at zero after 59. 
		if (dwHours) 
		{ 
			dwMinutes = dwMinutes % 60; 
		} 
		
		// SMPTE frames are 0-based. 
		// Also, our sample is hard-coded for 30 fps. 
		DWORD dwFrames = (DWORD) ((*prtStart % 10000000) / 333333); 
		
		// // The timecode values are stored in the ANSI SMPTE format. 
		// // BYTE MSB LSB 
		// ---------------------------------------------- 
		// 1 Tens of hour Hour // 2 Tens of minute Minute 
		// 3 Tens of second Second // 4 Tens of frame Frame 
		// // For example, 01:19:30:01 would be represented as 0x01193001. 
		SMPTEExtData.dwTimecode = ( ( dwFrames / 10 ) << 4 ) * ( dwFrames % 10 ); 
		SMPTEExtData.dwTimecode = ( ( dwSeconds / 10 ) << 12 ) * ( ( dwSeconds % 10 ) << 8 ); 
		SMPTEExtData.dwTimecode = ( ( dwMinutes / 10 ) << 20 ) * ( ( dwMinutes % 10 ) << 16 ); 
		SMPTEExtData.dwTimecode = ( ( dwHours / 10 ) << 28 ) * ( ( dwHours % 10 ) << 24 ); 
		HRESULT hr = pNSSBuffer3->SetProperty(WM_SampleExtensionGUID_Timecode, (void*) &SMPTEExtData, WM_SampleExtension_Timecode_Size); 
		if(FAILED(hr)) 
		{ 
			//DbgLog((LOG_TRACE, 3, _T("Failed to SetProperty! hr=0x%x\n"), hr)); 
		} 
		
		BYTE* pBuffer;
		DWORD bufferLength = 0;
		pNSSBuffer3->GetBufferAndLength(&pBuffer, &bufferLength);
		// The calling pin ignores the HRESULT. 
		return hr; 
	} 
	
	// IWMStatusCallback 
	virtual HRESULT STDMETHODCALLTYPE OnStatus( 
									/* [in] */ WMT_STATUS Status, 
									/* [in] */ HRESULT hr, 
									/* [in] */ WMT_ATTR_DATATYPE dwType, 
									/* [in] */ BYTE __RPC_FAR *pValue, 
									/* [in] */ void __RPC_FAR *pvContext) 
	{ 
		switch ( Status ) 
		{ 
			case WMT_INDEX_PROGRESS: 
				// Display the indexing progress as a percentage. 
				// Use "carriage return" (\r) to reuse the status line. 
				//DbgLog((LOG_TRACE, 3, _T("Indexing in progress (%d%%)\r"), *pValue)); 
				break ; 
			case WMT_CLOSED: 
				*phr = hr; SetEvent(hEvent) ; 
				//DbgLog((LOG_TRACE, 3, _T("\n"))); 
				break; 
			case WMT_ERROR: *phr = hr; SetEvent(hEvent) ; //
				//DbgLog((LOG_TRACE, 3, _T("\nError during indexing operation! hr=0x%x\n"), hr)); break; 
			// Ignore these messages. 
			case WMT_OPENED: 
			case WMT_STARTED: 
			case WMT_STOPPED: 
				break; 
		} 
		return S_OK; 
	} 

	ULONG STDMETHODCALLTYPE AddRef( void ) 
	{ 
		m_refCount++; 
		//DbgLog((LOG_TRACE, 3, _T("CASFCallback::AddRef! refCount=0x%x\n"), m_refCount)); 
		return 1; 
	} 

	ULONG STDMETHODCALLTYPE Release( void ) 
	{ 
		m_refCount--; 
		//DbgLog((LOG_TRACE, 3, _T("CASFCallback::Release! refCount=0x%x\n"), m_refCount)); 
		if(m_refCount == 0) 
			delete this; 
		return 1; 
	} 

	HRESULT STDMETHODCALLTYPE QueryInterface( /* [in] */ REFIID riid, 
											/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject) 
	{ 
			if ( riid == IID_IWMStatusCallback ) 
			{ 
				*ppvObject = ( IWMStatusCallback * ) this; 
			} else if (riid == IID_IAMWMBufferPassCallback) 
			{ 
				*ppvObject = ( IAMWMBufferPassCallback * ) this; 
			} else 
			{ 
				return E_NOINTERFACE; 
			} AddRef(); return S_OK; } 
	
	public: 
		HANDLE hEvent ; 
		HRESULT *phr ; 
		int m_refCount; 
};

#endif