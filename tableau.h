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

class tableau : public QWidget {
Q_OBJECT

public:
    explicit tableau(QWidget *parent = nullptr);
    ~tableau();

private:
    QGridLayout *gridLayout;
};

#endif //PERTEDECHARGEHERSE_TABLEAU_H
