from flask import Flask

app = Flask(__name__)

@app.route('/turnon', methods=['GET'])
def turn_on():
    return 'ON'

if __name__ == '__main__':
    app.run()
