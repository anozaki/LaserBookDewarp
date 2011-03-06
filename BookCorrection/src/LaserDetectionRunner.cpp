/*
 * SobelEdgeDetectionRunner.cpp
 *
 *  Created on: Feb 17, 2011
 *      Author: anozaki
 *
 * Copyright (C) 2011 by Akito Nozaki
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * TODO: This class needs to be configurable. Example different color laser (spectrum).
 *
 */

#include <math.h>

#include "ScanLineData.h"
#include "LaserDetectionRunner.h"

LaserDetectionRunner::LaserDetectionRunner(const QImage *image) {
	this->image = image;
}

LaserDetectionRunner::~LaserDetectionRunner() {
}

void LaserDetectionRunner::setScanLine(QRgb *scanLine, int workingY) {
	this->scanLine = scanLine;
	this->workingY = workingY;
}

void LaserDetectionRunner::run() {
	int w = image->width();

	bool leftFound = false;
	int leftFoundGreen;
	int leftFoundX = 0;

	bool rightFound = false;
	int rightFoundGreen;
	int rightFoundX = 0;

	const QRgb *originalScanLine = (const QRgb *) image->scanLine(workingY);
	for (int x = 0; x < w; x++) {
		scanLine[x] = processPixel(x, originalScanLine);

		int g = qGreen(scanLine[x]);

		if(scanLine[x] == qRgb(0,0,0)) {
			continue;
		}

		if (x < w / 2) {
			// left side
			if (leftFound == false || leftFoundGreen < g) {
				if (leftFound == true) {
					scanLine[leftFoundX] = qRgb(0, 0, 0);
				}

				leftFoundX = x;
				leftFoundGreen = g;
				leftFound = true;

				scanLine[leftFoundX] = qRgb(0, 255, 0);
			} else {
				scanLine[x] = qRgb(0, 0, 0);
			}
		} else {
			// right side
			if (rightFound == false || rightFoundGreen < g) {
				if (rightFound == true) {
					scanLine[rightFoundX] = qRgb(0, 0, 0);
				}

				rightFoundX = x;
				rightFoundGreen = g;
				rightFound = true;

				scanLine[rightFoundX] = qRgb(0, 255, 0);
			} else {
				scanLine[x] = qRgb(0, 0, 0);
			}
		}
	}

//	ScanLineData data;
//	data.setPointA(QVector2D(leftFoundX, workingY));
//	data.setPointAAvailable(leftFound);
//	data.setPointB(QVector2D(rightFoundX, workingY));
//	data.setPointBAvailable(leftFound);

//	emit completed(QVector2D(leftFoundX, workingY), leftFound, QVector2D(rightFoundX, workingY), leftFound, workingY);
}

/*
 * Makes sure the color we are looking at is green. This function also accounts for laser
 * that is too bright and blown the color out almost to white.
 */
QRgb LaserDetectionRunner::processPixel(int x, const QRgb *originalScanLine) {
	QRgb original = originalScanLine[x];

	float r = qRed(original);
	float g = qGreen(original);
	float b = qBlue(original);

	// based on difference
	float t = g - 20;
	if (t > r && t > b) {
		return original;
	}

	if (r > 200 && g > 200 && b > 200) {
		return original;
	}

	return qRgb(0, 0, 0);
}
