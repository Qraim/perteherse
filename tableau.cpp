//
// Created by qraim on 05/04/23.
//

#include "tableau.h"

// tableau.cpp

const int ROW_HEIGHT = 40;

void espacementcolonne(QGridLayout *layout) {
    for (int i = 0; i < layout->columnCount(); i++) {
        layout->setColumnStretch(i, 1);
    }
}

tableau::tableau(QWidget *parent) : QWidget(parent) {

    ligne = 1;

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

// Headers widget and layout
    QWidget *headersWidget = new QWidget(this);
    QGridLayout *headersGridLayout = new QGridLayout(headersWidget);

    // Add the column headers
// Add the column headers
    const QStringList headers = {"Numero", "Debit", "ΣDebit", "Diametre", "Longueur ", "Hauteur", "Vitesse", "Perte", "Piezo", "ΣPerte", "ΣPiezo"};

    for (int i = 0; i < headers.size(); ++i) {
        QLabel *label = new QLabel(headers[i], headersWidget);
        label->setAlignment(Qt::AlignCenter);
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        label->setFixedHeight(40); // Set only fixed height
        headersGridLayout->addWidget(label, 0, i);
        headersGridLayout->setHorizontalSpacing(0); // Remove spacing between headers
    }

// Add the units below the column headers
    const QStringList units = {"", "l/h", "l/h", "mm", "m", "m", "m/s", "m", "m", "m", "m"};

    for (int i = 0; i < units.size(); ++i) {
        QLabel *unitLabel = new QLabel(units[i], headersWidget);
        unitLabel->setAlignment(Qt::AlignCenter);
        unitLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        unitLabel->setFixedHeight(40); // Set only fixed height
        headersGridLayout->addWidget(unitLabel, 1, i); // Add the unit labels in the second row of the headersGridLayout
    }




    // Add inputs layout, scroll area, and bottom layout to the main layout
    mainLayout->addWidget(inputsWidget);
    mainLayout->addWidget(headersWidget);
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

    QLabel *Q = new QLabel("Debit (l/h)", this);
    QLabel *D = new QLabel("Diametre (mm)", this);
    QLabel *L = new QLabel("Longueur (m)", this);
    QLabel *H = new QLabel("Hauteur (m)", this);


    // Create QGridLayout for the inputs section
    QGridLayout *inputsGridLayout = new QGridLayout();
    inputsLayout->addLayout(inputsGridLayout);

    // Add horizontal spacers to center the input fields and labels
    inputsGridLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 0);
    inputsGridLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 8);


    // Add labels to inputsGridLayout
    inputsGridLayout->addWidget(Q, 0, 1);
    inputsGridLayout->addWidget(D, 0, 3);
    inputsGridLayout->addWidget(L, 0, 5);
    inputsGridLayout->addWidget(H, 0, 7);


    // Initialize input fields
    inputQ = new QLineEdit(this);
    inputD = new QLineEdit(this);
    inputL = new QLineEdit(this);
    inputH = new QLineEdit(this);

    inputQ->setMaximumWidth(75);
    inputD->setMaximumWidth(75);
    inputL->setMaximumWidth(75);
    inputH->setMaximumWidth(75);


    // Add input fields to inputsGridLayout
    inputsGridLayout->addWidget(inputQ, 1, 1);
    inputsGridLayout->addWidget(inputD, 1, 3);
    inputsGridLayout->addWidget(inputL, 1, 5);
    inputsGridLayout->addWidget(inputH, 1, 7);

    inputQ->setAlignment(Qt::AlignRight);
    inputD->setAlignment(Qt::AlignRight);
    inputL->setAlignment(Qt::AlignRight);
    inputH->setAlignment(Qt::AlignRight);

    inputsGridLayout->setSpacing(5);

    // Call the function to set the column widths for inputsGridLayout
    espacementcolonne(inputsGridLayout);

    // Call the function to set the column widths for gridLayout
    espacementcolonne(gridLayout);

    // Add the 3 QLineEdit at the bottom of fixedInputsLayout
    sigmadebitcase = new QLineEdit(bottomWidget);
    sigmalongueurcase = new QLineEdit(bottomWidget);
    sigmapertecase = new QLineEdit(bottomWidget);
    sigmapiezocase = new QLineEdit(bottomWidget);

    // Set the size of the QLineEdit widgets
    sigmadebitcase->setMaximumWidth(100);
    sigmalongueurcase->setMaximumWidth(100);
    sigmapertecase->setMaximumWidth(100);
    sigmapiezocase->setMaximumWidth(100);

    sigmadebitcase->setAlignment(Qt::AlignRight);
    sigmalongueurcase->setAlignment(Qt::AlignRight);
    sigmapertecase->setAlignment(Qt::AlignRight);
    sigmapiezocase->setAlignment(Qt::AlignRight);

    // Add labels for each QLineEdit
    QLabel *label1 = new QLabel("Débit cumulé :", bottomWidget);
    QLabel *label2 = new QLabel("Volume cumulé :", bottomWidget);
    QLabel *label3 = new QLabel("Perte cumulé :", bottomWidget);
    QLabel *label4 = new QLabel("Piezo cumulé :", bottomWidget);

    // Create a QHBoxLayout for each QLineEdit and its corresponding label
    QHBoxLayout *hbox1 = new QHBoxLayout();
    QHBoxLayout *hbox2 = new QHBoxLayout();
    QHBoxLayout *hbox3 = new QHBoxLayout();
    QHBoxLayout *hbox4 = new QHBoxLayout();

    // Add the labels and QLineEdit widgets to the QHBoxLayouts
    hbox1->addWidget(label1);
    hbox1->addWidget(sigmadebitcase);
    hbox2->addWidget(label2);
    hbox2->addWidget(sigmalongueurcase);
    hbox3->addWidget(label3);
    hbox3->addWidget(sigmapertecase);
    hbox4->addWidget(label4);
    hbox4->addWidget(sigmapiezocase);

