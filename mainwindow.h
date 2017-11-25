#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ruleta.h"
#include "persona.h"
#include "jugador.h"
#include "crupier.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    //window constructor
    explicit MainWindow(QWidget *parent = 0);
    //window destructor
    ~MainWindow();

private slots:
    //onClick methods
    void on_roll_clicked();
    void updateBolaInfo();
    void on_actionLoad_players_triggered();
    void on_actionSave_Players_triggered();
    void on_actionAdd_Player_triggered();
    void on_actionDelete_Player_triggered();
    void on_actionDetails_triggered();
    void on_actionExit_triggered();

    //output info methods
    void consoleOutput(QString file_path);
    void statusOutput(QString file_path, int timeout = 0);
    QString getPlayerString(Jugador &player);
    bool loadApuestas(QString path);

    void updateJugadoresList(int printConsole);    
    Jugador getPlayerByIndex(int index);

    void on_actionAbout_this_app_triggered();

private:
    Ui::MainWindow *ui;

    //ruleta elements
    QString file_path;
    Crupier c{"31025983H","cru"};
    Ruleta r{c};
};

#endif
