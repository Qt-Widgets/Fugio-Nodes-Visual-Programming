#include "requestmapper.h"

#include "webservercontroller.h"

StaticFileController* RequestMapper::staticFileController=0;
HttpSessionStore* RequestMapper::sessionStore=0;

RequestMapper::RequestMapper(QObject* parent)
	: HttpRequestHandler(parent) {
	// empty
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response)
{
	QByteArray path = request.getPath();

//	HttpSession session = sessionStore->getSession( request, response, true );

	qDebug("RequestMapper: path=%s",path.data());

	if ( path=="/hello")
	{
		WebServerController().service( request, response );
	}
	else
	{
		staticFileController->service( request, response );
	}

	qDebug("RequestMapper: finished request");
}
