import QtQuick 2.7
import QtQuick.Controls 2.3

SwipeView {
    id: root

    clip: true
    anchors { fill: parent }

    // Actually important: means clicks on the slide itself are not
    // 'eaten' for swipes -> they go to the background which uses
    // it for setting focus, which is important to direct key events
    // to moving the presentation back/forward.
    interactive: false

    function next(){
        if (! currentItem.next()){
            incrementCurrentIndex();
        }
        return true;
    }

    function previous(){
        if (! currentItem.previous()){
            decrementCurrentIndex();
        }
        return true;
    }


    function getPresentationState()
    {
        var childState = {};

        for (var idx in contentChildren)
        {
            try{
                childState[idx] = contentChildren[idx].getPresentationState();
            } catch (error){
                childState[idx] = {};
            }
        }

        return {"currentIndex": currentIndex,
            "children": childState
        };
    }

    function setPresentationState(state)
    {
        if (state === null)
            return;

        currentIndex = state.currentIndex;

        for (var idx in contentChildren)
        {
            try{
                contentChildren[idx].setPresentationState(state["children"][idx]);
            } catch (error){
                console.error(error);
            }
        }
    }
}
