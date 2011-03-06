/*
 * ConvolutionFilterRunnable.cpp
 *
 *  Created on: Feb 15, 2011
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
 */

#include <QImage>

#include "ConvolutionFilterRunner.h"

ConvolutionFilterRunner::ConvolutionFilterRunner(const QImage *image) {
	this->image = image;

	width = image->width();
}

ConvolutionFilterRunner::~ConvolutionFilterRunner() {
}

void ConvolutionFilterRunner::setMatrix(const QList<float> &matrix, int radius) {
	this->matrix = &matrix;
	this->radius = radius;
}

void ConvolutionFilterRunner::setScanLine(QRgb *scanLine, int workingY) {
	this->scanLine = scanLine;
	this->workingY = workingY;
}

void ConvolutionFilterRunner::run() {
	int size = radius * 2 + 1;

	int w = image->width();
	int h = image->height();

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

		QRgb *originalImage = (QRgb*) image->scanLine(y + offsetY);
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

	return qRgb(r, g, b);
}

