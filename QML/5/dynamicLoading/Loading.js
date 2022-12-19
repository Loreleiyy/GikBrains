var comp1
var comp2           // не смог придумать способ удаления получше



function createPage1(parent) {
    comp1 = Qt.createComponent("Page1.qml");
    var sprite = comp1.createObject(parent)
    if (sprite == null) {

        console.log("Error creating object");
    }

}


function createPage2(parent) {
    comp2 = Qt.createComponent("Page2.qml");
    var sprite = comp2.createObject(parent)
    if (sprite == null) {

        console.log("Error creating object");
    }

}

function deletePage1(){
    comp1.destroy()
}

function deletePage2(){
    comp2.destroy()
}
