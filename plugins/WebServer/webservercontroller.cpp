#include "webservercontroller.h"

WebServerController::WebServerController( QObject *pParent )
	: HttpRequestHandler( pParent )
{

}

void WebServerController::service( HttpRequest &request, HttpResponse &response )
{
	response.write( "Hello World", true );
}
