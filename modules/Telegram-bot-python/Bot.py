import telegram

from telegram.ext import Updater
from telegram.ext import CommandHandler
from telegram import (ReplyKeyboardMarkup, ReplyKeyboardRemove)
from telegram.ext import (Updater, CommandHandler, MessageHandler, Filters, RegexHandler,
                          ConversationHandler)
from telebot import util
import logging

# habilitando el login
logging.basicConfig(format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
                    level=logging.INFO)

logger = logging.getLogger(__name__)


TOKEN = '397025688:AAFFOaJ3VZqKnm1XN2BkjFW7ziKN6XZsnkY' #Ponemos nuestro TOKEN generado con el @Botfather

#Creamos nuestra instancia "mi_bot" a partir de ese TOKEN

mi_bot = telegram.Bot(token=TOKEN)
mi_bot_updater = Updater(mi_bot.token)
# mi_bot.setWebhook()  # esto es si falla el webhook para deshabilitarlo

# Handle para el incio de la conversacion /start
def start(bot=mi_bot, update=mi_bot_updater):
    print ("Iniciada conversacion: ")
    print (update.message.chat_id)
    bot.sendMessage(chat_id=update.message.chat_id, text="Bienvenido al bot del proyecto 1984, este bot solo es para la devolucion de informacion por parte de el face recognizer para obtener ayuda sobre su uso escriba /?")


# Handle para la ayuda /?
def ayuda(bot=mi_bot, update=mi_bot_updater):
   print ("Solicita ayuda")
   print (update.message.chat_id)
   chat_id=update.message.chat_id
   large_text = open("ayuda.txt", "rb").read()
   splitted_text = util.split_string(large_text, 3000)
   for text in splitted_text:
   	mi_bot.send_message(chat_id, text)

#Handle para enviar la info de oscar en pdf
def oscarpdf(bot=mi_bot, update=mi_bot_updater):
	print ("Iniciado el envio de informacion a la conversacion: ")
	print (update.message.chat_id)
	chat_id=update.message.chat_id
	doc = open('/var/www/html/login_register/final/oscarpdf.pdf', 'rb')
	mi_bot.send_document(chat_id, doc)

#Handle para enviar la info de antonio en pdf
def antoniopdf(bot=mi_bot, update=mi_bot_updater):
    print ("Iniciado el envio de informacion a la conversacion: ")
    print (update.message.chat_id)
    chat_id=update.message.chat_id	
    doc = open('/var/www/html/login_register/final/antoniopdf.pdf', 'rb')
    mi_bot.send_document(chat_id, doc)

#Handle para enviar la info de victor en pdf
def victorpdf(bot=mi_bot, update=mi_bot_updater):
    print ("Iniciado el envio de informacion a la conversacion: ")
    print (update.message.chat_id)
    chat_id=update.message.chat_id
    doc = open('/var/www/html/login_register/final/victorpdf.pdf', 'rb')
    mi_bot.send_document(chat_id, doc)

#Handle para enviar la info de jesus en pdf
def jesuspdf(bot=mi_bot, update=mi_bot_updater):
	print ("Iniciado el envio de informacion a la conversacion: ")
	print (update.message.chat_id)
	chat_id=update.message.chat_id
	doc = open('/var/www/html/login_register/final/jesuspdf.pdf', 'rb')
	mi_bot.send_document(chat_id, doc)

#Handle para enviar la info de andy en pdf
def andypdf(bot=mi_bot, update=mi_bot_updater):
	print ("Iniciado el envio de informacion a la conversacion: ")
	print (update.message.chat_id)
	chat_id=update.message.chat_id
	doc = open('/var/www/html/login_register/final/andypdf.pdf', 'rb')
	mi_bot.send_document(chat_id, doc)


#Handle para enviar la info de oscar en imagen
def oscar(bot=mi_bot, update=mi_bot_updater):
  print ("Iniciado el envio de informacion a la conversacion: ")
  print (update.message.chat_id)
  chat_id=update.message.chat_id
  photo = open('/var/www/html/login_register/final/oscar.png', 'rb')  
  mi_bot.send_photo(chat_id, photo) 

