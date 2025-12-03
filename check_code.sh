#!/bin/bash
# Script alternativo de verificação estática de código
# Simula funcionalidade básica do cppcheck enquanto não está instalado

echo "========================================"
echo "  Verificação Estática de Código"
echo "  (Alternativa ao cppcheck)"
echo "========================================"
echo ""

errors=0
warnings=0

# Verificar include guards
echo "[1/5] Verificando include guards..."
for file in include/*.h; do
    if ! grep -q "#ifndef.*_H_" "$file"; then
        echo "  WARNING: $file pode não ter include guard correto"
        ((warnings++))
    fi
done

# Verificar memória dinâmica não gerenciada
echo "[2/5] Verificando gerenciamento de memória..."
if grep -rn "malloc\|calloc\|realloc\|free" src/ include/ 2>/dev/null; then
    echo "  WARNING: Uso de malloc/free encontrado - considere usar RAII/smart pointers"
    ((warnings++))
fi

# Verificar funções inseguras
echo "[3/5] Verificando funções potencialmente inseguras..."
if grep -rn "strcpy\|strcat\|sprintf\|gets" src/ 2>/dev/null; then
    echo "  WARNING: Funções inseguras encontradas"
    ((warnings++))
fi

# Verificar TODOs e FIXMEs
echo "[4/5] Verificando marcadores de código..."
todos=$(grep -rn "TODO\|FIXME\|XXX\|HACK" src/ include/ 2>/dev/null | wc -l)
if [ "$todos" -gt 0 ]; then
    echo "  INFO: $todos marcador(es) TODO/FIXME encontrado(s)"
fi

# Verificar complexidade básica
echo "[5/5] Verificando funções muito longas..."
for file in src/*.cpp; do
    lines=$(wc -l < "$file")
    if [ "$lines" -gt 500 ]; then
        echo "  WARNING: $file tem $lines linhas (considere refatorar)"
        ((warnings++))
    fi
done

echo ""
echo "========================================"
echo "Resumo:"
echo "  Erros: $errors"
echo "  Avisos: $warnings"
if [ "$errors" -eq 0 ] && [ "$warnings" -eq 0 ]; then
    echo "  ✅ Nenhum problema encontrado!"
else
    echo "  ⚠️  Revise os avisos acima"
fi
echo "========================================"
echo ""
echo "NOTA: Para análise completa, instale o cppcheck:"
echo "  pacman -S mingw-w64-x86_64-cppcheck"
echo "  make static-analysis"
