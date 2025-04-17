/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:13:49 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 14:18:27 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

#include "get_next_line.h"

static void	trim_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}
}

static int	read_map_lines(int fd, t_list **lines_list, t_game *game)
{
	char	*line;
	t_list	*new_node;
	int		gnl_result;

	gnl_result = 1;
	while (gnl_result > 0)
	{
		gnl_result = get_next_line(fd, &line);
		if (gnl_result < 0)
			return (-1);
		if (gnl_result == 0 && ft_lstsize(*lines_list) == 0)
		{
			free(line); // GNL мог выделить память даже для пустого конца файла
			break; // Выходим, список останется пустым
		}
		trim_newline(line); // Убираем '\n' с конца строки
		new_node = ft_lstnew(line); // Создаем новый узел списка с прочитанной строкой
		if (!new_node)
		{
			free(line); // Освобождаем строку, если не удалось создать узел
			ft_lstclear(lines_list, free); // Очищаем уже созданную часть списка
			return (-1); // Ошибка выделения памяти
		}
		ft_lstadd_back(lines_list, new_node); // Добавляем узел в конец списка
		if (gnl_result == 0) // Достигнут конец файла
			break;
	}
	return (0); // Успех
}

/*
 * @brief Конвертирует связный список строк в двумерный массив (grid) в t_game.
 * Также определяет высоту и ширину карты.
 */
static int	convert_list_to_grid(t_list *lines_list, t_game *game)
{
	int		i;
	t_list	*current;

	game->map.height = ft_lstsize(lines_list);
	if (game->map.height == 0)
		return (-1); // Список пуст (пустая карта)
	game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (-1); // Ошибка выделения памяти
	game->map.width = ft_strlen((char *)lines_list->content); // Ширина по первой строке
	i = 0;
	current = lines_list;
	while (current != NULL)
	{
		// Не используем strdup, так как GNL уже выделил память,
		// и мы передали ее в ft_lstnew. Просто копируем указатель.
		game->map.grid[i] = (char *)current->content;
		// Важно: теперь free для списка не должно освобождать content,
		// так как он используется в grid.
		// Проверка на прямоугольность будет в map_validation_check.c
		current = current->next;
		i++;
	}
	game->map.grid[i] = NULL; // Завершаем массив указателей NULL'ом
	return (0); // Успех
}

/*
 * @brief Основная функция чтения карты. Открывает файл, читает строки,
 * конвертирует в grid и сохраняет в структуру game.
 */
void	read_map(char *filename, t_game *game)
{
	int		fd;
	t_list	*lines_list;
	int		read_status;
	int		convert_status;

	lines_list = NULL;
	fd = open(filename, O_RDONLY); // Открываем файл только для чтения
	if (fd < 0)
		exit_error(game, "Could not open map file."); // Ошибка открытия файла

	read_status = read_map_lines(fd, &lines_list, game); // Читаем строки в список
	close(fd); // Закрываем файл сразу после чтения
	if (read_status < 0)
	{
		ft_lstclear(&lines_list, free); // Очищаем список, если чтение не удалось
		exit_error(game, "Error reading map file or allocating memory.");
	}
	if (lines_list == NULL) // Проверка на случай, если файл был пуст
		exit_error(game, "Map file is empty.");

	convert_status = convert_list_to_grid(lines_list, game); // Конвертируем список в grid

	// Теперь очищаем ТОЛЬКО узлы списка, НЕ их содержимое (content),
	// так как строки теперь используются в game->map.grid.
	ft_lstclear(&lines_list, NULL); // Передаем NULL в качестве del функции

	if (convert_status < 0)
		exit_error(game, "Map is empty or memory allocation failed for grid.");
}

// В этом файле 4 функции:
// 1. trim_newline (static)
// 2. read_map_lines (static)
// 3. convert_list_to_grid (static)
// 4. read_map
// Соблюдаем ограничение в 5 функций.
