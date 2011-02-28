/*
 * BarrelCorrectionWindow.h
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

#ifndef BARRELCORRECTIONWINDOW_H_
#define BARRELCORRECTIONWINDOW_H_

#include <QObject>
#include <QWidget>
#include <QPainter>

#include "BarrelCorrection.h"
#include "BarrelImageView.h"

#include "ui_BarrelCorrectionWindow.h"

class BarrelCorrectionWindow : public QWidget {
	Q_OBJECT
public:
	BarrelCorrectionWindow(QWidget *parent = 0);
	virtual ~BarrelCorrectionWindow();

protected:

private slots:
	void k1SliderMoved(int);
	void k2SliderMoved(int);
	void k3SliderMoved(int);

	void scaleSlider(int);

	void k1ValueChanged(double);
	void k2ValueChanged(double);
	void k3ValueChanged(double);

	void onOpenImage();
	void onTestClicked();

private:
	Ui::BarrelCorrectionWindow ui;

	QImage image;
	QPainter painter;

	BarrelImageView imageArea;
	BarrelImageView imageArea2;

	BarrelCorrection correction;

	void setBarrelSetting();

};

#endif /* BARRELCORRECTIONWINDOW_H_ */
