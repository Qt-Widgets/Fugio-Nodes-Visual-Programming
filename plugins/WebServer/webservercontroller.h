#ifndef WEBSERVERCONTROLLER_H
#define WEBSERVERCONTROLLER_H

#include "httpserver/httprequesthandler.h"

using namespace stefanfrings;

class WebServerController : public HttpRequestHandler
{
	Q_OBJECT

public:
	WebServerController( QObject *pParent = Q_NULLPTR );

	void service( HttpRequest& request, HttpResponse& response);
};

#endif // WEBSERVERCONTROLLER_H
