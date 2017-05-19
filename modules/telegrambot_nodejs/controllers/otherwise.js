'use strict'

const Telegram = require('telegram-node-bot');

class OtherwiseController extends Telegram.TelegramBaseController{
    handle($){
        $.sendMessage('Try again');
    }

}
module.exports = OtherwiseController;