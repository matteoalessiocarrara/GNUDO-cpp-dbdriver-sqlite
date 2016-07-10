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
		using std::vector;
		using std::string;
        using std::time_t;
        using std::time;


		class TasksManager: public gnudo::abstract::TasksManager
		{
			public:
												TasksManager(sqlite3 *db);

                sqlite3_int64 					add(const string title="Untitled", const string description="", const time_t creationTime=time(NULL),
                                                    const time_t modificationTime=time(NULL), const bool completed=false);
				void 							remove(const gnudo::abstract::Task* task);
				Task*							getTask(const sqlite3_int64 id);
				vector<sqlite3_int64>			getIdList() const;

			private:
				sqlite3							*__sqlitedb;
		};
	}
}


# endif // ifndef GNUDO_SQLITE_MANAGERS_HPP
