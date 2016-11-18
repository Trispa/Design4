var socket = io.connect();
socket.on("sendCommandClientStatus", function(msg){
    console.log(msg);
    $("#status").text(msg);
});
socket.on("sendInfo", function(data){
    $("#tensionA4").text(data["tensionA4"]);
    $("#tensionA5").text(data["tensionA5"]);
    $("#tensionA6").text(data["tensionA6"]);
    $("#tensionA7").text(data["tensionA7"]);
    $("#temperature").text(data["temperature"]);
});
socket.on("/", function(){
    $("#startComand").prop("disabled", true);
})
socket.on("demarrerCommande", function(){
    $("#startComand").prop("disabled", true);
})

function demarrerCommande(){
    console.log("command launch");
    socket.emit("demarrerCommande");
}
function reset(){
    $("#buttonGo").prop("disabled",false);
}

function demarrerVentillo(){
    socket.emit("demarrerVentillo");
}

function precharger(){
    socket.emit("precharger");
}

function verifierSurtention(){

}

// verification etat Erreur et etat tention (surtention)

socket.on("verifierError", function(data){
    if(data){
        //TODO changer la couleur en rouge  car il y a une erreur
        }
})

socket.on("verifierSurtention", function(data){
    if(data){
        //TODO changer la couleur en rouge  car il y a une erreur
        }
})
//Debug section calls

/*function sendBotToChargingStation(){
    socket.emit("debugSendBotToChargingStation");
}
function alignBotToChargingStation(){
    socket.emit("debugAlignBotToChargingStation");
}
function searchAllTreasure(){
    socket.emit("debugSearchAllTreasure");
}
function sendBotToTreasure(){
    socket.emit("debugSendBotToTreasure");
}
function alignBotToTreasure(){
    socket.emit("debugAlignBotToTreasure");
}
function sendBotToTarget(){
    socket.emit("debugSendBotToTarget");
}
function alignBotToTarget(){
    socket.emit("debugAlignBotToTarget");
}
function initializeWorld(){
    socket.emit("initializeWorld");
}
*/