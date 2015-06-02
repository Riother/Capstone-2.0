#include "LabeledCheckBox.h"

LabeledCheckBox::LabeledCheckBox(const char * labelText, bool textOnLeft, bool isChecked)
{
	QLayout* layout = textOnLeft ? (QLayout*) new QHBoxLayout : new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(label = new QLabel);
	label->setText(labelText);
	label->setMinimumWidth(35);
	label->setAlignment(Qt::AlignCenter);

	layout->addWidget(checkbox = new QCheckBox);
	checkbox->setChecked(isChecked);

	connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(checkedUnchecked()));
	stateChanged();
}

void LabeledCheckBox::checkedUnchecked()
{
	emit stateChanged();
}

bool LabeledCheckBox::getState()
{
	return checkbox->isChecked();
}