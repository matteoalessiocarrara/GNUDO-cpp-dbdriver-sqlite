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
		using std::int64_t;
		
		class Db;


		// TODO Non tutti i metodi di sqlite3pp::objects::Table dovrebbero essere visibili in queste classi...

		
		class TasksManager: public sqlite3pp::objects::Table, public gnudo::abstract::TasksManager
		{
			public:
								TasksManager(sqlite3 *db, Db *gnudoDb);
				int64_t			add(const int priorityId, const string title="Untitled", const string description="", const time_t creationTime=time(NULL),
									const time_t modificationTime=time(NULL), const bool completed=false);
				vector<int64_t>	getIdList(int orderBy=Order::PRIORITY, bool ascending=false) const;
				Task*			getTask(const int64_t id) const;
				void			remove(const int64_t id);
		};
		
		
		class PriorityLevelsManager: public sqlite3pp::objects::Table, public gnudo::abstract::PriorityLevelsManager
		{
			public:
									PriorityLevelsManager(sqlite3 *db, Db *gnudoDb);

				// TODO cambiare priority in unsigned
				int64_t	 		add(const string name, const int priority, const string color="#00ff00"); // TODO Possono esistere due con la stessa priorità?
				vector<int64_t> getIdList(int orderBy=Order::PRIORITY, bool ascending=false) const;
				PriorityLevel*	getPriorityLevel(const int64_t id) const;
				void			remove(const int64_t id); // WARNING Non deve essere chiamato questo direttamente, ma il metodo ereditato da gnudo::abstract::PriorityLevelsManager
				void			remove(const int64_t id, int64_t moveToPriority);
			
		};
	}
}


# endif // ifndef GNUDO_SQLITE_MANAGERS_HPP
