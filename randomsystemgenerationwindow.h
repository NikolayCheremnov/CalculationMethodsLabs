#ifndef RANDOMSYSTEMGENERATIONWINDOW_H
#define RANDOMSYSTEMGENERATIONWINDOW_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class RandomSystemGenerationWindow;
}

class RandomSystemGenerationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RandomSystemGenerationWindow(QWidget *parent = nullptr);
    ~RandomSystemGenerationWindow();

private slots:
    void on_GenerateBtn_clicked();

private:
    Ui::RandomSystemGenerationWindow *ui;
    int n;
    double** A;
    double* b;

    double getNextValue(double min, double max);
    void clear_data();

    void warning(QString msg);

public:
    QString getSystemStr();
};

#endif // RANDOMSYSTEMGENERATIONWINDOW_H
