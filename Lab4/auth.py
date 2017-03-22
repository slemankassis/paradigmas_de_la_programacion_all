from flask import redirect, url_for, render_template, session, abort
from flask.ext.login import LoginManager, login_user, logout_user, \
    login_required
from flask_oauthlib.client import OAuth

from app import app
from models import User


oauth = OAuth(app)

lm = LoginManager(app)
lm.init_app(app)


github = oauth.remote_app(
    'github',
    consumer_key='337d9f16264a959aa3da',
    consumer_secret='ae0180618cc2a799bbde41022f76d9df1cfe0282',
    request_token_params={'scope': 'user:email'},
    base_url='https://api.github.com/',
    request_token_url=None,
    access_token_method='POST',
    access_token_url='https://github.com/login/oauth/access_token',
    authorize_url='https://github.com/login/oauth/authorize'
)


google = oauth.remote_app(
    'google',
    consumer_key=(
        '632779281731-lmfflauu5erirh3676e8d7dmm4bgalc8.'
        'apps.googleusercontent.com'),
    consumer_secret='yO_l9wUG_Cr5e6ul0PC2qmQR',
    request_token_params={'scope': 'email'},
    base_url='https://www.googleapis.com/oauth2/v1/',
    request_token_url=None,
    access_token_method='POST',
    access_token_url='https://accounts.google.com/o/oauth2/token',
    authorize_url='https://accounts.google.com/o/oauth2/auth',
)


dropbox = oauth.remote_app(
    'dropbox',
    consumer_key='29shr51verrf4fk',
    consumer_secret='8frgy06tq169dpu',
    request_token_params={},
    base_url='https://www.dropbox.com/1/',
    request_token_url=None,
    access_token_method='POST',
    access_token_url='https://api.dropbox.com/1/oauth2/token',
    authorize_url='https://www.dropbox.com/1/oauth2/authorize',
)


@lm.user_loader
def load_user(uid):
    try:
        return User.get(User.id == uid)
    except User.DoesNotExist:
        session.clear()
        return None


@app.route('/')
def root():
    if (
        'github_token' in session
            or 'google_token' in session
            or 'dropbox_token' in session):
        return redirect(url_for('index'))
    else:
        return redirect(url_for('login_html'))


@app.route('/login/<provider>')
def login(provider):
    if provider == 'github':
        return github.authorize(callback=url_for(
            'authorized',
            provider='github',
            _external=True))
    if provider == 'google':
        return google.authorize(callback=url_for(
            'authorized',
            provider='google',
            _external=True))
    if provider == 'dropbox':
        return dropbox.authorize(callback=url_for(
            'authorized',
            provider='dropbox',
            _external=True))
    else:
        return redirect(url_for('login_html'))


@app.route('/authorized/<provider>')
def authorized(provider):
    if provider == 'github':
        resp = github.authorized_response()
        if resp is None:
            return abort(404)
        session['github_token'] = (resp['access_token'], '')
        me = github.get('user')
        user_social_id = 'github' + str(me.data['login'])
        user_name = str(me.data['name'])

    if provider == 'google':
        resp = google.authorized_response()
        if resp is None:
            return abort(404)
        session['google_token'] = (resp['access_token'], '')
        me = google.get('userinfo')
        user_social_id = 'google' + str(me.data['id'])
        user_name = str(me.data['name'])

    if provider == 'dropbox':
        resp = dropbox.authorized_response()
        if resp is None:
            return abort(404)
        session['dropbox_token'] = (resp['access_token'], '')
        me = dropbox.get('account/info')
        user_social_id = 'dropbox' + str(me.data['uid'])
        user_name = str(me.data['display_name'])

    user_email = str(me.data['email'])
    try:
        user = User.get(User.social_id == user_social_id)
    except User.DoesNotExist:
        user = User.create(
            social_id=user_social_id,
            nickname=user_name,
            email=user_email)

    login_user(user)
    return redirect(url_for('index'))


@github.tokengetter
def get_github_oauth_token():
    return session.get('github_token')


@google.tokengetter
def get_google_oauth_token():
    return session.get('google_token')


@dropbox.tokengetter
def get_dropbox_oauth_token():
    return session.get('dropbox_token')


@app.route('/logout')
@login_required
def logout():
    if 'github_token' in session:
        session.pop('github_token', None)
    if 'google_token' in session:
        session.pop('google_token', None)
    if 'dropbox_token' in session:
        session.pop('dropbox_token', None)
    logout_user()
    return redirect(url_for('login_html'))
