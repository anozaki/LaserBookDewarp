/*
 * EdgeDetection.cpp
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

#include <QList>
#include <QImage>
#include <QThreadPool>

#include "EdgeDetection.h"
#include "LaserDetectionRunner.h"
#include "LaserDetectionHSVRunner.h"

EdgeDetection::EdgeDetection(QImage original) {
	this->original = original;
	image = QImage(original.width(), original.height(), QImage::Format_RGB32);
}

EdgeDetection::~EdgeDetection() {

}

void EdgeDetection::process() {

	QThreadPool threadPool;
	threadPool.setMaxThreadCount(16);
	int height = image.height();

	for (int y = 0; y < height; y++) {
		LaserDetectionRunner *runner = new LaserDetectionRunner(&original);
//		LaserDetectionHSVRunner *runner = new LaserDetectionHSVRunner(original);
		runner->setScanLine((QRgb*)image.scanLine(y),y);
		runner->setAutoDelete(true);

		threadPool.start(runner);
	}

	threadPool.waitForDone();
}

void EdgeDetection::scanLineComplete(QVector2D pointA, bool pointAAvailable, QVector2D pointB, bool pointBAvailable, int workingY) {
}

QImage EdgeDetection::getImage() {
	return image;
}
