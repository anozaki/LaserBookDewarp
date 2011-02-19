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
 */

#include <math.h>

#include "SobelEdgeDetectionRunner.h"

float gX[] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
float gY[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

SobelEdgeDetectionRunner::SobelEdgeDetectionRunner(QImage image) {
	this->image = image;
}

SobelEdgeDetectionRunner::~SobelEdgeDetectionRunner() {
}

void SobelEdgeDetectionRunner::setScanLine(QRgb *scanLine, int workingY) {
	this->scanLine = scanLine;
	this->workingY = workingY;
}

void SobelEdgeDetectionRunner::run() {
	int size = 3;

	int w = image.width();
	int h = image.height();

	for (int x = 0; x < w; x++) {
		scanLine[x] = processPixel(size, w, h, x, workingY);
	}

}

QRgb SobelEdgeDetectionRunner::processPixel(int size, int w, int h, int x,
		int y) {
	// starting pixes we are going to start working on.
	x -= 1;
	y -= 1;

	float r, g, b, r2, g2, b2;

	r = g = b = r2 = g2 = b2 = 0.0f;
	for (int offsetY = 0; offsetY < size; offsetY++) {
		if (offsetY + y >= h || offsetY + y < 0) {
			continue;
		}

		QRgb *originalImage = (QRgb*) image.scanLine(y + offsetY);
		for (int offsetX = 0; offsetX < size; offsetX++) {
			if (offsetX + x >= w || offsetX + x < 0) {
				continue;
			}

			QRgb *rgb = &originalImage[x + offsetX];

			float factor = gX[offsetX + (offsetY * size)];
			float factor2 = gY[offsetX + (offsetY * size)];

			r += qRed(*rgb) * factor;
			g += qGreen(*rgb) * factor;
			b += qBlue(*rgb) * factor;

			r2 += qRed(*rgb) * factor2;
			g2 += qGreen(*rgb) * factor2;
			b2 += qBlue(*rgb) * factor2;
		}

	}

	int rf = sqrt((r * r) + (r2 * r2));
	int gf = sqrt((g * g) + (g2 * g2));
	int bf = sqrt((b * b) + (b2 * b2));

	return qRgb(gf, gf, gf);
}
