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

# include "dbdefs.hpp"
# include "gnudo.hpp"
# include "managers.cpp"


using namespace gnudo::sqlite;


Db::Db(const std::string filename):  __sqlitedb(filename), __tasksManager(__sqlitedb)
{
}


const TasksManager &
Db::getTasks()
{
	return __tasksManager;
}


void
Db::__initTables()
{
	 __sqlitedb <<	"BEGIN TRANSACTION;";

	 __sqlitedb << 	"CREATE TABLE  IF NOT EXISTS " GNUDO_SQLITE_TASKS_TABLE 
					"("
					"	id PRIMARY KEY NOT NULL,"
					"	title TEXT NOT NULL,"
					"	description TEXT,"
					"	ctime INTEGER NOT NULL,"
					"	mtime INTEGER NOT NULL,"
					"	completed INTEGER NOT NULL"
					");";

	__sqlitedb << 	"END TRANSACTION;";
}
