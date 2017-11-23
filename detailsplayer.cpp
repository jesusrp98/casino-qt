#include "detailsplayer.h"
#include "ui_detailsplayer.h"

detailsPlayer::detailsPlayer(Jugador *player, QWidget *parent) : QDialog(parent), ui(new Ui::detailsPlayer){
    std::list<Apuesta> betList = player->getApuestas();

    ui->setupUi(this);

    //fill the labels with the player's info
    ui->dniLabel->setText("DNI: " + QString::fromUtf8(player->getDNI().c_str()));
    ui->fullNameLabel->setText("FULL NAME: " + QString::fromUtf8(player->getApellidosyNombre().c_str()));
    ui->codeLabel->setText("CODE: " + QString::fromUtf8(player->getCodigo().c_str()));
    if(hasAddress(player))
        ui->homeLabel->setText("ADDRESS: " + QString::fromUtf8(player->getDireccion().c_str()) +
                           ". (" + QString::fromUtf8(player->getLocalidad().c_str()) + ", " + QString::fromUtf8(player->getProvincia().c_str()) + "). " + QString::fromUtf8(player->getPais().c_str()));
    else
        ui->homeLabel->setText("NO ADDRESS FOUND");
    ui->moneyLabel->setText("REMAINING MONEY: " + QString::number(player->getDinero()) + "€");

    fillBetList(&betList);
}

detailsPlayer::~detailsPlayer(){
    delete ui;
}

void detailsPlayer::fillBetList(std::list<Apuesta> *betList){
    ui->betNumber->setText("Listed " + QString::number(betList->size()) + " bets down below.");
    for(std::list<Apuesta>::iterator it = betList->begin(); it != betList->end(); ++it)
        ui->betOutput->addItem(getBetString(*it));
}

QString detailsPlayer::getBetString(Apuesta apuesta){
    return(QString::number(apuesta.tipo) + ", " + QString::fromUtf8(apuesta.valor.c_str()) + ", " + QString::number(apuesta.cantidad));
}

bool detailsPlayer::hasAddress(Jugador *player){
    return(player->getDireccion() != "" || player->getLocalidad() != "" || player->getProvincia() != "" || player->getPais() != "");
}
