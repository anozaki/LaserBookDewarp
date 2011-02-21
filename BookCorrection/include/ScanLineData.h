/*
 * ScanLineData.h
 *
 *  Created on: Feb 19, 2011
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

#ifndef SCANLINEDATA_H_
#define SCANLINEDATA_H_

#include <QObject>
#include <QVector2D>

class ScanLineData{
public:
	ScanLineData();
	virtual ~ScanLineData();

	void setPointAAvailable(bool available);
	bool isPointAAvailable();

	QVector2D getPointA();
	void setPointA(QVector2D pointA);

	void setPointBAvailable(bool available);
	bool isPointBAvailable();

	QVector2D getPointB();
	void setPointB(QVector2D pointB);

private:
	QVector2D pointA;
	bool pointAAvailable;
	QVector2D pointB;
	bool pointBAvailable;
};

#endif /* SCANLINEDATA_H_ */
