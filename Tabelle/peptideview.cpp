#include "peptideview.h"
#include "qtableview.h"
#include "QEvent"

PeptideView::PeptideView()
{
    //listen for mouse events
    this->viewport()->installEventFilter(this);

    QObject::connect(this, SIGNAL(updateStar()),
                this, SLOT(updateEventStar()));

}

//Slot: updates View when receiving a new marked row
void PeptideView::toBeDisplayed(QList<QString> displayThese){

    int column = 0;
    bool accessionFound = false;

    //find the column in the model, that holds the accession numbers
    for(column; column < model()->columnCount(); column++){
        if(model()->headerData(column,Qt::Horizontal).toString() == "accession"){
            accessionFound = true;
            break;
        }



    }
    //No accession codes in the model under the expected header => ignore all signals
    if(!accessionFound){
        return;
    }

    //no items in protein model => display none
    if(displayThese.empty()){
        for(int i=0; i<model()->rowCount(); i++){
            hideRow(i);
        }
    }
    //some rows are selected => display only those
    else{
        for(int i=0; i<model()->rowCount(); i++){
            QString rowAccession = model()->data(model()->index(i, column)).toString();
            for(int j=0; j < displayThese.length(); j++){
                if(rowAccession == displayThese[j]){
                    showRow(i);
                    break;
                }
            hideRow(i);
            }
        }

    }
    return;
}

bool PeptideView::eventFilter(QObject * watched, QEvent * event)
{
  if(event->type() == QEvent::MouseButtonRelease){
      emit updateStar();
      return true;
  }
  return false;
}


void PeptideView::updateEventStar(){

    QItemSelectionModel* selectionModel = this->selectionModel();
    QModelIndexList indexList = selectionModel->selectedIndexes();



    clearPepStar();

    //Stest The Stars in selected Rows to marcked
    for (int i=0; i < indexList.length(); i++){

        if (indexList[i].column()==1 && (model()->data(indexList[i])) == 0){
            this->model()->setData(indexList[i],-1);
        }
  }
}


void PeptideView::clearPepStar(){

 //Stest the Stars in all Rows to unmarcked
    for(int i=0; i< this->model()->rowCount(); i++){
        QModelIndex indexA = model()->index(i,1,QModelIndex());
        this->model()->setData(indexA,0);
    }

}
