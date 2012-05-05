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
#include "Field.h"

Field::Field(const QString &name)
	: _isOpen(false), _name(name),
	  msdFile(NULL), jsmFile(NULL), walkmeshFile(NULL),
	  encounterFile(NULL), miscFile(NULL), backgroundFile(NULL),
	  tdwFile(NULL)
{
}

Field::~Field()
{
	if(msdFile!=NULL)			delete msdFile;
	if(jsmFile!=NULL)			delete jsmFile;
	if(walkmeshFile!=NULL)		delete walkmeshFile;
	if(encounterFile!=NULL)		delete encounterFile;
	if(miscFile!=NULL)			delete miscFile;
	if(backgroundFile!=NULL)	delete backgroundFile;
	if(tdwFile!=NULL)			delete tdwFile;
}

bool Field::isOpen() const
{
	return _isOpen;
}

void Field::setOpen(bool open)
{
	_isOpen = open;
}

void Field::openMsdFile(const QByteArray &msd)
{
	if(msdFile!=NULL) 	deleteMsdFile();
	msdFile = new MsdFile();

	if(!msdFile->open(msd)) {
		qWarning() << "Field::openMsdFile error" << _name;
		deleteMsdFile();
	}
}

void Field::openJsmFile(const QByteArray &jsm, const QByteArray &sym)
{
	if(jsmFile!=NULL) 	deleteJsmFile();
	jsmFile = new JsmFile();

	if(!jsmFile->open(jsm, sym)) {
		qWarning() << "Field::openJsmFile error" << _name;
		deleteJsmFile();
	}
}

void Field::openWalkmeshFile(const QByteArray &id, const QByteArray &ca)
{
	if(walkmeshFile!=NULL) 	deleteWalkmeshFile();
	walkmeshFile = new WalkmeshFile();

	if(!walkmeshFile->open(id, ca)) {
		qWarning() << "Field::openWalkmeshFile error" << _name;
		deleteWalkmeshFile();
	}
}

void Field::openEncounterFile(const QByteArray &rat, const QByteArray &mrt)
{
	if(encounterFile!=NULL) 	deleteEncounterFile();
	encounterFile = new EncounterFile();

	if(!encounterFile->open(rat, mrt)) {
		qWarning() << "Field::openEncounterFile error" << _name;
		deleteEncounterFile();
	}
}

void Field::openMiscFile(const QByteArray &inf, const QByteArray &pmp,
						 const QByteArray &pmd, const QByteArray &pvp)
{
	if(miscFile!=NULL) 	deleteMiscFile();
	miscFile = new MiscFile();

	if(!miscFile->open(inf, pmp, pmd, pvp)) {
		qWarning() << "Field::openMiscFile error" << _name;
		deleteMiscFile();
	}
}

void Field::openBackgroundFile(const QByteArray &map, const QByteArray &mim)
{
	if(backgroundFile!=NULL)	deleteBackgroundFile();
	backgroundFile = new BackgroundFile();

	if(!backgroundFile->open(map, mim)) {
		qWarning() << "Field::openBackgroundFile error" << _name;
		deleteBackgroundFile();
	}
}

void Field::openTdwFile(const QByteArray &tdw)
{
	if(tdwFile!=NULL)	deleteTdwFile();
	tdwFile = new TdwFile();

	if(!tdwFile->open(tdw)) {
		qWarning() << "Field::openTdwFile error" << _name;
		deleteTdwFile();
	}
}

void Field::deleteMsdFile()
{
	if(msdFile!=NULL) {
		delete msdFile;
		msdFile = NULL;
	}
}

void Field::deleteJsmFile()
{
	if(jsmFile!=NULL) {
		delete jsmFile;
		jsmFile = NULL;
	}
}

void Field::deleteWalkmeshFile()
{
	if(walkmeshFile!=NULL) {
		delete walkmeshFile;
		walkmeshFile = NULL;
	}
}

void Field::deleteEncounterFile()
{
	if(encounterFile!=NULL) {
		delete encounterFile;
		encounterFile = NULL;
	}
}

void Field::deleteMiscFile()
{
	if(miscFile!=NULL) {
		delete miscFile;
		miscFile = NULL;
	}
}

void Field::deleteBackgroundFile()
{
	if(backgroundFile!=NULL) {
		delete backgroundFile;
		backgroundFile = NULL;
	}
}

void Field::deleteTdwFile()
{
	if(tdwFile!=NULL) {
		delete tdwFile;
		tdwFile = NULL;
	}
}

bool Field::hasMsdFile() const
{
	return msdFile != NULL;
}

bool Field::hasJsmFile() const
{
	return jsmFile != NULL;
}

bool Field::hasWalkmeshFile() const
{
	return walkmeshFile != NULL;
}

bool Field::hasEncounterFile() const
{
	return encounterFile != NULL;
}

bool Field::hasMiscFile() const
{
	return miscFile != NULL;
}

bool Field::hasBackgroundFile() const
{
	return backgroundFile != NULL;
}

bool Field::hasTdwFile() const
{
	return tdwFile != NULL;
}

bool Field::hasFiles() const
{
	return hasMsdFile() || hasJsmFile() || hasMapMimFiles()
			|| hasWalkmeshFile() || hasMiscFile();
}

MsdFile *Field::getMsdFile() const
{
	return msdFile;
}

JsmFile *Field::getJsmFile() const
{
	return jsmFile;
}

WalkmeshFile *Field::getWalkmeshFile() const
{
	return walkmeshFile;
}

EncounterFile *Field::getEncounterFile() const
{
	return encounterFile;
}

MiscFile *Field::getMiscFile() const
{
	return miscFile;
}

BackgroundFile *Field::getBackgroundFile() const
{
	return backgroundFile;
}

TdwFile *Field::getTdwFile() const
{
	return tdwFile;
}

bool Field::isModified() const
{
	return (msdFile != NULL && msdFile->isModified())
			|| (jsmFile != NULL && jsmFile->isModified())
			|| (encounterFile != NULL && encounterFile->isModified())
			|| (miscFile != NULL && miscFile->isModified())
			|| (walkmeshFile != NULL && walkmeshFile->isModified())
			|| (backgroundFile != NULL && backgroundFile->isModified())
			|| (tdwFile != NULL && tdwFile->isModified());
}

const QString &Field::name() const
{
	return _name;
}
