/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demos of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "BrowserView.h"

#include <QtGui>
#include <QtNetwork>
#include <QtWebKit>

#include "CommandManager.h"
#include "DebugConsole.h"
#include "xqaccesspointmanager.h"
#include <qnetworkconfigmanager.h>


//#if defined (Q_OS_SYMBIAN)
//#include "sym_iap_util.h"
//#endif

BrowserView::BrowserView(QWidget *parent)
    : QWidget(parent)
    , m_webView(0)
    , m_progress(0)
    , m_currentZoom(100)
{
    m_webView = new QWebView(this);
    m_console = new QListWidget(this);

    m_zoomLevels << 30 << 50 << 67 << 80 << 90;
    m_zoomLevels << 100;
    m_zoomLevels << 110 << 120 << 133 << 150 << 170 << 200 << 240 << 300;

    QTimer::singleShot(0, this, SLOT(initialize()));
}

void BrowserView::initialize()
{
    QPalette pal = m_webView->palette();
    pal.setColor(QPalette::Base, QColor("red"));
    pal.setBrush(QPalette::Base, Qt::white);
    m_webView->setPalette(pal);

    m_webView->setZoomFactor(static_cast<qreal>(m_currentZoom)/100.0);
    connect(m_webView, SIGNAL(loadStarted()), SLOT(start()));
    connect(m_webView, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(m_webView, SIGNAL(loadFinished(bool)), SLOT(finish(bool)));
    connect(m_webView, SIGNAL(urlChanged(QUrl)), SLOT(updateTitleBar()));

    //this is how we will add the phonegap apis to the webview, yahoo
    CommandManager *manager = new CommandManager(this);
    manager->setWebView( m_webView, this );
    
    QDir www = QDir::current();
    www.cd("www");

    m_webView->load(QUrl::fromUserInput(www.filePath("index.html")));
    m_webView->page()->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
#ifdef Q_OS_SYMBIAN
    QTimer::singleShot(0, this, SLOT(setDefaultIap()));
#endif
}

void BrowserView::start()
{

}

void BrowserView::setProgress(int percent)
{

}

void BrowserView::finish(bool ok)
{
    // TODO: handle error
    if (!ok) {
        
    }
}

void BrowserView::zoomIn()
{
    int i = m_zoomLevels.indexOf(m_currentZoom);
    Q_ASSERT(i >= 0);
    if (i < m_zoomLevels.count() - 1)
        m_currentZoom = m_zoomLevels[i + 1];

    m_webView->setZoomFactor(static_cast<qreal>(m_currentZoom)/100.0);
}

void BrowserView::zoomOut()
{
    int i = m_zoomLevels.indexOf(m_currentZoom);
    Q_ASSERT(i >= 0);
    if (i > 0)
        m_currentZoom = m_zoomLevels[i - 1];

    m_webView->setZoomFactor(static_cast<qreal>(m_currentZoom)/100.0);
}

void BrowserView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    int h1 = 0;

    m_webView->setGeometry(0, h1, width(), height() - h1 - 200);
    m_console->setGeometry(0, height() - 200, width(), 200);
    m_console->raise();
}
#ifdef Q_OS_SYMBIAN
void BrowserView::setDefaultIap()
{

	//currently the best behaviour is if none of this happens, and the OS manages connections.
	//but its not ideal ... it will ask repeatedly if set to "ask always", even though
	//this setting does not ask repeatedly for other apps, and it is the default setting.
	return;
	//the code below is the behaviour we "want" but it actually simply breaks connectivity

    //qt_SetDefaultIap();
    //m_webView->load(QUrl("http://news.bbc.co.uk/text_only.stm"));

	// Create an Access Point Manager object
	XQAccessPointManager* apManager = new XQAccessPointManager(this);
	if (apManager->isSetDefaultAccessPointSupported())
		this->debug("default ap supported");
	else
		this->debug("default ap not supported");
	
	this->debug("preferred ap: " + apManager->preferredAccessPoint().name());
	this->debug("default ap: " + apManager->defaultAccessPoint().name());
	this->debug("system ap: " + apManager->systemAccessPoint().name());
	
	// Get a list of available access points
	QList <XQAccessPoint> accessPoints = apManager->availableAccessPoints();
	this->debug(QString::number(accessPoints.length()) + " access points");
	for (int i = 0; i < accessPoints.length(); i++)
		this->debug(accessPoints[i].name());
		
	// Get the preferred access point
	// this is not matching to the preferred AP of "Internet (Fido GPRS)" as set on the phone. wtf.
	XQAccessPoint ap = apManager->preferredAccessPoint();

	// Use the preferred access point if there is one
	if (!ap.isNull())
	{
		this->debug("preferred ap: " + ap.name());
	    apManager->setDefaultAccessPoint(ap);
	} else {
		// what should happen is here the prompt is given, we get the user input and set the default
		// or if the os could prompt and set that would be acceptable
		this->debug("no preffered ap available");
		apManager->setDefaultAccessPoint(accessPoints[0]);
	}

}
#endif

void BrowserView::navigate(const QUrl &url)
{
    m_webView->load(url);
}

void BrowserView::debug(QString output)
{
	m_console->addItem(output);
	//m_console->scrollToBottom();
}
