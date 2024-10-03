#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{

    char m_owner = (ui->checkBox_owner_read->isChecked() << 2)
            | (ui->checkBox_owner_write->isChecked() << 1)
            | ui->checkBox_owner_execute->isChecked();

    char m_group = (ui->checkBox_group_read->isChecked() << 2)
            | (ui->checkBox_group_write->isChecked() << 1)
            | ui->checkBox_group_execute->isChecked();

    char m_other = (ui->checkBox_other_read->isChecked() << 2)
            | (ui->checkBox_other_write->isChecked() << 1)
            | ui->checkBox_other_execute->isChecked();

    ui->lineEdit_octal->setText(QString::number(m_owner) + QString::number(m_group) + QString::number(m_other));



    char permisos_owner[3] = {'-','-','-'};
    if (m_owner & 0x04) permisos_owner[0] = 'r';
    if (m_owner & 0x02) permisos_owner[1] = 'w';
    if (m_owner & 0x01) permisos_owner[2] = 'x';

    char permisos_group[3] = {'-','-','-'};
    if (m_group & 0x04) permisos_group[0] = 'r';
    if (m_group & 0x02) permisos_group[1] = 'w';
    if (m_group & 0x01) permisos_group[2] = 'x';

    char permisos_other[3] = {'-','-','-'};
    if (m_other & 0x04) permisos_other[0] = 'r';
    if (m_other & 0x02) permisos_other[1] = 'w';
    if (m_other & 0x01) permisos_other[2] = 'x';

    char permisos_totales[] = "---------";
    memcpy(&permisos_totales[0], permisos_owner, sizeof(permisos_owner));
    memcpy(&permisos_totales[3], permisos_group, sizeof(permisos_group));
    memcpy(&permisos_totales[6], permisos_other, sizeof(permisos_other));

    ui->label_permisos->setText(QString(permisos_totales));

}
