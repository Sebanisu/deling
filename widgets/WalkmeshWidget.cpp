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
#include "widgets/WalkmeshWidget.h"

WalkmeshWidget::WalkmeshWidget(QWidget *parent) :
	PageWidget(parent), walkmeshGL(NULL)
{
}

void WalkmeshWidget::build()
{
	if(isBuilded())		return;

	walkmeshGL = new WalkmeshGLWidget;

	QSlider *slider1 = new QSlider(this);
	QSlider *slider2 = new QSlider(this);
	QSlider *slider3 = new QSlider(this);
//	QSlider *slider4 = new QSlider(this);

	slider1->setRange(0, 360 * 16);
	slider2->setRange(0, 360 * 16);
	slider3->setRange(0, 360 * 16);
//	slider4->setRange(-4096, 4096);

	slider1->setValue(0);
	slider2->setValue(0);
	slider3->setValue(0);
//	slider4->setValue(0);

	QTabWidget *tabWidget = new QTabWidget(this);
	tabWidget->addTab(buildCameraPage(), tr("Cam�ra"));
	tabWidget->addTab(buildGatewaysPage(), tr("Sorties"));
	tabWidget->addTab(buildMovieCameraPage(), tr("Cam�ra cin�matique"));
	tabWidget->setFixedHeight(200);

	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(walkmeshGL, 0, 0);
	layout->addWidget(tabWidget, 1, 0, 1, 4);
	layout->addWidget(slider1, 0, 1);
	layout->addWidget(slider2, 0, 2);
	layout->addWidget(slider3, 0, 3);
//	layout->addWidget(slider4, 0, 4);
	layout->setContentsMargins(QMargins());

	connect(slider1, SIGNAL(valueChanged(int)), walkmeshGL, SLOT(setXRotation(int)));
	connect(slider2, SIGNAL(valueChanged(int)), walkmeshGL, SLOT(setYRotation(int)));
	connect(slider3, SIGNAL(valueChanged(int)), walkmeshGL, SLOT(setZRotation(int)));
//	connect(slider4, SIGNAL(valueChanged(int)), walkmeshGL, SLOT(setZoom(int)));

	PageWidget::build();
}

QWidget *WalkmeshWidget::buildCameraPage()
{
	QWidget *ret = new QWidget(this);

	caVectorXEdit = new VertexWidget(ret);
	caVectorYEdit = new VertexWidget(ret);
	caVectorZEdit = new VertexWidget(ret);

	caSpaceXEdit = new QDoubleSpinBox(ret);
	qreal maxInt = qPow(2,31);
	caSpaceXEdit->setRange(-maxInt, maxInt);
	caSpaceXEdit->setDecimals(0);
	caSpaceYEdit = new QDoubleSpinBox(ret);
	caSpaceYEdit->setRange(-maxInt, maxInt);
	caSpaceYEdit->setDecimals(0);
	caSpaceZEdit = new QDoubleSpinBox(ret);
	caSpaceZEdit->setRange(-maxInt, maxInt);
	caSpaceZEdit->setDecimals(0);

	QGridLayout *caLayout = new QGridLayout(ret);
	caLayout->addWidget(new QLabel(tr("Axes de la cam�ra :")), 0, 0, 1, 6);
	caLayout->addWidget(caVectorXEdit, 1, 0, 1, 6);
	caLayout->addWidget(caVectorYEdit, 2, 0, 1, 6);
	caLayout->addWidget(caVectorZEdit, 3, 0, 1, 6);
	caLayout->addWidget(new QLabel(tr("Position de la cam�ra :")), 4, 0, 1, 6);
	caLayout->addWidget(new QLabel(tr("X")), 5, 0);
	caLayout->addWidget(caSpaceXEdit, 5, 1);
	caLayout->addWidget(new QLabel(tr("Y")), 5, 2);
	caLayout->addWidget(caSpaceYEdit, 5, 3);
	caLayout->addWidget(new QLabel(tr("Z")), 5, 4);
	caLayout->addWidget(caSpaceZEdit, 5, 5);
	caLayout->setRowStretch(6, 1);
	caLayout->setColumnStretch(1, 1);
	caLayout->setColumnStretch(3, 1);
	caLayout->setColumnStretch(5, 1);

	connect(caVectorXEdit, SIGNAL(valuesChanged(Vertex_s)), SLOT(editCaVector(Vertex_s)));
	connect(caVectorYEdit, SIGNAL(valuesChanged(Vertex_s)), SLOT(editCaVector(Vertex_s)));
	connect(caVectorZEdit, SIGNAL(valuesChanged(Vertex_s)), SLOT(editCaVector(Vertex_s)));

	connect(caSpaceXEdit, SIGNAL(valueChanged(double)), SLOT(editCaPos(double)));
	connect(caSpaceYEdit, SIGNAL(valueChanged(double)), SLOT(editCaPos(double)));
	connect(caSpaceZEdit, SIGNAL(valueChanged(double)), SLOT(editCaPos(double)));

	return ret;
}

