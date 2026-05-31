import pandas as pd
import matplotlib.pyplot as plt

# Lê o CSV
dados = pd.read_csv("dados_paciente.csv")

dias = dados["dia"]
sistolica = dados["sistolica"]
diastolica = dados["diastolica"]

# Criar gráfico
plt.figure()

# Linhas com pontos
plt.plot(dias, sistolica, marker='o', color='red', label="Sistólica")
plt.plot(dias, diastolica, marker='o', color='blue', label="Diastólica")

# Mostrar valores nos pontos
for i in range(len(dias)):
    plt.text(dias[i], sistolica[i] + 2, str(sistolica[i]),
             ha='center', color='red')

    plt.text(dias[i], diastolica[i] - 4, str(diastolica[i]),
             ha='center', color='blue')

# Títulos e eixos
plt.title("Evolução da Pressão Arterial")
plt.xlabel("Dias")
plt.ylabel("Pressão (mmHg)")

# Eixo X como Dia 1, Dia 2...
plt.xticks(dias, ["Dia " + str(int(d)) for d in dias])

# Legenda
plt.legend()

# Mostrar gráfico
plt.grid(True)
plt.show()