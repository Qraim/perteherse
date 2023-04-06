//
// Created by qraim on 05/04/23.
//
#ifndef PERTEDECHARGEHERSE_TABLEAU_H
#define PERTEDECHARGEHERSE_TABLEAU_H

#include <QApplication>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QKeyEvent>
#include <QShortcut>
#include <QIcon>
#include <QPixmap>
#include <QDesktopWidget>
#include <QFormLayout>
#include <QDoubleValidator>
#include <iostream>
#include <QScrollArea>
#include <QScrollBar>
#include <QDialog>


#include <vector>
#include <math.h>

class tableau : public QWidget {
Q_OBJECT

public:
    explicit tableau(QWidget *parent = nullptr);
    ~tableau();

private:

    int ligne;

    QLineEdit *inputD;
    QLineEdit *inputQ;
    QLineEdit *inputH;
    QLineEdit *inputL;
    QComboBox *Materiau;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget* scrollWidget;

    QLineEdit *sigmadebitcase;
    QLineEdit *sigmalongueurcase;
    QLineEdit *sigmapertecase;
    QLineEdit *sigmapiezocase;

    std::vector<std::vector<float>> _Donnees;

    void AjoutDonne();

    void AjoutLigne();

    void focusNextInput();

    void focusPreviousInput();

    void keyPressEvent(QKeyEvent *event);

    bool Allinputfill();

    void calcul();

    void RafraichirTableau();

    void clearchild();

    void recopiederniereligne();

    void showUpdateDialog();

    void updateData(int rowNumber, float debit, float diameter, float length, float height);

    void enleverLigne();
};

#endif //PERTEDECHARGEHERSE_TABLEAU_H
