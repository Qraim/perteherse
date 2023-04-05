//
// Created by qraim on 05/04/23.
//

#include "tableau.h"

// tableau.cpp

const int ROW_HEIGHT = 30;

tableau::tableau(QWidget *parent) : QWidget(parent) {

    ligne = 5;

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Inputs layout and widgets
    QWidget *inputsWidget = new QWidget(this);
    QVBoxLayout *inputsLayout = new QVBoxLayout(inputsWidget);

    // Scroll area and scroll widget
    scrollArea = new QScrollArea(this);
    scrollWidget = new QWidget(scrollArea);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidget(scrollWidget);
    scrollWidget->setMinimumSize(sizeHint());

    gridLayout = new QGridLayout(scrollWidget);
    scrollWidget->setLayout(gridLayout);

    // Bottom layout and widgets
    QWidget *bottomWidget = new QWidget(this);
    QVBoxLayout *bottomLayout = new QVBoxLayout(bottomWidget);

    // Add inputs layout, scroll area, and bottom layout to the main layout
    mainLayout->addWidget(inputsWidget);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(bottomWidget);

    // Add input fields and labels to fixedInputsLayout
    Materiau = new QComboBox(this);
    Materiau->setFixedSize(75, 25);
    Materiau->addItem("PVC");
    Materiau->addItem("PN");
    Materiau->addItem("Fonte");
    Materiau->addItem("Alu");

    inputsLayout->addWidget(Materiau);

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

    // Create QGridLayout for the inputs section
    QGridLayout *inputsGridLayout = new QGridLayout();
    inputsLayout->addLayout(inputsGridLayout);

// Add labels to inputsGridLayout
    inputsGridLayout->addWidget(numero, 0, 0);
    inputsGridLayout->addWidget(Q, 0, 2);
    inputsGridLayout->addWidget(sigmaQ, 0, 4);
    inputsGridLayout->addWidget(D, 0, 6);
    inputsGridLayout->addWidget(L, 0, 8);
    inputsGridLayout->addWidget(H, 0, 10);
    inputsGridLayout->addWidget(V, 0, 12);
    inputsGridLayout->addWidget(J, 0, 14);
    inputsGridLayout->addWidget(P, 0, 16);
    inputsGridLayout->addWidget(sigmaJ, 0, 18);
    inputsGridLayout->addWidget(sigmaP, 0, 20);



// Initialize input fields
    inputQ = new QLineEdit(this);
    inputD = new QLineEdit(this);
    inputL = new QLineEdit(this);
    inputH = new QLineEdit(this);

// Add input fields to inputsGridLayout
    inputsGridLayout->addWidget(inputQ, 1, 2);
    inputsGridLayout->addWidget(inputD, 1, 6);
    inputsGridLayout->addWidget(inputL, 1, 8);
    inputsGridLayout->addWidget(inputH, 1, 10);

// Add the 3 QLineEdit at the bottom of fixedInputsLayout
    QLineEdit *lineEdit1 = new QLineEdit(bottomWidget);
    QLineEdit *lineEdit2 = new QLineEdit(bottomWidget);
    QLineEdit *lineEdit3 = new QLineEdit(bottomWidget);

// Set the size of the QLineEdit widgets
    lineEdit1->setMaximumWidth(150);
    lineEdit2->setMaximumWidth(150);
    lineEdit3->setMaximumWidth(150);

// Add labels for each QLineEdit
    QLabel *label1 = new QLabel("Label1:", bottomWidget);
    QLabel *label2 = new QLabel("Label2:", bottomWidget);
    QLabel *label3 = new QLabel("Label3:", bottomWidget);

// Create a QHBoxLayout for each QLineEdit and its corresponding label
    QHBoxLayout *hbox1 = new QHBoxLayout();
    QHBoxLayout *hbox2 = new QHBoxLayout();
    QHBoxLayout *hbox3 = new QHBoxLayout();

// Add the labels and QLineEdit widgets to the QHBoxLayouts
    hbox1->addWidget(label1);
    hbox1->addWidget(lineEdit1);
    hbox2->addWidget(label2);
    hbox2->addWidget(lineEdit2);
    hbox3->addWidget(label3);
    hbox3->addWidget(lineEdit3);

// Add the QHBoxLayouts to the bottomLayout
    bottomLayout->addLayout(hbox1);
    bottomLayout->addLayout(hbox2);
    bottomLayout->addLayout(hbox3);

    inputQ->setFocus();

// Set the inputsLayout and bottomLayout spacing
    inputsLayout->setSpacing(10);
    bottomLayout->setSpacing(10);
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

    AjoutLigne();

}


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

        QLineEdit *lineEdit = new QLineEdit(scrollWidget); // Change parent from 'this' to 'scrollWidget'
        lineEdit->setReadOnly(true);
        lineEdit->setText(QString::number(rowData[i], 'f', 2));
        lineEdit->setFixedHeight(ROW_HEIGHT); // Set fixed height for each QLineEdit

        gridLayout->addWidget(lineEdit, ligne, i * 2);
    }

    ligne++; // Increment the row index for the next line

    // Adjust the height of the scrollWidget based on the number of rows
    scrollWidget->setMinimumHeight(ligne * ROW_HEIGHT);
    scrollWidget->setMaximumHeight(ligne * ROW_HEIGHT);
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

    if (event->key() == Qt::Key_Control) { // si control est appuyé
        focusPreviousInput();
        return;
    } else if (event->key() == Qt::Key_Tab || event->key() == Qt::Key_Return) { // Si tab ou entrée est appuyé
        if(event->key() == Qt::Key_Return && Allinputfill()){
            AjoutDonne(); // si entrée est appuyé et que toutes les données sont mises
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
        return false; // Si au moins 1 est vide
    }
    return true; // Tout les inputs sont remplis
}

