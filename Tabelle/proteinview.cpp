#include "proteinview.h"

ProteinView::ProteinView(){
        QObject::connect(this, SIGNAL(pressed(QModelIndex)),
                this, SLOT(selectionEvent(QModelIndex)));
    }

//generates a List of Accession Strings and emits them
void ProteinView::selectionEvent(QModelIndex modelIndex){
    QItemSelectionModel* selectionModel = this->selectionModel();
    QList<QString> accessionCodes;

    for(int i=0; i < selectionModel->model()->columnCount(); i++){
        if(selectionModel->model()->headerData(i,Qt::Horizontal).toString() == "accession"){
            QModelIndexList accessionIndexes = selectionModel->selectedRows(i);
            for(int j=0; j < accessionIndexes.length(); j++){
                accessionCodes.append(selectionModel->model()->data(accessionIndexes[j]).toString());
            }
            break;
        }
    }
    emit activeAccessions(accessionCodes);

}
