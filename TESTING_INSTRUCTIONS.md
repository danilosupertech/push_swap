Eu criei o script de teste `test_performance.sh`.

Para usá-lo, você precisará fazer duas coisas:

1.  **Torná-lo executável:**
    ```bash
    chmod +x test_performance.sh
    ```

2.  **Executar o script:**
    ```bash
    ./test_performance.sh
    ```

O script fará o seguinte:
- Compilará o `push_swap` usando `make`.
- Tentará compilar o `checker` com `make bonus` (se disponível) para validar
    a correção das operações (recomendado). Nota: `make bonus` compila apenas o
    `checker`.
- Executará uma série de testes, desde listas simples até uma lista com 100 números aleatórios.
- Para cada teste, ele verificará se as instruções geradas pelo seu `push_swap` ordenam a lista corretamente.
- Ele informará se cada teste passou (OK) ou falhou (KO) e mostrará o número de instruções usadas.

Isso ajuda a garantir que tudo está funcionando como esperado. Se houver erro,
o script mostra detalhes do caso que falhou.
