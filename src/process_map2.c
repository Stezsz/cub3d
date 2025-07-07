/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:19:33 by tborges-          #+#    #+#             */
/*   Updated: 2025/07/07 19:41:59 by tborges-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdbool.h>
#include <string.h>

// Verifica se um caractere é válido para o mapa
// static bool is_valid_map_char(char c)
// {
//     return (c == '0' || c == '1' || c == 'N' ||
//             c == 'S' || c == 'E' || c == 'W');
// }

// Verifica se uma linha tem apenas '1' e espaços
static bool is_wall_line(const char *line)
{
    int i = 0;
    bool found_content = false;

    while (line[i])
    {
        if (line[i] == '\n')
            break;
        if (line[i] != '1' && line[i] != ' ')
            return false;
        if (line[i] == '1')
            found_content = true;
        i++;
    }
    return found_content; // Garante que pelo menos um '1' foi encontrado
}

// Debug: imprime o mapa para verificar como foi lido
static void debug_print_map(char **map)
{
    int i = 0;
    printf("--- MAP AS READ ---\n");
    while (map[i])
    {
        printf("Line %d: [%s]\n", i, map[i]);
        i++;
    }
    printf("------------------\n");
}

bool validate_map_walls(char **map)
{
    int i, j, height, width;

    // Debug: imprimir o mapa como foi lido
    debug_print_map(map);

    // Contar linhas
    for (height = 0; map[height]; height++);

    // Verificar primeira e última linha
    if (!is_wall_line(map[0]) || !is_wall_line(map[height - 1]))
        return false;

    // Encontrar a largura máxima (ignorando '\n')
    width = 0;
    for (i = 0; i < height; i++)
    {
        int len = 0;
        while (map[i][len] && map[i][len] != '\n')
            len++;
        if (len > width)
            width = len;
    }

    // Verificar bordas laterais
    for (i = 1; i < height - 1; i++)
    {
        // Encontrar primeiro caractere não-espaço
        j = 0;
        while (map[i][j] && (map[i][j] == ' ' || map[i][j] == '\t'))
            j++;

        // Verificar se é uma parede
        if (map[i][j] != '1')
            return false;

        // Encontrar último caractere não-espaço antes de '\n'
        j = 0;
        while (map[i][j] && map[i][j] != '\n')
            j++;
        j--; // Voltar para último caractere antes de '\n'

        // Retroceder enquanto for espaço
        while (j >= 0 && (map[i][j] == ' ' || map[i][j] == '\t'))
            j--;

        if (j >= 0 && map[i][j] != '1')
            return false;
    }

    return true;
}

int	get_max_map_width(char **map)
{
    int max = 0;
    int len;
    int i = 0;
    while (map[i])
    {
        len = ft_strlen(map[i]);
        if (len > max)
            max = len;
        i++;
    }
    return (max);
}

void	normalize_map(char **map)
{
    int max = get_max_map_width(map);
    int i = 0;
    while (map[i])
    {
        int len = ft_strlen(map[i]);
        if (len < max)
        {
            char *new = malloc(max + 1);
            ft_memcpy(new, map[i], len);
            ft_memset(new + len, ' ', max - len);
            new[max] = '\0';
            free(map[i]);
            map[i] = new;
        }
        i++;
    }
}
