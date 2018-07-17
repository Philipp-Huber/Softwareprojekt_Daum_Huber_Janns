#include "proteinview.h"
#include "QEvent"

ProteinView::ProteinView(){

    //listen for mouse events
    this->viewport()->installEventFilter(this);

    //link mouse release with creation and emission of active accession list
    QObject::connect(this, SIGNAL(released()),
                this, SLOT(selectionEvent()));
    }

bool ProteinView::eventFilter(QObject * watched, QEvent * event)
{
  if(event->type() == QEvent::MouseButtonRelease){
      emit released();
  }
}

//generates a List of Accession Strings and emits them
void ProteinView::selectionEvent(){
    QItemSelectionModel* selectionModel = this->selectionModel();
    QList<QString> accessionCodes;

    for(int i=0; i < selectionModel->model()->columnCount(); i++){
        if(selectionModel->model()->headerData(i,Qt::Horizontal).toString() == "accession"){
            //generate a list of the indexes holding accession codes of all selected rows
            QModelIndexList accessionIndexes = selectionModel->selectedRows(i);
            for(int j=0; j < accessionIndexes.length(); j++){
                //add the accession code Strings to the list that will be emitted
                accessionCodes.append(selectionModel->model()->data(accessionIndexes[j]).toString());
            }
            break;
        }
    }
    emit activeAccessions(accessionCodes);

}
