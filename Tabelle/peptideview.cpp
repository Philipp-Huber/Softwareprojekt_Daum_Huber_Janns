#include "peptideview.h"
#include "qtableview.h"

PeptideView::PeptideView()
{
}

//Slot: updates View when receiving a new marked row
void PeptideView::toBeDisplayed(QModelIndex index){
    bool wasSelected = false;
    for(int i=0; i<displayThese.length(); i++){
        //row was selected before click => remove from selected list
        if(index.row() == displayThese[i]){
            displayThese.removeAt(i);
            wasSelected = true;
            break;
        }
    }
    // row wasn't selected before click => add to selected list
    if(!wasSelected){
        displayThese.append(index.row());
    }

    //no rows are selected => display all
    if(displayThese.empty()){
        for(int i=0; i<model()->rowCount(); i++){
            showRow(i);
        }
    }
    //some rows are selected => display only those
    else{
        for(int i=0; i<model()->rowCount(); i++){
            hideRow(i);
        }

        for(int i=0; i < displayThese.length(); i++){
            if(displayThese[i] <= model()->rowCount()){
                showRow(displayThese[i]);
            }
        }
    }
    return;
}
