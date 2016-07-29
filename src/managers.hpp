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

// Oggetti che gestiscono una lista di oggetti (in objects.hpp)

# ifndef GNUDO_SQLITE_MANAGERS_HPP
# define GNUDO_SQLITE_MANAGERS_HPP

# include <stdexcept>
# include <cstdint>
# include <vector>
# include <string>
# include <ctime>


# include <sqlite3pp.hpp>
# include <gnudo-cpp-dbdriver-abstract/managers.hpp>

# include "objects.hpp"


namespace gnudo
{
	namespace sqlite
	{
		class Db;


		namespace exceptions
		{
			class TaskNotFoundException: public std::runtime_error
			{
				public:
					TaskNotFoundException(const std::string &msg): std::runtime_error(msg) {}
			};
		}


		namespace managers
		{
			using std::int64_t;
			using std::vector;
			using std::string;
			using std::time_t;
			using std::time;

			using namespace objects;


			class TasksManager: public sqlite3pp::objects::Table, public gnudo::abstract::managers::TasksManager
			{
				public:
					TasksManager(sqlite3 *db, Db *gnudoDb);

					vector<int64_t>		getIdList(int orderBy, bool ascending) const;
					Task				*getObject(const int64_t id) const;
					void				remove(const int64_t id);

				protected:
					int64_t				_add(const int64_t priority, const string title, const string description, const time_t creationTime,
					                         const time_t modificationTime, const bool completed);

			};


			class PriorityLevelsManager: public sqlite3pp::objects::Table, public gnudo::abstract::managers::PriorityLevelsManager
			{
				public:
					PriorityLevelsManager(sqlite3 *db, Db *gnudoDb);

					vector<int64_t> 	getIdList(int orderBy, bool ascending) const;
					PriorityLevel		*getObject(const int64_t id) const;

				protected:
					int64_t	 			_add(const string name, const int64_t priority, const string color);
					void				_remove(const int64_t id);
			};
		}
	}
}


# endif // ifndef GNUDO_SQLITE_MANAGERS_HPP
