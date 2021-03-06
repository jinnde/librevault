/* Copyright (C) 2016 Alexander Shishenko <alex@shishenko.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
#pragma once
#include "GenericRemoteDictionary.h"
#include "AbstractConfig.h"
#include <QJsonValue>

class Daemon;

class RemoteConfig : public librevault::AbstractConfig {
	Q_OBJECT

signals:
	void changed();

public:
	explicit RemoteConfig(Daemon* daemon);
	virtual ~RemoteConfig() {}

public slots:
	/* Global configuration */
	QVariant getGlobal(QString name) override;
	void setGlobal(QString name, QVariant value) override;
	void removeGlobal(QString name) override;

	/* Folder configuration */
	void addFolder(QVariantMap fconfig) override;
	void removeFolder(QByteArray folderid) override;

	QVariantMap getFolder(QByteArray folderid) override;
	QList<QByteArray> listFolders() override;

	/* Export/Import */
	QJsonDocument exportUserGlobals() override;
	QJsonDocument exportGlobals() override;
	void importGlobals(QJsonDocument globals_conf) override;

	QJsonDocument exportUserFolders() override;
	QJsonDocument exportFolders() override;
	void importFolders(QJsonDocument folders_conf) override;

private:
	QVariantMap cached_globals_;
	QMap<QByteArray, QVariantMap> cached_folders_;

	Daemon* daemon_;

	void renew();
	void handleGlobals(QJsonDocument globals);
	void handleFolders(QJsonDocument folders);
	void handleEvent(QString name, QJsonObject event);
};
