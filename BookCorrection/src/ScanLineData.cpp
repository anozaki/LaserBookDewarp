/*
 * ScanLineData.cpp
 *
 *  Created on: Feb 19, 2011
 *      Author: anozaki
 */

#include <QVector2D>

#include "ScanLineData.h"


ScanLineData::ScanLineData() {
	pointAAvailable = false;
	pointBAvailable = false;
}

ScanLineData::~ScanLineData() {
}

void ScanLineData::setPointAAvailable(bool available) {
	pointAAvailable = available;
}

bool ScanLineData::isPointAAvailable() {
	return pointAAvailable;
}

QVector2D ScanLineData::getPointA() {
	return pointA;
}

void ScanLineData::setPointA(QVector2D pointA) {
	this->pointA = pointA;
}

void ScanLineData::setPointBAvailable(bool available) {
	pointBAvailable = available;
}

bool ScanLineData::isPointBAvailable() {
	return pointBAvailable;
}

QVector2D ScanLineData::getPointB() {
	return pointB;
}

void ScanLineData::setPointB(QVector2D pointB) {
	this->pointB = pointB;
}