QWidget *WalkmeshWidget::buildGatewaysPage()
{
	QWidget *ret = new QWidget(this);

	gateList = new QListWidget(ret);
	gateList->setFixedWidth(150);

	exitPoints[0] = new VertexWidget(ret);
	exitPoints[1] = new VertexWidget(ret);
	entryPoint = new VertexWidget(ret);

	doorPosition[0] = new VertexWidget(ret);
	doorPosition[1] = new VertexWidget(ret);

	doorId = new QSpinBox(ret);
	doorId->setRange(0, 255);

	unknownGate = new QLineEdit(ret);
	unknownGate->setMaxLength(12*2);

	QGridLayout *layout = new QGridLayout(ret);
	layout->addWidget(gateList, 0, 0, 7, 1, Qt::AlignLeft);
	layout->addWidget(new QLabel(tr("Ligne de sortie :")), 0, 1, Qt::AlignTop);
	layout->addWidget(exitPoints[0], 0, 2, Qt::AlignTop);
	layout->addWidget(exitPoints[1], 1, 2, Qt::AlignTop);
	layout->addWidget(new QLabel(tr("Point de destination :")), 2, 1, Qt::AlignTop);
	layout->addWidget(entryPoint, 2, 2, Qt::AlignTop);
	layout->addWidget(new QLabel(tr("Ligne d�clench. porte :")), 3, 1, Qt::AlignTop);
	layout->addWidget(doorPosition[0], 3, 2, Qt::AlignTop);
	layout->addWidget(doorPosition[1], 4, 2, Qt::AlignTop);
	layout->addWidget(new QLabel(tr("Id porte :")), 5, 1, Qt::AlignTop);
	layout->addWidget(doorId, 5, 2, Qt::AlignTop);
	layout->addWidget(new QLabel(tr("Inconnu :")), 6, 1, Qt::AlignTop);
	layout->addWidget(unknownGate, 6, 2, Qt::AlignTop);
	layout->setRowStretch(6, 1);

	connect(gateList, SIGNAL(currentRowChanged(int)), SLOT(setCurrentGateway(int)));
	connect(exitPoints[0], SIGNAL(valuesChanged(Vertex_s)), SLOT(editExitPoint(Vertex_s)));
	connect(exitPoints[1], SIGNAL(valuesChanged(Vertex_s)), SLOT(editExitPoint(Vertex_s)));
	connect(entryPoint, SIGNAL(valuesChanged(Vertex_s)), SLOT(editEntryPoint(Vertex_s)));
	connect(doorPosition[0], SIGNAL(valuesChanged(Vertex_s)), SLOT(editDoorPoint(Vertex_s)));
	connect(doorPosition[1], SIGNAL(valuesChanged(Vertex_s)), SLOT(editDoorPoint(Vertex_s)));
	connect(doorId, SIGNAL(valueChanged(int)), SLOT(editDoorId(int)));
	connect(unknownGate, SIGNAL(textEdited(QString)), SLOT(editUnknownGate(QString)));

	return ret;
}

