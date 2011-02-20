/*
 * ScanLineData.h
 *
 *  Created on: Feb 19, 2011
 *      Author: anozaki
 */

#ifndef SCANLINEDATA_H_
#define SCANLINEDATA_H_

#include <QVector2D>

class ScanLineData {
public:
	ScanLineData();
	virtual ~ScanLineData();

	void setPointAAvailable(bool available);
	bool isPointAAvailable();

	QVector2D getPointA();
	void setPointA(QVector2D pointA);

	void setPointBAvailable(bool available);
	bool isPointBAvailable();

	QVector2D getPointB();
	void setPointB(QVector2D pointB);

private:
	QVector2D pointA;
	bool pointAAvailable;
	QVector2D pointB;
	bool pointBAvailable;
};

#endif /* SCANLINEDATA_H_ */
