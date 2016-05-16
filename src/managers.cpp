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

# include <ctime>
# include <iostream>

# include "dbdefs.hpp"
# include "managers.hpp"
# include "objects.cpp"


using namespace gnudo::sqlite;


TasksManager::TasksManager(::sqlite::database &db): __sqlitedb(db)
{
}


Task &
TasksManager::add(const std::string title, std::string desc)
{
	__sqlitedb	<< "INSERT INTO " << GNUDO_SQLITE_TASKS_TABLE << " (title, description, ctime, mtime, completed) VALUES "
				<< title
				<< desc
				<< std::time(NULL)
				<< std::time(NULL)
				<< false;
	
				// FIXME Restituire oggetto Task
}


void
TasksManager::remove(const gnudo::abstract::Task& task)
{
	__sqlitedb << "DELETE FROM " << GNUDO_SQLITE_TASKS_TABLE << " WHERE id = " << ((gnudo::sqlite::Task&)task).getId() << ";";
}


std::vector<gnudo::abstract::Task*>
TasksManager::getList() const
{
	__sqlitedb << "SELECT * FROM " << GNUDO_SQLITE_TASKS_TABLE;
	// FIXME Restituire oggetti
}

