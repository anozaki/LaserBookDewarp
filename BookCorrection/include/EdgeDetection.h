/*
 * EdgeDetection.h
 *
 *  Created on: Feb 17, 2011
 *      Author: anozaki
 */

#ifndef EDGEDETECTION_H_
#define EDGEDETECTION_H_

#include <QImage>

class EdgeDetection {
public:
	EdgeDetection(QImage original);
	virtual ~EdgeDetection();

	void process();

	QImage getImage();
private:
	QImage original;
	QImage image;
};

#endif /* EDGEDETECTION_H_ */
