#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onCheckboxStateChange();
    void slotCheckAll();
    void slotCheckNone();
    void fromOctalToMatrix();

private:
    Ui::Widget *ui;
    void calcular_permisos();
};

#endif // WIDGET_H
