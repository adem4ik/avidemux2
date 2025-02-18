#ifndef T_TIMESTAMP_H
#define T_TIMESTAMP_H

#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#if QT_VERSION < QT_VERSION_CHECK(5,1,0)
    #include <QRegExpValidator>
#else
    #include <QRegularExpressionValidator>
#endif
#include <QKeyEvent>

#include "DIA_factory.h"
#include "ADM_dialogFactoryQt4.h"

/**
 *      \class fixedNumDigitsSpinBox
 *      \brief Custom spinbox with leading zeros
 */
class fixedNumDigitsSpinBox : public QSpinBox
{
public:
    int numDigits;
    fixedNumDigitsSpinBox(QWidget *parent) : QSpinBox(parent)
    {
        numDigits=2;
    }

    virtual QString textFromValue(int value) const
    {
        return QString("%1").arg(value, numDigits, 10, QChar('0'));
    }
};

/**
 *      \struct myTimeWidget
 */
typedef struct
{
    fixedNumDigitsSpinBox *hours;
    fixedNumDigitsSpinBox *minutes;
    fixedNumDigitsSpinBox *seconds;
    fixedNumDigitsSpinBox *mseconds;
}myTimeWidget;

namespace ADM_Qt4Factory
{
/**
    \class ADM_QTimeStamp
*/
class ADM_QTimeStamp : public QWidget
{
    Q_OBJECT

protected :
    uint32_t        _min;
    uint32_t        _max;
    myTimeWidget    *myTWidget;
#if QT_VERSION < QT_VERSION_CHECK(5,1,0)
    QRegExpValidator
#else
    QRegularExpressionValidator
#endif
                    *timeValidator;

    void            setSelectionAndBuddy(QLabel *label);
    void            setTime(uint32_t millisec);
    void            blockChanges(bool block);

public:
                    ADM_QTimeStamp(QString title, QWidget *dialog, QGridLayout *grid, uint32_t min, uint32_t max, uint32_t time, uint32_t line);
    uint32_t        getTime(void);

public slots:
    void            updateRange(int i);

private:
    bool            eventFilter(QObject* watched, QEvent* event);
};
} // end of namespace
#endif