QWidget *WalkmeshWidget::buildMovieCameraPage()
{
	QWidget *ret = new QWidget(this);

	camToolbar = new QToolBar(this);
	camToolbar->setIconSize(QSize(16, 16));
	camToolbar->setFixedWidth(150);
	camPlusAction = camToolbar->addAction(QIcon(":/images/plus.png"), tr("Ajouter"), this, SLOT(addMovieCameraPosition()));
	camPlusAction->setShortcut(QKeySequence("Ctrl++"));
	camMinusAction = camToolbar->addAction(QIcon(":/images/minus.png"), tr("Effacer"), this, SLOT(removeMovieCameraPosition()));
	camMinusAction->setShortcut(QKeySequence::Delete);

	frameList = new QListWidget(ret);
	frameList->setFixedWidth(150);
//	frameList->setDragDropMode(QAbstractItemView::InternalMove);//TODO

	camPoints[0] = new VertexWidget(ret);
	camPoints[1] = new VertexWidget(ret);
	camPoints[2] = new VertexWidget(ret);
	camPoints[3] = new VertexWidget(ret);

	QGridLayout *layout = new QGridLayout(ret);
	layout->addWidget(camToolbar, 0, 0);
	layout->addWidget(frameList, 1, 0, 4, 1, Qt::AlignLeft);
	layout->addWidget(camPoints[0], 1, 1, Qt::AlignLeft | Qt::AlignTop);
	layout->addWidget(camPoints[1], 2, 1, Qt::AlignLeft | Qt::AlignTop);
	layout->addWidget(camPoints[2], 3, 1, Qt::AlignLeft | Qt::AlignTop);
	layout->addWidget(camPoints[3], 4, 1, Qt::AlignLeft | Qt::AlignTop);
	layout->setRowStretch(4, 1);

	connect(frameList, SIGNAL(currentRowChanged(int)), SLOT(setCurrentMoviePosition(int)));

	return ret;
}

void WalkmeshWidget::clear()
{
	if(!isFilled())		return;

	if(walkmeshGL != NULL)
		walkmeshGL->clear();

	gateList->clear();
	frameList->clear();

	PageWidget::clear();
}

void WalkmeshWidget::fill()
{
	if(!isBuilded())	build();
	if(isFilled())		clear();

	if(!hasData() || !data()->hasWalkmeshFile()) return;

	if(data()->hasWalkmeshFile()) {
		walkmeshGL->fill(data()->getWalkmeshFile());
		bool hasCamera = data()->getWalkmeshFile()->cameraCount() > 0;

		if(hasCamera) {
			const int camID = 0;
			const CaStruct &cam = data()->getWalkmeshFile()->camera(camID);

//			qDebug() << cam.camera_axis[0].x << cam.camera_axis[0].y << cam.camera_axis[0].z;
//			qDebug() << cam.camera_axis[1].x << cam.camera_axis[1].y << cam.camera_axis[1].z;
//			qDebug() << cam.camera_axis[2].x << cam.camera_axis[2].y << cam.camera_axis[2].z;
//			qDebug() << cam.camera_position[0] << cam.camera_position[1] << cam.camera_position[2];

			caVectorXEdit->setValues(cam.camera_axis[0]);
			caVectorYEdit->setValues(cam.camera_axis[1]);
			caVectorZEdit->setValues(cam.camera_axis[2]);

			caSpaceXEdit->setValue(cam.camera_position[0]);
			caSpaceYEdit->setValue(cam.camera_position[1]);
			caSpaceZEdit->setValue(cam.camera_position[2]);
		}

		caVectorXEdit->setEnabled(hasCamera);
		caVectorYEdit->setEnabled(hasCamera);
		caVectorZEdit->setEnabled(hasCamera);

		caSpaceXEdit->setEnabled(hasCamera);
		caSpaceYEdit->setEnabled(hasCamera);
		caSpaceZEdit->setEnabled(hasCamera);
	}

	if(data()->hasInfFile()) {
		gateList->clear();
		foreach(const Gateway &gateway, data()->getInfFile()->getGateways()) {
			gateList->addItem(QString("%1 (%2)").arg(Data::maplist().value(gateway.fieldId)).arg(gateway.fieldId));
		}
		gateList->setCurrentRow(0);
	}

	if(data()->hasMskFile()) {
		frameList->clear();
		int cameraPositionCount = data()->getMskFile()->cameraPositionCount();
		for(int i=0 ; i<cameraPositionCount ; ++i) {
			frameList->addItem(QString("Position %1").arg(i+1));
		}
		frameList->setCurrentRow(0);
	}

	PageWidget::fill();
}

