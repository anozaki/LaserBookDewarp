/*
 * ConvolutionFilterRunnable.h
 *
 *  Created on: Feb 15, 2011
 *      Author: anozaki
 */

#ifndef CONVOLUTIONFILTERRUNNABLE_H_
#define CONVOLUTIONFILTERRUNNABLE_H_

#include <QImage>
#include <QRunnable>

class ConvolutionFilterRunner : public QRunnable {
public:
	ConvolutionFilterRunner(QImage image);
	virtual ~ConvolutionFilterRunner();

	virtual void run();

	void setMatrix(QList<float> &matrix, int radius);

	void setScanLine(QRgb *scanLine, int workingY);

private:
	QImage image;

	QList<float> *matrix;
	int radius;

	QRgb *scanLine;
	int width;
	int workingX, workingY;

	QRgb processPixel(int size, int w, int h, int x, int y);
};

#endif /* CONVOLUTIONFILTERRUNNABLE_H_ */
