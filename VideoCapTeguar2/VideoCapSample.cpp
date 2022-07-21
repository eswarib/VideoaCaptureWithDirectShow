// VideoCapSample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#import "sbeio.dll"

#include <iostream>
//#include "stdafx.h"
//#include <dbt.h>
//#include <mmreg.h>
//#include <msacm.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
//#include <commdlg.h>
#include <strsafe.h>
//#include "stdafx.h"
//#include "amcap.h"
//#include "status.h"
//#include "crossbar.h"
//#include "SampleCGB.h"
#include <strmif.h>
#include <Dshow.h>
#include <dshowasf.h>
#include <assert.h>
#include <string>
#include <dmo.h>
//#include <Mtype.h>
#include "namedguid.h"

#include <comutil.h>
#include <sbe.h>
#include "MyCallBack.h"
//#include <Amfilter.h>
//
// Create a large table to allow searches by CLSID, media type, IID, etc.
//

#define WIN32_DEFAULT_LIBS

extern const IID IID_IStreamBufferConfigure3;
const NamedGuid rgng[] =
{
    {&MEDIASUBTYPE_AIFF, TEXT("MEDIASUBTYPE_AIFF\0")},
    {&MEDIASUBTYPE_AU, TEXT("MEDIASUBTYPE_AU\0")},
    {&MEDIASUBTYPE_AnalogVideo_NTSC_M, TEXT("MEDIASUBTYPE_AnalogVideo_NTSC_M\0")},
    {&MEDIASUBTYPE_AnalogVideo_PAL_B, TEXT("MEDIASUBTYPE_AnalogVideo_PAL_B\0")},
    {&MEDIASUBTYPE_AnalogVideo_PAL_D, TEXT("MEDIASUBTYPE_AnalogVideo_PAL_D\0")},
    {&MEDIASUBTYPE_AnalogVideo_PAL_G, TEXT("MEDIASUBTYPE_AnalogVideo_PAL_G\0")},
    {&MEDIASUBTYPE_AnalogVideo_PAL_H, TEXT("MEDIASUBTYPE_AnalogVideo_PAL_H\0")},
    {&MEDIASUBTYPE_AnalogVideo_PAL_I, TEXT("MEDIASUBTYPE_AnalogVideo_PAL_I\0")},
    {&MEDIASUBTYPE_AnalogVideo_PAL_M, TEXT("MEDIASUBTYPE_AnalogVideo_PAL_M\0")},
    {&MEDIASUBTYPE_AnalogVideo_PAL_N, TEXT("MEDIASUBTYPE_AnalogVideo_PAL_N\0")},
    {&MEDIASUBTYPE_AnalogVideo_SECAM_B, TEXT("MEDIASUBTYPE_AnalogVideo_SECAM_B\0")},
    {&MEDIASUBTYPE_AnalogVideo_SECAM_D, TEXT("MEDIASUBTYPE_AnalogVideo_SECAM_D\0")},
    {&MEDIASUBTYPE_AnalogVideo_SECAM_G, TEXT("MEDIASUBTYPE_AnalogVideo_SECAM_G\0")},
    {&MEDIASUBTYPE_AnalogVideo_SECAM_H, TEXT("MEDIASUBTYPE_AnalogVideo_SECAM_H\0")},
    {&MEDIASUBTYPE_AnalogVideo_SECAM_K, TEXT("MEDIASUBTYPE_AnalogVideo_SECAM_K\0")},
    {&MEDIASUBTYPE_AnalogVideo_SECAM_K1, TEXT("MEDIASUBTYPE_AnalogVideo_SECAM_K1\0")},
    {&MEDIASUBTYPE_AnalogVideo_SECAM_L, TEXT("MEDIASUBTYPE_AnalogVideo_SECAM_L\0")},

    {&MEDIASUBTYPE_ARGB1555, TEXT("MEDIASUBTYPE_ARGB1555\0")},
    {&MEDIASUBTYPE_ARGB4444, TEXT("MEDIASUBTYPE_ARGB4444\0")},
    {&MEDIASUBTYPE_ARGB32, TEXT("MEDIASUBTYPE_ARGB32\0")},
    {&MEDIASUBTYPE_A2R10G10B10, TEXT("MEDIASUBTYPE_A2R10G10B10\0")},
    {&MEDIASUBTYPE_A2B10G10R10, TEXT("MEDIASUBTYPE_A2B10G10R10\0")},

    {&MEDIASUBTYPE_AYUV, TEXT("MEDIASUBTYPE_AYUV\0")},
    {&MEDIASUBTYPE_AI44, TEXT("MEDIASUBTYPE_AI44\0")},
    {&MEDIASUBTYPE_IA44, TEXT("MEDIASUBTYPE_IA44\0")},
    {&MEDIASUBTYPE_NV12, TEXT("MEDIASUBTYPE_NV12\0")},
    {&MEDIASUBTYPE_IMC1, TEXT("MEDIASUBTYPE_IMC1\0")},
    {&MEDIASUBTYPE_IMC2, TEXT("MEDIASUBTYPE_IMC2\0")},
    {&MEDIASUBTYPE_IMC3, TEXT("MEDIASUBTYPE_IMC3\0")},
    {&MEDIASUBTYPE_IMC4, TEXT("MEDIASUBTYPE_IMC4\0")},

    {&MEDIASUBTYPE_Asf, TEXT("MEDIASUBTYPE_Asf\0")},
    {&MEDIASUBTYPE_Avi, TEXT("MEDIASUBTYPE_Avi\0")},
    {&MEDIASUBTYPE_CFCC, TEXT("MEDIASUBTYPE_CFCC\0")},
    {&MEDIASUBTYPE_CLJR, TEXT("MEDIASUBTYPE_CLJR\0")},
    {&MEDIASUBTYPE_CPLA, TEXT("MEDIASUBTYPE_CPLA\0")},
    {&MEDIASUBTYPE_CLPL, TEXT("MEDIASUBTYPE_CLPL\0")},
    {&MEDIASUBTYPE_DOLBY_AC3, TEXT("MEDIASUBTYPE_DOLBY_AC3\0")},
    {&MEDIASUBTYPE_DOLBY_AC3_SPDIF, TEXT("MEDIASUBTYPE_DOLBY_AC3_SPDIF\0")},
    {&MEDIASUBTYPE_DVCS, TEXT("MEDIASUBTYPE_DVCS\0")},
    {&MEDIASUBTYPE_DVD_LPCM_AUDIO, TEXT("MEDIASUBTYPE_DVD_LPCM_AUDIO\0")},
    {&MEDIASUBTYPE_DVD_NAVIGATION_DSI, TEXT("MEDIASUBTYPE_DVD_NAVIGATION_DSI\0")},
    {&MEDIASUBTYPE_DVD_NAVIGATION_PCI, TEXT("MEDIASUBTYPE_DVD_NAVIGATION_PCI\0")},
    {&MEDIASUBTYPE_DVD_NAVIGATION_PROVIDER, TEXT("MEDIASUBTYPE_DVD_NAVIGATION_PROVIDER\0")},
    {&MEDIASUBTYPE_DVD_SUBPICTURE, TEXT("MEDIASUBTYPE_DVD_SUBPICTURE\0")},
    {&MEDIASUBTYPE_DVSD, TEXT("MEDIASUBTYPE_DVSD\0")},
    {&MEDIASUBTYPE_DRM_Audio, TEXT("MEDIASUBTYPE_DRM_Audio\0")},
    {&MEDIASUBTYPE_DssAudio, TEXT("MEDIASUBTYPE_DssAudio\0")},
    {&MEDIASUBTYPE_DssVideo, TEXT("MEDIASUBTYPE_DssVideo\0")},
    {&MEDIASUBTYPE_IF09, TEXT("MEDIASUBTYPE_IF09\0")},
    {&MEDIASUBTYPE_IEEE_FLOAT, TEXT("MEDIASUBTYPE_IEEE_FLOAT\0")},
    {&MEDIASUBTYPE_IJPG, TEXT("MEDIASUBTYPE_IJPG\0")},
    {&MEDIASUBTYPE_IYUV, TEXT("MEDIASUBTYPE_IYUV\0")},
    {&MEDIASUBTYPE_Line21_BytePair, TEXT("MEDIASUBTYPE_Line21_BytePair\0")},
    {&MEDIASUBTYPE_Line21_GOPPacket, TEXT("MEDIASUBTYPE_Line21_GOPPacket\0")},
    {&MEDIASUBTYPE_Line21_VBIRawData, TEXT("MEDIASUBTYPE_Line21_VBIRawData\0")},
    {&MEDIASUBTYPE_MDVF, TEXT("MEDIASUBTYPE_MDVF\0")},
    {&MEDIASUBTYPE_MJPG, TEXT("MEDIASUBTYPE_MJPG\0")},
    {&MEDIASUBTYPE_MPEG1Audio, TEXT("MEDIASUBTYPE_MPEG1Audio\0")},
    {&MEDIASUBTYPE_MPEG1AudioPayload, TEXT("MEDIASUBTYPE_MPEG1AudioPayload\0")},
    {&MEDIASUBTYPE_MPEG1Packet, TEXT("MEDIASUBTYPE_MPEG1Packet\0")},
    {&MEDIASUBTYPE_MPEG1Payload, TEXT("MEDIASUBTYPE_MPEG1Payload\0")},
    {&MEDIASUBTYPE_MPEG1System, TEXT("MEDIASUBTYPE_MPEG1System\0")},
    {&MEDIASUBTYPE_MPEG1Video, TEXT("MEDIASUBTYPE_MPEG1Video\0")},
    {&MEDIASUBTYPE_MPEG1VideoCD, TEXT("MEDIASUBTYPE_MPEG1VideoCD\0")},
    {&MEDIASUBTYPE_MPEG2_AUDIO, TEXT("MEDIASUBTYPE_MPEG2_AUDIO\0")},
    {&MEDIASUBTYPE_MPEG2_PROGRAM, TEXT("MEDIASUBTYPE_MPEG2_PROGRAM\0")},
    {&MEDIASUBTYPE_MPEG2_TRANSPORT, TEXT("MEDIASUBTYPE_MPEG2_TRANSPORT\0")},
    {&MEDIASUBTYPE_MPEG2_VIDEO, TEXT("MEDIASUBTYPE_MPEG2_VIDEO\0")},
    {&MEDIASUBTYPE_None, TEXT("MEDIASUBTYPE_None\0")},
    {&MEDIASUBTYPE_Overlay, TEXT("MEDIASUBTYPE_Overlay\0")},
    {&MEDIASUBTYPE_PCM, TEXT("MEDIASUBTYPE_PCM\0")},
    {&MEDIASUBTYPE_PCMAudio_Obsolete, TEXT("MEDIASUBTYPE_PCMAudio_Obsolete\0")},
    {&MEDIASUBTYPE_Plum, TEXT("MEDIASUBTYPE_Plum\0")},
    {&MEDIASUBTYPE_QTJpeg, TEXT("MEDIASUBTYPE_QTJpeg\0")},
    {&MEDIASUBTYPE_QTMovie, TEXT("MEDIASUBTYPE_QTMovie\0")},
    {&MEDIASUBTYPE_QTRle, TEXT("MEDIASUBTYPE_QTRle\0")},
    {&MEDIASUBTYPE_QTRpza, TEXT("MEDIASUBTYPE_QTRpza\0")},
    {&MEDIASUBTYPE_QTSmc, TEXT("MEDIASUBTYPE_QTSmc\0")},
    {&MEDIASUBTYPE_RAW_SPORT, TEXT("MEDIASUBTYPE_RAW_SPORT\0")},
    {&MEDIASUBTYPE_RGB1, TEXT("MEDIASUBTYPE_RGB1\0")},
    {&MEDIASUBTYPE_RGB24, TEXT("MEDIASUBTYPE_RGB24\0")},
    {&MEDIASUBTYPE_RGB32, TEXT("MEDIASUBTYPE_RGB32\0")},
    {&MEDIASUBTYPE_RGB4, TEXT("MEDIASUBTYPE_RGB4\0")},
    {&MEDIASUBTYPE_RGB555, TEXT("MEDIASUBTYPE_RGB555\0")},
    {&MEDIASUBTYPE_RGB565, TEXT("MEDIASUBTYPE_RGB565\0")},
    {&MEDIASUBTYPE_RGB8, TEXT("MEDIASUBTYPE_RGB8\0")},
    {&MEDIASUBTYPE_SPDIF_TAG_241h, TEXT("MEDIASUBTYPE_SPDIF_TAG_241h\0")},
    {&MEDIASUBTYPE_TELETEXT, TEXT("MEDIASUBTYPE_TELETEXT\0")},
    {&MEDIASUBTYPE_TVMJ, TEXT("MEDIASUBTYPE_TVMJ\0")},
    {&MEDIASUBTYPE_UYVY, TEXT("MEDIASUBTYPE_UYVY\0")},
    {&MEDIASUBTYPE_VPVBI, TEXT("MEDIASUBTYPE_VPVBI\0")},
    {&MEDIASUBTYPE_VPVideo, TEXT("MEDIASUBTYPE_VPVideo\0")},
    {&MEDIASUBTYPE_WAKE, TEXT("MEDIASUBTYPE_WAKE\0")},
    {&MEDIASUBTYPE_WAVE, TEXT("MEDIASUBTYPE_WAVE\0")},
    {&MEDIASUBTYPE_Y211, TEXT("MEDIASUBTYPE_Y211\0")},
    {&MEDIASUBTYPE_Y411, TEXT("MEDIASUBTYPE_Y411\0")},
    {&MEDIASUBTYPE_Y41P, TEXT("MEDIASUBTYPE_Y41P\0")},
    {&MEDIASUBTYPE_YUY2, TEXT("MEDIASUBTYPE_YUY2\0")},
    {&MEDIASUBTYPE_YV12, TEXT("MEDIASUBTYPE_YV12\0")},
    {&MEDIASUBTYPE_YVU9, TEXT("MEDIASUBTYPE_YVU9\0")},
    {&MEDIASUBTYPE_YVYU, TEXT("MEDIASUBTYPE_YVYU\0")},
    {&MEDIASUBTYPE_YUYV, TEXT("MEDIASUBTYPE_YUYV\0")},
    {&MEDIASUBTYPE_dvhd, TEXT("MEDIASUBTYPE_dvhd\0")},
    {&MEDIASUBTYPE_dvsd, TEXT("MEDIASUBTYPE_dvsd\0")},
    {&MEDIASUBTYPE_dvsl, TEXT("MEDIASUBTYPE_dvsl\0")},

    {&MEDIATYPE_AUXLine21Data, TEXT("MEDIATYPE_AUXLine21Data\0")},
    {&MEDIATYPE_AnalogAudio, TEXT("MEDIATYPE_AnalogAudio\0")},
    {&MEDIATYPE_AnalogVideo, TEXT("MEDIATYPE_AnalogVideo\0")},
    {&MEDIATYPE_Audio, TEXT("MEDIATYPE_Audio\0")},
    {&MEDIATYPE_DVD_ENCRYPTED_PACK, TEXT("MEDIATYPE_DVD_ENCRYPTED_PACK\0")},
    {&MEDIATYPE_DVD_NAVIGATION, TEXT("MEDIATYPE_DVD_NAVIGATION\0")},
    {&MEDIATYPE_File, TEXT("MEDIATYPE_File\0")},
    {&MEDIATYPE_Interleaved, TEXT("MEDIATYPE_Interleaved\0")},
    {&MEDIATYPE_LMRT, TEXT("MEDIATYPE_LMRT\0")},
    {&MEDIATYPE_MPEG1SystemStream, TEXT("MEDIATYPE_MPEG1SystemStream\0")},
    {&MEDIATYPE_MPEG2_PES, TEXT("MEDIATYPE_MPEG2_PES\0")},
    {&MEDIATYPE_Midi, TEXT("MEDIATYPE_Midi\0")},
    {&MEDIATYPE_ScriptCommand, TEXT("MEDIATYPE_ScriptCommand\0")},
    {&MEDIATYPE_Stream, TEXT("MEDIATYPE_Stream\0")},
    {&MEDIATYPE_Text, TEXT("MEDIATYPE_Text\0")},
    {&MEDIATYPE_Timecode, TEXT("MEDIATYPE_Timecode\0")},
    {&MEDIATYPE_URL_STREAM, TEXT("MEDIATYPE_URL_STREAM\0")},
    {&MEDIATYPE_VBI, TEXT("MEDIATYPE_VBI\0")},
    {&MEDIATYPE_Video, TEXT("MEDIATYPE_Video\0")},

    {&WMMEDIATYPE_Audio,  TEXT("WMMEDIATYPE_Audio\0")},
    {&WMMEDIATYPE_Video,  TEXT("WMMEDIATYPE_Video\0")},
    {&WMMEDIATYPE_Script, TEXT("WMMEDIATYPE_Script\0")},
    {&WMMEDIATYPE_Image,  TEXT("WMMEDIATYPE_Image\0")},
    {&WMMEDIATYPE_FileTransfer, TEXT("WMMEDIATYPE_FileTransfer\0")},
    {&WMMEDIATYPE_Text,   TEXT("WMMEDIATYPE_Text\0")},

    {&WMMEDIASUBTYPE_Base, TEXT("WMMEDIASUBTYPE_Base\0")},
    {&WMMEDIASUBTYPE_RGB1, TEXT("WMMEDIASUBTYPE_RGB1\0")},
    {&WMMEDIASUBTYPE_RGB4, TEXT("WMMEDIASUBTYPE_RGB4\0")},
    {&WMMEDIASUBTYPE_RGB8, TEXT("WMMEDIASUBTYPE_RGB8\0")},
    {&WMMEDIASUBTYPE_RGB565, TEXT("WMMEDIASUBTYPE_RGB565\0")},
    {&WMMEDIASUBTYPE_RGB555, TEXT("WMMEDIASUBTYPE_RGB555\0")},
    {&WMMEDIASUBTYPE_RGB24, TEXT("WMMEDIASUBTYPE_RGB24\0")},
    {&WMMEDIASUBTYPE_RGB32, TEXT("WMMEDIASUBTYPE_RGB32\0")},
    {&WMMEDIASUBTYPE_I420, TEXT("WMMEDIASUBTYPE_I420\0")},
    {&WMMEDIASUBTYPE_IYUV, TEXT("WMMEDIASUBTYPE_IYUV\0")},
    {&WMMEDIASUBTYPE_YV12, TEXT("WMMEDIASUBTYPE_YV12\0")},
    {&WMMEDIASUBTYPE_YUY2, TEXT("WMMEDIASUBTYPE_YUY2\0")},
    {&WMMEDIASUBTYPE_UYVY, TEXT("WMMEDIASUBTYPE_UYVY\0")},
    {&WMMEDIASUBTYPE_YVYU, TEXT("WMMEDIASUBTYPE_YVYU\0")},
    {&WMMEDIASUBTYPE_YVU9, TEXT("WMMEDIASUBTYPE_YVU9\0")},
    {&WMMEDIASUBTYPE_MP43, TEXT("WMMEDIASUBTYPE_MP43\0")},
    {&WMMEDIASUBTYPE_MP4S, TEXT("WMMEDIASUBTYPE_MP4S\0")},

    {&WMMEDIASUBTYPE_WMV1, TEXT("WMMEDIASUBTYPE_WMV1\0")},
    {&WMMEDIASUBTYPE_WMV2, TEXT("WMMEDIASUBTYPE_WMV2\0")},
    {&WMMEDIASUBTYPE_WMV3, TEXT("WMMEDIASUBTYPE_WMV3\0")},
    {&WMMEDIASUBTYPE_MSS1, TEXT("WMMEDIASUBTYPE_MSS1\0")},
    {&WMMEDIASUBTYPE_MSS2, TEXT("WMMEDIASUBTYPE_MSS2\0")},
    {&WMMEDIASUBTYPE_MPEG2_VIDEO,  TEXT("WMMEDIASUBTYPE_MPEG2_VIDEO\0")},
    {&WMMEDIASUBTYPE_PCM, TEXT("WMMEDIASUBTYPE_PCM\0")},
    {&WMMEDIASUBTYPE_DRM, TEXT("WMMEDIASUBTYPE_DRM\0")},
    {&WMMEDIASUBTYPE_WMAudioV9, TEXT("WMMEDIASUBTYPE_WMAudioV9\0")},
    {&WMMEDIASUBTYPE_WMAudio_Lossless, TEXT("WMMEDIASUBTYPE_WMAudio_Lossless\0")},
    {&WMMEDIASUBTYPE_WMAudioV8, TEXT("WMMEDIASUBTYPE_WMAudioV8\0")},
    {&WMMEDIASUBTYPE_WMAudioV7, TEXT("WMMEDIASUBTYPE_WMAudioV7\0")},
    {&WMMEDIASUBTYPE_WMAudioV2, TEXT("WMMEDIASUBTYPE_WMAudioV2\0")},
    {&WMMEDIASUBTYPE_ACELPnet, TEXT("WMMEDIASUBTYPE_ACELPnet\0")},
    {&WMMEDIASUBTYPE_WMSP1, TEXT("WMMEDIASUBTYPE_WMSP1\0")},

    {&WMFORMAT_VideoInfo,    TEXT("WMFORMAT_VideoInfo\0")},
    {&WMFORMAT_WaveFormatEx, TEXT("WMFORMAT_WaveFormatEx\0")},
    {&WMFORMAT_Script,       TEXT("WMFORMAT_Script\0")},
    {&WMFORMAT_MPEG2Video,   TEXT("WMFORMAT_MPEG2Video\0")},

    {&WMSCRIPTTYPE_TwoStrings, TEXT("WMSCRIPTTYPE_TwoStrings\0")},

    {&PIN_CATEGORY_ANALOGVIDEOIN, TEXT("PIN_CATEGORY_ANALOGVIDEOIN\0")},
    {&PIN_CATEGORY_CAPTURE, TEXT("PIN_CATEGORY_CAPTURE\0")},
    {&PIN_CATEGORY_CC, TEXT("PIN_CATEGORY_CC\0")},
    {&PIN_CATEGORY_EDS, TEXT("PIN_CATEGORY_EDS\0")},
    {&PIN_CATEGORY_NABTS, TEXT("PIN_CATEGORY_NABTS\0")},
    {&PIN_CATEGORY_PREVIEW, TEXT("PIN_CATEGORY_PREVIEW\0")},
    {&PIN_CATEGORY_STILL, TEXT("PIN_CATEGORY_STILL\0")},
    {&PIN_CATEGORY_TELETEXT, TEXT("PIN_CATEGORY_TELETEXT\0")},
    {&PIN_CATEGORY_TIMECODE, TEXT("PIN_CATEGORY_TIMECODE\0")},
    {&PIN_CATEGORY_VBI, TEXT("PIN_CATEGORY_VBI\0")},
    {&PIN_CATEGORY_VIDEOPORT, TEXT("PIN_CATEGORY_VIDEOPORT\0")},
    {&PIN_CATEGORY_VIDEOPORT_VBI, TEXT("PIN_CATEGORY_VIDEOPORT_VBI\0")},

    {&CLSID_ACMWrapper, TEXT("CLSID_ACMWrapper\0")},
    {&CLSID_AVICo, TEXT("CLSID_AVICo\0")},
    {&CLSID_AVIDec, TEXT("CLSID_AVIDec\0")},
    {&CLSID_AVIDoc, TEXT("CLSID_AVIDoc\0")},
    {&CLSID_AVIDraw, TEXT("CLSID_AVIDraw\0")},
    {&CLSID_AVIMIDIRender, TEXT("CLSID_AVIMIDIRender\0")},
    {&CLSID_ActiveMovieCategories, TEXT("CLSID_ActiveMovieCategories\0")},
    {&CLSID_AnalogVideoDecoderPropertyPage, TEXT("CLSID_AnalogVideoDecoderPropertyPage\0")},
    {&CLSID_WMAsfReader, TEXT("CLSID_WMAsfReader\0")},
    {&CLSID_WMAsfWriter, TEXT("CLSID_WMAsfWriter\0")},
    {&CLSID_AsyncReader, TEXT("CLSID_AsyncReader\0")},
    {&CLSID_AudioCompressorCategory, TEXT("CLSID_AudioCompressorCategory\0")},
    {&CLSID_AudioInputDeviceCategory, TEXT("CLSID_AudioInputDeviceCategory\0")},
    {&CLSID_AudioProperties, TEXT("CLSID_AudioProperties\0")},
    {&CLSID_AudioRecord, TEXT("CLSID_AudioRecord\0")},
    {&CLSID_AudioRender, TEXT("CLSID_AudioRender\0")},
    {&CLSID_AudioRendererCategory, TEXT("CLSID_AudioRendererCategory\0")},
    {&CLSID_AviDest, TEXT("CLSID_AviDest\0")},
    {&CLSID_AviMuxProptyPage, TEXT("CLSID_AviMuxProptyPage\0")},
    {&CLSID_AviMuxProptyPage1, TEXT("CLSID_AviMuxProptyPage1\0")},
    {&CLSID_AviReader, TEXT("CLSID_AviReader\0")},
    {&CLSID_AviSplitter, TEXT("CLSID_AviSplitter\0")},
    {&CLSID_CAcmCoClassManager, TEXT("CLSID_CAcmCoClassManager\0")},
    {&CLSID_CDeviceMoniker, TEXT("CLSID_CDeviceMoniker\0")},
    {&CLSID_CIcmCoClassManager, TEXT("CLSID_CIcmCoClassManager\0")},
    {&CLSID_CMidiOutClassManager, TEXT("CLSID_CMidiOutClassManager\0")},
    {&CLSID_CMpegAudioCodec, TEXT("CLSID_CMpegAudioCodec\0")},
    {&CLSID_CMpegVideoCodec, TEXT("CLSID_CMpegVideoCodec\0")},
    {&CLSID_CQzFilterClassManager, TEXT("CLSID_CQzFilterClassManager\0")},
    {&CLSID_CVidCapClassManager, TEXT("CLSID_CVidCapClassManager\0")},
    {&CLSID_CWaveOutClassManager, TEXT("CLSID_CWaveOutClassManager\0")},
    {&CLSID_CWaveinClassManager, TEXT("CLSID_CWaveinClassManager\0")},
    {&CLSID_CameraControlPropertyPage, TEXT("CLSID_CameraControlPropertyPage\0")},
    {&CLSID_CaptureGraphBuilder, TEXT("CLSID_CaptureGraphBuilder\0")},
    {&CLSID_CaptureProperties, TEXT("CLSID_CaptureProperties\0")},
    {&CLSID_Colour, TEXT("CLSID_Colour\0")},
    {&CLSID_CrossbarFilterPropertyPage, TEXT("CLSID_CrossbarFilterPropertyPage\0")},
    {&CLSID_DSoundRender, TEXT("CLSID_DSoundRender\0")},
    {&CLSID_DVDHWDecodersCategory, TEXT("CLSID_DVDHWDecodersCategory\0")},
    {&CLSID_DVDNavigator, TEXT("CLSID_DVDNavigator\0")},
    {&CLSID_DVDecPropertiesPage, TEXT("CLSID_DVDecPropertiesPage\0")},
    {&CLSID_DVEncPropertiesPage, TEXT("CLSID_DVEncPropertiesPage\0")},
    {&CLSID_DVMux, TEXT("CLSID_DVMux\0")},
    {&CLSID_DVMuxPropertyPage, TEXT("CLSID_DVMuxPropertyPage\0")},
    {&CLSID_DVSplitter, TEXT("CLSID_DVSplitter\0")},
    {&CLSID_DVVideoCodec, TEXT("CLSID_DVVideoCodec\0")},
    {&CLSID_DVVideoEnc, TEXT("CLSID_DVVideoEnc\0")},
    {&CLSID_DirectDraw, TEXT("CLSID_DirectDraw\0")},
    {&CLSID_DirectDrawClipper, TEXT("CLSID_DirectDrawClipper\0")},
    {&CLSID_DirectDrawProperties, TEXT("CLSID_DirectDrawProperties\0")},
    {&CLSID_Dither, TEXT("CLSID_Dither\0")},
    {&CLSID_DvdGraphBuilder, TEXT("CLSID_DvdGraphBuilder\0")},
    {&CLSID_FGControl, TEXT("CLSID_FGControl\0")},
    {&CLSID_FileSource, TEXT("CLSID_FileSource\0")},
    {&CLSID_FileWriter, TEXT("CLSID_FileWriter\0")},
    {&CLSID_FilterGraph, TEXT("CLSID_FilterGraph\0")},
    {&CLSID_FilterGraphNoThread, TEXT("CLSID_FilterGraphNoThread\0")},
    {&CLSID_FilterMapper, TEXT("CLSID_FilterMapper\0")},
    {&CLSID_FilterMapper2, TEXT("CLSID_FilterMapper2\0")},
    {&CLSID_InfTee, TEXT("CLSID_InfTee\0")},
    {&CLSID_LegacyAmFilterCategory, TEXT("CLSID_LegacyAmFilterCategory\0")},
    {&CLSID_Line21Decoder, TEXT("CLSID_Line21Decoder\0")},
    {&CLSID_MOVReader, TEXT("CLSID_MOVReader\0")},
    {&CLSID_MPEG1Doc, TEXT("CLSID_MPEG1Doc\0")},
    {&CLSID_MPEG1PacketPlayer, TEXT("CLSID_MPEG1PacketPlayer\0")},
    {&CLSID_MPEG1Splitter, TEXT("CLSID_MPEG1Splitter\0")},
    {&CLSID_MediaPropertyBag, TEXT("CLSID_MediaPropertyBag\0")},
    {&CLSID_MemoryAllocator, TEXT("CLSID_MemoryAllocator\0")},
    {&CLSID_MidiRendererCategory, TEXT("CLSID_MidiRendererCategory\0")},
    {&CLSID_ModexProperties, TEXT("CLSID_ModexProperties\0")},
    {&CLSID_ModexRenderer, TEXT("CLSID_ModexRenderer\0")},
    {&CLSID_OverlayMixer, TEXT("CLSID_OverlayMixer\0")},
    {&CLSID_PerformanceProperties, TEXT("CLSID_PerformanceProperties\0")},
    {&CLSID_PersistMonikerPID, TEXT("CLSID_PersistMonikerPID\0")},
    {&CLSID_ProtoFilterGraph, TEXT("CLSID_ProtoFilterGraph\0")},
    {&CLSID_QualityProperties, TEXT("CLSID_QualityProperties\0")},
    {&CLSID_SeekingPassThru, TEXT("CLSID_SeekingPassThru\0")},
    {&CLSID_SmartTee, TEXT("CLSID_SmartTee\0")},
    {&CLSID_SystemClock, TEXT("CLSID_SystemClock\0")},
    {&CLSID_SystemDeviceEnum, TEXT("CLSID_SystemDeviceEnum\0")},
    {&CLSID_TVAudioFilterPropertyPage, TEXT("CLSID_TVAudioFilterPropertyPage\0")},
    {&CLSID_TVTunerFilterPropertyPage, TEXT("CLSID_TVTunerFilterPropertyPage\0")},
    {&CLSID_TextRender, TEXT("CLSID_TextRender\0")},
    {&CLSID_URLReader, TEXT("CLSID_URLReader\0")},
    {&CLSID_VBISurfaces, TEXT("CLSID_VBISurfaces\0")},
    {&CLSID_VPObject, TEXT("CLSID_VPObject\0")},
    {&CLSID_VPVBIObject, TEXT("CLSID_VPVBIObject\0")},
    {&CLSID_VfwCapture, TEXT("CLSID_VfwCapture\0")},
    {&CLSID_VideoCompressorCategory, TEXT("CLSID_VideoCompressorCategory\0")},
    {&CLSID_VideoInputDeviceCategory, TEXT("CLSID_VideoInputDeviceCategory\0")},
    {&CLSID_VideoProcAmpPropertyPage, TEXT("CLSID_VideoProcAmpPropertyPage\0")},
    {&CLSID_VideoRenderer, TEXT("CLSID_VideoRenderer\0")},
    {&CLSID_VideoStreamConfigPropertyPage, TEXT("CLSID_VideoStreamConfigPropertyPage\0")},

    {&CLSID_WMMUTEX_Language,      TEXT("CLSID_WMMUTEX_Language\0")},
    {&CLSID_WMMUTEX_Bitrate,       TEXT("CLSID_WMMUTEX_Bitrate\0")},
    {&CLSID_WMMUTEX_Presentation,  TEXT("CLSID_WMMUTEX_Presentation\0")},
    {&CLSID_WMMUTEX_Unknown,       TEXT("CLSID_WMMUTEX_Unknown\0")},

    {&CLSID_WMBandwidthSharing_Exclusive, TEXT("CLSID_WMBandwidthSharing_Exclusive\0")},
    {&CLSID_WMBandwidthSharing_Partial,   TEXT("CLSID_WMBandwidthSharing_Partial\0")},

    {&FORMAT_AnalogVideo, TEXT("FORMAT_AnalogVideo\0")},
    {&FORMAT_DVD_LPCMAudio, TEXT("FORMAT_DVD_LPCMAudio\0")},
    {&FORMAT_DolbyAC3, TEXT("FORMAT_DolbyAC3\0")},
    {&FORMAT_DvInfo, TEXT("FORMAT_DvInfo\0")},
    {&FORMAT_MPEG2Audio, TEXT("FORMAT_MPEG2Audio\0")},
    {&FORMAT_MPEG2Video, TEXT("FORMAT_MPEG2Video\0")},
    {&FORMAT_MPEG2_VIDEO, TEXT("FORMAT_MPEG2_VIDEO\0")},
    {&FORMAT_MPEGStreams, TEXT("FORMAT_MPEGStreams\0")},
    {&FORMAT_MPEGVideo, TEXT("FORMAT_MPEGVideo\0")},
    {&FORMAT_None, TEXT("FORMAT_None\0")},
    {&FORMAT_VIDEOINFO2, TEXT("FORMAT_VIDEOINFO2\0")},
    {&FORMAT_VideoInfo, TEXT("FORMAT_VideoInfo\0")},
    {&FORMAT_VideoInfo2, TEXT("FORMAT_VideoInfo2\0")},
    {&FORMAT_WaveFormatEx, TEXT("FORMAT_WaveFormatEx\0")},

    {&TIME_FORMAT_BYTE, TEXT("TIME_FORMAT_BYTE\0")},
    {&TIME_FORMAT_FIELD, TEXT("TIME_FORMAT_FIELD\0")},
    {&TIME_FORMAT_FRAME, TEXT("TIME_FORMAT_FRAME\0")},
    {&TIME_FORMAT_MEDIA_TIME, TEXT("TIME_FORMAT_MEDIA_TIME\0")},
    {&TIME_FORMAT_SAMPLE, TEXT("TIME_FORMAT_SAMPLE\0")},

    {&AMPROPSETID_Pin, TEXT("AMPROPSETID_Pin\0")},
    {&AM_INTERFACESETID_Standard, TEXT("AM_INTERFACESETID_Standard\0")},
    {&AM_KSCATEGORY_AUDIO, TEXT("AM_KSCATEGORY_AUDIO\0")},
    {&AM_KSCATEGORY_CAPTURE, TEXT("AM_KSCATEGORY_CAPTURE\0")},
    {&AM_KSCATEGORY_CROSSBAR, TEXT("AM_KSCATEGORY_CROSSBAR\0")},
    {&AM_KSCATEGORY_DATACOMPRESSOR, TEXT("AM_KSCATEGORY_DATACOMPRESSOR\0")},
    {&AM_KSCATEGORY_RENDER, TEXT("AM_KSCATEGORY_RENDER\0")},
    {&AM_KSCATEGORY_TVAUDIO, TEXT("AM_KSCATEGORY_TVAUDIO\0")},
    {&AM_KSCATEGORY_TVTUNER, TEXT("AM_KSCATEGORY_TVTUNER\0")},
    {&AM_KSCATEGORY_VIDEO, TEXT("AM_KSCATEGORY_VIDEO\0")},
    {&AM_KSPROPSETID_AC3, TEXT("AM_KSPROPSETID_AC3\0")},
    {&AM_KSPROPSETID_CopyProt, TEXT("AM_KSPROPSETID_CopyProt\0")},
    {&AM_KSPROPSETID_DvdSubPic, TEXT("AM_KSPROPSETID_DvdSubPic\0")},
    {&AM_KSPROPSETID_TSRateChange, TEXT("AM_KSPROPSETID_TSRateChange\0")},

    {&IID_IAMDirectSound, TEXT("IID_IAMDirectSound\0")},
    {&IID_IAMLine21Decoder, TEXT("IID_IAMLine21Decoder\0")},
    {&IID_IBaseVideoMixer, TEXT("IID_IBaseVideoMixer\0")},
    {&IID_IDDVideoPortContainer, TEXT("IID_IDDVideoPortContainer\0")},
    {&IID_IDirectDraw, TEXT("IID_IDirectDraw\0")},
    {&IID_IDirectDraw2, TEXT("IID_IDirectDraw2\0")},
    {&IID_IDirectDrawClipper, TEXT("IID_IDirectDrawClipper\0")},
    {&IID_IDirectDrawColorControl, TEXT("IID_IDirectDrawColorControl\0")},
    {&IID_IDirectDrawKernel, TEXT("IID_IDirectDrawKernel\0")},
    {&IID_IDirectDrawPalette, TEXT("IID_IDirectDrawPalette\0")},
    {&IID_IDirectDrawSurface, TEXT("IID_IDirectDrawSurface\0")},
    {&IID_IDirectDrawSurface2, TEXT("IID_IDirectDrawSurface2\0")},
    {&IID_IDirectDrawSurface3, TEXT("IID_IDirectDrawSurface3\0")},
    {&IID_IDirectDrawSurfaceKernel, TEXT("IID_IDirectDrawSurfaceKernel\0")},
    {&IID_IDirectDrawVideo, TEXT("IID_IDirectDrawVideo\0")},
    {&IID_IFullScreenVideo, TEXT("IID_IFullScreenVideo\0")},
    {&IID_IFullScreenVideoEx, TEXT("IID_IFullScreenVideoEx\0")},
    {&IID_IKsDataTypeHandler, TEXT("IID_IKsDataTypeHandler\0")},
    {&IID_IKsInterfaceHandler, TEXT("IID_IKsInterfaceHandler\0")},
    {&IID_IKsPin, TEXT("IID_IKsPin\0")},
    {&IID_IMixerPinConfig, TEXT("IID_IMixerPinConfig\0")},
    {&IID_IMixerPinConfig2, TEXT("IID_IMixerPinConfig2\0")},
    {&IID_IMpegAudioDecoder, TEXT("IID_IMpegAudioDecoder\0")},
    {&IID_IQualProp, TEXT("IID_IQualProp\0")},
    {&IID_IVPConfig, TEXT("IID_IVPConfig\0")},
    {&IID_IVPControl, TEXT("IID_IVPControl\0")},
    {&IID_IVPNotify, TEXT("IID_IVPNotify\0")},
    {&IID_IVPNotify2, TEXT("IID_IVPNotify2\0")},
    {&IID_IVPObject, TEXT("IID_IVPObject\0")},
    {&IID_IVPVBIConfig, TEXT("IID_IVPVBIConfig\0")},
    {&IID_IVPVBINotify, TEXT("IID_IVPVBINotify\0")},
    {&IID_IVPVBIObject, TEXT("IID_IVPVBIObject\0")},

    {&LOOK_DOWNSTREAM_ONLY, TEXT("LOOK_DOWNSTREAM_ONLY\0")},
    {&LOOK_UPSTREAM_ONLY, TEXT("LOOK_UPSTREAM_ONLY\0")},
    {0, 0},
};

