/*
 * BarrelTranslationRunner.cpp
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
 *
 */

#include <math.h>

#include "BarrelTranslationRunner.h"

BarrelTranslationRunner::BarrelTranslationRunner(int width, int height, int workingY) {
	this->width = width;
	this->height = height;
	this->workingY = workingY;
}

BarrelTranslationRunner::~BarrelTranslationRunner() {
}

void BarrelTranslationRunner::setDistortionParam(double k1, double k2, double k3, int scale) {
	this->k1 = k1;
	this->k2 = k2;
	this->k3 = k3;

	this->scale = scale;
}

void BarrelTranslationRunner::setList(QList<QVector2D> *translation) {
	this->translation = translation;
}

void BarrelTranslationRunner::run() {
	double xc = width / 2;
	double yc = height / 2;

	int ySqr = (workingY - yc);
	ySqr *= ySqr;

	translation->clear();

	int yu = workingY - yc;
	for(int x = 0; x < width; x++) {
		int xu = x - xc;
		double r = sqrt(xu * xu + ySqr);

		double s = scale / (1000 + (k1 * r) + (k2 * r * r) + (k3 * r * r * r));

		float xd = xu * s;
		float yd = yu * s;

		translation->append(QVector2D(xd + xc, yd + yc));
	}

}


