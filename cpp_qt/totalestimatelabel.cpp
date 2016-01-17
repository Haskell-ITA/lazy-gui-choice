#include "totalestimatelabel.h"

TotalEstimateLabel::TotalEstimateLabel(QWidget *parent) : QLabel(parent)
{

}

void TotalEstimateLabel::setTotalEstimate(int value)
{

    int h;
    int m;

    if (value == 0) {
        h = 0;
        m = 0;
    } else {
        h = value / 60;
        m = value % 60;
    }

    setText(QString("%1h:%2m").arg(h).arg(m));
}
