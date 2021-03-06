#include "gui.h"
#include "ui_gui.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);

    // presets
    resize(800, 600);
    setWindowTitle("Calculation Methods");




}

GUI::~GUI()
{

}


void GUI::on_Lab1SolveBtn_clicked()
{
    double **A = nullptr;
    double *b = nullptr;
    StringLogger* output = nullptr;
    Lab1* lab = nullptr;
    int n = -1;
    QList<QString> data_rows;
    bool ok = true;

    auto release_memory = [=]() {
        if (A != nullptr) {
            for (int i = 0; i < n; i++)
                delete []A[i];
            delete []A;
        }
        if (b != nullptr)
            delete []b;
        if (output != nullptr)
            delete output;
        if (lab != nullptr)
            delete lab;
    };

    try {
        // 0. clear output
        sendOutput(ui->Lab1Output, "");

        // 1. Read source data
        QString input_data = ui->Lab1Input->toPlainText();
        data_rows = input_data.split("\n");
        if (data_rows.length() == 0) {
            sendOutput(ui->Lab1Output, "Empty data rows");
            return;
        }
        n = data_rows[0].toInt(&ok);
        if (!ok || n <= 0) {
            sendOutput(ui->Lab1Output, "Invalid input data: incorrect n");
            return;
        }
        if (input_data.length() < n + 1) {
            sendOutput(ui->Lab1Output, "Invalid input data: incorrect system format");
            return;
        }
        // reading linear system
        A = new double*[n];
        b = new double[n];
        for (int i = 0; i < n; i++)
            A[i] = new double[n];

        for (int i = 1; i <= n; i++) {
            QList<QString> row = data_rows[i].split(' ');
            if (row.length() != n + 1)
                throw;
            for (int j = 0; j < n; j++) {
                A[i - 1][j] = row[j].toDouble(&ok);
                if (!ok) throw;
            }
            b[i-1] = row[n].toDouble(&ok);
            if (!ok) throw;
        }

    }  catch (...) {
        sendOutput(ui->Lab1Output, "Something wrong during linear system parsing");
        release_memory();
        return;
    }

    // running LU-alhorythm
    output = new StringLogger();
    lab = new Lab1(true, output);
    lab->TestWithData(A, b, n);
    sendOutput(ui->Lab1Output, output->getLogsStr().c_str());
    release_memory();
}

void GUI::sendOutput(QTextEdit *output, QString msg)
{
    output->setPlainText(msg);
}


void GUI::on_Lab1FillBtn_clicked()
{
    QString test = ui->deteminedLab1Tests->currentText();
    if (test == "Simple")
        sendOutput(ui->Lab1Input, "3\n2 -1 1 23\n4 3 1 32\n6 -13 6 33");
    else if (test == "Task 1")
        sendOutput(ui->Lab1Input, "4\n5 7 6 5 23\n7 10 8 7 32\n6 8 10 9 33\n5 7 9 10 31");
    else if (test == "Task 2")
        sendOutput(ui->Lab1Input, "4\n5 7 6 5 23.01\n7 10 8 7 31.99\n6 8 10 9 32.99\n5 7 9 10 31.01");
    else if (test == "Task 3")
        sendOutput(ui->Lab1Input, "4\n5 7 6 5 23.1\n7 10 8 7 31.9\n6 8 10 9 32.9\n5 7 9 10 31.1");
}


void GUI::on_Lab1GenerateRandomSystemBtn_clicked()
{
    RandomSystemGenerationWindow* generatorWindow = new RandomSystemGenerationWindow();
    generatorWindow->exec();
    sendOutput(ui->Lab1Input, generatorWindow->getSystemStr());
    delete generatorWindow;
}

