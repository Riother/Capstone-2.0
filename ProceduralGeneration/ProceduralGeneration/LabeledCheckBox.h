#ifndef LABELED_CHECKBOX_H
#define LABELED_CHECKBOX_H
#include <Qt\qlabel.h>
#include <Qt\qcheckbox.h>
#include <QtGui\qvboxlayout>

class LabeledCheckBox : public QWidget
{
	Q_OBJECT
	QLabel* label;
	QCheckBox* checkbox;
	private slots:
		void checkedUnchecked();
signals:
	void stateChanged();
public:
	LabeledCheckBox(const char* labelText, bool textOnLeft, bool isChecked);
	
	bool getState();
};

#endif