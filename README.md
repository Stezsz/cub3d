ReadMe TODO

## Nota sobre Valgrind e MLX/X11

O Valgrind pode mostrar o erro `Syscall param writev(vector[0]) points to uninitialised byte(s)` ao rodar o cub3d.
Esse erro é causado internamente pela MLX/X11 e **não indica bug ou vazamento de memória no nosso código**.
Podemos ignorar esse warning, pois é esperado em projetos gráficos usando MLX.

> ✅ **Final Grade: 105/100**
