from flask import redirect, url_for, render_template, request
from flask.ext.login import current_user, login_required
import feedparser
from peewee import *

# Esta linea la agrego ya que sin estar logueado y se escribe /index
# en el navegador, salta error por no tener el login manager.
from auth import lm  # <-
from app import app, database
from models import User, Feed


@app.route('/index')
@login_required
def index():
    return render_template('index.html')


@app.route('/login')
def login_html():
    return render_template('login.html')


@app.route("/rss/<feed>")
@login_required
def rss(feed):
    # Con el id del feed obtengo el feed para mostrarlo con rss.
    try:
        feed_new = Feed.get(Feed.id == feed)
    except:
        return redirect(url_for('index'))
    feed = feedparser.parse(feed_new.url)
    return render_template('rss.html', feed=feed_new, entries=feed.entries)


@app.route('/newfeed', methods=['GET', 'POST'])
@login_required
def new_feed():
    if request.method == 'GET':
        return render_template('newfeed.html')
    # Si es POST es porque se ha enviado un formulario al servidor y espera
    # respuesta.
    else:
        # Obtiene del formulario la URL del feed ingresado.
        url = request.form.get('feed_url')
        # Ingreso al objeto User para agregarle los feeds asociados a su
        # cuenta.
        user = User.get(User.id == current_user.get_id())
        # Verifico si la URL es correcta y caso contrario muestro mensaje
        # de error. Permanezco en newfeed.
        try:
            d = feedparser.parse(url)
        except:
            return render_template(
                'newfeed.html',
                error_message='URL invalida')
        # Verifico que no exista ya el feed en los feeds del usuario para
        # que no hayan duplicados. Muestro el index.
        for feeds in user.feeds:
            if feeds.url == url:
                return render_template(
                    'index.html',
                    message='El Feed ya esta agregado')
        # Es excluyente que tenga titulo pero no necesariamente descripcion.
        try:
            a = d.feed.title
            try:
                f = d.feed.description
            except AttributeError:
                f = ''
            # Almaceno el feed para el usuario en la db.
            feed = Feed.create(
                user=user,
                title=a,
                url=url,
                description=f)
        except:
            return render_template(
                'newfeed.html',
                error_message='URL invalida')
        return redirect(url_for('index'))


@app.route('/delete_feed/<feed>')
@login_required
def delete_feed(feed):
    # Verifico que el feed exista y elimino. Recordar que siempre los
    # id de los feeds no dan informacion del usuario. Por lo tanto
    # dos feeds iguales pero de distintos usuarios tienen distintos ids.
    try:
        feed_new = Feed.get(Feed.id == feed)
    except:
        return 'Error'
    feed_new.delete_instance()
    # Muestro el index.
    return redirect(url_for('index'))


if __name__ == '__main__':
    database.connect()
    database.create_tables([User, Feed], safe=True)
    app.run()
