# Codigos-OpenGL-Computacao-Grafica

Códigos utilizando OpenGL realizados na disciplina de Computação Gráfica (lista de exercícios 3).

## Como executar

Para executar os códigos, é necessário ter o OpenGL instalado na máquina. Para isso, basta seguir os passos abaixo:

### Instalação das bibliotecas

```sh
sudo apt-get update

sudo apt-get install freeglut3

sudo apt-get install freeglut3-dev

sudo apt-get install binutils-gold

sudo apt-get install g++ cmake

sudo apt-get install libglew-dev

sudo apt-get install g++

sudo apt-get install mesa-common-dev

sudo apt-get install build-essential

sudo apt-get install libglew1.5-dev libglm-dev
```

## Compilação e execução

Para compilar e executar os códigos, basta seguir os passos abaixo:

```sh
cd <pasta do código>

g++ <nome do código>.cpp -o <nome do executável> -lstdc++ -lGL -lglut -lGLU

./<nome do executável>
```