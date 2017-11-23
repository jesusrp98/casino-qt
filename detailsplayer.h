#ifndef DETAILSPLAYER_H
#define DETAILSPLAYER_H

#include "jugador.h"

#include <QDialog>

namespace Ui {
    class detailsPlayer;
}

class detailsPlayer : public QDialog{
    Q_OBJECT

public:
    explicit detailsPlayer(Jugador *player, QWidget *parent = 0);
    ~detailsPlayer();
    void fillBetList(std::list<Apuesta> *betList);
    QString getBetString(Apuesta apuesta);
    bool hasAddress(Jugador *player);

private:
    Ui::detailsPlayer *ui;
};

#endif
