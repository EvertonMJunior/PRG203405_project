# Análise orientada a objeto
> [!NOTE]
> A **análise** orientada a objeto consiste na descrição do problema a ser tratado, duas primeiras etapas da tabela abaixo, a definição de casos de uso e a definição do domínio do problema.

## Descrição Geral do domínio do problema

### Domínio do problema

Os objetos do domínio do problema são:

- Jogo
- Gerador de animais
- Peixe
- Água Viva
- Pinguim
- Linha de pesca

O jogo é composto por um pinguim que está pescando no gelo, por meio de um buraco. Seu objetivo é pescar 20 peixes para ganhar, enquanto se mantém vivo ao evitar os choques com a água viva. O jogador é o pinguim e pode mover a linha de pesca para cima e para baixo utilizando o mouse. Ao encostar a ponta da linha em um peixe, o peixe é pescado e o jogador ganha um ponto. Se o pinguim encostar na água viva, ele perde uma vida. O jogo termina quando o pinguim perde todas as suas vidas. Os peixes e águas vivas são gerados aleatoriamente e controlados pelo gerador de animais, que também controla a taxa de geração dos animais, aumentando progressivamente a dificuldade até um limite. 

### Requisitos Funcionais

- O jogo deve ser capaz de gerar peixes e águas vivas aleatoriamente.
- O jogo deve ser capaz de controlar a taxa de geração dos animais, aumentando progressivamente a dificuldade até um limite.
- O jogo deve ser capaz de verificar se o pinguim encostou na água viva.
- O jogo deve ser capaz de verificar se o pinguim encostou em um peixe.
- O jogo deve ser capaz de verificar se o pinguim perdeu todas as suas vidas.

### Requisitos Não-Funcionais

- O jogo será desenvolvido em C++, utilizando Qt para a interface gráfica, sendo criado com o Qt Creator.

## Diagrama de Casos de Uso

Apresentar o diagram de casos de uso, identificando as funcionalidades do sistema assim como os atores envolvidos
 
## Diagrama de Domínio do problema

<div align="center">
<img src="img/diagrama-uml-dominio.png" width="60%" style="padding: 10px; margin-left: auto; margin-right: auto">
</div>


<div align="center">

[Retroceder](README.md) | [Avançar](projeto.md)

</div>
