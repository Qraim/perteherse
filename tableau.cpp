//
// Created by qraim on 05/04/23.
//

#include "tableau.h"

// tableau.cpp


tableau::tableau(QWidget *parent) : QWidget(parent) {

    ligne = 5; // Pour commencer en dessous des inputs

    gridLayout = new QGridLayout(this);
    gridLayout->setColumnStretch(11, 1);
    gridLayout->setSpacing(10);



    Materiau = new QComboBox(this);
    Materiau->setFixedSize(75, 25);
    Materiau->addItem("PVC");
    Materiau->addItem("PN");
    Materiau->addItem("Fonte");
    Materiau->addItem("Alu");

    gridLayout->addWidget(Materiau, 0, 0);

    QLabel *numero = new QLabel("Numéro", this);
    QLabel *Q = new QLabel("Debit (l/h)", this);
    QLabel *sigmaQ = new QLabel("Σ Debit", this);
    QLabel *D = new QLabel("Diametre (mm)", this);
    QLabel *L = new QLabel("Longueur (m)", this);
    QLabel *H = new QLabel("Hauteur (m)", this);
    QLabel *V = new QLabel("Vitesse (m/s)", this);
    QLabel *J = new QLabel("Perte de charge (m)", this);
    QLabel *P = new QLabel("Piezo (m)", this);
    QLabel *sigmaJ = new QLabel("Σ Perte ", this);
    QLabel *sigmaP = new QLabel("Σ Piezo ", this);

    gridLayout->addWidget(numero, 1, 0);
    gridLayout->addWidget(Q, 1, 2);
    gridLayout->addWidget(sigmaQ, 1, 4);
    gridLayout->addWidget(D, 1, 6);
    gridLayout->addWidget(L, 1, 8);
    gridLayout->addWidget(H, 1, 10);
    gridLayout->addWidget(V, 1, 12);
    gridLayout->addWidget(J, 1, 14);
    gridLayout->addWidget(P, 1, 16);
    gridLayout->addWidget(sigmaJ, 1, 18);
    gridLayout->addWidget(sigmaP, 1, 20);

    QFrame *hLine = new QFrame(this);
    hLine->setFrameShape(QFrame::HLine);
    hLine->setFrameShadow(QFrame::Sunken);
    gridLayout->addWidget(hLine, 2, 0, 1, 21);

    for (int i = 1; i < 21; i += 2) {
        QFrame *vLine = new QFrame(this);
        vLine->setFrameShape(QFrame::VLine);
        vLine->setFrameShadow(QFrame::Sunken);
        gridLayout->addWidget(vLine, 1, i, 1, 1);
    }

    // Add input fields under Q, D, L, and H labels
    inputQ = new QLineEdit(this);
    inputD = new QLineEdit(this);
    inputL = new QLineEdit(this);
    inputH = new QLineEdit(this);

    gridLayout->addWidget(inputQ, 3, 2);
    gridLayout->addWidget(inputD, 3, 6);
    gridLayout->addWidget(inputL, 3, 8);
    gridLayout->addWidget(inputH, 3, 10);

    QFrame *hLine2 = new QFrame(this);
    hLine2->setFrameShape(QFrame::HLine);
    hLine2->setFrameShadow(QFrame::Sunken);
    gridLayout->addWidget(hLine2, 4, 0, 1, 21);

    // Add read-only text fields under the other labels
    QLineEdit *readOnlyFields[7];
    int readOnlyColumns[] = {0, 4, 12,14, 16, 18, 20};

    inputQ->setFocus();
}


/*    for (int i = 0; i < 7; i++) {
        readOnlyFields[i] = new QLineEdit(this);
        readOnlyFields[i]->setReadOnly(true);
        gridLayout->addWidget(readOnlyFields[i], 3, readOnlyColumns[i]);
    }*/


tableau::~tableau() {
    delete gridLayout;
    delete inputD;
    delete inputH;
    delete inputL;
    delete inputQ;
    delete Materiau;
}