void WalkmeshWidget::editCaVector(const Vertex_s &values)
{
	QObject *s = sender();

	if(s == caVectorXEdit)			editCaVector(0, values);
	else if(s == caVectorYEdit)		editCaVector(1, values);
	else if(s == caVectorZEdit)		editCaVector(2, values);
}

void WalkmeshWidget::editCaVector(int id, const Vertex_s &values)
{
	if(data()->hasWalkmeshFile() && data()->getWalkmeshFile()->cameraCount() > 0) {
		const int camID = 0;
		CaStruct cam = data()->getWalkmeshFile()->camera(camID);
		Vertex_s oldV = cam.camera_axis[id];

		if(oldV.x != values.x || oldV.y != values.y || oldV.z != values.z) {
			cam.camera_axis[id] = values;
			data()->getWalkmeshFile()->setCamera(camID, cam);
			emit modified();
		}
	}
}

void WalkmeshWidget::editCaPos(double value)
{
	QObject *s = sender();

	if(s == caSpaceXEdit)			editCaPos(0, value);
	else if(s == caSpaceYEdit)		editCaPos(1, value);
	else if(s == caSpaceZEdit)		editCaPos(2, value);
}

void WalkmeshWidget::editCaPos(int id, double value)
{
	if(data()->hasWalkmeshFile() && data()->getWalkmeshFile()->cameraCount() > 0) {
		const int camID = 0;
		CaStruct cam = data()->getWalkmeshFile()->camera(camID);
		if(cam.camera_position[id] != (qint32)value) {
			cam.camera_position[id] = value;
			data()->getWalkmeshFile()->setCamera(camID, cam);
			emit modified();
		}
	}
}

void WalkmeshWidget::setCurrentGateway(int id)
{
	if(!data()->hasInfFile() || id < 0)    return;

	InfFile *inf = data()->getInfFile();
	QList<Gateway> gateways = inf->getGateways();
	if(gateways.size() <= id)    return;

	const Gateway &gateway = gateways.at(id);
	const Trigger &trigger = inf->getTrigger(id);

	exitPoints[0]->setValues(gateway.exitLine[0]);
	exitPoints[1]->setValues(gateway.exitLine[1]);
	entryPoint->setValues(gateway.destinationPoint);
	doorPosition[0]->setValues(trigger.trigger_line[0]);
	doorPosition[1]->setValues(trigger.trigger_line[1]);
	doorId->setValue(trigger.doorID);
	unknownGate->setText(QByteArray((char *)&gateway.unknown, 12).toHex());
}

void WalkmeshWidget::editExitPoint(const Vertex_s &values)
{
	QObject *s = sender();

	if(s == exitPoints[0])			editExitPoint(0, values);
	else if(s == exitPoints[1])		editExitPoint(1, values);
}

void WalkmeshWidget::editExitPoint(int id, const Vertex_s &values)
{
	if(data()->hasInfFile()) {
		int gateId = gateList->currentRow();
		Gateway old = data()->getInfFile()->getGateway(gateId);
		Vertex_s oldVertex = old.exitLine[id];
		if(oldVertex.x != values.x || oldVertex.y != values.y || oldVertex.z != values.z) {
			old.exitLine[id] = values;
			data()->getInfFile()->setGateway(gateId, old);
			emit modified();
		}
	}
}

