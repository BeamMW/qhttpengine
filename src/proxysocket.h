/*
 * Copyright (c) 2016 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef QHTTPENGINE_QPROXYSOCKET_H
#define QHTTPENGINE_QPROXYSOCKET_H

#include <QHostAddress>
#include <QObject>
#include <QTcpSocket>

#include <qhttpengine/socket.h>

/**
 * @brief HTTP socket for connecting to a proxy
 */
class QProxySocket : public QObject
{
    Q_OBJECT

public:

    explicit QProxySocket(HttpSocket *socket, const QString &path, const QHostAddress &address, quint16 port);

private Q_SLOTS:

    void onDownstreamReadyRead();

    void onUpstreamConnected();
    void onUpstreamReadyRead();
    void onUpstreamError(QTcpSocket::SocketError socketError);

private:

    QString methodToString(HttpSocket::Method method) const;

    HttpSocket *mDownstreamSocket;
    QTcpSocket mUpstreamSocket;

    QString mPath;
    bool mHeadersParsed;
    QByteArray mBuffer;
};

#endif // QHTTPENGINE_QPROXYSOCKET_H