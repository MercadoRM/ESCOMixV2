#!/bin/sh
ROUTERS=ip.lista
COMANDOS=ordenes.txt
while read IP #Mientra lea una linea, ip en este caso
do
 sudo mkdir /tftp-acr/$IP #Crear un directorio con el nombre de la IP
 sudo chmod +w /tftp-acr/$IP #Dar permisos de escritura en la carpeta creada
 #Esta linea es importante
 #1.- El siguiente comando es el que debe ejecutar el router para hacer el respaldo
 #2.- Como el router espera por que se presione enter
 #    debo simular ese comportamiento utilizando Crtl+V y luego presiono enter
 #    eso pondra el caracter especial  que simulara la tecla presionada 
 #3.- Los comandos a ejecutar en el router los guardo en COMANDOS, o sea, ordenes.txt
 echo " copy running-config tftp  10.1.2.1  $IP/running.cfg " > $COMANDOS
 echo "\n exit " >> $COMANDOS # Concatenar en COMANDOS
 # Uso sshpass para poder pasarle la contraseña por consola
 # Contraseña escom -c indica un cifrado en especial
 # ya que el router solo recibe algunos, este debe coincidir
 # me conecto con usuario mimi a la IP y le mando los comandos a ejecutar
 sshpass -p escom ssh -c aes256-cbc mimir@$IP < $COMANDOS
done < $ROUTERS #Leer del archivo ip.lista
