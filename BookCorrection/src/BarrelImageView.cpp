/*
 * BarrelImageView.cpp
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

#include <QPaintEvent>
#include <QPainterPath>
#include <QPainter>
#include <QLabel>

#include <math.h>

#include "BarrelImageView.h"

BarrelImageView::BarrelImageView() {
	k1 = k2 = k3 = 0;
}

BarrelImageView::~BarrelImageView() {
}

void BarrelImageView::setValue(double k1, double k2, double k3, int scale) {
	this->k1 = k1;
	this->k2 = k2;
	this->k3 = k3;
	this->scale = scale;

	repaint();
}

void BarrelImageView::paintEvent(QPaintEvent *event) {
	QLabel::paintEvent(event);

	QPainter painter(this);

	painter.setPen(Qt::blue);

	if(width() < 10 && height() < 10) {
		return;
	}

	int xc = width() / 2;
	int yc = height() / 2;

	// Xd = Xu( 1 + k1*r^2 + k2*r^4)
	// Yd = Yu( 1 + k1*r^2 + k2*r^4 )

	// not optimized for speed but it works.
	for(int y = 0; y <= 20; y++) {
		int workingY = height() / 20 * y;

		int yu = workingY - yc;

		QPainterPath path;
		for(int x = 0; x < width(); x++) {
			int xu = x - xc;
			double r = sqrt((xu * xu) + (yu * yu));
			double s = scale / (1000 + (k1 * r) + (k2 * r * r) + (k3 * r * r * r)) ;
			double xd = xu * s;
			double yd = yu * s;

			if(x == 0) {
				path.moveTo(xd + xc, yd + yc);
			} else {
				path.lineTo(xd + xc, yd + yc);
			}
		}
		painter.drawPath(path);


		for(int x = 0; x <= 20; x++) {
			int workingX = width() / 20 * x ;
			int xu = workingX - xc;

			QPainterPath path;
			for(int y = 0; y < height(); y++) {
				int yu = y - yc;
				double r = sqrt((xu * xu) + (yu * yu));
				double s = scale / (1000 + (k1 * r) + (k2 * r * r) + k3 * r * r * r) ;
				double xd = xu * s;
				double yd = yu * s;

				if(y == 0) {
					path.moveTo(xd + xc, yd + yc);
				} else {
					path.lineTo(xd + xc, yd + yc);
				}

			}
			painter.drawPath(path);
		}
	}
	printf("\n");
}

