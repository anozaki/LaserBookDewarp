/*
 * MainWindow.cpp
 *
 *  Created on: Feb 12, 2011
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

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QImage>

#include "ConvolutionFilter.h"
#include "EdgeDetection.h"
#include "ui_MainWindow.h"
#include "MainWindow.h"
#include "HeightTable.h"

const double PI = 3.141592;
// algorithm took from wiki page
QList<float> gaussianBlurKernel(int radius, float sigma) {
	float sigmaSquare = sigma * sigma;
	float sigma2 = 2 * sigmaSquare;
	float sigmaPie = 2 * PI * sigmaSquare;

	QList<float> result;

	float sum = 0.0f;

	int width = radius * 2 + 1;
	int height = radius * 2 + 1;
	for (int h = 0; h < height; h++) {
		int fixedH = h - radius;
		int hSquare = fixedH * fixedH;
		for (int w = 0; w < width; w++) {

			int fixedW = w - radius;
			float g = expf(-((hSquare + (fixedW * fixedW)) / sigma2))
					/ sigmaPie;

			sum += g;

			result.append(g);
		}
	}

	for (QList<float>::iterator i = result.begin(); i != result.end(); ++i) {
		*i /= sum;
	}

	return result;
}

MainWindow::MainWindow(QMainWindow *parent) :
	QMainWindow(parent) {
	ui.setupUi(this);

	connect(ui.actionOpen, SIGNAL(triggered()), SLOT(openImage()));
	connect(ui.showOriginalButton, SIGNAL(clicked()), SLOT(showOriginal()));
	connect(ui.showBlurredButton, SIGNAL(clicked()), SLOT(showBlurred()));
	connect(ui.showLaserButton, SIGNAL(clicked()), SLOT(showLaser()));
}

void MainWindow::showOriginal() {
	ui.processedImage->setPixmap(QPixmap::fromImage(original));
}

void MainWindow::showBlurred() {
	ui.processedImage->setPixmap(QPixmap::fromImage(blurred));
}

void MainWindow::showLaser() {
	ui.processedImage->setPixmap(QPixmap::fromImage(laser));
}

void MainWindow::openImage() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"),
			NULL, tr("Image (*.jpg *.jpeg *.png *.tif)"));

	if (fileName.isEmpty()) {
		return;
	}

	// TODO shouldn't be doing all this in one function...
	QImage image(fileName);

	HeightTable table(image.width(), image.height());

	// find the distance we need to put the origin if our FOV is 45 degree.
	int distance = (image.width() / 2) / tan(45.0f / 2);
	printf("%d \n", distance);

	table.setOrigin(QVector3D(0, 0, -distance));

	// setting the location of the laser crossing point and its angle. (TODO did not verify the angle is calulated correctly).
	table.setBaseDistance(QVector3D(0, 0, 1000), 45);
	table.generate();

	QTransform myTransform;
	myTransform.rotate(90);
	QImage rotated = image.transformed(myTransform);

	original = rotated;

	ConvolutionFilter filter(rotated);
	QList<float> gMatrix = gaussianBlurKernel(3, 1);
	filter.process(gMatrix, 3);

	blurred = filter.getImage();

	EdgeDetection edgeDetection(filter.getImage());
	edgeDetection.process();

	laser = edgeDetection.getImage();

	showOriginal();
}

