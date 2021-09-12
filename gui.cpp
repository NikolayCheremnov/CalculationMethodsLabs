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



    // creating workspaces tabs
    guiLayout = new QVBoxLayout(this);
    workspacesTabs = new QTabWidget(this);
    guiLayout->addWidget(workspacesTabs);

    setLayout(guiLayout);
}

GUI::~GUI()
{
    delete guiLayout;

    //
    delete workspacesTabs;
    delete ui;
}