void WalkmeshWidget::editEntryPoint(const Vertex_s &values)
{
	if(data()->hasInfFile()) {
		int gateId = gateList->currentRow();
		Gateway old = data()->getInfFile()->getGateway(gateId);
		Vertex_s oldVertex = old.destinationPoint;
		if(oldVertex.x != values.x || oldVertex.y != values.y || oldVertex.z != values.z) {
			old.destinationPoint = values;
			data()->getInfFile()->setGateway(gateId, old);
			emit modified();
		}
	}
}

void WalkmeshWidget::editDoorPoint(const Vertex_s &values)
{
	QObject *s = sender();

	if(s == doorPosition[0])			editDoorPoint(0, values);
	else if(s == doorPosition[1])		editDoorPoint(1, values);
}

void WalkmeshWidget::editDoorPoint(int id, const Vertex_s &values)
{
	if(data()->hasInfFile()) {
		int gateId = gateList->currentRow();
		Trigger old = data()->getInfFile()->getTrigger(gateId);
		Vertex_s oldVertex = old.trigger_line[id];
		if(oldVertex.x != values.x || oldVertex.y != values.y || oldVertex.z != values.z) {
			old.trigger_line[id] = values;
			data()->getInfFile()->setTrigger(gateId, old);
			emit modified();
		}
	}
}

void WalkmeshWidget::editUnknownGate(const QString &u)
{
	if(data()->hasInfFile()) {
		int gateId = gateList->currentRow();
		const char *uData = QByteArray::fromHex(u.toLatin1()).leftJustified(12, '\0', true).constData();
		Gateway old = data()->getInfFile()->getGateway(gateId);
		memcpy(old.unknown, uData, 12);
		data()->getInfFile()->setGateway(gateId, old);
		emit modified();
	}
}

void WalkmeshWidget::editDoorId(int v)
{
	if(data()->hasInfFile()) {
		int gateId = gateList->currentRow();
		Trigger old = data()->getInfFile()->getTrigger(gateId);
		if(old.doorID != v) {
			old.doorID = v;
			data()->getInfFile()->setTrigger(gateId, old);
			emit modified();
		}
	}
}

void WalkmeshWidget::setCurrentMoviePosition(int id)
{
	if(!data()->hasMskFile() || id < 0) {
		setMovieCameraPageEnabled(false);
		return;
	}

	MskFile *msk = data()->getMskFile();
	if(msk->cameraPositionCount() <= id) {
		setMovieCameraPageEnabled(false);
		return;
	}

	setMovieCameraPageEnabled(true);

	camPoints[0]->setValues(msk->cameraPosition(id)[0]);
	camPoints[1]->setValues(msk->cameraPosition(id)[1]);
	camPoints[2]->setValues(msk->cameraPosition(id)[2]);
	camPoints[3]->setValues(msk->cameraPosition(id)[3]);
}

void WalkmeshWidget::setMovieCameraPageEnabled(bool enabled)
{
	camPoints[0]->setEnabled(enabled);
	camPoints[1]->setEnabled(enabled);
	camPoints[2]->setEnabled(enabled);
	camPoints[3]->setEnabled(enabled);
}

void WalkmeshWidget::addMovieCameraPosition()
{
	if(!data()->hasMskFile()) return;

	int row = frameList->currentRow();
	if(row < 0)	row = 0;

	Vertex_s *camPos = new Vertex_s[4];

	memset(camPos, 0, sizeof(Vertex_s) * 4);

	data()->getMskFile()->insertCameraPosition(row+1, camPos);

	frameList->addItem(tr("Position %1").arg(row+1));
	for(int i=row+1 ; i<frameList->count() ; ++i) {
		frameList->item(i)->setText(tr("Position %1").arg(i+1));
	}

	emit modified();

	frameList->setCurrentRow(row+1);
}

void WalkmeshWidget::removeMovieCameraPosition()
{
	if(!data()->hasMskFile()) return;

	int row = frameList->currentRow();
	if(row < 0)	row = 0;

	data()->getMskFile()->removeCameraPosition(row);

	delete frameList->item(row);
	for(int i=row ; i<frameList->count() ; ++i) {
		frameList->item(i)->setText(tr("Position %1").arg(i+1));
	}

	emit modified();
}
