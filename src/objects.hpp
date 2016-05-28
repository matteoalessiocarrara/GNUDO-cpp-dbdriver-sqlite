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

# include "../lib/sqlite3pp/src/sqlite3pp.hpp"

# include "abstract/objects.hpp"


namespace gnudo
{
	namespace sqlite
	{
		using std::int64_t;
		using std::string;
		using std::time_t;


		class Task: public gnudo::abstract::Task
		{
			public:
								Task(const sqlite3_int64 id, sqlite3* db);

				sqlite3_int64	getId() const;
				string			getTitle() const;
				string			getDescription() const;
				time_t 			getCreationTime() const;
				time_t 			getModificationTime() const;
				bool 			isCompleted() const;

				void 			setTitle(const string title);
				void 			setDescription(const string description);
				void 			setStatus(const bool isCompleted);

			protected:
				template <typename R>
				R 				_getColumn(const string columnName, R (*sqlite3ppfunc) (sqlite3_stmt* ppStmt, int iCol, sqlite3* db)) const;				
				sqlite3_stmt*	_getSelectStatement(const string columnName) const;
				sqlite3_stmt*	_getUpdateStatement(const string columnName);

				void 			_setModificationTime(const time_t time);

			private:
				const sqlite3_int64	__id;
				sqlite3 			*__sqlitedb;
		};
	}
}

# endif // ifndef GNUDO_SQLITE_OBJECTS_HPP
