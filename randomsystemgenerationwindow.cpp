#include "randomsystemgenerationwindow.h"
#include "ui_randomsystemgenerationwindow.h"

RandomSystemGenerationWindow::RandomSystemGenerationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomSystemGenerationWindow)
{
    ui->setupUi(this);
    setWindowTitle("Random system generation");

    // empty data
    A = nullptr;
    b = nullptr;
    n = 0;
}

RandomSystemGenerationWindow::~RandomSystemGenerationWindow()
{
    clear_data();

    delete ui;
}

void RandomSystemGenerationWindow::on_GenerateBtn_clicked()
{
    bool ok_1, ok_2, ok_3;
    int n = ui->N->text().toInt(&ok_1);
    double min = ui->Min->text().toDouble(&ok_2);
    double max = ui->Max->text().toDouble(&ok_3);

    if (!ok_1 || !ok_2 || !ok_3) {
        warning("Invalid input data");
        return;
    }

    clear_data();

    this->n = n;
    A = new double*[n];
    b = new double[n];

    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
        for (int j = 0; j < n; j++)
            A[i][j] = getNextValue(min, max);
        b[i] = getNextValue(min, max);
    }
    QMessageBox::information(this, "Done", "System was generated");
    this->accept();
}

double RandomSystemGenerationWindow::getNextValue(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

void RandomSystemGenerationWindow::clear_data()
{
    if (A != nullptr) {
        for (int i = 0; i < n; i++)
            delete []A[i];
        delete []A;
    }
    if (b != nullptr)
        delete []b;

    A = nullptr;
    b = nullptr;
    n = 0;
}

void RandomSystemGenerationWindow::warning(QString msg)
{
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();
}

QString RandomSystemGenerationWindow::getSystemStr()
{
    QString out = "";
    if (A != nullptr && b != nullptr) {
        out.append(QString::number(n) + "\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                out.append(QString::number(A[i][j]) + " ");
            out.append(QString::number(b[i]) + "\n");
        }
    }
    return out;
}

