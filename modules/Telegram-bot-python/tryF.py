import telegram

from telegram.ext import Updater
from telegram.ext import CommandHandler
from telegram import (ReplyKeyboardMarkup, ReplyKeyboardRemove)
from telegram.ext import (Updater, CommandHandler, MessageHandler, Filters, RegexHandler,
                          ConversationHandler)

import logging

# Enable logging
logging.basicConfig(format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
                    level=logging.INFO)

logger = logging.getLogger(__name__)


TOKEN = '397025688:AAFFOaJ3VZqKnm1XN2BkjFW7ziKN6XZsnkY' #Ponemos nuestro TOKEN generado con el @Botfather

#Creamos nuestra instancia "mi_bot" a partir de ese TOKEN

mi_bot = telegram.Bot(token=TOKEN)
mi_bot_updater = Updater(mi_bot.token)
# mi_bot.setWebhook()  # unset webhook by supplying no parameter esto es si falla el webhookpara deshabilitarlo

# Handle para el incio de la conversacion /start
def start(bot=mi_bot, update=mi_bot_updater):
    print ("Iniciada conversación: ")
    print (update.message.chat_id)
    bot.sendMessage(chat_id=update.message.chat_id, text="Bienvenido al bot del proyecto 1984, este bot solo es para la devolución de informacion por parte de el face recognizer para obtener ayuda sobre su uso escriba /?")


# Handle para la ayuda /?
def ayuda(bot=mi_bot, update=mi_bot_updater):
    print ("Solicita ayuda")
    bot.sendMessage(chat_id=update.message.chat_id, text="actualmente este bot no tiene la opcion de subir datos solo de recibir los datos del servidor ")

#Handle para enviar la info de
def oscar(bot=mi_bot, update=mi_bot_updater):
	print ("Iniciado el envio de informacion a la conversacion: ")
	print (update.message.chat_id)
	#chat_id=update.message.chat_id
	doc = open('/tmp/oscar.pdf', 'rb')
	mi_bot.send_document(chat_id, doc)

#Handle para enviar la info de
def antonio(bot=mi_bot, update=mi_bot_updater):
    print ("Iniciado el envio de informacion a la conversacion: ")
    print (update.message.chat_id)

    doc = open('/tmp/antonio.pdf', 'rb')
    mi_bot.send_document(chat_id, doc)

#Handle para enviar la info de
def victor(bot=mi_bot, update=mi_bot_updater):
    print ("Iniciado el envio de informacion a la conversacion: ")
    print (update.message.chat_id)

    doc = open('/tmp/victor.pdf', 'rb')
    mi_bot.send_document(chat_id, doc)

#Handle para enviar la info de
def jesus(bot=mi_bot, update=mi_bot_updater):
	print ("Iniciado el envio de informacion a la conversacion: ")
	print (update.message.chat_id)

	doc = open('/tmp/jesus.pdf', 'rb')
	mi_bot.send_document(chat_id, doc)

#Handle para enviar la info de
def andy(bot=mi_bot, update=mi_bot_updater):
	print ("Iniciado el envio de informacion a la conversacion: ")
	print (update.message.chat_id)

	doc = open('/tmp/andy.pdf', 'rb')
	mi_bot.send_document(chat_id, doc)

#Definimos para cada comando la función que atendera la peticion
start_handler = CommandHandler('start', start)
ayuda_handler = CommandHandler('?', ayuda)
oscar_handler = CommandHandler('oscar', start)
antonio_handler = CommandHandler('antonio', start)
victor_handler = CommandHandler('victor', start)
jesus_handler = CommandHandler('jesus', start)
andy_handler = CommandHandler('andy', start)
dispatcher = mi_bot_updater.dispatcher

dispatcher.add_handler(start_handler)
dispatcher.add_handler(ayuda_handler)
dispatcher.add_handler(oscar_handler)
dispatcher.add_handler(antonio_handler)
dispatcher.add_handler(victor_handler)
dispatcher.add_handler(jesus_handler)
dispatcher.add_handler(andy_handler)

mi_bot_updater.start_polling()

while True: #Ejecutamos nuestro programa por siempre
    pass
