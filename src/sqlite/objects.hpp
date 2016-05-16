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
# include <cstdint>

# include "../../lib/sqlite/hdr/sqlite_modern_cpp.h"

# include "../abstract/objects.hpp"


# ifndef GNUDO_SQLITE_OBJECTS_HPP
# define GNUDO_SQLITE_OBJECTS_HPP


namespace gnudo
{
	namespace sqlite
	{
		class Task: public gnudo::abstract::Task
		{
			public:
				Task(const std::uint64_t id, ::sqlite::database &db);
				std::uint64_t getId() const;
				std::string getTitle() const;
				void setTitle(const std::string title);
				std::string getDescription() const;
				void setDescription(const std::string desc);
				std::time_t getCreationTime() const;
				std::time_t getModificationTime() const;
				bool isCompleted() const;
				void setStatus(const bool isCompleted);

			protected:
				void setModificationTime(const std::time_t time);
				
			private:
				const std::uint64_t __id;
				::sqlite::database &__sqlitedb;
			
		};
	}
}

# endif // ifndef GNUDO_SQLITE_OBJECTS_HPP
