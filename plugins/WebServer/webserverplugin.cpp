#include "webserverplugin.h"

#include <QTranslator>
#include <QApplication>
#include <QTemporaryFile>
#include <QSettings>
#include <QDir>

#include <fugio/webserver/uuid.h>

#include <fugio/nodecontrolbase.h>

#include "httpserver/httplistener.h"
#include "httpserver/httprequesthandler.h"

#include "requestmapper.h"

using namespace stefanfrings;

QList<QUuid>				NodeControlBase::PID_UUID;

ClassEntry		mNodeClasses[] =
{
//	ClassEntry( "Filename", "GUI", NID_FILENAME, &FilenameNode::staticMetaObject ),
	ClassEntry()
};

ClassEntry		mPinClasses[] =
{
	ClassEntry()
};

WebServerPlugin::WebServerPlugin()
	: mApp( 0 )
{
	//-------------------------------------------------------------------------
	// Install translator

	static QTranslator		Translator;

	if( Translator.load( QLocale(), QLatin1String( "translations" ), QLatin1String( "_" ), ":/" ) )
	{
		qApp->installTranslator( &Translator );
	}
}

PluginInterface::InitResult WebServerPlugin::initialise( fugio::GlobalInterface *pApp, bool pLastChance )
{
	Q_UNUSED( pLastChance )

	while( mTmpNam.isEmpty() )//|| QFile::exists( mTmpNam ) )
	{
		mTmpNam = QDir( QDir::tempPath() ).filePath( "Fugio.webserver." );
	}

	qDebug() << mTmpNam;

	if( true )
	{
		QSettings		*FilesSettings = new QSettings( mTmpNam + "files.ini", QSettings::IniFormat, this );

		FilesSettings->clear();

		FilesSettings->beginGroup( "files" );

		FilesSettings->setValue( "path", "E:/docroot" );
		FilesSettings->setValue( "encoding", "UTF-8" );
		FilesSettings->setValue( "maxAge", 90000 );
		FilesSettings->setValue( "cacheTime", 5000 );
		FilesSettings->setValue( "cacheSize", 1000000 );
		FilesSettings->setValue( "maxCachedFileSize", 65536 );

		RequestMapper::staticFileController = new StaticFileController( FilesSettings, this );
	}

	if( true )
	{
		QSettings		*SessionSettings = new QSettings( mTmpNam + "session.ini", QSettings::IniFormat, this );

		SessionSettings->clear();

		SessionSettings->beginGroup( "sessions" );

		SessionSettings->setValue( "expirationTime", 3600000 );
		SessionSettings->setValue( "cookieName", "sessionid" );
//		SessionSettings->setValue( "cookieDomain", "mydomain.com" );
		SessionSettings->setValue( "cookiePath", "/" );
		SessionSettings->setValue( "cookieComment", "Identifies the user" );

		RequestMapper::sessionStore = new HttpSessionStore( SessionSettings, this );
	}

	if( true )
	{
		QSettings		*ListenerSettings = new QSettings( mTmpNam + "listener.ini", QSettings::IniFormat, this );

		ListenerSettings->clear();

		ListenerSettings->beginGroup( "listener" );

		ListenerSettings->setValue( "port", 8118 );
		ListenerSettings->setValue( "minThreads", 4 );
		ListenerSettings->setValue( "maxThreads", 100 );
		ListenerSettings->setValue( "cleanupInterval", 60000 );
		ListenerSettings->setValue( "readTimeout", 60000 );
		ListenerSettings->setValue( "maxRequestSize", 16000 );
		ListenerSettings->setValue( "maxMultiPartSize", 10000000 );

		new HttpListener( ListenerSettings, new RequestMapper( this ), this );
	}

	mApp = pApp;

	mApp->registerNodeClasses( mNodeClasses );

	mApp->registerPinClasses( mPinClasses );

	return( INIT_OK );
}

void WebServerPlugin::deinitialise()
{
	mApp->unregisterPinClasses( mPinClasses );

	mApp->unregisterNodeClasses( mNodeClasses );

	mApp = 0;

	if( !mTmpNam.isEmpty() )
	{
		QFile::remove( mTmpNam );
	}
}
