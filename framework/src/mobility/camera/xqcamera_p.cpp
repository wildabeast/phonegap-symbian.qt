#include "xqcamera.h"
#include "xqcamera_p.h"
#include <cameraengine.h>
#include <fbs.h>
#include <QImage>

XQCameraPrivate::XQCameraPrivate(XQCamera* qq) : q(qq), iCaptureSize(QSize(640, 480))
{
}

XQCameraPrivate::~XQCameraPrivate()
{
    delete iCameraEngine;
}

bool XQCameraPrivate::open(int index)
{
    TRAP(iError,
        iCameraEngine = CCameraEngine::NewL(index, 0, this);
        iCameraEngine->ReserveAndPowerOn();
        )
    iIndex = index;
    return (iError == KErrNone);
}

void XQCameraPrivate::setCaptureSize(QSize size)
{
    iCaptureSize = size;
}

bool XQCameraPrivate::capture()
{
    if (iCameraEngine)
    {
        TSize size(iCaptureSize.width(), iCaptureSize.height());
        if(iIndex == 0)
        {
            TRAP(iError,
                iCameraEngine->PrepareL(size);
                iCameraEngine->CaptureL());
        }
        else
        {
            TRAP(iError,
                iCameraEngine->PrepareL(size, CCamera::EFormatFbsBitmapColor64K);
                iCameraEngine->CaptureL());
        }
    }
    return (iCameraEngine && iError == KErrNone);
}

void XQCameraPrivate::close()
{
    iCameraEngine->ReleaseAndPowerOff();
}

bool XQCameraPrivate::focus()
{
    if (iCameraEngine)
    {
        TRAP(iError, iCameraEngine->StartFocusL();)
    }    
    return (iCameraEngine && iError == KErrNone);
}

void XQCameraPrivate::cancelFocus()
{
    iCameraEngine->FocusCancel();
}

void XQCameraPrivate::MceoCameraReady()
{
    emit q->cameraReady();
}

void XQCameraPrivate::MceoFocusComplete()
{
    emit q->focused();
}

void XQCameraPrivate::MceoCapturedDataReady(TDesC8* aData)
{
    emit q->captureCompleted(QByteArray::fromRawData((const char *)aData->Ptr(), aData->Length()));
}

void XQCameraPrivate::releaseImageBuffer()
{
    iCameraEngine->ReleaseImageBuffer();
}

void XQCameraPrivate::MceoCapturedBitmapReady(CFbsBitmap* aBitmap)
{
    if(aBitmap)
    {
        TSize size = aBitmap->SizeInPixels();
        TUint32 sizeInWords = size.iHeight * CFbsBitmap::ScanLineLength( size.iWidth, aBitmap->DisplayMode()) / sizeof( TUint32 );

        TUint32* pixelData = new TUint32[ sizeInWords ];

        if ( !pixelData )
            return;

        // convert to QImage
        aBitmap->LockHeap();
        TUint32* dataPtr = aBitmap->DataAddress();
        memcpy(pixelData, dataPtr, sizeof(TUint32) * sizeInWords);
        aBitmap->UnlockHeap();

        TDisplayMode displayMode = aBitmap->DisplayMode();  

        QImage::Format format;
        switch(displayMode)
        {
            case EColor256:
                format = QImage::Format_Indexed8;
                break;
            case EColor4K:
                format = QImage::Format_RGB444;
                break;
            case EColor64K:
                format = QImage::Format_RGB16;
                break;
            case EColor16M:
                format = QImage::Format_RGB666;
                break;
            case EColor16MU:
                format = QImage::Format_RGB32;
                break;
            case EColor16MA:
                format = QImage::Format_ARGB32;
                break;
            default:
                User::Leave( -1 );
                break;
        }

        QImage *snapImage = new QImage(
                (uchar*)pixelData,
                size.iWidth,
                size.iHeight,
                CFbsBitmap::ScanLineLength( size.iWidth, aBitmap->DisplayMode() ),
                format );

        emit q->captureCompleted(snapImage);
        aBitmap = NULL;
    }
}

void XQCameraPrivate::MceoViewFinderFrameReady(CFbsBitmap& aFrame)
{
    if (iVFProcessor)
    {
        int bytesPerLine = aFrame.ScanLineLength(iViewFinderSize.width(),
            aFrame.DisplayMode());
        QImage image((uchar *)aFrame.DataAddress(), iViewFinderSize.width(), 
            iViewFinderSize.height(), bytesPerLine, QImage::Format_RGB32);
        iVFProcessor->ViewFinderFrameReady(image);     
        iCameraEngine->ReleaseViewFinderBuffer();
    }
}

void XQCameraPrivate::MceoHandleError(TCameraEngineError /*aErrorType*/,
    TInt aError)
{   
    iError = aError;
    emit q->error(error());
}

void XQCameraPrivate::setVFProcessor(MVFProcessor* VFProcessor)
{
    iVFProcessor = VFProcessor;
}

int XQCameraPrivate::camerasAvailable()
{
    return CCameraEngine::CamerasAvailable();
}

XQCamera::Error XQCameraPrivate::error() const
{
    switch (iError) {
        case KErrNone:
            return XQCamera::NoError;
        case KErrNoMemory:
            return XQCamera::OutOfMemoryError;
        case KErrInUse:
            return XQCamera::InUseError;
        case KErrNotReady:
            return XQCamera::NotReadyError;
        default:
            return XQCamera::UnknownError;
    }    
}

// End of file
