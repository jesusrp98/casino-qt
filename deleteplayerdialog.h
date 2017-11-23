#ifndef DELETEPLAYERDIALOG_H
#define DELETEPLAYERDIALOG_H

#include <QDialog>

namespace Ui {
    class deletePlayerDialog;
}

class deletePlayerDialog : public QDialog{
    Q_OBJECT

public:
    explicit deletePlayerDialog(QString dni, QWidget *parent = 0);
    ~deletePlayerDialog();

private:
    Ui::deletePlayerDialog *ui;
};

#endif
