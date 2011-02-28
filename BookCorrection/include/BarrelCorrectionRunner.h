/*
 * BarrelCorrectionRunner.h
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

#ifndef BARRELCORRECTIONRUNNER_H_
#define BARRELCORRECTIONRUNNER_H_

#include <QList>
#include <QVector2D>
#include <QImage>
#include <QRunnable>

#include "BarrelCorrection.h"

class BarrelCorrectionRunner : public QRunnable {
public:
	BarrelCorrectionRunner(const QImage &image, const QList<QVector2D> &translation);
	virtual ~BarrelCorrectionRunner();

	virtual void run();

	void setScanLine(QRgb *scanLine, int workingY);

	void setMethod(BarrelCorrection::Interpolation type);

private:
	QImage image;

	QRgb *scanLine;
	int width;
	int workingY;
	QList<QVector2D> translation;

	BarrelCorrection::Interpolation interpolation;

	void findPoint(QRgb scanLine[], int x, int width, int step);

	QRgb processNNPixel(double x, double y);
	QRgb processPixel(double x, double y);
	QRgb processCubicPixel(double x, double y);
};


#endif /* BARRELCORRECTIONRUNNER_H_ */