int main()
{
    std::cout << "Hello World!\n";


    IAMVideoCompression* pVC = NULL;
    IAMStreamConfig* pVSC = NULL;
    AM_MEDIA_TYPE* pmt = NULL;
    IMediaSample2* pMSC = NULL;

    HRESULT hr = S_FALSE;
    IBaseFilter* pFilter = NULL;
    IBaseFilter* pAudioFilter = NULL;
    bool fPreviewFaked = true;
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    // create a graph builder
    // create a graph
    // give the graph to the builder 

    IGraphBuilder* pGraph = NULL;
    ICaptureGraphBuilder2* pBuilder = NULL;

    // Create the Filter Graph Manager.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL,
        CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
    if (hr == S_FALSE) {
        assert("could not create filter graph manager");
        //goto Error;
    }
    if (hr == S_OK)
    {
        assert("Filter Graph Manager created");
        // Create the Capture Graph Builder.
        hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL,
            CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2,
            (void**)&pBuilder);
        if (SUCCEEDED(hr))
        {
            assert("Capture Graph Builder created and assigning the graph");
            pBuilder->SetFiltergraph(pGraph);
        }
    }

    //lets create AVI Mux filter and add to the graph
     /*
    IBaseFilter* pMux;
    IBaseFilter** ppF = NULL;

   hr = CoCreateInstance(CLSID_AviDest, NULL, CLSCTX_INPROC_SERVER,
        //IID_PPV_ARGS(&pMux));
        //hr = CoCreateInstance(CLSID_VfwCapture, NULL, CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&pMux));
    
    if (SUCCEEDED(hr))
    {
        assert("AVI mux filter created and added to the graph");
        hr = pGraph->AddFilter(pMux, L"AVI Mux");
        ppF = &pMux;
        (*ppF)->AddRef();

    }
    */
    //lets create ASF Writer
    IBaseFilter* pASFWriter;
    IBaseFilter** ppF = NULL;

    //lets create the capture filter
    //first creating instance system device enum
    ICreateDevEnum* pDevEnum;
    IEnumMoniker* pEMoniker = NULL;
    
    hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));
   
   
    // Create an enumerator for the category.
   hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEMoniker, 0);
    //hr = pDevEnum->CreateClassEnumerator(CLSID_VideoCompressorCategory, &pEMoniker, 0);
    
    if (hr == S_FALSE) 
    {
        hr = VFW_E_NOT_FOUND;  // The category is empty. Treat as an error.
        assert("Vide Input Device not found");
    }
    else {
        pEMoniker->Reset();
        IMoniker* pMoniker = NULL;
        ULONG cFetched;
        while (hr = pEMoniker->Next(1, &pMoniker, &cFetched), hr == S_OK)
        {

            //find the friendly name of the device and print
            IPropertyBag* pPropBag = NULL;
            hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
                (void**)&pPropBag);

            if (SUCCEEDED(hr))
            {
                // To retrieve the filter's friendly name, do the following:
                VARIANT varName;
                VariantInit(&varName);
                varName.vt = VT_BSTR;
                hr = pPropBag->Read(L"FriendlyName", &varName, 0);
                if (SUCCEEDED(hr))
                {
                    // Display the name in your UI somehow.
                    printf("Device name : %S\n", varName.bstrVal);
    
                }
                // To create an instance of the filter, do the following:
                //create a filter if it is a DV video encoder
                //if (_bstr_t(varName.bstrVal) == _bstr_t(L"DV Video Encoder"))
                //if (0 == wcscmp(varName.bstrVal, L"QP0203 PCI, Analog 01 Capture"))
                {
                    hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter,
                        (void**)&pFilter);
                    // Now add the filter to the graph. 

                    //Remember to release pFilter later.
                    assert("Capture filter created");
                    if (SUCCEEDED(hr))
                    {
                        hr = pGraph->AddFilter(pFilter, L"Capture Filter");
                        assert("capture filter added to graph with hr = ");
                    }
                    pMoniker->AddRef();
                }
                VariantClear(&varName);
                pPropBag->Release();

            }
            pMoniker->Release();

        }

    }
    pEMoniker->Release();
    //pDevEnum->Release();
 
    //lets bind the audio to the audio filter
    hr = pDevEnum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory, &pEMoniker, 0);
    if (hr == S_FALSE)
    {
        hr = VFW_E_NOT_FOUND;  // The category is empty. Treat as an error.
        assert("Audio Input Device not found");
    }
    else
    {
        pEMoniker->Reset();
        IMoniker* pMoniker = NULL;
        ULONG cFetched;
        while (hr = pEMoniker->Next(1, &pMoniker, &cFetched), hr == S_OK)
        {
            //find the friendly name of the device and print
            IPropertyBag* pPropBag = NULL;
            hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
                (void**)&pPropBag);

            if (SUCCEEDED(hr))
            {
                // To retrieve the filter's friendly name, do the following:
                VARIANT varName;
                VariantInit(&varName);
                varName.vt = VT_BSTR;
                hr = pPropBag->Read(L"FriendlyName", &varName, 0);
                if (SUCCEEDED(hr))
                {
                    // Display the name in your UI somehow.
                    printf("Device name : %S\n", varName.bstrVal);
                }
                // To create an instance of the filter, do the following:
                //if (0 == wcscmp(varName.bstrVal, L"QP0203 PCI, Analog 01 WaveIn"))
                {
                    hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter,
                        (void**)&pAudioFilter);
                    // Now add the filter to the graph. 

                    //Remember to release pAudioFilter later.
                    printf("Audio Capture filter created\n");
                    if (SUCCEEDED(hr))
                    {
                        hr = pGraph->AddFilter(pAudioFilter, L"Audio Capture Filter");
                        printf("capture filter added to graph with hr = %d\n", hr);
                    }
                    pMoniker->AddRef();
                }
                VariantClear(&varName);
                pPropBag->Release();
            }
         }
         pMoniker->Release();
    }
    pDevEnum->Release();


  
    hr = pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
        &MEDIATYPE_Interleaved, pFilter,
        IID_IAMStreamConfig, (void**)&pVSC);
    if (hr != S_OK)
    {

        hr = pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
            &MEDIATYPE_Video, pFilter,
            IID_IAMStreamConfig, (void**)&pVSC);
    }
 
    
    
      
    // default capture format
    if (pVSC && pVSC->GetFormat(&pmt) == S_OK)
    {
        // DV capture does not use a VIDEOINFOHEADER
        if (pmt->formattype == FORMAT_VideoInfo)
        {
            VIDEOINFOHEADER* pVih = (VIDEOINFOHEADER*)pmt->pbFormat;
            // resize our window to the default capture size
            printf("biSize : %d\n",pVih->bmiHeader.biSize);
            printf("biWidth : %d\n", pVih->bmiHeader.biWidth);
            printf("biHeight : %d\n", pVih->bmiHeader.biHeight);
            printf("biSizeImage : %d",pVih->bmiHeader.biSizeImage);
            printf("pVih->bmiHeader.biBitCount %d\n", pVih->bmiHeader.biBitCount);


        }
        //DeleteMediaType(pmt);
    }

    /*
    IBaseFilter* pSinkFilter;

    hr = CoCreateInstance(CLSID_SBE2Sink, NULL, CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&pSinkFilter));

    if (SUCCEEDED(hr))
    {
        assert("sink filter created and added to the graph");
        hr = pGraph->AddFilter(pSinkFilter, L"Sink Filter");
        ppF = &pSinkFilter;
        (*ppF)->AddRef();

    }
    IMemInputPin* pMemPin;
    hr = pBuilder->FindInterface(NULL,
        &MEDIATYPE_Video, pSinkFilter,
        IID_IMemInputPin, (void**)&pMemPin);


    IStreamBufferSink* pBufferSink;
    hr = pSinkFilter->QueryInterface(&pBufferSink);

        hr = pBuilder->RenderStream(
            &PIN_CATEGORY_CAPTURE, // Pin category.
            &MEDIATYPE_Video,      // Media type.
            pFilter,                  // Capture filter.
            NULL,                  // Intermediate filter (optional).
            pSinkFilter);                 // Mux or file sink filter.
 

    IStreamBufferConfigure3* pStreamBufferConfig;
    hr = pSinkFilter->QueryInterface(CLSID_StreamBufferConfig,(void** )&pStreamBufferConfig);
    if (S_OK == hr)
    {
        LPWSTR dirName[64];
        pStreamBufferConfig->SetNamespace(NULL);
        pStreamBufferConfig->GetDirectory(&dirName[0]);
        printf("StreamBufferSink temporary file location %ls",dirName);
    }
    
    pBufferSink->LockProfile(NULL);
    */

 //set the file name for the asf file
 
    hr = pBuilder->SetOutputFileName(
        &MEDIASUBTYPE_Asf,
        L"C:\\Users\\shank\\Documents\\SampleCapture.asf", // File name.
        &pASFWriter,              // Receives a pointer to the mux.
        NULL);              // (Optional) Receives a pointer to the file sink.
    
    
    //render video and audio    

    //lets create instance of ASF reader and add to the graph

    hr = pBuilder->RenderStream(
        &PIN_CATEGORY_CAPTURE, // Pin category.
        &MEDIATYPE_Interleaved,      // Media type.
        pFilter,                  // Capture filter.
        NULL,                  // Intermediate filter (optional).
        pASFWriter);                 // Mux or file sink filter.
    if (hr != NOERROR)
    {
        hr = pBuilder->RenderStream(
            &PIN_CATEGORY_CAPTURE, // Pin category.
            &MEDIATYPE_Video,      // Media type.
            pFilter,                  // Capture filter.
            NULL,                  // Intermediate filter (optional).
            pASFWriter);                 // Mux or file sink filter.
    }
   
    //we need to connect the filters manually instead of calling RenderStream
    //lets connect the MJPEG compressor and decompressor
   
    hr = pBuilder->RenderStream(
            &PIN_CATEGORY_CAPTURE, // Pin category.
            &MEDIATYPE_Audio,      // Media type.
            pAudioFilter,                  // Capture filter.
            NULL,                  // Intermediate filter (optional).
        pASFWriter);                 // Mux or file sink filter.
            
    IConfigAsfWriter2* pConfig = 0;
    hr = pASFWriter->QueryInterface(IID_IConfigAsfWriter, (void**)&pConfig);
    if (SUCCEEDED(hr))
    {
        TCHAR sz[64];
        // Configure the ASF Writer filter.
        pConfig->SetIndexMode(FALSE);
        //pConfig->SetParam(AM_CONFIGASFWRITER_PARAM_DONTCOMPRESS, TRUE, 0);
        IWMProfile* pProfile;
        IWMStreamConfig* pStreamConfig1=NULL, * pStreamConfig2 = NULL;
        hr = pConfig->GetCurrentProfile(&pProfile);
        DWORD desc, streamCnt;
        WCHAR descStr[64];
        pProfile->GetDescription(descStr, &desc);
        printf("profile description : %ls\n", descStr);
        pProfile->GetName(descStr, &desc);
        printf("profile name : %ls\n", descStr);

        pProfile->GetStreamCount(&streamCnt);
        printf("stream count : %d\n", streamCnt);
 
        GUID pProfileId;
        pConfig->GetCurrentProfileGuid(&pProfileId);
        hr = GetGUIDString(sz, NUMELMS(sz), &pProfileId);
        printf("current profile id : %ls\n", sz);

        pConfig->Release();

    }
    
    IAMWMBufferPassCallback* pBufferPassCallBack;
    //IAMWMBufferPass* pBufferPass;
    //Find the video pinand register our callback. 
    // Note here we use the same object to handle DUE callbacks 
    // and index callbacks. So we create the object 
    // on the heap , which is how COM objects should be created anyway. 
    MyCallback *pASFCallback = new MyCallback(); 
    if(!pASFCallback) { return E_OUTOFMEMORY; }
    hr = pASFCallback->QueryInterface( IID_IAMWMBufferPassCallback , (void**) &pBufferPassCallBack);
    if(FAILED(hr)) 
    { 
        return hr; 
    } 
    // Find the video pin. 
    CComPtr<IPin> pVideoPin;


    //HRESULT GetPinByMajorType(IBaseFilter * pFilter, PIN_DIRECTION PinDir, GUID majortype, IPin * *ppPin)
    
        IEnumPins  *pEnum;
        IPin       *pPin;
        //hr = pASFWriter->EnumPins(&pEnum);
        hr = pSinkFilter->EnumPins(&pEnum);
        if (FAILED(hr))
        {
            //ON_FAIL("Failed to EnumPins in GetPinByMajorType!", hr)
            return hr;
        }
        hr = E_FAIL;
        while (pEnum->Next(1, &pPin, 0) == S_OK)
        {
            PIN_DIRECTION PinDirThis;
            pPin->QueryDirection(&PinDirThis);
            AM_MEDIA_TYPE mt;
            // Try this first as it is easy
            hr = pPin->ConnectionMediaType(&mt);
            if (SUCCEEDED(hr))
            {
                if (PINDIR_INPUT == PinDirThis && IsEqualGUID(MEDIATYPE_Video, mt.majortype))
                {
                    pVideoPin = pPin;
                    CoTaskMemFree(mt.pbFormat);
                    hr = S_OK;
                    break;
                }
                CoTaskMemFree(mt.pbFormat);
            }
            else
            {
                if (hr == VFW_E_NOT_CONNECTED)
                {
                    IEnumMediaTypes *pEnumMediaTypes;
                    AM_MEDIA_TYPE* pMT;
                    pPin->EnumMediaTypes(&pEnumMediaTypes);
                    while (pEnumMediaTypes->Next(1, &pMT, 0) == S_OK)
                    {
                        if (pMT->majortype == MEDIATYPE_Video)
                        {
                            pVideoPin = pPin;
                            //delete(*pMT);
                            hr = S_OK;
                            break;
                        }
                        //delete(*pMT);
                    } // end while
                } // end if VFW_E_NOT_CONNECTED
            } //end else
            pPin->Release();
        } // while while pPin
 
    //hr = GetPinByMajorType(pASFWriter, PINDIR_INPUT, MEDIATYPE_Video, &pVideoPin); 
    if(SUCCEEDED(hr))
    { 
        // Get its IAMWMBufferPass interface. 
        CComQIPtr<IAMWMBufferPass, &IID_IAMWMBufferPass> pBufferPass( pVideoPin ) ; 
        // Give it the pointer to our object. 
        hr = pBufferPass->SetNotify( (IAMWMBufferPassCallback*)pBufferPassCallBack) ;
        //ignoring the failure case
    }

    //render preview pin
    hr = pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Interleaved,
        pFilter, NULL, NULL);
    if (hr == VFW_S_NOPREVIEWPIN)
    {
        // preview was faked up for us using the (only) capture pin
        fPreviewFaked = TRUE;
    }
    else if (hr != S_OK)
    {
        hr = pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
            pFilter, NULL, NULL);
        if (hr == VFW_S_NOPREVIEWPIN)
        {
            // preview was faked up for us using the (only) capture pin
            fPreviewFaked = TRUE;
        }
        else if (hr != S_OK)
        {
            std::cout << "Cannot render video preview stream";
        }
    }


    REFERENCE_TIME start = MAXLONGLONG, stop = MAXLONGLONG;

    // don't capture quite yet...the below code stops any prevoius start request on the pin
   hr = pBuilder->ControlStream(&PIN_CATEGORY_CAPTURE, NULL,
       NULL, &start, NULL, 0, 0);
   hr = pBuilder->ControlStream(&PIN_CATEGORY_PREVIEW, NULL,
       NULL, &start, NULL, 0, 0);

    // Do we have the ability to control capture and preview separately?
    bool fHasStreamControl = SUCCEEDED(hr);
    //bool fHasStreamControl = TRUE;

    // prepare to run the graph
    IMediaControl *pMC = NULL;

    hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if (FAILED(hr))
    {
        std::cout << "Error %x: Cannot get IMediaControl";
        return FALSE;
    }

    // If we were able to keep capture off, then we can
    // run the graph now for frame accurate start later yet still showing a
    // preview.   Otherwise, we can't run the graph yet without capture
    // starting too, so we'll pause it so the latency between when they
    // press a key and when capture begins is still small (but they won't have
    // a preview while they wait to press a key)

    if (fHasStreamControl)
    {
        hr = pMC->Run();
        //pRecObject->Start();
    }
    else
        hr = pMC->Pause();
    if (FAILED(hr))
    {
        // stop parts that started
        pMC->Stop();
        pMC->Release();
        std::cout << "Error %x: Cannot start graph";
        return FALSE;
    }
    // Start capture NOW!
    if (fHasStreamControl)
    {

        // turn the capture pin on now!
        hr = pBuilder->ControlStream(&PIN_CATEGORY_CAPTURE, NULL,
            NULL, NULL, &stop, 0, 0);
        // make note of the current dropped frame counts
        //hr = pBuilder->ControlStream(&PIN_CATEGORY_PREVIEW, NULL,
          //  NULL, NULL, &stop, 0, 0);

    }
    else
    {
        hr = pMC->Run();
        hr = pBuilder->ControlStream(&PIN_CATEGORY_CAPTURE, NULL,
            NULL, NULL, &stop, 0, 0);
        if (FAILED(hr))
        {
            // stop parts that started
            pMC->Stop();
            pMC->Release();
            printf("Error : Cannot run graph");
            return false;
        }
    }

