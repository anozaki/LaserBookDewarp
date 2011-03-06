/*
 * ConvolutionFilter.cpp
 *
 *  Created on: Feb 13, 2011
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
 */

#include <QList>
#include <QImage>
#include <QThreadPool>

#include <math.h>

#include "ConvolutionFilter.h"
#include "ConvolutionFilterRunner.h"

ConvolutionFilter::ConvolutionFilter(QImage image) {
	this->image = image;
	this->processed = QImage(this->image);
}

ConvolutionFilter::~ConvolutionFilter() {
}

void ConvolutionFilter::setImage(QImage image) {
	this->image = image;
	this->processed = QImage(this->image);
}

void ConvolutionFilter::process(const QList<float> &matrix, int radius) {

	QThreadPool threadPool;
	threadPool.setMaxThreadCount(16);
	int height = image.height();

	for (int y = 0; y < height; y++) {
		ConvolutionFilterRunner *runner = new ConvolutionFilterRunner(&image);
		runner->setMatrix(matrix, radius);
		runner->setScanLine((QRgb *) processed.scanLine(y), y);
		runner->setAutoDelete(true);

		threadPool.start(runner);
	}

	printf("waiting for convolution filter...");
	threadPool.waitForDone();
}

QImage ConvolutionFilter::getImage() {
	return this->processed;
}

