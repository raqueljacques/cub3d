#!/bin/bash

EXECUTABLE="./cub3d"

GOOD_MAPS_DIR="./maps/good"
BAD_MAPS_DIR="./maps/bad"

COLOR_GREEN='\033[0;32m'
COLOR_RED='\033[0;31m'
COLOR_YELLOW='\033[1;33m'
COLOR_NC='\033[0m'

passed_tests=0
failed_tests=0

run_test() {
    local map_path=$1
    local expected_exit_code=$2
    local test_type=$3

    echo -e "${COLOR_YELLOW}Testando: ${map_path}${COLOR_NC}"

    output=$($EXECUTABLE $map_path 2>&1)
    actual_exit_code=$?

    if [ $expected_exit_code -eq 0 ]; then
        if [ $actual_exit_code -eq 0 ]; then
            echo -e "  └─ ${COLOR_GREEN}OK: O programa executou com sucesso, como esperado.${COLOR_NC}"
            ((passed_tests++))
        else
            echo -e "  └─ ${COLOR_RED}FALHA: O programa falhou inesperadamente com o código de saída ${actual_exit_code}.${COLOR_NC}"
            echo -e "     Saída: $output"
            ((failed_tests++))
        fi
    else
        if [ $actual_exit_code -ne 0 ]; then
            echo -e "  └─ ${COLOR_GREEN}OK: O programa detectou um erro, como esperado.${COLOR_NC}"
            ((passed_tests++))
        else
            echo -e "  └─ ${COLOR_RED}FALHA: O programa deveria ter falhado, mas executou com sucesso.${COLOR_NC}"
            ((failed_tests++))
        fi
    fi
}

echo "Compilando o projeto..."
make re > /dev/null
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${COLOR_RED}Erro de compilação. Abortando testes.${COLOR_NC}"
    exit 1
fi

echo -e "\n--- Iniciando testes com mapas VÁLIDOS (esperando sucesso) ---"
for map_file in $GOOD_MAPS_DIR/*.cub; do
    if [ -f "$map_file" ]; then
        run_test "$map_file" 0
    fi
done

echo -e "\n--- Iniciando testes com mapas INVÁLIDOS (esperando erro) ---"
for map_file in $BAD_MAPS_DIR/*.cub; do
    if [ -f "$map_file" ]; then
        run_test "$map_file" 1
    fi
done

echo -e "\n--- Resumo dos Testes ---"
echo -e "${COLOR_GREEN}Testes que passaram: $passed_tests${COLOR_NC}"
if [ $failed_tests -gt 0 ]; then
    echo -e "${COLOR_RED}Testes que falharam: $failed_tests${COLOR_NC}"
    exit 1
else
    echo -e "${COLOR_GREEN}Todos os testes passaram! ✨${COLOR_NC}"
    exit 0
fi