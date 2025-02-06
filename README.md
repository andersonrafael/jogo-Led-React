

https://github.com/user-attachments/assets/67a54276-92e5-4d2a-bcd5-b9c07885801c

Objetivo do Jogo:
O objetivo do jogo é testar a rapidez do jogador em apertar o botão correto, quando a cor correspondente do LED aparecer. 
O tempo de reação é medido em milissegundos e a cada rodada, o jogador tenta superar seu próprio recorde.

Componentes Utilizados:
Placa BitDogLab com microcontrolador Raspberry Pi Pico W
LEDs RGB 5050 WS2812B (conectados aos pinos 13, 11 e 12)
Botões (A e B, conectados aos pinos 5 e 6)
Buzzer (conectado ao pino 21)

Funcionamento:
Inicialização do Jogo:

O jogo começa com um som de introdução (notas simples) e uma explicação das regras.
O jogador deve apertar os botões conforme a cor do LED acesa.
Cor do LED e Resposta do Jogador:

O LED acende em uma das cores do arco-íris, e o jogador deve apertar o botão correto:
Vermelho, Laranja, Verde, Azul → Botão B
Amarelo, Anil, Violeta → Botão A
Se o jogador apertar o botão errado, um som de erro é tocado.
Medindo o Tempo de Reação:

O tempo de reação é registrado, e o som é tocado conforme o tempo: um tom de sucesso se o tempo for rápido, ou um som de erro se o jogador apertar o botão errado.
O jogo acompanha o tempo mais rápido de cada rodada e o melhor tempo de reação global.
Recordes:

A cada rodada, o jogo verifica se o jogador quebrou seu recorde pessoal.
Quando um novo recorde global é alcançado, um som de celebração é tocado.
Histórico de Melhores Tempos:

Ao fim de 5 rodadas, o jogo exibe o histórico dos 5 melhores tempos de reação, permitindo ao jogador ver seu progresso.
Reinício do Jogo:

Após 5 rodadas, o jogo reinicia automaticamente após 10 segundos, com um efeito de LEDs piscando e o histórico de tempos sendo mostrado novamente.


Recursos Adicionais:
Efeitos Visuais: O LED RGB cria um efeito de arco-íris dinâmico para a resposta do jogador.
Sonoridade: O buzzer toca diferentes sequências de som para indicar sucesso, erro ou a superação de um recorde.
Melhoria de Performance: O jogo mantém um histórico dos melhores tempos dos últimos jogos e o jogador pode tentar superá-los a cada nova rodada.


link do Projeto no simulador wokwi:
https://wokwi.com/projects/422175428422596609
![projeto final embarcatech](https://github.com/user-attachments/assets/02588312-e27e-433a-8bf7-2fe0f6811440)

 * O projeto no simulador wokwi teve o led RGB substituido pelos leds VERMELHO, AZUL E VERDE por critério de funcionalidades do simulador.
