#ifndef LABELED_SPINBOX_H
#define LABELED_SPINBOX_H
#include <Qt\qlabel.h>
#include <Qt\qspinbox.h>
#include <QtGui\qvboxlayout>

class LabeledSpinbox : public QWidget
{
	Q_OBJECT
	QLabel* label;
	QSpinBox* spinbox;
	int max, min;
	private slots:
		void spinboxValueChanged();
signals:
	void valueChanged();
public:
	LabeledSpinbox(const char* labelText, bool textOnLeft, int minRange, int maxRange, int value = 0);
	void setSpinboxValue(int newValue);
	int getSpinboxValue();
	void setSpinboxRange(int min, int max);
	void setMinRange(int min);
	void setMaxRange(int max);
	int getMinRange();
	int getMaxRange();
};

#endif