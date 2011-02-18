/*
 * ConvolutionFilter.h
 *
 *  Created on: Feb 13, 2011
 *      Author: anozaki
 */

#ifndef CONVOLUTIONFILTER_H_
#define CONVOLUTIONFILTER_H_

#include <QImage>
#include <QList>

class ConvolutionFilter {
public:
	ConvolutionFilter(QImage image);
	virtual ~ConvolutionFilter();

	void setImage(QImage image);

	void process(QList<float> &matrix, int radius);

	QImage getImage();

private:
	QImage image;

	QImage processed;
};

#endif /* CONVOLUTIONFILTER_H_ */
