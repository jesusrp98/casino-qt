#include "rolldialog.h"
#include "ui_rolldialog.h"

RollDialog::RollDialog(Ruleta *r, QWidget *parent) : QDialog(parent), ui(new Ui::RollDialog){
    ui->setupUi(this);

    int oldBanca, i = 0;
    int oldList[r->getJugadores().size()];

    //colects the info before roll the ruleta
    getOldStuff(r, oldList, oldBanca);

    //now, it is time to rock 'n roll
    r->giraRuleta();
    r->getPremios(false);
    updateLabels(r, oldBanca);

    //fill the list with results
    std::list<Jugador> list = r->getJugadores();
    for(std::list<Jugador>::iterator it = list.begin(); it != list.end(); ++it, ++i)
        ui->betOutput->addItem(getPlayerString(*it, oldList[i]));
}

RollDialog::~RollDialog(){
    delete ui;
}

void RollDialog::getOldStuff(Ruleta *r, int *oldDinero, int &oldBanca){
    std::list<Jugador> aux = r->getJugadores();
    int i = 0;

    oldBanca = r->getBanca();
    for(std::list<Jugador>::iterator it = aux.begin(); i != (signed) aux.size(); ++it, i++)
        oldDinero[i] = it->getDinero();
}

void RollDialog::updateLabels(Ruleta *r, int oldBanca){
    ui->ballLabel->setText("The result is a " + QString::number(r->getBola()) + "!");
    ui->nextLabel->setText("Here is the list with the result from the " + QString::number(r->getJugadores().size()) + " players:");
    ui->bankMoney->setText("Bank Money: " + QString::number(oldBanca) + "€ + " + QString::number(r->getBanca() - oldBanca) + "€ = " + QString::number(r->getBanca()) + "€");
}

QString RollDialog::getPlayerString(Jugador player, int oldMoney){
    return("Player " + QString::fromUtf8(player.getDNI().c_str()) + ": " + QString::number(oldMoney) + "€ + " + QString::number(player.getDinero() - oldMoney) + "€ = " + QString::number(player.getDinero()) + "€");
}
