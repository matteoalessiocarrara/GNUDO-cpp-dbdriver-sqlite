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

// TODO Serve libreria per logging (?)
// TODO Liberare memoria puntatori
// TODO Rimuovere include/using inutili
// TODO Riutilizzare sqlite3_stmt


# ifndef GNUDO_SQLITE_GNUDO_HPP
# define GNUDO_SQLITE_GNUDO_HPP


# include <string>

# include <sqlite3pp.hpp>
# include <gnudo-cpp-dbdriver-abstract/gnudo.hpp>

# include "managers.hpp"


namespace gnudo
{
	namespace sqlite
	{
		using std::string;


		class Db: public gnudo::abstract::Db
		{
			public:
				Db(const string filename);
				~Db();
				managers::TasksManager				*getTasks();
				managers::PriorityLevelsManager 	*getPriorityLevels();

			private:
				void 								__createTables();

				sqlite3								*__sqlitedb;
				managers::TasksManager				*__tasksManager;
				managers::PriorityLevelsManager		*__priorityLevels;
		};


	}
}


# endif // ifndef GNUDO_SQLITE_GNUDO_HPP
