'use strict'

const Telegram = require('telegram-node-bot'),
tg = new Telegram.Telegram('390418313:AAGU7JM9ZE2gUnma-k6CP9lxmAJtonULkG0',{
    workers: 1
});

const TodoController = require('./controllers/ping')
    , OtherwiseController = require('./controllers/otherwise');

tg.router.when(new Telegram.TextCommand('/add', 'addCommand'), new TodoController())
.otherwise(new OtherwiseController());
