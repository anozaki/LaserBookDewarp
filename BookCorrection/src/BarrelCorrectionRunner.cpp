/*
 * BarrelCorrectionRunner.cpp
 *
 *  Created on: Feb 21, 2011
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
 */

#include <math.h>

#include "BarrelCorrectionRunner.h"

BarrelCorrectionRunner::BarrelCorrectionRunner(const QImage &image, const QList<QVector2D> &translation) {
	this->image = image;
	this->translation = translation;

	interpolation = BarrelCorrection::Bilinear;
}

BarrelCorrectionRunner::~BarrelCorrectionRunner() {
	// TODO Auto-generated destructor stub
}

void BarrelCorrectionRunner::setScanLine(QRgb *scanLine, int workingY) {
	this->scanLine = scanLine;
	this->workingY = workingY;
}

void BarrelCorrectionRunner::run() {
	for(int x = 0; x < image.width(); x++) {
		switch(interpolation) {
		case BarrelCorrection::Bilinear:
			scanLine[x] = processPixel(translation[x].x(), translation[x].y());
			break;
		case BarrelCorrection::NearestNeighbor:
			scanLine[x] = processNNPixel(translation[x].x(), translation[x].y());
			break;
		case BarrelCorrection::Bicubic:
			scanLine[x] = processCubicPixel(translation[x].x(), translation[x].y());
		}
	}
}

void BarrelCorrectionRunner::setMethod(BarrelCorrection::Interpolation type) {
	interpolation = type;
}

// bilinear interpolation
QRgb BarrelCorrectionRunner::processNNPixel(double x, double y) {
	double xFloor = x - floor(x);
	double yFloor = y - floor(y);

	int xPix = x - xFloor;
	int yPix = y - yFloor;

	if(xPix >= image.width() - 1 || yPix >= image.height() - 1 || xPix < 0 || yPix < 0) {
		return qRgb(0,0,0);
	}

	return image.pixel(xPix, yPix);
}

int linearInterpolation(int a, int b, int c, int d, double x, double y) {
	return a * (1 - x) * (1 - y) + b * x * (1 - y) + c * y * (1 - x) + d * x * y;
}

// bilinear interpolation
QRgb BarrelCorrectionRunner::processPixel(double x, double y) {
	double xFloor = x - floor(x);
	double yFloor = y - floor(y);

	int xPix = x - xFloor;
	int yPix = y - yFloor;

	if(xPix >= image.width() - 1 || yPix >= image.height() - 1 || xPix < 0 || yPix < 0) {
		return qRgb(0,0,0);
	}

	QRgb a = image.pixel(xPix, yPix);
	QRgb b = image.pixel(xPix + 1, yPix + 1);
	QRgb c = image.pixel(xPix, yPix + 1);
	QRgb d = image.pixel(xPix + 1, yPix + 1);

	int red = linearInterpolation(qRed(a), qRed(b), qRed(c), qRed(d), xFloor, yFloor);
	int green = linearInterpolation(qGreen(a), qGreen(b), qGreen(c), qGreen(d), xFloor, yFloor);
	int blue = linearInterpolation(qBlue(a), qBlue(b), qBlue(c), qBlue(d), xFloor, yFloor);

	return qRgb(red, green, blue);
}

// http://www.paulinternet.nl/?page=bicubic
double cubicInterpolate (double a, double b, double c, double d, double x) {
	return b + 0.5 * x*(c - a + x*(2.0*a - 5.0 * b + 4.0 * c - d + x*(3.0*(b - c) + d - a)));
}

double Fx(double x) {
	if ( x > 0)
		return x;

	return 0;
}

double Rx(double x) {
	return (pow(Fx(x + 2.0), 3) - 4 * pow(Fx(x + 1.0), 3) + 6 * pow(Fx(x), 3) - 4 * pow(Fx(x - 1.0), 3)) / 6;
}

// Paul Bourke's algorithm
// Not working...
double wikiProcessCubic(int data[4][4], double x, double y) {
	double result = 0;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			result += (double)data[i][j] * Rx((i - 1) - x) * Rx(y - (j - 1));
		}
	}

	return result;
}

int processCubic(int data[4][4], double x, double y) {

	double a = cubicInterpolate(data[0][0], data[0][1], data[0][2], data[0][3], x);
	double b = cubicInterpolate(data[1][0], data[1][1], data[1][2], data[1][3], x);
	double c = cubicInterpolate(data[2][0], data[2][1], data[2][2], data[2][3], x);
	double d = cubicInterpolate(data[3][0], data[3][1], data[3][2], data[3][3], x);
	double e = cubicInterpolate(a, b, c, d, y);

	if(e < 0) {
		return 0;
	}

	if( e > 255) {
		return 255;
	}

	return e;
}

QRgb BarrelCorrectionRunner::processCubicPixel(double x, double y) {

	int redData[4][4];
	int greenData[4][4];
	int blueData[4][4];

	double xFloor = x - floor(x);
	double yFloor = y - floor(y);

	int xPix = x - xFloor;
	int yPix = y - yFloor;

	if(xPix >= image.width() - 4 || yPix >= image.height() - 4 || xPix < 0 || yPix < 0) {
		return qRgb(0,0,0);
	}

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			QRgb color = image.pixel(xPix + j, yPix + i);
			redData[i][j] = qRed(color);
			greenData[i][j] = qGreen(color);
			blueData[i][j] = qBlue(color);
		}
	}

	int red = processCubic(redData, xFloor, yFloor);
	int green = processCubic(greenData, xFloor, yFloor);
	int blue = processCubic(blueData, xFloor, yFloor);

	return qRgb(red, green, blue);
}
//
//void BarrelCorrectionRunner::findPoint(QRgb scanLine[], int x, int width, int step) {
//
//}
