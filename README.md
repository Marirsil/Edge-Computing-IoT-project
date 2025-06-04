# 🌧️ Alerta Climático em Tempo Real

Sistema de monitoramento ambiental que detecta possíveis riscos de **chuva forte** e **enchentes**, emitindo alertas visuais (LED RGB) e sonoros (buzzer), com base em sensores de umidade, luminosidade, vento e nível da água.

---

## 🎯 Problema

Com as mudanças climáticas, as chuvas têm se agravado, causando **alagamentos repentinos** e colocando comunidades em risco. Esse projeto visa mitigar os efeitos dessas situações por meio de alertas preventivos em tempo real.

---

## 🛠️ Tecnologias e Componentes Utilizados:

<div align="left">
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/arduino/arduino-original.svg" height="40" alt="arduino logo" />
  <img width="12" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/c/c-original.svg" height="40" alt="c logo" />
  <img width="12" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/github/github-original.svg" height="40" alt="github logo" />
</div>

* **Arduino UNO (Simulado no Wokwi)**
* Sensor **DHT22** (umidade)
* **LDR** (luminosidade)
* **Potenciômetro** (simula vento)
* Sensor **ultrassônico HC-SR04** (nível da água)
* **LED RGB**
* **Buzzer**
* **Display LCD I2C 16x2**

---

## 📹 Demonstração

🎬 [Clique aqui para assistir ao vídeo explicativo](https://youtu.be/de9r0YpJRZw)

---

## 🧪 Simulação no Wokwi

🔗 [Acesse o projeto no simulador Wokwi](https://wokwi.com/projects/432795705208443905)

### Como simular:

1. Aumente o valor do potenciômetro (vento).
2. Aumente a umidade com o DHT22.
3. Diminua a luminosidade (LDR) para simular céu nublado.
4. Aproxime um objeto do sensor ultrassônico para simular aumento no nível da água.

---

## 🧾 Organização do Código

* `main.ino`: código principal do Arduino com toda a lógica de leitura de sensores, pontuação e alertas.
* `README.md`: documentação explicando o funcionamento, simulação e links úteis.

---

## 📖 Níveis de Alerta

| Pontos             | Situação               | LED RGB           | Buzzer       |
| ------------------ | ---------------------- | ----------------- | ------------ |
| 0                  | Normal                 | Desligado         | Desligado    |
| 1                  | Atenção                | Amarelo           | Desligado    |
| 2                  | Possibilidade de chuva | Laranja           | Desligado    |
| 3                  | Chuva forte            | Vermelho fixo     | Desligado    |
| ≥4 ou água < 395cm | Enchente ⚠️            | Vermelho piscando | Buzzer ativo |

---

## 📂 Como baixar e rodar

1. Baixe este repositório como `.zip` ou faça um fork.
2. Acesse o link do simulador Wokwi.
3. Cole o conteúdo do código no editor.
4. Inicie a simulação.

---

## 👥 Autores

* [Kaua Carvalho (RM566371)](https://github.com/seuUsuarioKaua)
* [Mariana Silva (RM564241)](https://github.com/seuUsuarioMariana)
* [Vitor Tigre (RM561746)](https://github.com/VitorTigre)
