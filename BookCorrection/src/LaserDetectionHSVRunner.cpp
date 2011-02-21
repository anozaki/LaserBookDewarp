/*
 * LaserDetectionHSVRunner.cpp
 *
 *  Created on: Feb 20, 2011
 *      Author: Akito Nozaki
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
 *
 */

#include <math.h>
#include <iostream>

#include <QColor>

#include "ScanLineData.h"
#include "LaserDetectionHSVRunner.h"

LaserDetectionHSVRunner::LaserDetectionHSVRunner(QImage image) {
	this->image = image;
}

LaserDetectionHSVRunner::~LaserDetectionHSVRunner() {
}

void LaserDetectionHSVRunner::setScanLine(QRgb *scanLine, int workingY) {
	this->scanLine = scanLine;
	this->workingY = workingY;
}

void LaserDetectionHSVRunner::run() {
	int w = image.width();

	bool leftFound = false;
	int leftFoundGreen;
	int leftFoundX = 0;

	bool rightFound = false;
	int rightFoundGreen;
	int rightFoundX = 0;

	for (int x = 0; x < w; x++) {
		scanLine[x] = processPixel(x, workingY);

//		int g = qGreen(scanLine[x]);
//
//		if (scanLine[x] == qRgb(0, 0, 0)) {
//			continue;
//		}
//
//		if (x < w / 2) {
//			// left side
//			if (leftFound == false || leftFoundGreen < g) {
//				if (leftFound == true) {
//					scanLine[leftFoundX] = qRgb(0, 0, 0);
//				}
//
//				leftFoundX = x;
//				leftFoundGreen = g;
//				leftFound = true;
//
//				scanLine[leftFoundX] = qRgb(0, 255, 0);
//			} else {
//				scanLine[x] = qRgb(0, 0, 0);
//			}
//		} else {
//			// right side
//			if (rightFound == false || rightFoundGreen < g) {
//				if (rightFound == true) {
//					scanLine[rightFoundX] = qRgb(0, 0, 0);
//				}
//
//				rightFoundX = x;
//				rightFoundGreen = g;
//				rightFound = true;
//
//				scanLine[rightFoundX] = qRgb(0, 255, 0);
//			} else {
//				scanLine[x] = qRgb(0, 0, 0);
//			}
//		}
	}

}

const double PI = 3.141592;

float getHue(float r, float g, float b) {

	float h = 180 / PI * atan2( sqrt(3)*(g - b),  2*r-g-b );
	if(h < 0) {
		return h + 360;
	}

	return h;
}

const float greenHue = QColor(0, 255, 0).hsvHueF();

QRgb LaserDetectionHSVRunner::processPixel(int x, int y) {
	QRgb original = image.pixel(x, y);

	QColor color(original);

//	printf("%f %f\n", color.hsvHueF(), greenHue);

	qreal h = color.hsvHueF();
	qreal s = color.hsvSaturationF();

	// 108/255 120/255
//	if (.45f > h && h > .50) { // && s > .4) {
//		return original;
//	}

	int a = h * 255;
//	int a = s * 255;
//	return qRgb(a, a, a);

	return qRgb(0, 0, 0);
}
