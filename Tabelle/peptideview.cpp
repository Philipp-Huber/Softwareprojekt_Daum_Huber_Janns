#include "peptideview.h"
#include "qtableview.h"
#include "QEvent"
#include <QHeaderView>

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

void PeptideView::clearSelection(){
    this->QAbstractItemView::clearSelection();
    emit updateStar();
}

void PeptideView::updateEventStar(){
    bool sortedByStars = false;
    Qt::SortOrder order;

    //Ham-fisted fix to the strange star bug when sorting by the star column:
    //Since every other column works fine, temporarily set the sorting to another column and switch back later...
    if(this->horizontalHeader()->sortIndicatorSection() == 1){
        sortedByStars = true;
        order = this->horizontalHeader()->sortIndicatorOrder();
        this->sortByColumn(0, Qt::AscendingOrder);
    }

    clearPepStar();

    int StarRow = 1;
    QItemSelectionModel* selectionModel = this->selectionModel();
    QModelIndexList indexList = selectionModel->selectedRows(StarRow);

    //Sets the Stars in selected Rows to marked
    for (int i=0; i < indexList.length(); i++){
            this->model()->setData(model()->index(indexList[i].row(), 1),-1.0f, Qt::DisplayRole);
    }

    //Switch back to previous sorting by stars if that was set
    if(sortedByStars){
        this->sortByColumn(1, order);
    }
}


void PeptideView::clearPepStar(){
    //Sets the Stars in all Rows to unmarked
    for(int i=0; i< this->model()->rowCount(); i++){
        QModelIndex indexA = model()->index(i,1,QModelIndex());
        this->model()->setData(indexA, 0.0f, Qt::DisplayRole);
    }
}
