#include <qdebug.h>
#include <qwebview.h>
#include <qwebframe.h>

#include "DebugConsole.h"

DebugConsole::DebugConsole( QWebView *view, BrowserView *bview  )
{
	QWebPage *page = view->page();
	frame = page->mainFrame();
	m_bview = bview;
}

void DebugConsole::log( const QString &param )
{
    qDebug() << param;
    m_bview->debug(param);
}
