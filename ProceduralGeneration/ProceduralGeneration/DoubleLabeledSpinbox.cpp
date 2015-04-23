//#include "DoubleLabeledSpinbox.h"
//
//DoubleLabeledSpinbox::DoubleLabeledSpinbox(const char* labelText, bool textOnLeft, int minRange, int maxRange, double value)
//{
//	QLayout* layout = textOnLeft ? (QLayout*) new QHBoxLayout : new QVBoxLayout;
//	setLayout(layout);
//
//	layout->addWidget(label = new QLabel);
//	label->setText(labelText);
//	label->setMinimumWidth(35);
//	label->setAlignment(Qt::AlignCenter);
//
//	layout->addWidget(spinbox = new QSpinBox);
//	spinbox->setValue(value);
//	min = minRange;
//	max = maxRange;
//	spinbox->setRange(minRange, maxRange);
//	connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(spinboxValueChanged()));
//	spinboxValueChanged();
//}
//
//void DoubleLabeledSpinbox::setSpinboxValue(double newValue)
//{
//	spinbox->setValue(newValue);
//}
//
//double DoubleLabeledSpinbox::getSpinboxValue()
//{
//	return spinbox->value();
//}
//
//void DoubleLabeledSpinbox::setSpinboxRange(int min, int max)
//{
//	this->min = min;
//	this->max = max;
//	spinbox->setRange(min, max);
//}
//
//void DoubleLabeledSpinbox::setMinRange(int min)
//{
//	this->min = min;
//	spinbox->setMinimum(min);
//}
//
//void DoubleLabeledSpinbox::setMaxRange(int max)
//{
//	this->max = max;
//	spinbox->setMaximum( max);
//}
//
//int DoubleLabeledSpinbox::getMinRange()
//{
//	return min;
//}
//
//int DoubleLabeledSpinbox::getMaxRange()
//{
//	return max;
//}
//
//void DoubleLabeledSpinbox::spinboxValueChanged()
//{
//	emit valueChanged();
//}