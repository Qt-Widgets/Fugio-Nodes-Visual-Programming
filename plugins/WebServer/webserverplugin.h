#ifndef WEBSERVERPLUGIN_H
#define WEBSERVERPLUGIN_H

#include <QObject>

#include <QTemporaryFile>

#include <fugio/core/uuid.h>
#include <fugio/global_interface.h>
#include <fugio/plugin_interface.h>

using namespace fugio;

class WebServerPlugin : public QObject, public fugio::PluginInterface
{
	Q_OBJECT
	Q_INTERFACES( fugio::PluginInterface )
	Q_PLUGIN_METADATA( IID "com.bigfug.fugio.webserver.plugin" )

public:
	explicit WebServerPlugin( void );

	virtual ~WebServerPlugin( void ) {}

	//-------------------------------------------------------------------------
	// fugio::PluginInterface

	virtual InitResult initialise( fugio::GlobalInterface *pApp, bool pLastChance );

	virtual void deinitialise( void );

private:
	GlobalInterface			*mApp;
	QString					 mTmpNam;
};

#endif // WEBSERVERPLUGIN_H
