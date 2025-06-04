# 🌧️ Alerta Climático em Tempo Real

Sistema de monitoramento ambiental que detecta riscos de **chuvas fortes** e **enchentes**, emitindo alertas visuais e sonoros com base em sensores físicos.

---

## 🎯 Problema

Com as mudanças climáticas, as chuvas têm se agravado, causando alagamentos repentinos. Este projeto busca mitigar esses efeitos com alertas preventivos.

## 🛠️ Tecnologias e Componentes

<div align="left">
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/arduino/arduino-original.svg" height="30" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/c/c-original.svg" height="30" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/github/github-original.svg" height="30" />
</div>

* Arduino UNO (Wokwi)
* Sensor DHT22 (umidade)
* LDR (luminosidade)
* Potenciômetro (vento)
* Sensor Ultrassônico HC-SR04 (nível da água)
* LED RGB e Buzzer
* Display LCD I2C 16x2

## 📹 Demonstração

🎬 [Ver vídeo no YouTube](https://youtu.be/de9r0YpJRZw)

## 🧪 Simulação no Wokwi

🔗 [Abrir no Wokwi](https://wokwi.com/projects/432795705208443905)

### Como testar:

* Aumente a umidade (DHT22)
* Diminua a luz (LDR)
* Gire o potenciômetro (vento)
* Aproxime um objeto do sensor ultrassônico (nível da água)

## 📖 Níveis de Alerta

| Pontos             | Situação       | LED RGB           | Buzzer       |
| ------------------ | -------------- | ----------------- | ------------ |
| 0                  | Normal         | Desligado         | Desligado    |
| 1                  | Atenção        | Amarelo           | Desligado    |
| 2                  | Possível chuva | Laranja           | Desligado    |
| 3                  | Chuva forte    | Vermelho fixo     | Desligado    |
| ≥4 ou água < 395cm | Enchente ⚠️    | Vermelho piscando | Buzzer ativo |

## 📂 Estrutura do Projeto

* `main.ino`: Código principal com lógica e sensores
* `README.md`: Documentação com instruções, simulação e links úteis

## 👥 Autores

* [Kaua Carvalho (RM566371)](https://github.com/seuUsuarioKaua)
* [Mariana Silva (RM564241)](https://github.com/seuUsuarioMariana)
* [Vitor Tigre (RM561746)](https://github.com/VitorTigre)
