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
#ifndef FSDIALOG_H
#define FSDIALOG_H

#include <QtGui>
#include "FsArchive.h"
#include "Config.h"
#include "FsWidget.h"
#include "FsPreviewWidget.h"
#include "FF8Image.h"
#include "MapFile.h"

class FsDialog : public QWidget
{
    Q_OBJECT
public:
	explicit FsDialog(FsArchive *fsArchive, QWidget *parent=0);
	~FsDialog();
signals:
private slots:
	void setButtonsEnabled();
	void generatePreview();
	void doubleClicked(QTreeWidgetItem *);
	void openDir();
	void parentDir();
	void extract(QStringList sources=QStringList());
	void replace(QString source=QString(), QString destination=QString());
	void add(QStringList sources=QStringList());
	void remove(QStringList destinations=QStringList());
	void rename();
	void renameOK(QTreeWidgetItem *, int);
private:
	void openDir(const QString &);
	QStringList listFilesInDir(QString dirPath);

	QToolBar *toolBar;
	QAction *extractAction, *replaceAction, *_addAction, *removeAction, *renameAction;
	FsWidget *list;
	FsPreviewWidget *preview;
	QPushButton *up;
	QLineEdit *pathWidget;
	QString currentPath;
	FsArchive *fsArchive;
};

#endif // FSDIALOG_H
