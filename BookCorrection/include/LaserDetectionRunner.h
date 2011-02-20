/*
 * SobelEdgeDetectionRunner.h
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

#ifndef SOBELEDGEDETECTIONRUNNER_H_
#define SOBELEDGEDETECTIONRUNNER_H_

#include <QObject>
#include <QImage>
#include <QRunnable>

#include "ScanLineData.h"

class LaserDetectionRunner: public QObject, public QRunnable {
Q_OBJECT
public:
	LaserDetectionRunner(QImage image);
	virtual ~LaserDetectionRunner();

	virtual void run();

	void setScanLine(QRgb *scanLine, int workingY);

signals:
	void completed(ScanLineData data, int workingY);

private:
	QImage image;

	QRgb *scanLine;
	int width;
	int workingY;

	void findPoint(QRgb scanLine[], int x, int width, int step);
	QRgb processPixel(int x, int y);
};

#endif /* SOBELEDGEDETECTIONRUNNER_H_ */
