//
// Created by qraim on 05/04/23.
//
#ifndef PERTEDECHARGEHERSE_TABLEAU_H
#define PERTEDECHARGEHERSE_TABLEAU_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QComboBox>
#include <QLineEdit>
#include <vector>
#include <math.h>

class tableau : public QWidget {
Q_OBJECT

public:
    explicit tableau(QWidget *parent = nullptr);
    ~tableau();

private:
    QGridLayout *gridLayout;

    void AjoutDonne();

    void cumul();

    std::vector<std::vector<float>> _Donnees;
    QLineEdit *inputD;
    QLineEdit *inputQ;
    QLineEdit *inputH;
    QLineEdit *inputL;
    QComboBox *Materiau;


};

#endif //PERTEDECHARGEHERSE_TABLEAU_H
