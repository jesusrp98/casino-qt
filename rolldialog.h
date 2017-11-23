#ifndef ROLLDIALOG_H
#define ROLLDIALOG_H

#include "ruleta.h"

#include <QDialog>

namespace Ui {
    class RollDialog;
}

class RollDialog : public QDialog{
    Q_OBJECT

public:
    explicit RollDialog(Ruleta *r, QWidget *parent = 0);
    ~RollDialog();

private:
    Ui::RollDialog *ui;
    void getOldStuff(Ruleta *r, int *oldDinero, int &oldBanca);
    void updateLabels(Ruleta *r, int oldBanca);
    QString getPlayerString(Jugador player, int oldMoney);
};

#endif
