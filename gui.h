#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

    QVBoxLayout* guiLayout;
    QTabWidget* workspacesTabs;

private:
    Ui::GUI *ui;
};
#endif // GUI_H
