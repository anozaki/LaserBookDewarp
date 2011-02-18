/*
 * ConvolutionFilter.cpp
 *
 *  Created on: Feb 13, 2011
 *      Author: anozaki
 */

#include <QList>
#include <QImage>
#include <QThreadPool>

#include <math.h>

#include "ConvolutionFilter.h"
#include "ConvolutionFilterRunner.h"

ConvolutionFilter::ConvolutionFilter(QImage image) {
	this->image = image;
	this->processed = QImage(this->image);
}

ConvolutionFilter::~ConvolutionFilter() {
}

void ConvolutionFilter::setImage(QImage image) {
	this->image = image;
	this->processed = QImage(this->image);
}

void ConvolutionFilter::process(QList<float> &matrix, int radius) {

	QThreadPool threadPool;
	int height = image.height();

	for(int y = 0; y < height; y++) {
		ConvolutionFilterRunner *runner = new ConvolutionFilterRunner(image);
		runner->setMatrix(matrix, radius);
		runner->setScanLine((QRgb *)processed.scanLine(y), y);
		runner->setAutoDelete(true);

		threadPool.start(runner);
	}

	while(threadPool.activeThreadCount() > 0) {
		sleep(1);
	}

//	int width = radius * 2 + 1;
//	int height = radius * 2 + 1;
//
//	int imageWidth = image->width();
//	int imageHeight = image->height();
//
//	int offsetY, offsetX, workingX, workingY;
//	float r = 0.0f, g = 0.0f, b = 0.0f;
//	float matrixData;
//	QRgb rgb;
//
//	for (int x = 0; x < processed->width(); x++) {
//		for (int y = 0; y < processed->height(); y++) {
//			// let get the radius block...
//			workingX = x - radius;
//			workingY = y - radius;
//
//			r = g = b = 0.0f;
//			for (offsetY = 0; offsetY < height; offsetY++) {
//				if (offsetY + workingY >= imageHeight || offsetY + workingY < 0) {
//					continue;
//				}
//
//				for (offsetX = 0; offsetX < width; offsetX++) {
//					if (offsetX + workingX >= imageWidth || offsetX + workingX
//							< 0) {
//						continue;
//					}
//
//					rgb = image->pixel(workingX + offsetX, workingY
//							+ offsetY);
//
//					matrixData = matrix[offsetX + (offsetY * width)];
//
//					r += qRed(rgb) * matrixData;
//					g += qGreen(rgb) * matrixData;
//					b += qBlue(rgb) * matrixData;
//				}
//			}
//
//			if (r > 256) {
//				r = 256;
//			} else if (r < 0) {
//				r = 0;
//			}
//
//			if (g > 256) {
//				g = 256;
//			} else if (g < 0) {
//				g = 0;
//			}
//
//			if (b > 256) {
//				b = 256;
//			} else if (b < 0) {
//				b = 0;
//			}
//
//			processed->setPixel(x, y, qRgb(r, g, b));
//		}
//	}
}

QImage ConvolutionFilter::getImage() {
	return this->processed;
}