// Add the QHBoxLayouts to the bottomLayout
    bottomLayout->addLayout(hbox1);
    bottomLayout->addLayout(hbox2);
    bottomLayout->addLayout(hbox3);
    bottomLayout->addLayout(hbox4);

    inputQ->setValidator(new QDoubleValidator(0.000001, 1000000, 6, this));
    inputD->setValidator(new QDoubleValidator(0.000001, 1000000, 6, this));
    inputL->setValidator(new QDoubleValidator(0.000001, 1000000, 6, this));
    inputH->setValidator(new QDoubleValidator(0.000001, 1000000, 6, this));

    inputQ->setFocus();

    // Set the inputsLayout and bottomLayout spacing
    inputsLayout->setSpacing(10);
    bottomLayout->setSpacing(5);
}


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

    int numero = _Donnees.size()+1; // numéro

    std::vector<float> temp(11, 0.0f); // variable temporaire

    temp[0] = numero;
    temp[1] = debit;
    temp[3] = diametre;
    temp[4] = longueur;
    temp[5] = hauteur;

    _Donnees.push_back(temp); // mise dans le set des données

    AjoutLigne();

}

void tableau::AjoutLigne() {

    if (_Donnees.empty()) {
        return;
    }

    const std::vector<float> &rowData = _Donnees.back();

    // Specify the column numbers corresponding to the inputs above
    const std::vector<int> columnIndices = {0, 1, -1, 3, 4, 5, -1, -1, -1, -1, -1};

    for (int i = 0; i < columnIndices.size(); ++i) {

        QLineEdit *lineEdit = new QLineEdit(scrollWidget);
        lineEdit->setReadOnly(true);
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // Set horizontal size policy to Expanding
        lineEdit->setFixedHeight(40); // Set only fixed height

        if (columnIndices[i] != -1) {
            if (i == 0) {
                lineEdit->setText(QString::number(rowData[i], 'f', 0));
            } else {
                lineEdit->setText(QString::number(rowData[columnIndices[i]], 'f', 2));
            }
        } else {
            lineEdit->setText(""); // Empty case for other columns
        }

        gridLayout->addWidget(lineEdit, ligne, i);
    }

    ligne++; // Increment the row index for the next line

    // Adjust the height of the scrollWidget based on the number of rows
    int scrollWidgetHeight = ligne * ROW_HEIGHT;
    scrollWidget->setMinimumHeight(scrollWidgetHeight);
    scrollWidget->setMaximumHeight(scrollWidgetHeight);

    // Set the vertical spacing and align the grid layout to the top
    gridLayout->setVerticalSpacing(15);
    gridLayout->setAlignment(Qt::AlignTop);
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
        if (event->modifiers() == Qt::ShiftModifier && event->key() == Qt::Key_Return && Allinputfill()) { // Si shift + entrée est appuyé
            calcul();
            return;
        } else if(event->key() == Qt::Key_Return && Allinputfill()){
            AjoutDonne(); // si entrée est appuyé et que toutes les données sont mises
        } else {
            focusNextInput();
        }
        return;
    } else if(event->key() == Qt::Key_E){
        _Donnees.clear();
        clearchild();
    } else if(event->key() == Qt::Key_R){
        if(_Donnees.size() > 0){ // Vérifier s'il y a des données
            recopiederniereligne();
        }
    } else if(event->key() == Qt::Key_M){
        showUpdateDialog();
    } else if(event->key() == Qt::Key_Z){
        enleverLigne();
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

void tableau::calcul() {

    float  k =0; // On initialise les parametres
    float a=0;
    float b = 0 ;

    float debit = 0;
    float debit_m3 = 0;
    float debit_ls = 0;

    float diametre = 0;
    float longueur = 0;
    float hauteur = 0;

    float pertecharge = 0;
    float piezo = 0;

    float sigmadebit = 0;
    float vitesse = 0;
    float airetuyau = 0;

    float sigmapiezo =0;
    float sigmaperte = 0;

    float sigmalongueur = 0;

    for (int i = 0; i < _Donnees.size(); ++i) {
        sigmadebit += _Donnees[i][1];
        _Donnees[i][2] = sigmadebit;
    }


    if (Materiau->currentText() == "PVC" || Materiau->currentText() == "PN") { // Selection des critere selon la matiere
        k=831743.11;
        a = 1.75;
        b=-4.75;
    } else if (Materiau->currentText() == "Fonte") {
        k=1458844.82;
        a = 1.83;
        b=-4.89;
    } else if (Materiau->currentText() == "Alu") {
        k=1707785.38;
        a = 1.89;
        b=-4.87;
    }

    for (int i = 0; i <_Donnees.size() ; ++i) {

        debit = _Donnees[i][1];
        sigmadebit = _Donnees[i][2];
        diametre = _Donnees[i][3];
        longueur = _Donnees[i][4];
        hauteur = _Donnees[i][5];

        airetuyau = (M_PI * pow((diametre/1000) / 2, 2)); // calcul de l'air du tuyau
        debit_m3 = sigmadebit / 3600.0 / 1000.0; //  l/h -> m3/s

        vitesse = debit_m3 / airetuyau ; // calcul vitesse

        float sigmadebit_ls = sigmadebit /3600.0; // convert l/h -> l/s

        pertecharge = k * pow(sigmadebit_ls,a)*pow(diametre,b)*longueur;// calcul perte

        piezo = pertecharge + hauteur; // calcul piezo

        _Donnees[i][6] = vitesse;
        _Donnees[i][7] = pertecharge;
        _Donnees[i][8] = piezo;

    }

    for (int i = 0; i < _Donnees.size(); ++i) {
        sigmaperte += _Donnees[i][7];
        sigmapiezo += _Donnees[i][8];
        sigmalongueur += _Donnees[i][4];


        _Donnees[i][9] = sigmaperte;
        _Donnees[i][10] = sigmapiezo;
    }

    sigmadebitcase->setText(QString::number(sigmadebit, 'f', 2));
    sigmadebitcase->setAlignment(Qt::AlignCenter);

    sigmalongueurcase->setText(QString::number(sigmalongueur, 'f', 2));
    sigmalongueurcase->setAlignment(Qt::AlignCenter);

    sigmapertecase->setText(QString::number(sigmaperte, 'f', 2));
    sigmapertecase->setAlignment(Qt::AlignCenter);

    sigmapiezocase->setText(QString::number(sigmapiezo, 'f', 2));
    sigmapiezocase->setAlignment(Qt::AlignCenter);

    RafraichirTableau();
}


void tableau::RafraichirTableau() {
    // Clear all widgets from the scroll area
    clearchild();

    ligne = 1;

    // Calculate the total cumulative flow rate
    float totalCumulativeFlowRate = 0.0f;
    for (const std::vector<float> &rowData : _Donnees) {
        totalCumulativeFlowRate += rowData[2];
    }

    // Find the index of the row where the cumulative flow rate is greater than or equal to half of the total cumulative flow rate
    float cumulativeFlowRate = _Donnees[_Donnees.size()-1][2];
    float halfFlowRate = cumulativeFlowRate/2;
    float halfFlowRateRowIndex = 0;

    for (int i = 0; i < _Donnees.size(); ++i) {
        if (_Donnees[i][2]>halfFlowRate) {
            halfFlowRateRowIndex = i;
            break;
        }
    }

    // Add the data to the scroll area
    for (const std::vector<float> &rowData : _Donnees) {
        const std::vector<int> columnIndices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        bool redText = (rowData[6] > 2);

        for (int i = 0; i < columnIndices.size(); ++i) {
            QLineEdit *lineEdit = new QLineEdit(scrollWidget);
            lineEdit->setReadOnly(true);
            lineEdit->setAlignment(Qt::AlignCenter);
            lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // Set horizontal size policy to Expanding
            lineEdit->setFixedHeight(40); // Set only fixed height

            if (i == 0) {
                lineEdit->setText(QString::number(rowData[i], 'f', 0));
            } else if (i == 6 && redText) {
                lineEdit->setStyleSheet("QLineEdit { background-color : red; color : white; }");
                lineEdit->setText(QString::number(rowData[columnIndices[i]], 'f', 2));
            } else {
                lineEdit->setText(QString::number(rowData[columnIndices[i]], 'f', 2));
            }

            // Set the background color to orange for the row where the cumulative flow rate is greater than or equal to half of the total cumulative flow rate
            if (ligne - 1 == halfFlowRateRowIndex) {
                lineEdit->setStyleSheet("QLineEdit { background-color : orange; }");
            }

            gridLayout->setVerticalSpacing(10);
            gridLayout->addWidget(lineEdit, ligne, columnIndices[i]);
        }

        ligne++;
    }

    // Adjust the height of the scrollWidget based on the number of rows
    int scrollWidgetHeight = ligne * ROW_HEIGHT;
    scrollWidget->setMinimumHeight(scrollWidgetHeight);
    scrollWidget->setMaximumHeight(scrollWidgetHeight);
    gridLayout->setVerticalSpacing(15);

    // Align the grid layout to the top
    gridLayout->setAlignment(Qt::AlignTop);
}



void tableau::clearchild() {
    QLayoutItem *child;
    while ((child = gridLayout->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }
    scrollWidget->setMinimumHeight(0);
    scrollWidget->setMaximumHeight(0);
}


void tableau::recopiederniereligne() {

    int taille =_Donnees.size();
    std::vector<float> lastline = _Donnees[taille-1]; // Pour avoir la derniere ligne du vecteur
    std::vector<float> recopie(11, 0.0f);

    recopie[0] = lastline[0]+1;
    recopie[1] = lastline[1];
    recopie[3] = lastline[3];
    recopie[4] = lastline[4];
    recopie[5] = lastline[5];

    _Donnees.push_back(recopie);
    AjoutLigne();
}


void tableau::showUpdateDialog() {
    QDialog *updateDialog = new QDialog(this);
    updateDialog->setWindowTitle("Modifier ligne");

    QFormLayout *formLayout = new QFormLayout(updateDialog);

    QLineEdit *rowNumberLineEdit = new QLineEdit(updateDialog);
    rowNumberLineEdit->setValidator(new QIntValidator(0, _Donnees.size() - 1, updateDialog));
    formLayout->addRow("Ligne :", rowNumberLineEdit);

    QLineEdit *debitLineEdit = new QLineEdit(updateDialog);
    formLayout->addRow("Debit:", debitLineEdit);

    QLineEdit *diameterLineEdit = new QLineEdit(updateDialog);
    formLayout->addRow("Diametre :", diameterLineEdit);

    QLineEdit *lengthLineEdit = new QLineEdit(updateDialog);
    formLayout->addRow("Longueur :", lengthLineEdit);

    QLineEdit *heightLineEdit = new QLineEdit(updateDialog);
    formLayout->addRow("Hauteur :", heightLineEdit);

    QPushButton *updateButton = new QPushButton("Update", updateDialog);
    formLayout->addWidget(updateButton);

    auto handleEnterKeyPress = [](QLineEdit *current, QLineEdit *next) {
        QObject::connect(current, &QLineEdit::returnPressed, [current, next]() {
            if (!current->text().isEmpty() && (next == nullptr || !next->text().isEmpty())) {
                if (next) {
                    next->setFocus();
                }
            }
        });
    };

    handleEnterKeyPress(rowNumberLineEdit, debitLineEdit);
    handleEnterKeyPress(debitLineEdit, diameterLineEdit);
    handleEnterKeyPress(diameterLineEdit, lengthLineEdit);
    handleEnterKeyPress(lengthLineEdit, heightLineEdit);
    handleEnterKeyPress(heightLineEdit, nullptr);

    auto updateDataAndClose = [this, rowNumberLineEdit, debitLineEdit, diameterLineEdit, lengthLineEdit, heightLineEdit, updateDialog]() {
        int rowNumber = rowNumberLineEdit->text().toInt();
        float debit = debitLineEdit->text().toFloat();
        float diameter = diameterLineEdit->text().toFloat();
        float length = lengthLineEdit->text().toFloat();
        float height = heightLineEdit->text().toFloat();

        updateData(rowNumber, debit, diameter, length, height);
        updateDialog->close();
    };

    connect(updateButton, &QPushButton::clicked, updateDataAndClose);

    // Add a QShortcut to trigger update when Enter is pressed
    QShortcut *enterShortcut = new QShortcut(QKeySequence(Qt::Key_Enter), updateDialog);
    QShortcut *returnShortcut = new QShortcut(QKeySequence(Qt::Key_Return), updateDialog);
    connect(enterShortcut, &QShortcut::activated, updateDataAndClose);
    connect(returnShortcut, &QShortcut::activated, updateDataAndClose);

    updateDialog->setLayout(formLayout);
    updateDialog->exec();
}


void tableau::updateData(int rowNumber, float debit, float diameter, float length, float height) {
    if (rowNumber >= 0 && rowNumber < _Donnees.size()) {
        rowNumber-=1;
        _Donnees[rowNumber][1] = debit;
        _Donnees[rowNumber][3] = diameter;
        _Donnees[rowNumber][4] = length;
        _Donnees[rowNumber][5] = height;

        // Recalculate and refresh the table.
        calcul();
        RafraichirTableau();
    }
}

void tableau::enleverLigne() {
    // Create a new dialog for inputting the row number
    QDialog *deleteDialog = new QDialog(this);
    deleteDialog->setWindowTitle("Supprimer une ligne");
    deleteDialog->setFixedSize(300, 100);

    // Add a label and line edit for inputting the row number
    QLabel *rowNumberLabel = new QLabel("Numéro de ligne :", deleteDialog);
    QLineEdit *rowNumberLineEdit = new QLineEdit(deleteDialog);
    rowNumberLineEdit->setValidator(new QIntValidator(1, _Donnees.size(), deleteDialog)); // Only allow integers within the range of the data
    rowNumberLineEdit->setFixedWidth(50);

    // Add a button to confirm the deletion
    QPushButton *deleteButton = new QPushButton("Supprimer", deleteDialog);
    connect(deleteButton, &QPushButton::clicked, [this, rowNumberLineEdit, deleteDialog]() {
        int rowNumber = rowNumberLineEdit->text().toInt() - 1;
        if (rowNumber >= 0 && rowNumber < _Donnees.size()) {
            _Donnees.erase(_Donnees.begin() + rowNumber); // Remove the row from the data
            // Reassign line numbers starting from the deleted row
            for (int i = rowNumber; i < _Donnees.size(); ++i) {
                _Donnees[i][0] = i + 1;
            }
            RafraichirTableau(); // Refresh the table display
        }
        deleteDialog->close();
    });

    // Add a layout to the dialog
    QVBoxLayout *layout = new QVBoxLayout(deleteDialog);
    layout->addWidget(rowNumberLabel);
    layout->addWidget(rowNumberLineEdit);
    layout->addWidget(deleteButton);
    layout->setAlignment(Qt::AlignCenter);

    // Show the dialog
    deleteDialog->exec();

    calcul();
    RafraichirTableau();
}


