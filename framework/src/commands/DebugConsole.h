/*
 * DebugConsole.h
 *
 *  Created on: Nov 16, 2009
 *      Author: nitobi-test
 */

#ifndef DEBUGCONSOLE_H_
#define DEBUGCONSOLE_H_

#include <qobject.h>

#include "BrowserView.h"

class QWebView;
class QWebFrame;

class DebugConsole : public QObject
{
    Q_OBJECT
public:
	DebugConsole( QWebView *view, BrowserView *bview  );

public slots:
    void log( const QString &param );

private slots:
   

private:
    QWebFrame *frame;
    BrowserView *m_bview;
};
#endif /* DEBUGCONSOLE_H_ */
