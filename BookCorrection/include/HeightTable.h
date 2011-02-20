/*
 * HeightTable.h
 *
 *  Created on: Feb 19, 2011
 *      Author: anozaki
 */

#ifndef HEIGHTTABLE_H_
#define HEIGHTTABLE_H_

#include <QVector3D>
#include <QtGlobal>
#include <QImage>

class HeightTable {
public:
	// width and height of the image
	HeightTable(int width, int height);
	virtual ~HeightTable();

	void setOrigin(QVector3D origin);

	// this determins where the 45 degree plane is comming from.
	void setBaseDistance(QVector3D base, qreal degree);

	void generate();

	QImage asImage();

private:
	int width, height;

	QVector3D normalTop, normalBottom;

	QVector3D origin, base;

	QVector<QVector3D> heightTable;

	QVector3D getNormal(QVector3D common, QVector3D pointA, QVector3D pointB);

	qreal minHeight, maxHeight;
};

#endif /* HEIGHTTABLE_H_ */