void tableau::AjoutDonne() {

    float debit = inputQ->text().toFloat(); // récupération des inputs
    float diametre = inputD->text().toFloat();
    float longueur = inputL->text().toFloat();
    float hauteur = inputH->text().toFloat();

    float  k =0; // On initialise les parametres
    float a=0;
    float b = 0 ;

    float diametre_m = diametre / 1000; // convert mm to m
    float airetuyau = M_PI * pow(diametre_m / 2, 2); // calcul de l'air du tuyau

    float debit_m3 = debit / 3600.0 / 1000.0; // convert l/h -> m3/s
    float debit_ls = debit / 3600.0; // convert l/h -> l/s


    if (Materiau->currentText() == "PVC" || Materiau->currentText() == "Polyéthylène") { // Selection des critere selon la matiere
        k=831743.11;
        a = 1.75;
        b=-4.75;
    } else if (Materiau->currentText() == "Fonte") {
        k=1458844.82;
        a = 1.83;
        b=-4.89;
    } else if (Materiau->currentText() == "Aluminium") {
        k=1707785.38;
        a = 1.89;
        b=-4.87;
    }

    float pertecharge = k*pow(debit_ls,a)*pow((diametre),b)*longueur; // calcul perte
    std::cout<<pertecharge<<std::endl;

    float piezo = pertecharge + hauteur; // calcul piezo

    float vitesse = debit_m3 / airetuyau; // calcul vitesse

    int numero = _Donnees.size()+1; // numéro

    std::vector<float> temp(11, 0.0f); // variable temporaire

    temp[0] = numero;
    temp[1] = debit;
    temp[3] = diametre;
    temp[4] = longueur;
    temp[5] = hauteur;
    temp[6] = vitesse;
    temp[7] = pertecharge;
    temp[8] = piezo;

    _Donnees.push_back(temp); // mise dans le set des données

    cumul();

    std::cout<<"here"<<std::endl;

    AjoutLigne();

}

/*void tableau::cumul() {

    float sigmadebit = 0;
    float sigmaperte = 0;
    float sigmapiezo = 0;


    for(int i=0; i<_Donnees.size();++i){

        sigmadebit = 0;
        sigmaperte = 0;
        sigmapiezo = 0;

        for(int j=0; j<i;j++){

            sigmadebit += _Donnees[j][1];
            sigmaperte += _Donnees[j][7];
            sigmapiezo += _Donnees[j][8];

        }

        _Donnees[i][2] = sigmadebit ;
        _Donnees[i][9] = sigmaperte ;
        _Donnees[i][10] = sigmapiezo ;

    }
}*/

void tableau::cumul() {
    float sigmadebit = 0;
    float sigmaperte = 0;
    float sigmapiezo = 0;

    for (int i = 0; i < _Donnees.size(); ++i) {
        sigmadebit += _Donnees[i][1];
        sigmaperte += _Donnees[i][7];
        sigmapiezo += _Donnees[i][8];

        _Donnees[i][2] = sigmadebit;
        _Donnees[i][9] = sigmaperte;
        _Donnees[i][10] = sigmapiezo;
    }
}


void tableau::AjoutLigne() {
    if (_Donnees.empty()) {
        return;
    }

    const std::vector<float> &rowData = _Donnees.back();

    for (int i = 0; i < rowData.size(); ++i) {

        QLineEdit *lineEdit = new QLineEdit(this);
        lineEdit->setReadOnly(true);
        lineEdit->setText(QString::number(rowData[i], 'f', 2));

        gridLayout->addWidget(lineEdit, ligne, i * 2);
    }

    ligne++; // Increment the row index for the next line

}

void tableau::focusPreviousInput() {

    if (inputH->hasFocus()) {
        inputL->setFocus();
        return;
    } else if (inputL->hasFocus()) {
        inputD->setFocus();
        return;
    } else if (inputD->hasFocus()){
        inputQ->setFocus();
    }
}

void tableau::focusNextInput() {
    if (inputQ->hasFocus()) {
        inputD->setFocus();
        return;
    } else if (inputD->hasFocus()) {
        inputL->setFocus();
        return;
    } else if (inputL->hasFocus()){
        inputH->setFocus();
    }
}

void tableau::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Control) {
        focusPreviousInput();
        return;
    } else if (event->key() == Qt::Key_Tab || event->key() == Qt::Key_Return) {
        if(event->key() == Qt::Key_Return && Allinputfill()){
            AjoutDonne();
        } else {
            focusNextInput();
        }
        return;
    } else {
        QWidget::keyPressEvent(event);
    }
}

bool tableau::Allinputfill() {
    if (inputD->text().isEmpty() || inputQ->text().isEmpty() ||
        inputH->text().isEmpty() || inputL->text().isEmpty()) {
        return false; // At least one input field is empty
    }
    return true; // All input fields are filled
}

