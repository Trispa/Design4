process.env.NODE_TLS_REJECT_UNAUTHORIZED = '0';
var socket = require('socket.io');
var express = require('express');
var http = require('http');
var https = require('https');
var request = require('request');
var app = express();
var port  = 8080;
app.use(express.static('../web/UI'));
var server = http.createServer(app);
var io = socket.listen(server);

var commandClientStatus = "Not connected";

var allClients = [];
var command;
app.get('/', function(req, res){
    res.sendFile('./index.html');
})
io.on('connection', function (client) {
    allClients.push(socket);
    io.emit('sendCommandClientStatus',commandClientStatus );
    client.on('sendCommandClientStatus', function(status){
        console.log(status);
        command = client;
        commandClientStatus = status;
        io.emit('sendCommandClientStatus', status);
    });
    client.on('disconnect', function() {
        console.log('A client got disconnected');
        if(client == command){
            console.log('humm! it\'s the command');
            commandClientStatus = "Not connected";
            io.emit('sendBotClientStatus', commandClientStatus);
        }
        var i = allClients.indexOf(client);
        allClients.splice(i, 1);
    });
//    client.on('reset', function(status){
//        console.log(status);
//        commandClientStatus = status;
//        io.emit('reset', status);
//    });

    client.on("arreterCommande",function(){
        console.log('server : arreter Commande');
        io.emit("arreterCommande");
    })
    client.on("sendInfo", function(data){
        io.emit('sendInfo', data);
    });
    client.on('verifierError', function(data){
        io.emit('verifierError', data);
    });
    client.on('verifierSurtention',function(data){
        io.emit('verifierSurtention', data);
    });
//
//
//
//    client.on('sendManchesterCode', function(data){
//        request(manchesterUrl+'?code='+data, function(error, response, body) {
//            manchesterInfo = {"decryptedCharacter":data, "target":JSON.parse(body)};
//            //manchesterInfo = {"decryptedCharacter":data, "target":{"forme" : "triangle"}};
//            io.emit('sendManchesterInfo', manchesterInfo);
//        });
//    });
});


//    client.on('readManchester', function(){
//        console.log('readManchester');
//        io.emit('readManchester');
//    });
//
//
//
//
//    //debug section
//    client.on("debugAlignBotToTarget", function(){
//        console.log("sending align to target command to base");
//        io.emit('debugAlignBotToTarget');
//    });
//    client.on("debugSendBotToTarget", function(){
//        console.log("sending send bot to target command to base");
//        io.emit('debugSendBotToTarget');
//    });


server.listen(8080, 'localhost');
console.log('listening on ' + port + '....');
console.log('press Ctrl + c to stop.');


