process.env.NODE_TLS_REJECT_UNAUTHORIZED = '0';
var socket = require('socket.io');
var express = require('express');
var http = require('http');
var https = require('https');
var request = require('request');
var app = express();
app.use(express.static('../Client/UI'));


var server = http.createServer(app);
var io = socket.listen(server);

var allClients = [];
var botClientStatus = "Not connected";
var robot;


io.on('connection', function (client) {
    allClients.push(socket);
    io.emit('statusInfo');
    client.on('statusInfo', function(status){
        console.log(status);
        command = client;
        commandClientStatus = status;
        io.emit('statusInfo', status);
    });
    client.on('reset', function(status){
        console.log(status);
        command = client;
        commandClientStatus = status;
        io.emit('reset', status);
    });
    client.on('disconnect', function() {
        console.log('A client got disconnected');
        if(client == command){
            console.log('Bad news, it\'s the bot');
            botClientStatus = "Not connected";
            io.emit('sendBotClientStatus', botClientStatus);
        }
        var i = allClients.indexOf(client);
        allClients.splice(i, 1);
    });
    client.on('/',function(){
    io.emit('statusInfo');
    });
    client.on('sendInfo', function(data){
        io.emit('sendInfo', data);
    });



    client.on('sendManchesterCode', function(data){
        request(manchesterUrl+'?code='+data, function(error, response, body) {
            manchesterInfo = {"decryptedCharacter":data, "target":JSON.parse(body)};
            //manchesterInfo = {"decryptedCharacter":data, "target":{"forme" : "triangle"}};
            io.emit('sendManchesterInfo', manchesterInfo);
        });
    });
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



