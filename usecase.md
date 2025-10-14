# Caso de uso 1: Iniciar o jogo

| Requisito            | Explicação                                           |     |     |     |
| -------------------- | ---------------------------------------------------- | --- | --- | --- |
| Objetivo:            | Permitir que o ator inicie o jogo.                |     |     |     |
| Requisitos:          | -                                                    |     |     |     |
| Atores:              | Usuário                                              |     |     |     |
| Prioridade:          | Alta                                                 |     |     |     |
| Pré-condições:       | - Não ter iniciado o jogo;                           |     |     |     |
| Freqüência de uso:   | Eventual.                                            |     |     |     |
| Criticalidade:       | Alta                                                 |     |     |     |
| Condição de Entrada: | O ator clicar no botão "Jogar" no menu principal. |     |     |     |
| Fluxo Principal:     | - O jogo apresenta a tela inicial contendo um botão "Jogar". <br> - Para iniciar o jogo, o ator deve clicar no botão. <br> - O jogo vai iniciar com um pinguim com 3 vidas na posição inicial e após 1 segundo, o gerador de animais deve ser iniciado, com uma taxa de geração de 2 segundos por peixe e 4 segundos por água viva.<br> - O ator tem a opção de mover o mouse para cima e para baixo e a linha de pesca deve seguir o movimento vertical do mouse.<br> - Quando a ponta da linha de pesca encostar em um peixe, o peixe será pescado e o ator ganha um ponto.<br> - Quando uma água viva encostar em qualquer parte da linha, o pinguim leva um choque e o ator perde uma vida.<br> - Se o ator atingir 20 peixes acumulados, o jogo termina e ele ganha a partida.<br> - Se o ator perder todas as suas vidas, o jogo termina e este perde a partida, podendo reiniciar o jogo clicando no botão "Reiniciar" no menu final.<br> - A cada 5 peixes pescados, a taxa de geração dos animais deve ser diminuída em 0.5 segundos, até um limite de 0.5 segundos por peixe e 1 segundo por água viva.                                                  |     |     |     |
