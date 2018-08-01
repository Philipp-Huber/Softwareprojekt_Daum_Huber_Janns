#include "proteinview.h"
#include "QEvent"

ProteinView::ProteinView(){

    //listen for mouse events
    this->viewport()->installEventFilter(this);

    //link mouse release with creation and emission of active accession list
    QObject::connect(this, SIGNAL(update()),
                this, SLOT(updateEvent()));


    }

bool ProteinView::eventFilter(QObject * watched, QEvent * event)
{
  if(event->type() == QEvent::MouseButtonRelease){
      emit update();
      return true;
  }
  return false;
}


void ProteinView::clearAllStars(){

    for(int i=0; i< this->model()->rowCount(); i++){
        QModelIndex indexA = model()->index(i,1,QModelIndex());
        this->model()->setData(indexA,0);

    }
}

void ProteinView::clearSelection(){
    this->QAbstractItemView::clearSelection();
    emit update();

}

//generates a List of Accession Strings and emits them
void ProteinView::updateEvent(){

    QItemSelectionModel* selectionModel = this->selectionModel();
    QList<QString> accessionCodes;
    int accessionColumn;
    bool accessionFound = false;

    clearAllStars();

    for(int i=0; i < selectionModel->model()->columnCount(); i++){
        if(selectionModel->model()->headerData(i,Qt::Horizontal).toString() == "accession"){
            accessionColumn = i;
            accessionFound = true;
            //generate a list of the indexes holding accession codes of all selected rows
            QModelIndexList accessionIndexes = selectionModel->selectedRows(accessionColumn);
            for(int j=0; j < accessionIndexes.length(); j++){
                //add the accession code Strings to the list that will be emitted
                accessionCodes.append(selectionModel->model()->data(accessionIndexes[j]).toString());

                // sets all stars in selected rows as checked
                this->model()->setData(model()->index(accessionIndexes[j].row(),1,QModelIndex()),-1);
            }
            break;
        }
    }
    //  No accession codes in the model under the expected header => do not send signals
    if(!accessionFound){
        return;
    }

    // no rows selected => signal all access codes to treat "none selected" equivalent to "all selected"
    if(accessionCodes.length()==0){
        for(int i=0; i < model()->rowCount(); i++){
            QString rowAccession = model()->data(model()->index(i, accessionColumn)).toString();
            accessionCodes.append(rowAccession);
        }
    }

        emit activeAccessions(accessionCodes);

}
/*
void ProteinView::starRow(int row){

    this->selectRow(row);
    emit released();
}
*/
