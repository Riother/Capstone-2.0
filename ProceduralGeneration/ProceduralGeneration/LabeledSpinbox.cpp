#include "LabeledSpinbox.h"

LabeledSpinbox::LabeledSpinbox(const char* labelText, bool textOnLeft, int minRange, int maxRange, int value)
{
	QLayout* layout = textOnLeft ? (QLayout*) new QHBoxLayout : new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(label = new QLabel);
	label->setText(labelText);
	label->setMinimumWidth(35);
	label->setAlignment(Qt::AlignCenter);

	layout->addWidget(spinbox = new QSpinBox);
	spinbox->setValue(value);
	min = minRange;
	max = maxRange;
	spinbox->setRange(minRange, maxRange);
	connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(spinboxValueChanged()));
	spinboxValueChanged();
}

void LabeledSpinbox::setSpinboxValue(int newValue)
{
	spinbox->setValue(newValue);
}

int LabeledSpinbox::getSpinboxValue()
{
	return spinbox->value();
}

void LabeledSpinbox::setSpinboxRange(int min, int max)
{
	this->min = min;
	this->max = max;
	spinbox->setRange(min, max);
}

void LabeledSpinbox::setMinRange(int min)
{
	this->min = min;
	spinbox->setMinimum(min);
}

void LabeledSpinbox::setMaxRange(int max)
{
	this->max = max;
	spinbox->setMaximum( max);
}

int LabeledSpinbox::getMinRange()
{
	return min;
}

int LabeledSpinbox::getMaxRange()
{
	return max;
}

void LabeledSpinbox::spinboxValueChanged()
{
	emit valueChanged();
}