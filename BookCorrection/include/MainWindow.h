/*
 * MainWindow.h
 *
 *  Created on: Feb 12, 2011
 *      Author: anozaki
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QObject>
#include <QMainWindow>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QMainWindow *parent = 0);

private slots:
	void openImage();

private:
	Ui::MainWindow ui;
};

#endif /* MAINWINDOW_H_ */
