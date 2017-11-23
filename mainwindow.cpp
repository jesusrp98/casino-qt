#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addplayerdialog.h"
#include "deleteplayerdialog.h"
#include "detailsplayer.h"
#include "rolldialog.h"

#include <QFileDialog>
#include <QDateTime>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    ui->crupierInfo->setText("CRUPIER: " + QString::fromUtf8(r.getCrupier().getDNI().c_str()) + " (" + QString::fromUtf8(r.getCrupier().getCodigo().c_str()) + ")");
    statusOutput("No file loaded. Load a file to start");
    consoleOutput("Welcome to Casino Royale!");

    updateBolaInfo();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_roll_clicked(){
    if(!r.getJugadores().empty()){
        RollDialog dialog(&r);
        dialog.exec();
        updateBolaInfo();
        updateJugadoresList(0);
    }else{
        QMessageBox::critical(this, "Error", "Player list if empty, consider adding some players before executing this action.");
    }
}

void MainWindow::on_actionSave_Players_triggered(){
    if(file_path == NULL){
        //we have to create new file to storage the info
        file_path = QFileDialog::getSaveFileName(this, "Save players list file", QDir::homePath() + "/.pla", "Player list (*.pla)");
        if(file_path != NULL){
            r.escribeJugadores(file_path.toUtf8().constData());
            consoleOutput("File " + file_path + " has been successfully saved");
            statusOutput("File has been saved");
        }
    }else{
        //file alredy exists, so we overwrite it
        r.escribeJugadores(file_path.toUtf8().constData());
        consoleOutput("File " + file_path + " has been successfully saved");
        statusOutput("File has been saved");
    }
}

void MainWindow::on_actionLoad_players_triggered(){
    QString aux = QFileDialog::getOpenFileName(this, "Load players list file", QDir::homePath(), "Player list (*.pla)");

    //checks if returned string is valid
    if(aux != NULL){
        r.leeJugadores(aux.toUtf8().constData());

        //checks if every loaded player has his own bets file
        if(loadApuestas(QFileInfo(aux).absolutePath() + "/")){
            file_path = aux;
            consoleOutput("File " + file_path + " has been successfully loaded");
            statusOutput("File loaded successfully");
            updateJugadoresList(1);
            updateBolaInfo();
        }
    }
}

void MainWindow::on_actionDetails_triggered(){
    if(r.getJugadores().empty()){
        QMessageBox::critical(this, "Error", "Player list if empty, consider adding some players before executing this action.");
    }else{
        Jugador aux = getPlayerByIndex(ui->playerOutput->selectionModel()->currentIndex().row());
        detailsPlayer dialog(&aux, this);
        dialog.exec();
    }
}

void MainWindow::on_actionExit_triggered(){
    QApplication::quit();
}

void MainWindow::on_actionAdd_Player_triggered(){
    addPlayerDialog dialog(this);

    //checks if returned player has all the info needed
    if(dialog.exec() == QDialog::Accepted && dialog.hasObligatoryInfo()){
        r.addJugador(dialog.getPlayer());

        //checks if we have alredy a text file
        if(file_path == NULL)
            on_actionSave_Players_triggered();

        //get bets file and update stuff
        dialog.getPlayer().writeApuestas((QFileInfo(file_path).absolutePath() + "/").toUtf8().constData());
        updateJugadoresList(0);
        updateBolaInfo();
        consoleOutput("Player added successfully");
        statusOutput("Player " + QString::fromUtf8(dialog.getPlayer().getDNI().c_str()) + " added successfully");
    }
}

void MainWindow::on_actionDelete_Player_triggered(){
    if(r.getJugadores().empty()){
        QMessageBox::critical(this, "Error", "Player list if empty, consider adding some players before executing this action.");
    }else{
        Jugador aux = getPlayerByIndex(ui->playerOutput->selectionModel()->currentIndex().row());

        deletePlayerDialog dialog(QString::fromUtf8(aux.getDNI().c_str()), this);

        //checks if the user confirms the delete dialog
        if(dialog.exec() == QDialog::Accepted){
            r.deleteJugador(aux);
            updateJugadoresList(0);
            consoleOutput("Player " + QString::fromUtf8(aux.getDNI().c_str()) + " deleted successfully");
            statusOutput("Player deleted successfully");
        }
    }
}

void MainWindow::updateBolaInfo(){
    int nJugadores, dineroTotal, nBola, dineroBanca;

    //gets the necessary info and update the ui labels
    r.getEstadoRuleta(nJugadores, dineroTotal, nBola, dineroBanca);

    ui->nBola->setText("LAUNCH TIMES: " + QString::number(nBola));
    ui->valueBola->setText("BALL VALUE: " + QString::number(r.getBola()));
    ui->bankMoney->setText("BANK MONEY: " + QString::number(dineroBanca + 1000000) + "€");
    ui->playerMoney->setText("PLAYERS MONEY: " + QString::number(dineroTotal - dineroBanca - 1000000) +  "€");
    ui->playerNumber->setText("NUMBER OF PLAYERS: " + QString::number(nJugadores));
}

void MainWindow::consoleOutput(QString text){
    ui->consoleOutput->append("[" + QTime::currentTime().toString() + "] " + text);
}

void MainWindow::statusOutput(QString text, int timeout){
    ui->statusBar->showMessage(text, timeout);
}

bool MainWindow::loadApuestas(QString path){
    std::list<Jugador> aux = r.getJugadores();

    //checks if exists one bet file per player
    for(std::list<Jugador>::iterator it = aux.begin(); it != aux.end(); ++it){
        if(!QDir(path).exists(QString::fromUtf8(it->getDNI().c_str()) + ".apu")){
            QMessageBox::critical(this, "Error", "Error loading bets files from path.");
            return false;
        }
    }

    //if yes, load them all
    r.getPlayerListApuesta(path.toUtf8().constData());
    return true;
}

void MainWindow::updateJugadoresList(int printConsole){
    std::list<Jugador> playerList = r.getJugadores();

    //prints player by player its info
    ui->playerOutput->clear();
    for(std::list<Jugador>::iterator it = playerList.begin(); it != playerList.end(); ++it){
        ui->playerOutput->addItem(getPlayerString(*it));
        if(printConsole)
            consoleOutput("Player " + QString::fromUtf8(it->getDNI().c_str()) + " added");
    }
    ui->playerOutput->setCurrentRow(0);
}

QString MainWindow::getPlayerString(Jugador &player){
    //returns string with the player info to display in the list
    return QString(QString::fromUtf8(player.getDNI().c_str()) + " - " +
                   QString::fromUtf8(player.getApellidosyNombre().c_str()) +
                   " (" + QString::fromUtf8(player.getCodigo().c_str()) + ") - " +
                   " "+ QString::number(player.getDinero()) + "€");
}

Jugador MainWindow::getPlayerByIndex(int index){
    std::list<Jugador>::iterator it;
    std::list<Jugador> lista = r.getJugadores();

    for(it = lista.begin(); index != 0; ++it, --index);
    return (*it);
}
