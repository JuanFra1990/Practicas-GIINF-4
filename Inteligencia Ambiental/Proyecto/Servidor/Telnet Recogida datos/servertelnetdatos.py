import socket
import smtplib
import time  
import config

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Bind the socket to the port
server_address = ('192.168.48.32', 10002)
sock.bind(server_address)
# Listen for incoming connections
sock.listen(1)
 
try: 
    while True:
        # Wait for a connection
        print('waiting for a connection...')
        connection, client_address = sock.accept()
        print('connection from %s:%d' % client_address)
        advertencia = 0
        try:
            while True:
                # Receive the data one byte at a time
                data = connection.recv(1)
                contador = 0
                vtemperatura = []
                time.strftime("%H:%M:%S")
                
                
                if data=="w":
                    if advertencia==0:
                        print('Enviando mensaje de advertencia')
                        remitente = "correo que envia" 
                        contrasena = "**************"
                        destinatario = "correo que recibe" 
                        asunto = "Advertencia Sala Servidor 1" 
                        mensaje = "La sala servidor advierte que no se detecta el sensor"
                        
                        email = """From: %s 
                        To: %s 
                        MIME-Version: 1.0 
                        Content-type: text/html 
                        Subject: %s 
                        %s
                        """ % (remitente, destinatario, asunto, mensaje)
                        try:
                            smtp = smtplib.SMTP('smtp.gmail.com', 587)
                            smtp.starttls()
                            smtp.login(remitente, contrasena)
                            smtp.sendmail(remitente, destinatario, email)
                            smtp.quit()
                        
                            advertencia = 1
                        except Exception as e:
                           print "No se puede enviar el mensaje"
                           print type(e)
                           print e
                            
                    else:
                        print('Advertencia ya realizada al Personal')
                        
                elif data=="d":
                    if advertencia==0:
                       print('Enviando mensaje de advertencia')
                        remitente = "correo que envia" 
                        contrasena = "**************"
                        destinatario = "correo que recibe"  
                        asunto = "Peligro Sala Servidor 1" 
                        mensaje = "La sala servidor advierte peligro de incendio"
                        
                        email = """From: %s 
                        To: %s 
                        MIME-Version: 1.0 
                        Content-type: text/html 
                        Subject: %s 
                        %s
                        """ % (remitente, destinatario, asunto, mensaje)
                        try:
                            smtp = smtplib.SMTP('smtp.gmail.com', 587)
                            smtp.starttls()
                            smtp.login(remitente, contrasena)
                            smtp.sendmail(remitente, destinatario, email)
                            smtp.quit()
                        except Exception as e:
                           print "No se puede enviar el mensaje"
                           print type(e)
                           print e
                    else:
                        print('Advertencia ya realizada al Personal')
                
                elif time.strftime("%H:%M:%S")=="00:00:00":
                    # Calculando las estadisticas
                    dOrder=sorted(vtemperatura)
                    
                    n=len(dOrder)
                    middle=n/2
                    
                    #Calculo de la mediana 
                    if n%2==0:
                        mediana=(dOrder[middle+1] + dOrder[middle+2]) / 2
                    else:
                        mediana=dOrder[middle+1]*1
                                      
                                      
                    #Calculo de la media
                    media = round(sum(vtemperatura)*1.0/n,2)
                    
                    # Calculo de la moda
                    
                    repetir = 0                                                                         
                    for i in data:                                                                              
                        aparece = data.count(i)                                                             
                        if aparece > repetir:                                                       
                            repetir = aparece                                                       
                                                                                                             
                    moda = []                                                                               
                    for i in data:                                                                              
                        aparece = data.count(i)                                                             
                        if aparece == repetir and i not in moda:                                   
                            moda.append(i)
                    
                    print('Es media noche..')
                    print ('Procedemos al envio de las estadisticas del día')
                    
                    remitente = "correo que envia" 
                    contrasena = "**************"
                    destinatario = "correo que recibe"  
                    asunto = "Estadisticas temperatura Sala Servidor 1" 
                    mensaje = "Las estadisticas de temperatura son: "
                    mensaje += "Mediana: mediana "
                    mensaje += "Media: media "
                    mensaje += "Moda: moda "
                    
                    email = """From: %s 
                    To: %s 
                    MIME-Version: 1.0 
                    Content-type: text/html 
                    Subject: %s 
                    %s
                    """ % (remitente, destinatario, asunto, mensaje)
                    try:
                        smtp = smtplib.SMTP('smtp.gmail.com', 587)
                        smtp.starttls()
                        smtp.login(remitente, contrasena)
                        smtp.sendmail(remitente, destinatario, email)
                        smtp.quit()
                    except: 
                        print "Error: el mensaje no pudo enviarse."
                
                elif data=="f":
                    print('Sistema inteligente de luz apagado')
                
                elif data=="t":
                    print('Sistema inteligente de luz encendido')
                    data = connection.recv(4)
                    vtemperatura.append(data);
                    
                    
        finally:
            # Clean up the connection
            connection.close()
except KeyboardInterrupt:
    print('exiting.')
finally:
    sock.shutdown(socket.SHUT_RDWR)
    sock.close()
