#ifndef ADDPLAYERDIALOG_H
#define ADDPLAYERDIALOG_H

#include "jugador.h"

#include <QDialog>

namespace Ui {
    class addPlayerDialog;
}

class addPlayerDialog : public QDialog{
    Q_OBJECT

public:
    explicit addPlayerDialog(QWidget *parent = 0);
    ~addPlayerDialog();
    inline Jugador getPlayer() const {return player_;}
    bool hasObligatoryInfo();

private slots:
    void on_buttonBox_accepted();
    bool isBetEmpty();
    void on_addBet_clicked();

private:
    Jugador player_{"", ""};
    Ui::addPlayerDialog *ui;
};

#endif
