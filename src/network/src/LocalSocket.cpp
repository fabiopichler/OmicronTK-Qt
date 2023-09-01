/*******************************************************************************
  OmicronTK_qt

  Author: Fábio Pichler
  Website: http://fabiopichler.net
  License: MIT License

  Copyright 2018-2019, Fábio Pichler

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the Software
  is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
  THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*******************************************************************************/

#include "OmicronTK/qt/network/LocalSocket.hpp"
#include "OmicronTK/qt/network/LocalServer.hpp"

#include <QLocalServer>
#include <QLocalSocket>

namespace OmicronTK {
namespace qt {
    
LocalSocket::LocalSocket(const QString &appKey, int timeout)
    : m_appKey(appKey)
    , m_timeout(timeout)
{
}

LocalSocket::LocalSocket(const LocalServer &localServer)
    : m_appKey(localServer.m_appKey)
    , m_timeout(localServer.m_timeout)
{
}

bool LocalSocket::sendMessage(const QVector<QString> &messageList)
{
    QLocalSocket localSocket(this);
    localSocket.connectToServer(m_appKey, QIODevice::WriteOnly);

    if (!localSocket.waitForConnected(m_timeout))
    {
        qWarning() << localSocket.errorString();
        return false;
    }

    QByteArray data;

    for (const QString &message : messageList)
    {
        data.push_back(message.toUtf8());
        data.push_back(":!#!:");
    }

    localSocket.write(data);

    if (!localSocket.waitForBytesWritten(m_timeout))
    {
        qWarning() << localSocket.errorString();
        return false;
    }

    localSocket.disconnectFromServer();

    return true;
}

}
}
