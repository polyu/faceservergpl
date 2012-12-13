/** @file */


#include <QtGui>
#include "opencv2/opencv.hpp"
#ifndef _INCL_QTUTILS
#define _INCL_QTUTILS
/**
* Convert IplImage to QImage
*@param input Input Image
*@result Output QImage
*/
QImage *QImageIplImageCvt(IplImage *input);
#endif
