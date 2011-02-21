######################################################################
# Automatically generated by qmake (2.01a) Sat Feb 12 18:57:06 2011
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += ./include

FORMS += ui/MainWindow.ui

HEADERS += include/MainWindow.h \
	include/ConvolutionFilter.h \
	include/ConvolutionFilterRunner.h \
	include/EdgeDetection.h \
	include/SobelEdgeDetectionRunner.h \
	include/LaserDetectionRunner.h \
	include/LaserDetectionHSVRunner.h \
	include/ScanLineData.h \
	include/HeightTable.h 

# Input
SOURCES += src/BookScanner.cpp \
	src/MainWindow.cpp \
	src/ConvolutionFilter.cpp \
	src/ConvolutionFilterRunner.cpp \
	src/EdgeDetection.cpp \
	src/SobelEdgeDetectionRunner.cpp \
	src/LaserDetectionRunner.cpp \
	src/LaserDetectionHSVRunner.cpp \
	src/ScanLineData.cpp \
	src/HeightTable.cpp