/*
    if (pMemPin)
    {
        hr = pMemPin->Receive(pMSC);
        if (S_OK == hr)
        {
            BYTE* pBuffer = NULL, * pSampleBuffer = NULL;
            if (S_OK == hr && pMSC)
            {
                pMSC->GetPointer(&pSampleBuffer);
                if (pSampleBuffer)
                {
                    int size = pMSC->GetActualDataLength();
                    pBuffer = (BYTE*)malloc(size);
                    memcpy(pBuffer, pSampleBuffer, size);
                }
            }

        }

    }
*/
    //now lets read back the file

    IGraphBuilder* pReadGraph = NULL;
    IMediaControl* pReadControl = NULL;
    IMediaEvent* pReadEvent = NULL;

 
    // Create the Filter Graph Manager and query for interfaces.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder, (void**)&pReadGraph);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager for reading ASF file.");
        return hr;
    }

    IBaseFilter* pASFReader;
    
    hr = CoCreateInstance(CLSID_WMAsfReader, NULL, CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&pASFReader));

    if (SUCCEEDED(hr))
    {
        assert("ASF Reader created and added to the graph");
        hr = pReadGraph->AddFilter(pASFReader, L"ASF Reader");
        ppF = &pASFReader;
        (*ppF)->AddRef();

    }

 
    hr = pReadGraph->QueryInterface(IID_IMediaControl, (void**)&pReadControl);
    hr = pReadGraph->QueryInterface(IID_IMediaEvent, (void**)&pReadEvent);

    // Build the graph. IMPORTANT: Change this string to a file
    // on your system.
    hr = pReadGraph->RenderFile(L"C:\\Users\\shank\\Documents\\SampleCapture.asf", NULL);
    /*
    if (SUCCEEDED(hr))
    {
        // Run the graph.
        hr = pReadControl->Run();
        if (SUCCEEDED(hr))
        {
            // Wait for completion.
            long evCode;
            pReadEvent->WaitForCompletion(10, &evCode);

            // Note: Do not use INFINITE in a real application, because it
            // can block indefinitely.
        }
    }
    */
    printf("Press RTN Key To Exit...\r\n");
    getchar();

    pMC->Stop();

    pReadControl->Release();
    pReadEvent->Release();
    pReadGraph->Release();

//    pASFWriter->Release();

    CoUninitialize();
    return hr;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

HRESULT GetGUIDString(TCHAR* szString, int cchBuffer, GUID* pGUID)
{
    int i = 0;
    HRESULT hr = E_FAIL;

    if (cchBuffer < 1)
    {
        return E_INVALIDARG;
    }

    szString[0] = TEXT('\0');

    // Find format GUID's name in the named guids table
    while (rgng[i].pguid != 0)
    {
        if (*pGUID == *(rgng[i].pguid))
        {
            hr = StringCchCat(szString, cchBuffer, rgng[i].psz);
            break;
        }
        i++;
    }

    if (FAILED(hr))
    {
        // No match, use the string representation of the GUID
        hr = StringFromGUID2(*pGUID, szString, cchBuffer);
    }

    return hr;
}
