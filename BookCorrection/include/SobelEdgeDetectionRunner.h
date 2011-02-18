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

class SobelEdgeDetectionRunner: public QRunnable {
public:
	SobelEdgeDetectionRunner(QImage image);
	virtual ~SobelEdgeDetectionRunner();

	virtual void run();

	void setScanLine(QRgb *scanLine, int workingY);

private:
	QImage image;

	QRgb *scanLine;
	int width;
	int workingY;

	QRgb processPixel(int size, int w, int h, int x, int y);
};

#endif /* SOBELEDGEDETECTIONRUNNER_H_ */
