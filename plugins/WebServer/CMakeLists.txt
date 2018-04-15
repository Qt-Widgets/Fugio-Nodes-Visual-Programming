cmake_minimum_required( VERSION 3.1 )

project( fugio-webserver )

set( SOURCE_FILES
	../../include/fugio/nodecontrolbase.h
	../../include/fugio/pincontrolbase.h
	../../include/fugio/webserver/uuid.h

	webserverplugin.cpp
	webserverplugin.h

	webservercontroller.cpp
	webservercontroller.h
	requestmapper.cpp
	requestmapper.h

	httpserver/httpglobal.h
	httpserver/httplistener.h
	httpserver/httpconnectionhandler.h
	httpserver/httpconnectionhandlerpool.h
	httpserver/httprequest.h
	httpserver/httpresponse.h
	httpserver/httpcookie.h
	httpserver/httprequesthandler.h
	httpserver/httpsession.h
	httpserver/httpsessionstore.h
	httpserver/staticfilecontroller.h

	httpserver/httpglobal.cpp
	httpserver/httplistener.cpp
	httpserver/httpconnectionhandler.cpp
	httpserver/httpconnectionhandlerpool.cpp
	httpserver/httprequest.cpp
	httpserver/httpresponse.cpp
	httpserver/httpcookie.cpp
	httpserver/httprequesthandler.cpp
	httpserver/httpsession.cpp
	httpserver/httpsessionstore.cpp
	httpserver/staticfilecontroller.cpp
)

set( QRC_FILES
#	resources.qrc
)

add_library( ${PROJECT_NAME} MODULE ${SOURCE_FILES} ${QRC_FILES} )

set_target_properties( ${PROJECT_NAME} PROPERTIES
  BUNDLE TRUE
)

#------------------------------------------------------------------------------
# Install

install( TARGETS ${PROJECT_NAME} DESTINATION ${PATH_PLUGIN} )

#------------------------------------------------------------------------------
# Qt5

find_package( Qt5 COMPONENTS Core Network Widgets LinguistTools REQUIRED )

target_link_libraries( ${PROJECT_NAME} Qt5::Core Qt5::Network Qt5::Widgets )

include( ${CMAKE_SOURCE_DIR}/cmake/AddTranslations.cmake )
