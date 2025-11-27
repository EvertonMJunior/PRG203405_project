# Implementação

>[!NOTE] 
 Relatar o processo de implementação do problemas, incluindo as
 ferramentas e bibliotecas utilizadas
>

## Ferramentas e Tecnologias

* **Linguagem:** C++
* **Framework:** Qt 6.10.0 (Widgets + Graphics Framework)
* **Renderização:** QGraphicsView / QGraphicsScene
* **Recursos:** Qt Resource System (.qrc)
* **Padrão utilizado:** Model-View-Controller (MVC)

## Arquitetura da Solução

A implementação segue o padrão **Model-View-Controller (MVC)**, separando claramente estado, interface e lógica do jogo.

### Diagrama de Classes Implementadas

<div align="center">
<img src="./img/diagrama-uml-final.jpeg" width="100%" style="padding: 10px; margin-left: auto; margin-right: auto">
</div>

### Model - Estado e Lógica Central

O singleton *Game* gerencia:

* Vidas
* Contagem de peixes capturados
* Condições de vitória e derrota
* Progressão da dificuldade
* Comunicação com a UI via sinais

### View - Interface e Telas

A interface é controlada por *MainWindow*, que utiliza um *QStackedWidget* para alternar entre quatro telas:

1. Tela Inicial
2. Tela do Jogo
3. Tela de Vitória
4. Tela de Derrota

Componentes utilizados:

* QLabel para textos e imagens
* QPushButton para interação
* Layouts Qt (QVBoxLayout, QHBoxLayout)
* Fonte personalizada carregada via QFontDatabase

O HUD do jogo exibe:

* Vidas (ícones de minhocas)
* Contador de peixes em formato X/20

### Controller - Lógica do Jogo

A classe *GameScene* atua como controlador principal:

* Executa o loop do jogo usando *QTimer*
* Atualiza o movimento das entidades
* Detecta colisões
* Gera sinais de vitória/derrota
* Adiciona e remove objetos da cena conforme necessário

## Entidades do Jogo

As entidades aquáticas utilizam a classe base *AcquaticAnimal*, que combina:

* QObject - para uso de sinais/slots
* QGraphicsPixmapItem - para exibição na cena gráfica

Subclasses especializadas:

* Fish
* Jellyfish

Cada entidade:

* Carrega seu sprite gráfico
* Move-se horizontalmente
* É removida ao sair da área visível

## Mecânica do Jogador

A interação ocorre por meio de uma **linha de pesca**, composta por:

* FishingLine - controla o movimento vertical via mouse
* Worm - ponto usado para detectar capturas
* Penguin - exibe efeitos visuais (como choque ao tocar águas-vivas)

Toda a detecção do movimento da linha e colisões ocorre dentro da *GameScene*.

## Sistema de Atualização (Game Loop)

O jogo utiliza um loop baseado em *QTimer* configurado para aproximadamente 60 FPS (16 ms).

A cada atualização:

1. Entidades são movidas
2. Colisões são verificadas
3. Animais fora da tela são removidos
4. Estado global é atualizado via *Game*
5. O HUD recebe atualizações por sinais

## Colisões

As regras de colisão foram implementadas usando os métodos de interseção do Qt.

### Peixes

* Colisão entre a isca e o peixe incrementa o progresso.

### Águas-vivas

* Colisão com a isca ou com a linha causa perda de vida e ativa o efeito visual do pinguim.

## Sistema de Criação de Entidades (Spawn)

A classe *AnimalGenerator* é responsável por criar peixes e águas-vivas.

* Dois timers controlam o spawn de cada tipo de entidade.
* As taxas de spawn variam conforme o progresso do jogador.
* O controle da dificuldade é feito pela classe *Game*.

## Interface Gráfica

As telas foram criadas utilizando componentes Qt padrão:

* *QLabel* para imagens e textos
* *QPushButton* para interação
* Estilos personalizados via stylesheet (cores, bordas, sombras)
* Fonte BUMBASTIKA aplicada globalmente
* Imagens e fontes incorporadas via .qrc
  

[Clique aqui para assistir à demonstração do nosso jogo](https://youtu.be/bMThfFt74gE?si=Wztq7aDw0d7qwPIa)

<div align="center">

[Retroceder](projeto.md) | [Início](analise.md)

</div>
