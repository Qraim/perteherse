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
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget* scrollWidget;


    void AjoutDonne();

    void cumul();

    void AjoutLigne();

    std::vector<std::vector<float>> _Donnees;
    int ligne;
    QLineEdit *inputD;
    QLineEdit *inputQ;
    QLineEdit *inputH;
    QLineEdit *inputL;
    QComboBox *Materiau;


    void focusNextInput();

    void focusPreviousInput();

    void keyPressEvent(QKeyEvent *event);

    bool Allinputfill();
};

#endif //PERTEDECHARGEHERSE_TABLEAU_H
