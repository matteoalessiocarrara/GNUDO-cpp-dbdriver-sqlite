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

# ifndef GNUDO_SQLITE_OBJECTS_HPP
# define GNUDO_SQLITE_OBJECTS_HPP


# include <cstdint>
# include <string>
# include <ctime>

# include <sqlite3pp.hpp>
# include <gnudo-cpp-dbdriver-abstract/objects.hpp>


namespace gnudo
{
	namespace sqlite
	{
		using std::int64_t;
		using std::string;
		using std::time_t;


		namespace managers
		{
			class TasksManager;
			class PriorityLevelsManager;
		}


		namespace objects
		{
			using namespace managers;


			class PriorityLevel: public sqlite3pp::objects::Row, public gnudo::abstract::objects::PriorityLevel
			{
				public:
					PriorityLevel(sqlite3 *db, const int64_t id, PriorityLevelsManager *parentManager);

					string		getName() const;
					int64_t		getLevel() const;
					string 		getColor() const;

					void		setName(const string name);
					void		setColor(const string color);
			};


			class Task: public sqlite3pp::objects::Row, public gnudo::abstract::objects::Task
			{
				public:
					Task(const int64_t id, sqlite3 *db, TasksManager *parentManager);

					string			getTitle() const;
					string			getDescription() const;
					PriorityLevel	*getPriorityLevel() const;
					time_t 			getCreationTime() const;
					time_t 			getModificationTime() const;
					bool 			isCompleted() const;

					void 			setTitle(const string title);
					void 			setDescription(const string description);
					void			setPriorityLevel(const int64_t priority);
					void			setCreationTime(const time_t time);
					void 			setModificationTime(const time_t time);
					void 			setStatus(const bool isCompleted);
			};
		}
	}
}

# endif // ifndef GNUDO_SQLITE_OBJECTS_HPP
