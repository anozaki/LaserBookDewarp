/*
 * EdgeDetection.cpp
 *
 *  Created on: Feb 17, 2011
 *      Author: anozaki
 */

#include <QList>
#include <QImage>
#include <QThreadPool>

#include "EdgeDetection.h"
#include "LaserDetectionRunner.h"

EdgeDetection::EdgeDetection(QImage original) {
	this->original = original;
	image = QImage(original.width(), original.height(), QImage::Format_RGB32);
}

EdgeDetection::~EdgeDetection() {

}

void EdgeDetection::process() {

	QThreadPool threadPool;
	int height = image.height();

	for (int y = 0; y < height; y++) {
		LaserDetectionRunner *runner = new LaserDetectionRunner(original);
		runner->setScanLine((QRgb*)image.scanLine(y),y);
		runner->setAutoDelete(true);
		threadPool.start(runner);
	}

	while(threadPool.activeThreadCount() > 0) {
		sleep(1);
	}

}

QImage EdgeDetection::getImage() {
	return image;
}