#Handle para enviar la info de antonio en imagen
def antonio(bot=mi_bot, update=mi_bot_updater):
    print ("Iniciado el envio de informacion a la conversacion: ")
    print (update.message.chat_id)
    chat_id=update.message.chat_id  
    photo = open('/var/www/html/login_register/final/antonio.png', 'rb')  
    mi_bot.send_photo(chat_id, photo) 

#Handle para enviar la info de victor en imagen
def victor(bot=mi_bot, update=mi_bot_updater):
    print ("Iniciado el envio de informacion a la conversacion: ")
    print (update.message.chat_id)
    chat_id=update.message.chat_id
    photo = open('/var/www/html/login_register/final/victor.png', 'rb')  
    mi_bot.send_photo(chat_id, photo) 

#Handle para enviar la info de jesus en imagen
def jesus(bot=mi_bot, update=mi_bot_updater):
  print ("Iniciado el envio de informacion a la conversacion: ")
  print (update.message.chat_id)
  chat_id=update.message.chat_id
  photo = open('/var/www/html/login_register/final/jesus.png', 'rb')  
  mi_bot.send_photo(chat_id, photo)  

#Handle para enviar la info de andy en imagen
def andy(bot=mi_bot, update=mi_bot_updater):
  print ("Iniciado el envio de informacion a la conversacion: ")
  print (update.message.chat_id)
  chat_id=update.message.chat_id
  photo = open('/var/www/html/login_register/final/andy.png', 'rb')  
  mi_bot.send_photo(chat_id, photo) 

  #Handle para enviar la info de un desconocido en imagen
def nadie (bot=mi_bot, update=mi_bot_updater):
  print ("Iniciado el envio de informacion a la conversacion: ")
  print ("Un usuario desconocido ha entrado en el sistema")
  print (update.message.chat_id)
  chat_id=update.message.chat_id
  photo = open('/var/www/html/login_register/final/desconocido.png', 'rb')  
  mi_bot.send_photo(chat_id, photo) 
  bot.sendMessage(chat_id=update.message.chat_id, text="Se ha detectado un usuario no autorizado")
  
  #Handle para enviar la info de jurado en imagen
def jurado(bot=mi_bot, update=mi_bot_updater):
  print ("Iniciado el envio de informacion a la conversacion: ")
  print (update.message.chat_id)
  chat_id=update.message.chat_id
  photo = open('/var/www/html/login_register/final/jurado.png', 'rb')  
  mi_bot.send_photo(chat_id, photo) 


#Definimos para cada comando la funcion que atendera la peticion
start_handler = CommandHandler('start', start)
ayuda_handler = CommandHandler('?', ayuda)
oscarpdf_handler = CommandHandler('oscarpdf', oscarpdf)
antoniopdf_handler = CommandHandler('antoniopdf', antoniopdf)
victorpdf_handler = CommandHandler('victorpdf', victorpdf)
jesuspdf_handler = CommandHandler('jesuspdf', jesuspdf)
andypdf_handler = CommandHandler('andypdf', andypdf)
oscar_handler = CommandHandler('oscar', oscar)
antonio_handler = CommandHandler('antonio', antonio)
victor_handler = CommandHandler('victor', victor)
jesus_handler = CommandHandler('jesus', jesus)
andy_handler = CommandHandler('andy', andy)
nadie_handler = CommandHandler('nadie', nadie)
jurado_handler = CommandHandler('jurado', jurado)
dispatcher = mi_bot_updater.dispatcher

dispatcher.add_handler(start_handler)
dispatcher.add_handler(ayuda_handler)
dispatcher.add_handler(oscarpdf_handler)
dispatcher.add_handler(antoniopdf_handler)
dispatcher.add_handler(victorpdf_handler)
dispatcher.add_handler(jesuspdf_handler)
dispatcher.add_handler(andypdf_handler)
dispatcher.add_handler(oscar_handler)
dispatcher.add_handler(antonio_handler)
dispatcher.add_handler(victor_handler)
dispatcher.add_handler(jesus_handler)
dispatcher.add_handler(andy_handler)
dispatcher.add_handler(nadie_handler)
dispatcher.add_handler(jurado_handler)
mi_bot_updater.start_polling()

while True: #Ejecutamos nuestro programa por siempre
    pass
