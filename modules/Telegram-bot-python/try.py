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


TOKEN = '397025688:AAFFOaJ3VZqKnm1XN2BkjFW7ziKN6XZsnkY' #Ponemos nuestro TOKEN generado con el

#Creamos nuestra instancia "mi_bot" a partir de ese TOKEN

mi_bot = telegram.Bot(token=TOKEN)  
mi_bot_updater = Updater(mi_bot.token)  
mi_bot.setWebhook()  # unset webhook by supplying no parameter

# Handle para el incio de la conversacion /start
def start(bot=mi_bot, update=mi_bot_updater):  
	print ("Iniciada conversación: ")
	print (update.message.chat_id)
	chat_id=update.message.chat_id

	photo = open('/home/andy/Descargas/gatito-tumbado-lamiendo-sus-patitas.jpg', 'rb')  
	mi_bot.send_photo(chat_id , photo)     

    
    #bot.sendMessage(chat_id=update.message.chat_id, text="Hola, soy tu bot!!!")

# Handle para la ayuda /?
def ayuda(bot=mi_bot, update=mi_bot_updater):  
    print ("Solicita ayuda")
    bot.sendMessage(chat_id=update.message.chat_id, text="No tengo mucho que ofrecerte por ahora")

#Definimos para cada comando la función que atendera la peticion
start_handler = CommandHandler('start', start)  
ayuda_handler = CommandHandler('?', ayuda)  

dispatcher = mi_bot_updater.dispatcher

dispatcher.add_handler(start_handler)  
dispatcher.add_handler(ayuda_handler)  

mi_bot_updater.start_polling()

while True: #Ejecutamos nuestro programa por siempre  
    pass
