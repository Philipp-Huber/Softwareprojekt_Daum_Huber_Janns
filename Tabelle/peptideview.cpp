#include "peptideview.h"
#include "qtableview.h"

PeptideView::PeptideView()
{
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
