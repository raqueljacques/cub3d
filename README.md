# CUB3D — 42RJ Project

![C](https://img.shields.io/badge/language-C-blue) ![status](https://img.shields.io/badge/status-in%20progress-yellow)

## ✨ Objetivo
Projeto de um jogo 3D simples, inspirado no clássico Wolfenstein 3D, utilizando a técnica de raycasting. O objetivo é aplicar conceitos de gráficos computacionais, manipulação de imagens e desenvolvimento de jogos em C.

## 🛠️ Compilação
Para compilar o projeto, utilize o seguinte comando no terminal:

```bash
make
```

## 🚀 Execução
Para executar o jogo, utilize o comando:

```bash
./cub3D <mapa.cub>
```

## ⚠️ Possíveis Problemas de Compilação

### Erro de Permissão na MinilibX
Se você encontrar o erro `./configure: Permissão negada` durante a compilação, execute o seguinte comando para corrigir as permissões:

```bash
chmod +x libraries/minilibx/configure
```

Em seguida, tente compilar novamente:

```bash
make
```

## 📁 Estrutura
- `includes/` - Arquivos de cabeçalho.
- `libraries/libft/` - Biblioteca auxiliar de funções em C.
- `libraries/minilibx/` - Biblioteca gráfica MiniLibX.
- `maps/` - Exemplos de mapas para o jogo.
- `src/` - Código-fonte do projeto.
- `Makefile` - Script de compilação.

## 🤝 Autores

- Ana Carla — [@anacpp](https://github.com/anacpp)
- Raquel — [@raqueljacques](https://github.com/raqueljacques)

## 📄 Licença

Projeto educacional para a 42 rj. Sem fins lucrativos.