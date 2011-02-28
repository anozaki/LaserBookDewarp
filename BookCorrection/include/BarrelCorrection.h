/*
 * BarrelTraslationCaculator.h
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

#ifndef BARRELTRASLATIONCACULATOR_H_
#define BARRELTRASLATIONCACULATOR_H_

#include <QList>
#include <QVector2D>
#include <QImage>

class BarrelCorrection {
public:
	enum Interpolation { NearestNeighbor, Bilinear, Bicubic };

	BarrelCorrection();
	virtual ~BarrelCorrection();

	void createTranslation(const QImage &image, double k1, double k2, double k3, int scale);

	void createTranslation(int width, int height, double k1, double k2, double k3, int scale);

	void fixImage(const QImage &original, BarrelCorrection::Interpolation method);

	const QImage &getImage();

private:
	int width, height;
	QList< QList<QVector2D>* > translation;

	QImage image;
};

#endif /* BARRELTRASLATIONCACULATOR_H_ */
