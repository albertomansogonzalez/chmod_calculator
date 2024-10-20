#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->checkBox_group_execute, &QCheckBox::stateChanged, this, &Widget::onCheckboxStateChange);
    connect(ui->checkBox_group_write, &QCheckBox::stateChanged, this, &Widget::onCheckboxStateChange);
    connect(ui->checkBox_group_read, &QCheckBox::stateChanged, this, &Widget::onCheckboxStateChange);

    connect(ui->checkBox_other_execute, &QCheckBox::stateChanged, this, &Widget::onCheckboxStateChange);
    connect(ui->checkBox_other_write, &QCheckBox::stateChanged, this, &Widget::onCheckboxStateChange);
    connect(ui->checkBox_other_read, &QCheckBox::stateChanged, this, &Widget::onCheckboxStateChange);

    connect(ui->checkBox_owner_execute, &QCheckBox::stateChanged, this, &Widget::onCheckboxStateChange);
    connect(ui->checkBox_owner_write, &QCheckBox::stateChanged, this, &Widget::onCheckboxStateChange);
    connect(ui->checkBox_owner_read, &QCheckBox::stateChanged, this, &Widget::onCheckboxStateChange);

    connect(ui->pushButton_all, &QPushButton::clicked, this, &Widget::slotCheckAll);
    connect(ui->pushButton_none, &QPushButton::clicked, this, &Widget::slotCheckNone);

    connect(ui->lineEdit_octal, &QLineEdit::editingFinished, this, &Widget::fromOctalToMatrix);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::onCheckboxStateChange()
{
    calcular_permisos();
}


void Widget::slotCheckAll()
{
    ui->checkBox_group_execute->setChecked(true);
    ui->checkBox_group_write->setChecked(true);
    ui->checkBox_group_read->setChecked(true);
    ui->checkBox_other_execute->setChecked(true);
    ui->checkBox_other_write->setChecked(true);
    ui->checkBox_other_read->setChecked(true);
    ui->checkBox_owner_execute->setChecked(true);
    ui->checkBox_owner_write->setChecked(true);
    ui->checkBox_owner_read->setChecked(true);

}


void Widget::slotCheckNone()
{
    ui->checkBox_group_execute->setChecked(false);
    ui->checkBox_group_write->setChecked(false);
    ui->checkBox_group_read->setChecked(false);
    ui->checkBox_other_execute->setChecked(false);
    ui->checkBox_other_write->setChecked(false);
    ui->checkBox_other_read->setChecked(false);
    ui->checkBox_owner_execute->setChecked(false);
    ui->checkBox_owner_write->setChecked(false);
    ui->checkBox_owner_read->setChecked(false);
}



void Widget::calcular_permisos()
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

void Widget::fromOctalToMatrix(){
    //pasar de octal ej 644 a los permisos binarios

    char m_owner = ui->lineEdit_octal->text().at(0).toLatin1() - '0';
    char m_group = ui->lineEdit_octal->text().at(1).toLatin1() - '0';
    char m_other = ui->lineEdit_octal->text().at(2).toLatin1() - '0';

    ui->checkBox_owner_execute->setChecked(m_owner & (1 << 0));
    ui->checkBox_owner_write->setChecked(m_owner & (1 << 1));
    ui->checkBox_owner_read->setChecked(m_owner & (1 << 2));

    ui->checkBox_other_execute->setChecked(m_other & (1 << 0));
    ui->checkBox_other_write->setChecked(m_other & (1 << 1));
    ui->checkBox_other_read->setChecked(m_other & (1 << 2));

    ui->checkBox_group_execute->setChecked(m_group & (1 << 0));
    ui->checkBox_group_write->setChecked(m_group & (1 << 1));
    ui->checkBox_group_read->setChecked(m_group & (1 << 2));

}
