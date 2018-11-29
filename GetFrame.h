#ifndef VIDEOWIDGETSURFACE_H
#define VIDEOWIDGETSURFACE_H

#include <QAbstractVideoSurface>
#include <QImage>
#include <QVideoFrame>
#include <QLabel>

class myQAbstractVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    myQAbstractVideoSurface(QObject *parent = nullptr);
    void stop();
Q_SIGNALS:
    void fnSurfaceStopped(QPixmap pix);

private slots:
    void fnClearPixmap();

private:
    QImage::Format imageFormat;
    QPixmap imageCaptured;
    QRect targetRect;
    QRect sourceRect;
    QVideoFrame currentFrame;

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;

    bool isFormatSupported(const QVideoSurfaceFormat &format) const;

    bool start(const QVideoSurfaceFormat &format);

    bool present(const QVideoFrame &frame);
};

#endif
