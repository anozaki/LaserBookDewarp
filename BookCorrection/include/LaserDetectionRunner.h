/*
 * SobelEdgeDetectionRunner.h
 *
 *  Created on: Feb 17, 2011
 *      Author: anozaki
 */

#ifndef SOBELEDGEDETECTIONRUNNER_H_
#define SOBELEDGEDETECTIONRUNNER_H_

#include <QImage>
#include <QRunnable>

class LaserDetectionRunner: public QRunnable {
public:
	LaserDetectionRunner(QImage image);
	virtual ~LaserDetectionRunner();

	virtual void run();

	void setScanLine(QRgb *scanLine, int workingY);

private:
	QImage image;

	QRgb *scanLine;
	int width;
	int workingY;

	QRgb processPixel(int x, int y);
};

#endif /* SOBELEDGEDETECTIONRUNNER_H_ */
