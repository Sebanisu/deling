/****************************************************************************
 ** Deling Final Fantasy VIII Field Editor
 ** Copyright (C) 2009-2012 Arzel J�r�me <myst6re@gmail.com>
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#ifndef FSARCHIVEPC_H
#define FSARCHIVEPC_H

#include "FieldArchive.h"
#include "FieldPC.h"
#include "FsArchive.h"

class FieldArchivePC : public FieldArchive
{
public:
	FieldArchivePC();
	~FieldArchivePC();
	QString archivePath() const;
	FsArchive *getFsArchive() const;
	int open(const QString &, QProgressDialog *progress);
	bool save(QProgressDialog *progress, QString save_path=QString());
	bool openBG(Field *field, QByteArray &tdw_data, QByteArray &chara_data) const;
	void restoreFieldHeaders(const QMap<Field *, QMap<QString, FsHeader> > &oldFields) const;
	bool optimiseArchive(QProgressDialog *progress);
private:
	FsArchive *archive;
};

#endif // FSARCHIVEPC_H
