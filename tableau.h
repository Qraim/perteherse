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

    QLineEdit *lineEdit1;
    QLineEdit *lineEdit2;
    QLineEdit *lineEdit3;
    QLineEdit *lineEdit4;


    std::vector<std::vector<float>> _Donnees;

    void AjoutDonne();

    void AjoutLigne();

    void focusNextInput();

    void focusPreviousInput();

    void keyPressEvent(QKeyEvent *event);

    bool Allinputfill();

    void calcul();

    void RafraichirTableau();

};

#endif //PERTEDECHARGEHERSE_TABLEAU_H
