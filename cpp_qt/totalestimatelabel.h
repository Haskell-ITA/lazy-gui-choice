#ifndef TOTALESTIMATELABEL_H
#define TOTALESTIMATELABEL_H

#include <QLabel>

/**
 * @brief The TotalEstimateLabel class show the hours and minutes of effort/estimate.
 */
class TotalEstimateLabel : public QLabel
{
    Q_OBJECT
public:
    explicit TotalEstimateLabel(QWidget *parent = 0);

public slots:

    void setTotalEstimate(int value);
};

#endif // TOTALESTIMATELABEL_H
