#include "addplayerdialog.h"
#include "ui_addplayerdialog.h"

#include <QMessageBox>

addPlayerDialog::addPlayerDialog(QWidget *parent) : QDialog(parent), ui(new Ui::addPlayerDialog){
    ui->setupUi(this);
}

addPlayerDialog::~addPlayerDialog(){
    delete ui;
}

void addPlayerDialog::on_buttonBox_accepted(){
    on_addBet_clicked();
    if(hasObligatoryInfo()){
        player_.setDNI(ui->dniBox->text().toUtf8().constData());
        player_.setCodigo(ui->codeBox->text().toUtf8().constData());
        player_.setNombre(ui->nameBox->text().toUtf8().constData());
        player_.setApellidos(ui->surnameBox->text().toUtf8().constData());
        player_.setDireccion(ui->addressBox->text().toUtf8().constData());
        player_.setLocalidad(ui->cityBox->text().toUtf8().constData());
        player_.setProvincia(ui->stateBox->text().toUtf8().constData());
        player_.setPais(ui->countryBox->text().toUtf8().constData());        
    }else{
        QMessageBox::critical(0, "Error", "You must enter the obligatory information and bets of the new player.");
    }
}

bool addPlayerDialog::hasObligatoryInfo(){
    return (ui->dniBox->text() != "" && ui->nameBox->text() != "" && ui->surnameBox->text() != "" && ui->codeBox->text() != "" && !player_.getApuestas().empty());
}

void addPlayerDialog::on_addBet_clicked(){
    Apuesta aux;

    if(!isBetEmpty()){
        aux.tipo = ui->typeBetBox->text().toInt();
        aux.valor = ui->valueBetBox->text().toUtf8().constData();
        aux.cantidad = ui->cuantBetBox->text().toInt();
        player_.addApuesta(aux);

        ui->typeBetBox->clear();
        ui->valueBetBox->clear();
        ui->cuantBetBox->clear();
    }
}

bool addPlayerDialog::isBetEmpty(){
    return (ui->typeBetBox->text() == "" || ui->valueBetBox->text() == "" || ui->cuantBetBox->text() == "");
}
