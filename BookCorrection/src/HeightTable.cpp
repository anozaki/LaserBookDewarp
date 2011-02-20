/*
 * HeightTable.cpp
 *
 *  Created on: Feb 19, 2011
 *      Author: anozaki
 */

#include <QVector>
#include <QVector3D>
#include <QImage>
#include <math.h>

#include "HeightTable.h"

HeightTable::HeightTable(int width, int height) {
	this->width = width;
	this->height = height;
}

HeightTable::~HeightTable() {
}

void HeightTable::setOrigin(QVector3D origin) {
	this->origin = origin;
}

void HeightTable::setBaseDistance(QVector3D base, qreal degree) {
	this->base = base;

	// find a coordinate that exist on the laser plane. Simple geometry...
	qreal y = base.z() / tan(degree);

	// we can always assume one edge along the base going across.
	normalTop = getNormal(base, QVector3D(base.z(), 0, base.z()), QVector3D(
			0, y, 0));
	normalBottom = getNormal(base, QVector3D(base.z(), 0, base.z()),
			QVector3D(0, -y, 0));
}

// generate the normal of the plane
QVector3D HeightTable::getNormal(QVector3D common, QVector3D pointA,
		QVector3D pointB) {
	// base
	QVector3D u = pointA - common;
	QVector3D v = pointB - common;

	qreal nX = (u.y() * v.z()) - (u.z() * v.y());
	qreal nY = (u.z() * v.x()) - (u.x() * v.z());
	qreal nZ = (u.x() * v.y()) - (u.y() * v.x());

	QVector3D result = QVector3D(nX, nY, nZ).normalized();

	return result;
}

// simple linear interpolation algorithm...
int getPixel(qreal x, qreal x0, qreal x1) {
	qreal y0 = 0;
	qreal y1 = 255;

	return ((x - x0) * y1 + (x1 - x) * y0) / (x1 - x0);
}


// TODO convert this to multi thread... This is some complex calculation, but should only needs to be done once.
void HeightTable::generate() {
	QVector3D normalToUse;

	qreal minz, maxz;
	minz = maxz = 0;

	QVector<QVector3D> data(width * height);

	for (int y = 0; y < height; y++) {
		int coordinateY = y - (height / 2);

		if(coordinateY < 0) {
			normalToUse = normalBottom;
		} else {
			normalToUse = normalTop;
		}

		for (int x = 0; x < width; x++) {
			int coordinateX = x - (width / 2);

			QVector3D direction = QVector3D(coordinateX, coordinateY, 0);

			qreal t = QVector3D::dotProduct(normalToUse, (base - origin))
					/ QVector3D::dotProduct(normalToUse, (direction - origin));

			QVector3D intersect = origin + (t * (direction - origin));
			data[x + (y * width)] = intersect;

			if(intersect.z() > maxz) {
				maxz = intersect.z();
			}

			if(intersect.z() < minz) {
				minz = intersect.z();
			}
		}
	}

	minHeight = minz;
	maxHeight = maxz;

	heightTable = data;
}


QImage HeightTable::asImage() {
	QImage image(width, height, QImage::Format_RGB32);

	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			int c = getPixel(heightTable[x + (y * width)].z(), minHeight, maxHeight);

			image.setPixel(x,y,qRgb(c,c,c));
		}
	}

	return image;
}
