/*
 * BarrelTranslationRunner.h
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

#ifndef BARRELTRANSLATIONRUNNER_H_
#define BARRELTRANSLATIONRUNNER_H_

#include <QList>
#include <QVector2D>
#include <QRunnable>

class BarrelTranslationRunner : public QRunnable {
public:
	BarrelTranslationRunner(int width, int height, int workingY);
	virtual ~BarrelTranslationRunner();

	void setDistortionParam(double k1, double k2, double k3, int scale);

	virtual void run();

	void setList(QList<QVector2D> *translation);
private:
	int width, height;
	int workingY;
	int scale;

	double k1, k2, k3;

	QList<QVector2D> *translation;

};

#endif /* BARRELTRANSLATIONRUNNER_H_ */
