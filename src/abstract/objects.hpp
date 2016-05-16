/*
 * Copyright 2016 Matteo Alessio Carrara <sw.matteoac@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

// Oggetti di base

# include <string>
# include <ctime>


# ifndef GNUDO_ABSTRACT_OBJECTS_HPP
# define GNUDO_ABSTRACT_OBJECTS_HPP

namespace gnudo
{
	namespace abstract
	{
		class Task
		{
			public:
				virtual std::string getTitle() const = 0;
				virtual void setTitle(const std::string title) = 0;
				virtual std::string getDescription() const = 0;
				virtual void setDescription(const std::string desc) = 0;
				virtual std::time_t getCreationTime() const = 0;
				virtual std::time_t getModificationTime() const = 0;
				virtual bool isCompleted() const = 0;
				virtual void setStatus(const bool isCompleted) = 0;
		};
	}
}

# endif // ifndef GNUDO_ABSTRACT_OBJECTS_HPP
