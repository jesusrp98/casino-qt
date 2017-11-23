#include "deleteplayerdialog.h"
#include "ui_deleteplayerdialog.h"

#include <QMessageBox>

deletePlayerDialog::deletePlayerDialog(QString dni, QWidget *parent) : QDialog(parent), ui(new Ui::deletePlayerDialog){
    ui->setupUi(this);
    ui->dniLabel->setText("Would you like to delete player with DNI " + dni + "?");
}

deletePlayerDialog::~deletePlayerDialog(){
    delete ui;
}
