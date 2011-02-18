/*
 * SobelEdgeDetectionRunner.cpp
 *
 *  Created on: Feb 17, 2011
 *      Author: anozaki
 */

#include <math.h>

#include "LaserDetectionRunner.h"

LaserDetectionRunner::LaserDetectionRunner(QImage image) {
	this->image = image;
}

LaserDetectionRunner::~LaserDetectionRunner() {
}

void LaserDetectionRunner::setScanLine(QRgb *scanLine, int workingY) {
	this->scanLine = scanLine;
	this->workingY = workingY;
}

void LaserDetectionRunner::run() {
	int w = image.width();

	for (int x = 0; x < w; x++) {
		scanLine[x] = processPixel(x, workingY);
	}

}

QRgb LaserDetectionRunner::processPixel(int x, int y) {
	QRgb original = image.pixel(x, y);

	// based on difference
	float t = qGreen(original) - 30;
	if (t > qRed(original) && t > qBlue(original)) {
		return original;
	}

	return qRgb(0, 0, 0);
}
