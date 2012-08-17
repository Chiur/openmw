#include "opencs.hpp"
#include "ui_opencs.h"

#include <QDebug>
#include <QFileDialog>
#include <QDockWidget>

#include "esmdatamodel.hpp"


#include "views/filter/filtertree.hpp"
#include "views/filter/filtereditor.hpp"

OpenCS::OpenCS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenCS)
{
    ui->setupUi(this);


    setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks);
    setCentralWidget(NULL);

    connect(ui->actionOpen,SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionAddIdList, SIGNAL(triggered()), this, SLOT(addIdList()));

    model = new ESMDataModel(this);

    FilterEditModel *filterModel = new FilterEditModel(this);
    filterModel->load();


    QDockWidget *idListDock = new QDockWidget("Filter Tree", this);
    idListDock->setFeatures(QDockWidget::AllDockWidgetFeatures);

    idList = new IdList(this);
    idList->setModel(model);
    idList->setFilterModel(filterModel);
    idListDock->setWidget(idList);

    this->addDockWidget(Qt::RightDockWidgetArea, idListDock);

    //FIXME Copy paste
    QDockWidget *filterTreeDock = new QDockWidget("Filter Tree", this);
    filterTreeDock->setFeatures(QDockWidget::AllDockWidgetFeatures);

    FilterTree *filterTree = new FilterTree(filterTreeDock);
    filterTree->setModel(filterModel);
    filterTreeDock->setWidget(filterTree);

    this->addDockWidget(Qt::LeftDockWidgetArea, filterTreeDock);

    //FIXME Copy paste
    QDockWidget *filterEditDock = new QDockWidget("Filter Editor", this);
    filterEditDock->setFeatures(QDockWidget::AllDockWidgetFeatures);

    FilterEditor *filterEditor = new FilterEditor(filterEditDock);
    //filterEdit->setModel(filterModel);
    filterEditDock->setWidget(filterEditor);

    this->addDockWidget(Qt::LeftDockWidgetArea, filterEditDock);


    connect(filterTree, SIGNAL(filterSelected(Filter*)), filterEditor, SLOT(editFilter(Filter*)));
}

OpenCS::~OpenCS()
{
    delete ui;
}

void OpenCS::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Esm"), "", tr("Esm Files (*.esm)"));
    if (!fileName.isEmpty())
    {
        model->loadEsmFile(fileName);

        idList->loadColumnConfig();
    }
}

void OpenCS::addIdList()
{
//    IdList *idList = new IdList(this);
//    idList->setModel(model);
//    this->addDockWidget(Qt::RightDockWidgetArea, idList);
}
