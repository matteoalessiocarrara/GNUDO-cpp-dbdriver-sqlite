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

// Header principale

// TODO Leggere convenzioni SQL
// TODO Leggere doc sqlite
// TODO Serve libreria per logging


# include <string>

# include "../../lib/sqlite/hdr/sqlite_modern_cpp.h"

# include "../abstract/gnudo.hpp"
# include "managers.hpp"


# ifndef GNUDO_SQLITE_GNUDO_HPP
# define GNUDO_SQLITE_GNUDO_HPP


namespace gnudo
{
	namespace sqlite
	{
		class Db: public gnudo::abstract::Db
		{
			public:
				Db(const std::string filename);
				const TasksManager &getTasks();

			private:
				::sqlite::database __sqlitedb;
				::gnudo::sqlite::TasksManager __tasksManager;

				void __initTables();
		};
	}
}


# endif // ifndef GNUDO_SQLITE_GNUDO_HPP
