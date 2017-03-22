# **Introduccion**

En este laboratorio se crea una aplicacion web para leer actualizaciones de informacion de diferentes medios, feeds. Provee actualizaciones mediante protocolos Atom y RSS. Se trabaja con Python que es un lenguaje multiparadigma y con Flaks que es un framework micro web.

Flask se modulariza segun la forma Model - Template - View, donde models.py y templates.py nos es otorgado como codigo base por la catedra y View va en runserver.py implementado por nosotros.


# **app**

Define la aplicacion Flask y la base de datos. 


# **auth**

Crea el objeto Oauth con app y los diccionarios con los datos de tokens, id, secreto, etc, que son datos propios de las APIs para el desarrollo.

Crea el login manager con app y lo inicializa.

A continuacion se describen las funciones de autentificacion pertenecientes a este modulo.


## load_user

Corrobora que el usuario actual sea correcto, caso contrario borra la sesion.


## root

Es la pagina principal. Si hay alguna cuenta abierta entonces redirige a su index, caso contrario redirige a login_html. Ya que depende de los token de sesion se decidio incluirlo en este modulo.


## login

Recibe el parametro proveedor, dependiendo de el se procede a pedir la autorizacion de acceso de informacion de la cuenta. El usuario debe ingresar a su cuenta del proveedor si no esta abierta, lo puede hacer en el mismo proceso. Si en el URL se escribe un proveedor que no esta definido entonces redirige a login_html (se explica en el modulo server.py).


## authorized

Recibe el parametro proveedor, se consulta si el proveedor devolvio una respuesta favorable para compartir informacion, caso contrario retorna Not Found 404. Si la respuesta es positiva entonces apila la sesion del token correspondiente y obtiene los valores.

En particular, mi cuenta de Github no me daba email ni id, para el id que realmente se necesitaba para crear un id de usuario unico para la db le otorgo el campo login que me retornaba en data.

Para hacer mas comoda la vista de esta funcion se decide sacar los else y directamente colocar return si los proveedores no retornaban nada. Ademas el campo email era el mismo, entonces se agrega su obtencion despues de los condicionales.

Todos los campos obtenidos se castean a string por si alguno es None.

Observaciones:

+ Dropbox pide autorizacion cada vez que se quiere loguear usandola.

+ Github tiene la URI callback unicamente como localhost.

+ Google y Dropbox permiten multiples URIs callback y se agrego tanto localhost como la IP de localhost (127.0.0.1).

+ El puerto sobre el que se trabaja es siempre 5000.


## get_<proveedor>_oauth_token

Obtiene los token del proveedor correspondiente. Se utiliza internamete en funciones del framework.


## logout

Desapila el token segun el proveedor que este en la sesion y desloguea al usuario. Redirige a login. Requiere que el usuario este logueado.


# **runserver**

Contiene todas las View y funciones y aca es donde se ejecuta la aplicacion web.

Observaciones:

+ Todas las siguientes funciones y tambien logout requieren que el usuario este logueado, esto se verifica con @login_required de flask.ext.login library.


## index y login_html

Renderizan los html index y login respectivamente.


## rss

Interfaz del feed, cargando el feed y las entradas que tiene.


## new_feed

Crea un feed con el metodo HTTP llamado POST (boton submit), caso contrario (por ser HTTP 1.1, seria GET) renderiza el template feed.

Para crearlo primero obtiene la url del formulario, luego obtiene el usuario actual para asignarle la feed nueva, seguidamente intenta parsear con feedparser la url ingresada, si no puede renderiza el html nuevamente lanzando un mensaje de error acerca de la URL. Luego verifica que no exista ya el feed, si esta entonces renderiza index e indica con un mensaje que ya existia. 

Verifica el titulo y la descripcion y crea la feed llamando al objeto Feed para almacenarla, si nada de esto se pudo entonces renderiza newfeed y lanza mensaje de error. Al terminar redirige a index si la feed se agrego con exito.


## delete_feed

Verifico que el feed exista y elimino. Recordar que siempre los id de los feeds no dan informacion del usuario. Por lo tanto dos feeds iguales pero de distintos usuarios tienen distintos ids. Al finalizar muestro el index.


## main

Crea la base de datos y corre la aplicacion web.


# **Compilacion y ejecucion**

Instalar venv.

Instalar las librerias con los links provee la catedra usando pip o con install "requirements.txt".

$ cd .../grupo18/Lab4/

$ source venv/bin/activate

$ python runserver.py


# **Punto extra**

Se añade login de Dropbox.


# **Librerias Auxiliares**

ipdb para debug.

pep8 para estilo.


# **Bibligrafia**

Recomendada por la catedra.

StackOverflow