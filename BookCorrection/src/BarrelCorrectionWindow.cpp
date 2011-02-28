/*
 * BarrelCorrectionWindow.cpp
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

#include "BarrelImageView.h"
#include "BarrelCorrectionWindow.h"

#include <QImage>
#include <QObject>
#include <QFileDialog>
#include <QSizePolicy>

BarrelCorrectionWindow::BarrelCorrectionWindow(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	connect(ui.k1Slider, SIGNAL(sliderMoved(int)), SLOT(k1SliderMoved(int)));
	connect(ui.k2Slider, SIGNAL(sliderMoved(int)), SLOT(k2SliderMoved(int)));
	connect(ui.k3Slider, SIGNAL(sliderMoved(int)), SLOT(k3SliderMoved(int)));

	connect(ui.k1Spinner, SIGNAL(valueChanged(double)), SLOT(k1ValueChanged(double)));
	connect(ui.k2Spinner, SIGNAL(valueChanged(double)), SLOT(k2ValueChanged(double)));
	connect(ui.k3Spinner, SIGNAL(valueChanged(double)), SLOT(k3ValueChanged(double)));

	connect(ui.scaleSlider, SIGNAL(sliderMoved(int)), SLOT(scaleSlider(int)));

	connect(ui.openImageButton, SIGNAL(clicked()), SLOT(onOpenImage()));
	connect(ui.testButton, SIGNAL(clicked()), SLOT(onTestClicked()));

//	ui.scrollArea->setWidget(&imageArea);
	setBarrelSetting();

	ui.gridLayout->addWidget(&imageArea);
	imageArea.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	ui.gridLayout->addWidget(&imageArea2);
	imageArea2.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

BarrelCorrectionWindow::~BarrelCorrectionWindow() {
}

void BarrelCorrectionWindow::onOpenImage() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"),
			NULL, tr("Image (*.jpg *.jpeg *.png *.tif)"));

	if (fileName.isEmpty()) {
		return;
	}

	this->image = QImage(fileName);

	imageArea.setPixmap(QPixmap::fromImage(image));
}

void BarrelCorrectionWindow::onTestClicked() {
	correction.createTranslation(image, ui.k1Spinner->value(), ui.k2Spinner->value(), ui.k3Spinner->value(), ui.scaleSlider->value());

	if(ui.nnRadioButton->isChecked()) {
		correction.fixImage(image, BarrelCorrection::NearestNeighbor);
	} else if (ui.bilinearRadioButton->isChecked()) {
		correction.fixImage(image, BarrelCorrection::Bilinear);
	} else if (ui.cubicRadioButton->isChecked()) {
		correction.fixImage(image, BarrelCorrection::Bicubic);
	}

	imageArea2.setValue(0,0,0, 1000);
	imageArea2.setPixmap(QPixmap::fromImage(correction.getImage()));
}

void BarrelCorrectionWindow::k1SliderMoved(int position) {
	ui.k1Spinner->blockSignals(true);
	ui.k1Spinner->setValue(ui.k1Spinner->maximum() * (position / 100.0f));
	ui.k1Spinner->blockSignals(false);

	setBarrelSetting();
}

void BarrelCorrectionWindow::k2SliderMoved(int position) {
	ui.k2Spinner->blockSignals(true);
	ui.k2Spinner->setValue(ui.k2Spinner->maximum() * (position / 100.0f));
	ui.k2Spinner->blockSignals(false);

	setBarrelSetting();
}

void BarrelCorrectionWindow::k3SliderMoved(int position) {
	ui.k3Spinner->blockSignals(true);
	ui.k3Spinner->setValue(ui.k3Spinner->maximum() * (position / 100.0f));
	ui.k3Spinner->blockSignals(false);

	setBarrelSetting();
}

void BarrelCorrectionWindow::scaleSlider(int) {
	setBarrelSetting();
}

void BarrelCorrectionWindow::k1ValueChanged(double value) {
	ui.k1Slider->blockSignals(true);
	ui.k1Slider->setValue(value / ui.k1Spinner->maximum() * 100);
	ui.k1Slider->blockSignals(false);

	setBarrelSetting();
}

void BarrelCorrectionWindow::k2ValueChanged(double value) {
	ui.k2Slider->blockSignals(true);
	ui.k2Slider->setValue(value / ui.k2Spinner->maximum() * 100);
	ui.k2Slider->blockSignals(false);

	setBarrelSetting();
}

void BarrelCorrectionWindow::k3ValueChanged(double value) {
	ui.k3Slider->blockSignals(true);
	ui.k3Slider->setValue(value / ui.k3Spinner->maximum() * 100);
	ui.k3Slider->blockSignals(false);

	setBarrelSetting();
}

void BarrelCorrectionWindow::setBarrelSetting() {
	imageArea.setValue(ui.k1Spinner->value(), ui.k2Spinner->value(), ui.k3Spinner->value(), ui.scaleSlider->value());
}
