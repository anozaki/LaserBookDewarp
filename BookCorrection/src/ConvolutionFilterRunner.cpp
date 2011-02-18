/*
 * ConvolutionFilterRunnable.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: anozaki
 */

#include <QImage>

#include "ConvolutionFilterRunner.h"

ConvolutionFilterRunner::ConvolutionFilterRunner(QImage image) {
	this->image = image;

	width = image.width();
}

ConvolutionFilterRunner::~ConvolutionFilterRunner() {
}

void ConvolutionFilterRunner::setMatrix(QList<float> &matrix, int radius) {
	this->matrix = &matrix;
	this->radius = radius;
}

void ConvolutionFilterRunner::setScanLine(QRgb *scanLine, int workingY) {
	this->scanLine = scanLine;
	this->workingY = workingY;
}

void ConvolutionFilterRunner::run() {
	int size = radius * 2 + 1;

	int w = image.width();
	int h = image.height();

	for (int x = 0; x < width; x++) {
		scanLine[x] = processPixel(size, w, h, x, workingY);
	}
}

QRgb ConvolutionFilterRunner::processPixel(int size, int w, int h, int x, int y) {
	// starting pixes we are going to start working on.
	x -= radius;
	y -= radius;


	float r, g, b;

	r = g = b = 0.0f;
	for (int offsetY = 0; offsetY < size; offsetY++) {
		if (offsetY + y >= h || offsetY + y < 0) {
			continue;
		}

		QRgb *originalImage = (QRgb*)image.scanLine(y + offsetY);
		for (int offsetX = 0; offsetX < size; offsetX++) {
			if (offsetX + x >= w || offsetX + x < 0) {
				continue;
			}

			QRgb *rgb = &originalImage[x + offsetX];

			float factor = (*matrix)[offsetX + (offsetY * size)];

			r += qRed(*rgb) * factor;
			g += qGreen(*rgb) * factor;
			b += qBlue(*rgb) * factor;
		}
	}

	return qRgb(r,g,b);
}

