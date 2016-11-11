var socket = io.connect();
socket.on("statusInfo", function(msg){
    console.log(msg);
    $("#state").text(msg);
});
socket.on("sendInfo", function(data){
    $("#tensionA4").text(data["tensionA4"]);
    $("#tensionA5").text(data["tensionA"]);
    $("#tensionA6").text(data["tensionA6"]);
    $("#tensionA7").text(data["tensionA7"]);
    $("#tensionA7").text(data["temperature"]);
});

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