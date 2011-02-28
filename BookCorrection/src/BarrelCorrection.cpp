/*
 * BarrelTraslationCaculator.cpp
 *
 *  Created on: Feb 26, 2011
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

#include "BarrelCorrection.h"
#include "BarrelTranslationRunner.h"
#include "BarrelCorrectionRunner.h"

#include <QImage>
#include <QThreadPool>

BarrelCorrection::BarrelCorrection() {
}

BarrelCorrection::~BarrelCorrection() {
	// TODO Auto-generated destructor stub
}

void BarrelCorrection::createTranslation(const QImage &image, double k1, double k2, double k3, int scale) {
	createTranslation(image.width(), image.height(), k1, k2, k3, scale);
}

void BarrelCorrection::createTranslation(int width, int height, double k1, double k2, double k3, int scale) {
	QThreadPool threadPool;

	for(QList< QList<QVector2D>* >::iterator i = translation.begin(); i != translation.end(); ++i) {
		delete *i;
	}
	translation.clear();


	for(int y = 0; y < height; y++) {
		QList<QVector2D> *list = new QList<QVector2D>;

		BarrelTranslationRunner *runner = new BarrelTranslationRunner(width, height, y);
		runner->setList(list);
		runner->setDistortionParam(k1, k2, k3, scale);
		runner->setAutoDelete(true);

		threadPool.start(runner);

		translation.append(list);
	}

	threadPool.waitForDone();
}

void BarrelCorrection::fixImage(const QImage &original, BarrelCorrection::Interpolation method) {

	image = QImage(original.width(), original.height(), QImage::Format_RGB32);
	QThreadPool pool;

	for(int y = 0; y < image.height(); y++) {
		BarrelCorrectionRunner *runner = new BarrelCorrectionRunner(original, *translation[y]);
		runner->setScanLine((QRgb*)image.scanLine(y),y);
		runner->setAutoDelete(true);
		runner->setMethod(method);

		pool.start(runner);
	}

	pool.waitForDone();
}

const QImage &BarrelCorrection::getImage() {
	return image;
}
