#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httpserver/httprequesthandler.h"
#include "httpserver/staticfilecontroller.h"
#include "httpserver/httpsessionstore.h"

using namespace stefanfrings;

class RequestMapper : public HttpRequestHandler
{
	Q_OBJECT

public:
	RequestMapper(QObject* parent=0);

	void service(HttpRequest& request, HttpResponse& response);

public:
	static StaticFileController* staticFileController;
	static HttpSessionStore* sessionStore;
};

#endif // REQUESTMAPPER_H
