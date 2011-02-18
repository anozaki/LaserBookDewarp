/*
 * MainWindow.cpp
 *
 *  Created on: Feb 12, 2011
 *      Author: anozaki
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

	for(QList<float>::iterator i = result.begin(); i != result.end(); ++i) {
		*i /= sum;
	}

	return result;
}


MainWindow::MainWindow(QMainWindow *parent) :
	QMainWindow(parent) {
	ui.setupUi(this);

	connect(ui.actionOpen, SIGNAL(triggered()), SLOT(openImage()));
}

void MainWindow::openImage() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), NULL, tr("Image (*.jpg *.jpeg *.png *.tif)"));

	QImage image(fileName);
	QTransform myTransform;
	myTransform.rotate(90);
	QImage rotated = image.transformed(myTransform);

	ConvolutionFilter filter(rotated);
	QList<float> gMatrix = gaussianBlurKernel(3, 1);
	filter.process(gMatrix, 3);

	EdgeDetection edgeDetection(filter.getImage());
	edgeDetection.process();

	ui.processedImage->setPixmap(QPixmap::fromImage(edgeDetection.getImage()));

}

