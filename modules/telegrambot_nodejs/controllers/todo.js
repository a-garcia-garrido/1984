'use strict'

const Telegram = require('telegram-node-bot');

class TodoController extends Telegram.TelegramBaseController{
    todoHandler($){
        $.sendMessage('pong');
    }
    get routes(){
        return{
            'todoCommand': 'todoHandler'
        };
    }

}
module.exports = TodoController;