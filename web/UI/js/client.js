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
socket.on("demarrerCommande", function(){
    $("#startComand").prop("disabled", true);
})

function demarrerCommande(){
    console.log("command launch");
    socket.emit("demarrerCommande");
}
//Arreter la commande

function arreterCommande(){
    console.log("client :arreter commande");
    socket.emit("arreterCommande");
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
        $("#error").attr('class', 'col-md-3 col-sm-12 col-xs-12 btn-lg btn-danger');
        }
});

socket.on("verifierSurtention", function(data){
    console.log(data);
    if(data){
        $("#surtension").attr('class', 'col-md-3 col-sm-12 col-xs-12 btn-lg btn-danger');
        }
})
