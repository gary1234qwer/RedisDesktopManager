#include "Updater.h"

#include <QtNetwork>

Updater::Updater()
{
	QNetworkAccessManager *manager = new QNetworkAccessManager();

	QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(requestFinished(QNetworkReply*)));

	QString platform("unknown");

	#ifdef Q_OS_WIN32
		platform = "windows"; 
	#endif

	#ifdef Q_OS_LINUX
		platform = "linux"; 
	#endif

	#ifdef Q_OS_MACX
		platform = "osx"; 
	#endif
	
	QUrl updateUrl(
		QString("http://%1/get-update?version=%2&platform=%3")
			.arg("redisdesktop.com")
			.arg(QCoreApplication::applicationVersion())
			.arg(platform)
		);

	manager->get(QNetworkRequest(updateUrl));

}
Updater::~Updater()
{
}

void Updater::requestFinished(QNetworkReply* response)
{
	if (response->error() != QNetworkReply::NoError)
	{
		return;			
	}

	QString result(response->readAll());

	if (!result.isEmpty()) 
	{
		emit updateUrlRetrived(result);
	}
}