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

# include <string>
# include <stdexcept>

# include <sqlite3pp.hpp>

# include "dbdefs.hpp"
# include "gnudo.hpp"


using namespace sqlite3pp::functions;
using namespace gnudo::sqlite;
using std::string;



Db::Db(const string filename)
{
	sqlite3pp_open(filename.c_str(), &__sqlitedb);

	__createTables();
	__tasksManager = new TasksManager(__sqlitedb);
}


Db::~Db()
{
	sqlite3pp_close(__sqlitedb);
	delete __tasksManager;
}


TasksManager *
Db::getTasks()
{
	return __tasksManager;
}


void
Db::__createTables()
{	
	char *err	=	 NULL;
	string sql	=	"BEGIN TRANSACTION;"
					
					"CREATE TABLE  IF NOT EXISTS " GNUDO_SQLITE_TASKS_TABLE
					"(															"
					"	id INTEGER PRIMARY KEY,									"
					"	title TEXT NOT NULL,									"
					"	description TEXT,										"
					"	ctime INTEGER NOT NULL,									"
					"	mtime INTEGER NOT NULL,									"
					"	completed INTEGER NOT NULL								"
					");"

					"END TRANSACTION;";

	sqlite3pp_exec(__sqlitedb, sql.c_str(), NULL, NULL, &err);	
	
	if (err != NULL)
		throw std::runtime_error(err);
}




