'''
Enrique Granado Novaes - 10276914
Gabriel Santos de Oliveira Arruda - 10388025
Paulo Camargo - 32107803
'''
from flask import Flask, jsonify, request
import requests
import socket

app = Flask(__name__)

@app.route("/convertemoeda/<valor_real>", methods=["GET"])

def convertemoeda(valor_real):
  valor_real_int = int(valor_real)
  
  #Caminho das APIs
  path_api_dolar = "https://api.exchangerate-api.com/v4/latest/BRL"
  path_api_euro = "https://api.exchangerate-api.com/v4/latest/BRL"

  ## Obtendo dados a partir das APIs ##
  
  #Dólar
  print("\n######## DOLAR ########\n")
  response_dolar = requests.get(path_api_dolar)
  print('API de Dólar conectada com sucesso!')
  
  data_dolar = response_dolar.json()
  taxa_dolar = data_dolar["rates"]["USD"]
  valor_dolar = valor_real_int * taxa_dolar
  print('Valor Dólar = ',valor_dolar)
  print('Taxa Dólar = ',taxa_dolar)
  
  #Euro
  print("\n######## EURO ########\n")
  response_euro = requests.get(path_api_euro)
  print('API de Euro conectada com sucesso!')
  
  data_euro = response_euro.json()
  taxa_euro = data_euro["rates"]["EUR"]
  valor_euro = valor_real_int * taxa_euro
  print('Taxa Euro = ',taxa_euro)
  print('Valor Euro = ',valor_euro)

  #Estrutura do arquivo JSON
  return {
    "conversao": [{
      "real": valor_real_int, 
      "dolar": valor_dolar, 
      "euro": valor_euro, 
      "maquina": socket.gethostname() #<hostname_backend>
    }]
  }

def conversao():
  valor_real = float(request.args.get("valor_real"))
  resultado = convertemoeda(valor_real)
  return jsonify(resultado)

if __name__ == "__main__":
  app.run(host="0.0.0.0", port=5000)
