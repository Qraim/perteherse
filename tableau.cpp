//
// Created by qraim on 05/04/23.
//

#include "tableau.h"

tableau::tableau(QWidget *parent) : QWidget(parent) {
    gridLayout = new QGridLayout(this);
    gridLayout->setColumnStretch(11, 1);
    gridLayout->setSpacing(10);

    QComboBox *comboBox1 = new QComboBox(this);
    comboBox1->setFixedSize(75,25);
    comboBox1->addItem("PVC");
    comboBox1->addItem("PN");
    comboBox1->addItem("Fonte");
    comboBox1->addItem("Alu");

    gridLayout->addWidget(comboBox1, 0, 0);

    QLabel *label1 = new QLabel("Numéro", this);
    QLabel *label2 = new QLabel("Q", this);
    QLabel *label3 = new QLabel("ΣQ", this);
    QLabel *label4 = new QLabel("D", this);
    QLabel *label5 = new QLabel("L", this);
    QLabel *label6 = new QLabel("H", this);
    QLabel *label7 = new QLabel("V", this);
    QLabel *label8 = new QLabel("J", this);
    QLabel *label9 = new QLabel("P", this);
    QLabel *label10 = new QLabel("ΣJ", this);
    QLabel *label11 = new QLabel("ΣP", this);

    gridLayout->addWidget(label1, 1, 0);
    gridLayout->addWidget(label2, 1, 2);
    gridLayout->addWidget(label3, 1, 4);
    gridLayout->addWidget(label4, 1, 6);
    gridLayout->addWidget(label5, 1, 8);
    gridLayout->addWidget(label6, 1, 10);
    gridLayout->addWidget(label7, 1, 12);
    gridLayout->addWidget(label8, 1, 14);
    gridLayout->addWidget(label9, 1, 16);
    gridLayout->addWidget(label10, 1, 18);
    gridLayout->addWidget(label11, 1, 20);

    for (int i = 0; i < 21; i += 2) {
        QFrame *hLine = new QFrame(this);
        hLine->setFrameShape(QFrame::HLine);
        hLine->setFrameShadow(QFrame::Sunken);
        gridLayout->addWidget(hLine, 2, i, 1, 2);
    }
}


tableau::~tableau() {
    delete gridLayout;
}
